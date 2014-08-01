#! /usr/local/bin/python

# Make sure to have FY_DEVROOT set properly before running this script
#
#
# Get help via
#
#  python runjstests.py --help
#
#  On my system, for example, use via python runjstests.py --port=COM3
import os
import re
import sys
import time

from optparse import OptionParser, TitledHelpFormatter

import serial
import threading


rootdir = os.path.join(os.environ['FY_DEVROOT'], '3rdParty/WebKit/JavaScriptCore/tests/mozilla')
buildtype = 'debug'
timedelay = 20.0


osChoices = ( 'WII', 'WIN' )
buildChoices = ( 'debug', 'debug_o', 'debug_o2', 'release', 'final' )

usage = 'usage: %prog [-b (' + '|'.join(buildChoices) + ')] [-c category[,category2...]] [-m regex] [-r rootdir] [-t delayseconds] [-v (' + '|'.join(osChoices) + ')]'

parser = OptionParser(usage)

parser.add_option( '-b'
                  ,'--buildtype'
                  ,choices=buildChoices
                  ,dest='buildtype'
                  ,default=buildtype
                  ,help='The build type of the target executable. Used to find the path to the executable. (Alternatively, this could be changed to use the path as an input option if it more useful.) The default is: '+buildtype )
parser.add_option( '-c'
                  ,'--categorylist'
                  ,type='string'
                  ,dest='catstring'
                  ,default=''
                  ,help='A comma separated list of test categories to run. The default is an empty list, which will run all test categories.' )
parser.add_option( '-m'
                  ,'--matchexpr'
                  ,type='string'
                  ,dest='matchexpr'
                  ,default='.*'
                  ,help='A regular expression used to match what test filenames are run.  The default is .*' )
parser.add_option( '-r'
                  ,'--rootdir'
                  ,type='string'
                  ,dest='rootdir'
                  ,default=rootdir
                  ,help='The rot directory where the testsuites are defined. The default is defined based on the FY_DEVROOT environment variable. Currently: '+rootdir )
parser.add_option( '-t'
                  ,'--timedelay'
                  ,type='float'
                  ,dest='timedelay'
                  ,default=timedelay
                  ,help='Time delay in seconds when execution pauses to give the test time to complete before restarting the devkit. Only used if the OS version is WII. Default is: ' + str(timedelay) )
parser.add_option( '-v'
                  ,'--osversion'
                  ,choices=osChoices
                  ,dest='osversion'
                  ,default='WII'
                  ,help='Select which OS to run the tests on. The default is WII' )
parser.add_option( '-p'
                  ,'--port'
                  ,type='string'
                  ,dest='serialPortName'
                  ,default='COM1'
                  ,help='Select PC serial port to use' )
parser.add_option( '-a'
                  ,'--all'
                  ,action='store_true'
                  ,dest='bAllMsg'
                  ,default=False
                  ,help='See all console messages' )

parser.formatter = TitledHelpFormatter()

(options, args) = parser.parse_args()

osversion = options.osversion
rootdir = options.rootdir
buildtype = options.buildtype
matchexpr = options.matchexpr
catstring = options.catstring
serialPortName = options.serialPortName
bAllMsg = options.bAllMsg

catlist = set( catstring.split(',') )
categorylist = set([])

# Make all the categories lowercase so they are easy to compare
for category in catlist:
    if category!='':
        categorylist = categorylist | set( [category.lower()] )

# Compile the regular expression
    filePattern = re.compile(matchexpr)

print "Using matchexpr: " + matchexpr

print len(categorylist)

if not os.path.isdir(rootdir):
    print "Could not find JavaScriptCore unit tests.  If you are not defining this explicitly, please make sure that the FY_DEVROOT enviornment variable is set correctly!"
    sys.exit(50)

os.chdir( rootdir )

if osversion=='WII':
    jscpath = 'nfp/test/WebKit/javascriptcore/out/wii/' + buildtype + '/mt/jscTest'
    if buildtype=='debug':
        jscpath = jscpath + 'D'
    jscpath = jscpath + '.elf'
    elffilepath = os.path.join(os.environ['FY_DEVROOT'], jscpath)

    if not os.path.exists(elffilepath):
        print "Could not find elf file.  Exepected to be at: " + elffilepath
        print "Perhaps it needs to be built?"
        sys.exit(50)

else:
    jscpath = 'bin/jsc_debug.exe';
    exefilepath = os.path.join(os.environ['WebKitOutputDir'], jscpath)

    if not os.path.exists(exefilepath):
        print "Could not find exe file.  Expected to be at: " + exefilepath
        print "Please make sure the WebKitOutputDir environment variable is set correctly!"
        sys.exit(50)


os.system( 'setndenv "DvdRoot" ' + rootdir )

class Terminal(threading.Thread):
    def __init__(self, portName, bAllMsg):
        threading.Thread.__init__(self)
        self.alive = False
        self.ser = None
        self.portName = portName
        self.error = 0
        self.bAllMsg = bAllMsg
        self.bDoOutput = False

    def run(self):
        self.ser = serial.Serial(port=self.portName, baudrate=115200, timeout=1)
        self.alive = True
        bPrintPrefix = True
        textLine = ""
        while self.alive:
            msg = self.ser.readline()
            # CR/LR translation
            for c in msg:
                if bPrintPrefix and self.bAllMsg:
                    sys.stdout.write("[WII]")
                    bPrintPrefix = False
                if self.bAllMsg:
                    sys.stdout.write(c)
                textLine += c
                if ord(c) == 13:
                    bPrintPrefix = True
                    textLine += "\n"
                    if self.bAllMsg:
                        sys.stdout.write("\n")
                    else:
                        if "Begin test." in textLine:
                            self.bDoOutput = True

                        if self.bDoOutput:
                            sys.stdout.write("[WII]"+textLine)

                        if "End test." in textLine:
                            self.bDoOutput = False

                    # Some parser for Wii commands here (?)
                    # e.g. if wii outputs some special 'strings' we can call python stuff
                    #
                    # Proposal would be to print something like this on Wii:
                    # runjstests.result() and calling the method result(...) here

                    # SOME HACK FROM ACHIM
                    if "FAILED!" in textLine:
                        self.error = 101
                        self.alive = False
                        break

                    if "End test." in textLine:
                        self.alive = False
                        break
                    # Reset text line
                    textLine = ""


        self.ser.close()
        print "*** SERIAL THREAD END"



def ShouldRunTest(testfilepath):
    if not os.path.isfile(testfilepath):
        return False
    if os.path.splitext(testfile)[1]!='.js':
        return False
    if testfile=='shell.js':
        return False
    if testfile=='browser.js':
        return False

    return filePattern.match(testfilepath)


numtests = 0
for testsuite in os.listdir(rootdir):
    testsuitepath = os.path.join(rootdir, testsuite)
    if os.path.isdir(testsuitepath):
        # Is there a shell.js file in the directory?  If so, we have a valid testsuite
        if os.path.exists(os.path.join(testsuitepath, 'shell.js')):
            print "Running testsuite: " + testsuite
            for testcategory in os.listdir(testsuitepath):
                testcategorypath = os.path.join(testsuitepath, testcategory)
                if os.path.isdir(testcategorypath):
                    if (len(categorylist)==0) or (testcategory.lower() in categorylist):
                        print "    Category: " + testcategory
                        for testfile in os.listdir(testcategorypath):
                            testfilepath = os.path.join(testcategorypath, testfile)
                            if ShouldRunTest(testfilepath):

                                try:
                                    # Star the termnial thread
                                    if osversion=='WII':
                                        wiiTerminal = Terminal(serialPortName, bAllMsg)
                                        wiiTerminal.start()

                                    if osversion=='WII':
                                        command = 'ndevrun.exe -enfw ' + elffilepath + ' -a '
                                    else: # (osversion=='WIN')
                                        command = exefilepath + ' '
                                    command += 'begintest.js ' + testsuite + '/shell.js '
                                    if os.path.exists(os.path.join(testcategorypath, 'shell.js')):
                                        command += testsuite + '/' + testcategory + '/shell.js '
                                    command += testsuite + '/' + testcategory + '/' + testfile
                                    command += ' endtest.js'
                                    numtests = numtests + 1
                                    print '[', numtests, '] ', command

                                    os.system(command)

                                    # wait for the terminal thread to end or for timeout
                                    if osversion=='WII':
                                            # We wait for a max of this delay.
                                            # But perhaps the thread was terminted before(?)
                                            wiiTerminal.join(timedelay)

                                            # SOME HACK FROM ACHIM
                                            if wiiTerminal.error != 0:
                                                print "-------------------------------------------"
                                                print "TEST ERROR: %d" % (wiiTerminal.error)
                                                print "-------------------------------------------"
                                                # WE STOP IN THIS CASE
                                                sys.exit(wiiTerminal.error)

                                            # Check if timeout happend
                                            if wiiTerminal.isAlive():
                                                # Signal the terminal thread to stop
                                                wiiTerminal.alive = False
                                                # Really wait for the loop to exit
                                                wiiTerminal.join()
                                                # If this triggers something is wrong
                                                assert not wiiTerminal.isAlive()

                                                # SOME HACK FROM ACHIM
                                                # WE STOP IN THIS CASE, BECAUSE NO CLEAN WII EXIT
                                                sys.exit(100)

                                            wiiTerminal = None

                                # Try to exit gracefully...
                                except KeyboardInterrupt:
                                    wiiTerminal.alive = False
                                    wiiTerminal.join()
                                    sys.exit(50)

# Regular exit here
print("Done. Performed %d tests." % (numtests))
sys.exit(0)
