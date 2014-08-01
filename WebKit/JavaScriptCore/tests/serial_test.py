import socket
import sys
import serial
import threading

class Terminal(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self) 
        self.alive = False 
        self.ser = None
 
    def run(self): 
        self.ser = serial.Serial(port='COM3', baudrate=115200, timeout=1)
        self.alive = True
        while self.alive:
            msg = self.ser.readline()
            # CR/LR translation
            for c in msg:
                sys.stdout.write(c)
                if ord(c) == 13:
                    sys.stdout.write("\n")

                    
                    
wiiTerminal = Terminal()
wiiTerminal.start()
#wiiTerminal.join()


            
            

