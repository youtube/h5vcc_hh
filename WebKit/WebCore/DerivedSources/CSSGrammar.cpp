
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         cssyyparse
#define yylex           cssyylex
#define yyerror         cssyyerror
#define yylval          cssyylval
#define yychar          cssyychar
#define yydebug         cssyydebug
#define yynerrs         cssyynerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "WebCore/css/CSSGrammar.y"


/*
 *  Copyright (C) 2002-2003 Lars Knoll (knoll@kde.org)
 *  Copyright (C) 2004, 2005, 2006, 2007, 2008 Apple Inc. All rights reserved.
 *  Copyright (C) 2006 Alexey Proskuryakov (ap@nypop.com)
 *  Copyright (C) 2008 Eric Seidel <eric@webkit.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "config.h"

#include "CSSMediaRule.h"
#include "CSSParser.h"
#include "CSSPrimitiveValue.h"
#include "CSSPropertyNames.h"
#include "CSSRuleList.h"
#include "CSSSelector.h"
#include "CSSStyleSheet.h"
#include "Document.h"
#include "HTMLNames.h"
#include "MediaList.h"
#include "WebKitCSSKeyframeRule.h"
#include "WebKitCSSKeyframesRule.h"
#include <wtf/FastMalloc.h>
#include <stdlib.h>
#include <string.h>

using namespace WebCore;
using namespace HTMLNames;

#define YYMALLOC fastMalloc
#define YYFREE fastFree

#define YYENABLE_NLS 0
#define YYLTYPE_IS_TRIVIAL 1
#define YYMAXDEPTH 10000
#define YYDEBUG 0

// FIXME: Replace with %parse-param { CSSParser* parser } once we can depend on bison 2.x
#define YYPARSE_PARAM parser
#define YYLEX_PARAM parser



/* Line 189 of yacc.c  */
#line 141 "WebCore/DerivedSources/CSSGrammar.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EOF = 0,
     LOWEST_PREC = 258,
     UNIMPORTANT_TOK = 259,
     WHITESPACE = 260,
     SGML_CD = 261,
     INCLUDES = 262,
     DASHMATCH = 263,
     BEGINSWITH = 264,
     ENDSWITH = 265,
     CONTAINS = 266,
     STRING = 267,
     IDENT = 268,
     NTH = 269,
     HEX = 270,
     IDSEL = 271,
     IMPORT_SYM = 272,
     PAGE_SYM = 273,
     MEDIA_SYM = 274,
     FONT_FACE_SYM = 275,
     CHARSET_SYM = 276,
     NAMESPACE_SYM = 277,
     WEBKIT_RULE_SYM = 278,
     WEBKIT_DECLS_SYM = 279,
     WEBKIT_KEYFRAME_RULE_SYM = 280,
     WEBKIT_KEYFRAMES_SYM = 281,
     WEBKIT_VALUE_SYM = 282,
     WEBKIT_MEDIAQUERY_SYM = 283,
     WEBKIT_SELECTOR_SYM = 284,
     WEBKIT_VARIABLES_SYM = 285,
     WEBKIT_DEFINE_SYM = 286,
     VARIABLES_FOR = 287,
     WEBKIT_VARIABLES_DECLS_SYM = 288,
     TOPLEFTCORNER_SYM = 289,
     TOPLEFT_SYM = 290,
     TOPCENTER_SYM = 291,
     TOPRIGHT_SYM = 292,
     TOPRIGHTCORNER_SYM = 293,
     BOTTOMLEFTCORNER_SYM = 294,
     BOTTOMLEFT_SYM = 295,
     BOTTOMCENTER_SYM = 296,
     BOTTOMRIGHT_SYM = 297,
     BOTTOMRIGHTCORNER_SYM = 298,
     LEFTTOP_SYM = 299,
     LEFTMIDDLE_SYM = 300,
     LEFTBOTTOM_SYM = 301,
     RIGHTTOP_SYM = 302,
     RIGHTMIDDLE_SYM = 303,
     RIGHTBOTTOM_SYM = 304,
     ATKEYWORD = 305,
     IMPORTANT_SYM = 306,
     MEDIA_ONLY = 307,
     MEDIA_NOT = 308,
     MEDIA_AND = 309,
     REMS = 310,
     QEMS = 311,
     EMS = 312,
     EXS = 313,
     PXS = 314,
     CMS = 315,
     MMS = 316,
     INS = 317,
     PTS = 318,
     PCS = 319,
     DEGS = 320,
     RADS = 321,
     GRADS = 322,
     TURNS = 323,
     MSECS = 324,
     SECS = 325,
     HERZ = 326,
     KHERZ = 327,
     DIMEN = 328,
     PERCENTAGE = 329,
     FLOATTOKEN = 330,
     INTEGER = 331,
     URI = 332,
     FUNCTION = 333,
     NOTFUNCTION = 334,
     UNICODERANGE = 335,
     VARCALL = 336
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 62 "WebCore/css/CSSGrammar.y"

    bool boolean;
    char character;
    int integer;
    double number;
    CSSParserString string;

    CSSRule* rule;
    CSSRuleList* ruleList;
    CSSSelector* selector;
    Vector<CSSSelector*>* selectorList;
    CSSSelector::MarginBoxType marginBox;
    CSSSelector::Relation relation;
    MediaList* mediaList;
    MediaQuery* mediaQuery;
    MediaQuery::Restrictor mediaQueryRestrictor;
    MediaQueryExp* mediaQueryExp;
    CSSParserValue value;
    CSSParserValueList* valueList;
    Vector<MediaQueryExp*>* mediaQueryExpList;
    WebKitCSSKeyframeRule* keyframeRule;
    WebKitCSSKeyframesRule* keyframesRule;
    float val;



/* Line 214 of yacc.c  */
#line 286 "WebCore/DerivedSources/CSSGrammar.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 87 "WebCore/css/CSSGrammar.y"


static inline int cssyyerror(const char*)
{
    return 1;
}

static int cssyylex(YYSTYPE* yylval, void* parser)
{
    return static_cast<CSSParser*>(parser)->lex(yylval);
}



/* Line 264 of yacc.c  */
#line 313 "WebCore/DerivedSources/CSSGrammar.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1670

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  291
/* YYNRULES -- Number of states.  */
#define YYNSTATES  551

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   336

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   100,     2,   101,     2,     2,
      90,    91,    20,    93,    92,    96,    18,    99,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    17,    89,
       2,    98,    95,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    19,     2,    97,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,    21,    88,    94,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    11,    14,    17,    20,    23,    26,
      29,    36,    43,    49,    55,    61,    67,    73,    74,    77,
      78,    81,    84,    85,    87,    89,    91,    97,   101,   105,
     106,   110,   112,   114,   116,   118,   120,   122,   124,   126,
     128,   130,   132,   133,   137,   139,   141,   143,   145,   147,
     149,   151,   153,   155,   157,   159,   166,   173,   177,   181,
     189,   197,   198,   202,   204,   207,   209,   213,   215,   218,
     222,   227,   231,   237,   242,   247,   254,   259,   267,   270,
     276,   280,   285,   288,   295,   302,   306,   310,   311,   314,
     316,   318,   321,   322,   327,   335,   337,   343,   344,   348,
     349,   351,   353,   355,   360,   361,   363,   365,   370,   373,
     381,   388,   391,   400,   402,   404,   405,   409,   416,   418,
     424,   426,   428,   437,   441,   445,   447,   450,   452,   453,
     455,   460,   461,   469,   471,   473,   475,   477,   479,   481,
     483,   485,   487,   489,   491,   493,   495,   497,   499,   501,
     509,   513,   517,   520,   523,   526,   528,   529,   531,   533,
     539,   541,   546,   549,   552,   554,   556,   559,   563,   566,
     568,   571,   574,   576,   579,   581,   584,   588,   591,   593,
     595,   597,   600,   603,   605,   607,   609,   611,   613,   616,
     619,   624,   633,   639,   649,   651,   653,   655,   657,   659,
     661,   663,   665,   668,   671,   675,   682,   690,   697,   704,
     706,   709,   711,   715,   717,   720,   723,   727,   731,   736,
     740,   746,   751,   756,   763,   769,   772,   775,   782,   789,
     792,   796,   801,   804,   807,   810,   811,   813,   817,   820,
     824,   827,   830,   833,   834,   836,   839,   842,   845,   848,
     852,   855,   858,   860,   863,   865,   868,   871,   874,   877,
     880,   883,   886,   889,   892,   895,   898,   901,   904,   907,
     910,   913,   916,   919,   922,   925,   928,   931,   934,   936,
     942,   946,   949,   952,   954,   957,   961,   965,   968,   974,
     978,   980
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     103,     0,    -1,   111,   113,   112,   116,    -1,   104,   111,
      -1,   106,   111,    -1,   108,   111,    -1,   109,   111,    -1,
     110,   111,    -1,   107,   111,    -1,   105,   111,    -1,    28,
      87,   111,   117,   111,    88,    -1,    30,    87,   111,   146,
     111,    88,    -1,    29,    87,   111,   175,    88,    -1,    38,
      87,   111,   125,    88,    -1,    32,    87,   111,   180,    88,
      -1,    33,     5,   111,   138,    88,    -1,    34,    87,   111,
     160,    88,    -1,    -1,   111,     5,    -1,    -1,   112,     6,
      -1,   112,     5,    -1,    -1,   115,    -1,    88,    -1,     0,
      -1,    26,   111,    12,   111,    89,    -1,    26,     1,   190,
      -1,    26,     1,    89,    -1,    -1,   116,   118,   112,    -1,
     159,    -1,   141,    -1,   149,    -1,   155,    -1,   143,    -1,
     129,    -1,   122,    -1,   123,    -1,   117,    -1,   189,    -1,
     188,    -1,    -1,   119,   121,   112,    -1,   159,    -1,   149,
      -1,   155,    -1,   143,    -1,   120,    -1,   189,    -1,   188,
      -1,   129,    -1,   122,    -1,   123,    -1,   141,    -1,    22,
     111,   131,   111,   139,    89,    -1,    22,   111,   131,   111,
     139,   190,    -1,    22,     1,    89,    -1,    22,     1,   190,
      -1,    35,   111,   139,    87,   111,   125,    88,    -1,    36,
     111,   124,    87,   111,   125,    88,    -1,    -1,    37,     5,
     140,    -1,   127,    -1,   126,   127,    -1,   126,    -1,     1,
     191,     1,    -1,     1,    -1,   126,     1,    -1,   127,    89,
     111,    -1,   127,   191,    89,   111,    -1,     1,    89,   111,
      -1,     1,   191,     1,    89,   111,    -1,   126,   127,    89,
     111,    -1,   126,     1,    89,   111,    -1,   126,     1,   191,
       1,    89,   111,    -1,   128,    17,   111,   180,    -1,   128,
     111,    87,   111,   175,    88,   111,    -1,   128,     1,    -1,
     128,    17,   111,     1,   180,    -1,   128,    17,   111,    -1,
     128,    17,   111,     1,    -1,    13,   111,    -1,    27,   111,
     130,   131,   111,    89,    -1,    27,   111,   130,   131,   111,
     190,    -1,    27,     1,   190,    -1,    27,     1,    89,    -1,
      -1,    13,   111,    -1,    12,    -1,    82,    -1,    13,   111,
      -1,    -1,    17,   111,   180,   111,    -1,    90,   111,   132,
     111,   133,    91,   111,    -1,   134,    -1,   135,   111,    59,
     111,   134,    -1,    -1,    59,   111,   135,    -1,    -1,    57,
      -1,    58,    -1,   135,    -1,   137,   111,   142,   136,    -1,
      -1,   140,    -1,   138,    -1,   140,    92,   111,   138,    -1,
     140,     1,    -1,    24,   111,   140,    87,   111,   119,   187,
      -1,    24,   111,    87,   111,   119,   187,    -1,    13,   111,
      -1,    31,   111,   144,   111,    87,   111,   145,    88,    -1,
      13,    -1,    12,    -1,    -1,   145,   146,   111,    -1,   147,
     111,    87,   111,   175,    88,    -1,   148,    -1,   147,   111,
      92,   111,   148,    -1,    79,    -1,    13,    -1,    23,   111,
     150,   111,    87,   111,   151,   114,    -1,    23,     1,   190,
      -1,    23,     1,    89,    -1,    13,    -1,    13,   173,    -1,
     173,    -1,    -1,   175,    -1,   151,   152,   111,   175,    -1,
      -1,   154,   153,   111,    87,   111,   175,   114,    -1,    39,
      -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,    44,
      -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    25,   111,    87,   111,   175,    88,   111,    -1,    25,
       1,   190,    -1,    25,     1,    89,    -1,    93,   111,    -1,
      94,   111,    -1,    95,   111,    -1,   158,    -1,    -1,    96,
      -1,    93,    -1,   160,    87,   111,   175,   114,    -1,   162,
      -1,   160,    92,   111,   162,    -1,   160,     1,    -1,   162,
       5,    -1,   164,    -1,   161,    -1,   161,   164,    -1,   162,
     156,   164,    -1,   162,     1,    -1,    21,    -1,    20,    21,
      -1,    13,    21,    -1,   165,    -1,   165,   166,    -1,   166,
      -1,   163,   165,    -1,   163,   165,   166,    -1,   163,   166,
      -1,    13,    -1,    20,    -1,   167,    -1,   166,   167,    -1,
     166,     1,    -1,    16,    -1,    15,    -1,   168,    -1,   170,
      -1,   174,    -1,    18,    13,    -1,    13,   111,    -1,    19,
     111,   169,    97,    -1,    19,   111,   169,   171,   111,   172,
     111,    97,    -1,    19,   111,   163,   169,    97,    -1,    19,
     111,   163,   169,   171,   111,   172,   111,    97,    -1,    98,
      -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,    11,
      -1,    13,    -1,    12,    -1,    17,    13,    -1,    17,    13,
      -1,    17,    17,    13,    -1,    17,    83,   111,    14,   111,
      91,    -1,    17,    83,   111,   157,    81,   111,    91,    -1,
      17,    83,   111,    13,   111,    91,    -1,    17,    84,   111,
     164,   111,    91,    -1,   177,    -1,   176,   177,    -1,   176,
      -1,     1,   191,     1,    -1,     1,    -1,   176,     1,    -1,
     176,   191,    -1,   177,    89,   111,    -1,   177,   191,   111,
      -1,   177,   191,    89,   111,    -1,     1,    89,   111,    -1,
       1,   191,     1,    89,   111,    -1,   176,   177,    89,   111,
      -1,   176,     1,    89,   111,    -1,   176,     1,   191,     1,
      89,   111,    -1,   178,    17,   111,   180,   179,    -1,   184,
     111,    -1,   178,     1,    -1,   178,    17,   111,     1,   180,
     179,    -1,   178,    17,   111,   180,   179,     1,    -1,    56,
     111,    -1,   178,    17,   111,    -1,   178,    17,   111,     1,
      -1,   178,   190,    -1,    13,   111,    -1,    56,   111,    -1,
      -1,   182,    -1,   180,   181,   182,    -1,   180,   191,    -1,
     180,   191,     1,    -1,   180,     1,    -1,    99,   111,    -1,
      92,   111,    -1,    -1,   183,    -1,   158,   183,    -1,    12,
     111,    -1,    13,   111,    -1,    78,   111,    -1,   158,    78,
     111,    -1,    82,   111,    -1,    85,   111,    -1,   186,    -1,
     100,   111,    -1,   185,    -1,   184,   111,    -1,   101,   111,
      -1,    81,   111,    -1,    80,   111,    -1,    79,   111,    -1,
      64,   111,    -1,    65,   111,    -1,    66,   111,    -1,    67,
     111,    -1,    68,   111,    -1,    69,   111,    -1,    70,   111,
      -1,    71,   111,    -1,    72,   111,    -1,    73,   111,    -1,
      74,   111,    -1,    75,   111,    -1,    76,   111,    -1,    77,
     111,    -1,    62,   111,    -1,    61,   111,    -1,    63,   111,
      -1,    60,   111,    -1,    86,    -1,    83,   111,   180,    91,
     111,    -1,    83,   111,     1,    -1,    15,   111,    -1,    16,
     111,    -1,   114,    -1,     1,   114,    -1,    55,     1,   190,
      -1,    55,     1,    89,    -1,     1,   190,    -1,    87,     1,
     191,     1,   114,    -1,    87,     1,   114,    -1,   190,    -1,
     191,     1,   190,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   292,   292,   293,   294,   295,   296,   297,   298,   299,
     303,   309,   315,   321,   327,   341,   348,   358,   359,   362,
     364,   365,   368,   370,   375,   376,   380,   386,   388,   392,
     394,   402,   403,   404,   405,   406,   407,   408,   409,   413,
     416,   417,   421,   422,   433,   434,   435,   436,   440,   441,
     442,   443,   444,   445,   446,   451,   454,   457,   460,   466,
     470,   476,   480,   486,   489,   494,   497,   500,   503,   509,
     512,   515,   518,   521,   526,   529,   535,   539,   543,   547,
     551,   556,   563,   569,   573,   576,   579,   585,   586,   590,
     591,   595,   601,   604,   610,   617,   622,   629,   632,   638,
     641,   644,   650,   655,   663,   666,   670,   675,   680,   686,
     689,   695,   701,   708,   709,   713,   714,   722,   728,   733,
     742,   743,   756,   768,   771,   777,   783,   791,   796,   804,
     805,   809,   809,   817,   820,   823,   826,   829,   832,   835,
     838,   841,   844,   847,   850,   853,   856,   859,   862,   868,
     872,   875,   881,   882,   883,   887,   888,   892,   893,   897,
     904,   914,   923,   929,   935,   938,   942,   958,   978,   984,
     985,   986,   990,   995,  1002,  1008,  1018,  1030,  1043,  1051,
    1059,  1062,  1075,  1081,  1089,  1101,  1102,  1103,  1107,  1118,
    1129,  1134,  1140,  1148,  1160,  1163,  1166,  1169,  1172,  1175,
    1181,  1182,  1186,  1197,  1231,  1251,  1269,  1287,  1306,  1321,
    1324,  1329,  1332,  1335,  1338,  1341,  1347,  1350,  1353,  1356,
    1359,  1362,  1367,  1370,  1376,  1390,  1402,  1406,  1413,  1418,
    1423,  1428,  1433,  1440,  1446,  1447,  1451,  1456,  1470,  1473,
    1476,  1482,  1485,  1488,  1494,  1495,  1496,  1497,  1503,  1504,
    1505,  1506,  1507,  1508,  1510,  1513,  1516,  1522,  1523,  1524,
    1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,
    1535,  1536,  1537,  1538,  1539,  1540,  1541,  1542,  1553,  1561,
    1570,  1586,  1587,  1594,  1597,  1603,  1606,  1612,  1630,  1633,
    1639,  1640
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "TOKEN_EOF", "error", "$undefined", "LOWEST_PREC", "UNIMPORTANT_TOK",
  "WHITESPACE", "SGML_CD", "INCLUDES", "DASHMATCH", "BEGINSWITH",
  "ENDSWITH", "CONTAINS", "STRING", "IDENT", "NTH", "HEX", "IDSEL", "':'",
  "'.'", "'['", "'*'", "'|'", "IMPORT_SYM", "PAGE_SYM", "MEDIA_SYM",
  "FONT_FACE_SYM", "CHARSET_SYM", "NAMESPACE_SYM", "WEBKIT_RULE_SYM",
  "WEBKIT_DECLS_SYM", "WEBKIT_KEYFRAME_RULE_SYM", "WEBKIT_KEYFRAMES_SYM",
  "WEBKIT_VALUE_SYM", "WEBKIT_MEDIAQUERY_SYM", "WEBKIT_SELECTOR_SYM",
  "WEBKIT_VARIABLES_SYM", "WEBKIT_DEFINE_SYM", "VARIABLES_FOR",
  "WEBKIT_VARIABLES_DECLS_SYM", "TOPLEFTCORNER_SYM", "TOPLEFT_SYM",
  "TOPCENTER_SYM", "TOPRIGHT_SYM", "TOPRIGHTCORNER_SYM",
  "BOTTOMLEFTCORNER_SYM", "BOTTOMLEFT_SYM", "BOTTOMCENTER_SYM",
  "BOTTOMRIGHT_SYM", "BOTTOMRIGHTCORNER_SYM", "LEFTTOP_SYM",
  "LEFTMIDDLE_SYM", "LEFTBOTTOM_SYM", "RIGHTTOP_SYM", "RIGHTMIDDLE_SYM",
  "RIGHTBOTTOM_SYM", "ATKEYWORD", "IMPORTANT_SYM", "MEDIA_ONLY",
  "MEDIA_NOT", "MEDIA_AND", "REMS", "QEMS", "EMS", "EXS", "PXS", "CMS",
  "MMS", "INS", "PTS", "PCS", "DEGS", "RADS", "GRADS", "TURNS", "MSECS",
  "SECS", "HERZ", "KHERZ", "DIMEN", "PERCENTAGE", "FLOATTOKEN", "INTEGER",
  "URI", "FUNCTION", "NOTFUNCTION", "UNICODERANGE", "VARCALL", "'{'",
  "'}'", "';'", "'('", "')'", "','", "'+'", "'~'", "'>'", "'-'", "']'",
  "'='", "'/'", "'#'", "'%'", "$accept", "stylesheet", "webkit_rule",
  "webkit_keyframe_rule", "webkit_decls", "webkit_variables_decls",
  "webkit_value", "webkit_mediaquery", "webkit_selector", "maybe_space",
  "maybe_sgml", "maybe_charset", "closing_brace", "charset", "rule_list",
  "valid_rule", "rule", "block_rule_list", "block_valid_rule",
  "block_rule", "import", "variables_rule", "variables_media_list",
  "variables_declaration_list", "variables_decl_list",
  "variables_declaration", "variable_name", "namespace", "maybe_ns_prefix",
  "string_or_uri", "media_feature", "maybe_media_value", "media_query_exp",
  "media_query_exp_list", "maybe_and_media_query_exp_list",
  "maybe_media_restrictor", "media_query", "maybe_media_list",
  "media_list", "media", "medium", "keyframes", "keyframe_name",
  "keyframes_rule", "keyframe_rule", "key_list", "key", "page",
  "page_selector", "declarations_and_margins", "margin_box", "$@1",
  "margin_sym", "font_face", "combinator", "maybe_unary_operator",
  "unary_operator", "ruleset", "selector_list",
  "selector_with_trailing_whitespace", "selector", "namespace_selector",
  "simple_selector", "element_name", "specifier_list", "specifier",
  "class", "attr_name", "attrib", "match", "ident_or_string",
  "pseudo_page", "pseudo", "declaration_list", "decl_list", "declaration",
  "property", "prio", "expr", "operator", "term", "unary_term",
  "variable_reference", "function", "hexcolor", "save_block", "invalid_at",
  "invalid_rule", "invalid_block", "invalid_block_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,    58,    46,    91,
      42,   124,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   123,   125,    59,
      40,    41,    44,    43,   126,    62,    45,    93,    61,    47,
      35,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   111,   112,
     112,   112,   113,   113,   114,   114,   115,   115,   115,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   118,
     118,   118,   119,   119,   120,   120,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   122,   122,   122,   122,   123,
     123,   124,   124,   125,   125,   125,   125,   125,   125,   126,
     126,   126,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   128,   129,   129,   129,   129,   130,   130,   131,
     131,   132,   133,   133,   134,   135,   135,   136,   136,   137,
     137,   137,   138,   138,   139,   139,   140,   140,   140,   141,
     141,   142,   143,   144,   144,   145,   145,   146,   147,   147,
     148,   148,   149,   149,   149,   150,   150,   150,   150,   151,
     151,   153,   152,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   155,
     155,   155,   156,   156,   156,   157,   157,   158,   158,   159,
     160,   160,   160,   161,   162,   162,   162,   162,   162,   163,
     163,   163,   164,   164,   164,   164,   164,   164,   165,   165,
     166,   166,   166,   167,   167,   167,   167,   167,   168,   169,
     170,   170,   170,   170,   171,   171,   171,   171,   171,   171,
     172,   172,   173,   174,   174,   174,   174,   174,   174,   175,
     175,   175,   175,   175,   175,   175,   176,   176,   176,   176,
     176,   176,   176,   176,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   178,   179,   179,   180,   180,   180,   180,
     180,   181,   181,   181,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   184,   185,
     185,   186,   186,   187,   187,   188,   188,   189,   190,   190,
     191,   191
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     2,     2,     2,     2,     2,     2,     2,
       6,     6,     5,     5,     5,     5,     5,     0,     2,     0,
       2,     2,     0,     1,     1,     1,     5,     3,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     6,     3,     3,     7,
       7,     0,     3,     1,     2,     1,     3,     1,     2,     3,
       4,     3,     5,     4,     4,     6,     4,     7,     2,     5,
       3,     4,     2,     6,     6,     3,     3,     0,     2,     1,
       1,     2,     0,     4,     7,     1,     5,     0,     3,     0,
       1,     1,     1,     4,     0,     1,     1,     4,     2,     7,
       6,     2,     8,     1,     1,     0,     3,     6,     1,     5,
       1,     1,     8,     3,     3,     1,     2,     1,     0,     1,
       4,     0,     7,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     7,
       3,     3,     2,     2,     2,     1,     0,     1,     1,     5,
       1,     4,     2,     2,     1,     1,     2,     3,     2,     1,
       2,     2,     1,     2,     1,     2,     3,     2,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     2,     2,
       4,     8,     5,     9,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     6,     7,     6,     6,     1,
       2,     1,     3,     1,     2,     2,     3,     3,     4,     3,
       5,     4,     4,     6,     5,     2,     2,     6,     6,     2,
       3,     4,     2,     2,     2,     0,     1,     3,     2,     3,
       2,     2,     2,     0,     1,     2,     2,     2,     2,     3,
       2,     2,     1,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     5,
       3,     2,     2,     1,     2,     3,     3,     2,     5,     3,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      17,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      17,    17,    17,    17,    17,    17,    22,    17,    17,    17,
      17,    17,    17,    17,     1,     3,     9,     4,     8,     5,
       6,     7,    18,     0,    19,    23,     0,     0,     0,     0,
      99,     0,     0,     0,     0,    29,   178,   184,   183,     0,
       0,    17,   179,   169,     0,     0,    17,     0,     0,    17,
      17,    17,    17,    37,    38,    36,    32,    35,    33,    34,
      31,     0,   165,     0,     0,   164,   172,     0,   180,   185,
     186,   187,   213,    17,    17,   278,     0,     0,   209,     0,
      17,   121,   120,    17,    17,   118,    17,    17,    17,    17,
      17,    17,    17,    17,    17,    17,    17,    17,    17,    17,
      17,    17,    17,    17,    17,    17,    17,    17,    17,    17,
      17,    17,    17,    17,    17,   158,   157,    17,    17,     0,
       0,   236,   244,    17,   254,   252,   100,   101,    17,    95,
     102,    17,     0,     0,    67,    17,     0,     0,    63,     0,
       0,    28,    27,    17,    21,    20,     0,   171,   203,     0,
      17,    17,   188,     0,   170,     0,     0,     0,   128,    99,
       0,     0,     0,    87,     0,    99,    61,     0,   162,    17,
      17,   166,   168,   163,    17,    17,    17,     0,   178,   179,
     175,     0,     0,   182,   181,    17,   290,     0,   233,   229,
      12,   214,   210,     0,    17,     0,   226,    17,   232,   225,
       0,     0,   246,   247,   281,   282,   277,   275,   274,   276,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   248,   259,   258,   257,   250,     0,
     251,   253,   256,    17,   245,   240,    14,    17,    17,     0,
       0,   255,     0,     0,     0,    15,    16,    17,     0,    82,
      13,    68,    64,    17,     0,    78,    17,     0,     0,     0,
       0,     0,    39,    19,    41,    40,   204,   156,     0,    17,
       0,     0,     0,    57,    58,    89,    90,    17,   124,   123,
     125,     0,    17,   127,    17,   106,     0,   151,   150,    17,
      86,    85,    17,     0,   114,   113,    17,     0,     0,     0,
       0,    10,     0,     0,   152,   153,   154,   167,     0,   219,
     212,    17,     0,    17,     0,   216,    17,   217,     0,    11,
      17,    17,   280,     0,   249,   242,   241,   237,   239,    17,
      17,    17,    17,    97,    71,    66,    17,     0,    17,    69,
      17,     0,    17,    25,    24,   289,     0,    26,   287,     0,
      30,    17,    17,     0,   155,    17,   189,    17,     0,   195,
     196,   197,   198,   199,   190,   194,    17,   104,   126,   202,
       0,    42,   108,    17,    17,     0,    88,    17,     0,    17,
      99,    17,     0,     0,    17,   291,   222,     0,   221,   218,
     231,     0,     0,     0,    17,    91,    92,     0,   111,    17,
     103,    17,    74,     0,    73,    70,    81,     0,     0,     0,
     286,   285,     0,     0,    17,     0,   192,    17,     0,     0,
      17,     0,    42,    99,     0,     0,    17,     0,     0,     0,
     159,   220,    17,     0,    17,     0,     0,   119,   279,    17,
       0,    96,     0,    72,    17,     0,     0,   288,   207,   205,
       0,   208,     0,   201,   200,    17,    55,    56,     0,     0,
     283,    48,    19,    52,    53,    51,    54,    47,    45,    46,
      44,   110,    50,    49,     0,   107,    17,    83,    84,   115,
       0,     0,   223,   227,   234,   228,   117,     0,    17,    98,
      75,    17,   206,    17,     0,     0,   129,   284,    43,   109,
     149,     0,    59,    60,     0,    94,    77,     0,   191,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   122,    17,   131,   112,    17,
      93,   193,     0,    17,   116,   130,     0,    17,     0,     0,
     132
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,    13,    14,    15,   253,
      45,    34,   470,    35,   156,    62,   273,   431,   471,   472,
      63,    64,   310,   146,   147,   148,   149,    65,   303,   287,
     340,   450,   139,   140,   410,   141,   295,   307,   308,    66,
     343,    67,   306,   511,    93,    94,    95,    68,   292,   505,
     536,   543,   537,    69,   187,   363,   129,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,   282,    80,   376,
     465,   293,    81,    86,    87,    88,    89,   445,   130,   249,
     131,   132,    90,   134,   135,   481,   482,   483,   196,   250
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -264
static const yytype_int16 yypact[] =
{
     499,   -80,   -60,   -47,   -24,    64,    -8,   159,   307,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,    24,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,   314,   314,   314,   314,   314,
     314,   314,  -264,   369,  -264,  -264,   925,   224,     3,  1222,
     259,   453,    36,   247,   205,    47,   299,  -264,  -264,   356,
     332,  -264,   308,  -264,   310,   260,  -264,   189,   300,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,    38,   698,    76,   489,  -264,   463,   397,  -264,  -264,
    -264,  -264,   291,  -264,  -264,  -264,   268,  1480,   312,   180,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,   561,
     958,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
      21,  -264,   283,    70,   316,  -264,   287,   164,   321,   191,
     399,  -264,  -264,  -264,  -264,  -264,   788,  -264,  -264,   404,
    -264,  -264,  -264,   413,  -264,   333,   188,   359,   418,   267,
     366,   209,   370,    61,   346,   338,     1,   194,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,   698,  -264,  -264,
     463,  1309,  1328,  -264,  -264,  -264,  -264,   420,   314,   314,
    -264,   375,   340,  1554,  -264,  1462,  -264,  -264,  -264,   314,
     216,   167,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,  1180,
     314,   314,   314,  -264,  -264,  -264,  -264,  -264,  -264,  1373,
     510,   314,   196,   285,   372,  -264,  -264,  -264,   431,   314,
    -264,   406,   348,  -264,    77,  -264,  -264,   211,   144,   182,
     351,   440,  -264,  -264,  -264,  -264,  -264,    59,   453,   299,
     308,   434,    37,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
     435,   443,  -264,  -264,  -264,  -264,    91,  -264,  -264,  -264,
    -264,  -264,  -264,   250,  -264,  -264,  -264,   376,   166,   470,
     389,  -264,   224,   453,   314,   314,   314,  -264,  1337,   314,
     407,  -264,   486,  -264,   351,   314,  -264,   314,   694,  -264,
    -264,  -264,  -264,  1048,   314,   314,   314,  -264,   351,  -264,
    -264,  -264,  -264,   441,   314,   410,  -264,   511,  -264,   314,
    -264,  1090,  -264,  -264,  -264,  -264,   512,  -264,  -264,   429,
      47,  -264,  -264,   439,  -264,  -264,   314,  -264,    78,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,   270,  -264,  -264,
     221,   314,  -264,  -264,  -264,   224,   314,  -264,   222,  -264,
     -22,  -264,   148,   146,  -264,  -264,   314,   432,   314,   314,
    1373,   604,   224,     3,  -264,   314,    26,    60,   314,  -264,
    -264,  -264,   314,   451,   314,   314,  1373,   784,   224,   144,
    -264,  -264,   169,   177,  -264,   183,  -264,  -264,   438,   455,
    -264,  1556,   314,   259,   436,   206,  -264,    36,   158,    36,
    -264,   314,  -264,   604,  -264,  1319,   442,  -264,   314,  -264,
     444,  -264,    60,   314,  -264,   826,   446,  -264,  -264,  -264,
     193,  -264,   438,  -264,  -264,  -264,  -264,  -264,   224,   144,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  1556,  -264,  -264,  -264,  -264,   314,
     457,   477,   314,  -264,   314,  -264,  -264,  1222,  -264,    21,
     314,  -264,  -264,  -264,    -2,  1582,  -264,  -264,    47,  -264,
     314,   276,  -264,  -264,   916,   314,   314,    29,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
     314,  -264,   224,  -264,   314,  -264,   246,  -264,   224,   148,
    -264
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,     0,
    -248,  -264,  -263,  -264,  -264,   385,  -264,   135,  -264,  -264,
    -240,  -203,  -264,   109,  -264,   421,  -264,  -196,  -264,   266,
    -264,  -264,   187,   155,  -264,  -264,   -36,   223,  -168,  -146,
    -264,   -96,  -264,  -264,    97,  -264,   210,   -94,  -264,  -264,
    -264,  -264,  -264,   -78,  -264,  -264,   335,   -65,   573,  -264,
     302,   496,   -48,   544,   -44,   -49,  -264,   380,  -264,   294,
     201,   398,  -264,  -245,  -264,   611,  -264,   258,  -197,  -264,
     459,   583,   -37,  -264,  -264,   218,   564,   565,    48,   -12
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -244
static const yytype_int16 yytable[] =
{
      16,   296,   133,    32,   142,   355,    32,    17,    32,    25,
      26,    27,    28,    29,    30,    31,    91,    36,    37,    38,
      39,    40,    41,    42,   181,   360,   -17,    18,   194,    32,
     191,    32,   192,    44,    32,   136,   137,   144,   309,   178,
      19,    32,   333,   449,   369,   370,   371,   372,   373,   145,
      33,   163,   154,   155,   166,   168,   169,   171,   173,   174,
     175,   176,   177,    20,    32,    32,    32,   392,   138,    21,
     197,   178,   361,   362,   302,   203,   205,   182,   324,    22,
     -17,   183,    92,   198,   199,   369,   370,   371,   372,   373,
     209,   152,   382,   210,   211,   518,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   179,   541,   241,   242,   440,
     180,   401,   258,   251,   374,   375,   264,   208,   252,   317,
     434,   254,   194,   194,   353,   259,   318,   182,   353,   267,
     138,   183,   125,   269,   417,   126,   457,   446,   256,   382,
     277,   278,   180,  -160,  -160,   261,   350,   382,  -160,   184,
     185,   186,    32,   456,    32,   426,   375,   145,   383,   312,
     313,   206,    32,   384,   314,   315,   316,    32,    32,   322,
     170,   473,   265,    32,   -17,   319,   -17,   207,    32,    32,
     285,    32,   133,   443,   325,   327,   507,   328,   266,   339,
      32,    32,   133,   284,    32,   289,    32,   153,   298,   455,
     301,    32,   438,   506,   508,    82,    32,    32,   474,    32,
     365,   150,   354,  -161,  -161,   475,   354,    83,  -161,   184,
     185,   186,   535,   334,   473,   -62,    23,   335,   336,   347,
     384,    32,   -65,  -105,   330,  -105,   356,   344,   384,   331,
     458,   167,   285,   349,    32,   -17,   351,   150,   459,   194,
     286,   357,    32,   -17,   461,    32,   -17,   -17,   -17,   366,
      84,   474,   311,   -99,   502,   476,   550,   377,   475,    91,
      32,   133,   380,   150,   381,   487,   299,   545,   352,   385,
     514,   172,   386,   549,   329,   -17,   388,    24,   430,   436,
      85,   165,   -17,   -17,   133,   -17,   136,   137,   358,    32,
     157,   396,   -17,   398,   136,   137,   399,   136,   137,   164,
     402,   403,   286,   547,   150,   477,   151,   478,   476,   405,
     406,   407,   408,    32,   341,   162,   412,   -17,   414,   138,
     415,    32,   418,   479,   294,    92,   200,   138,   304,   305,
     138,   422,   423,   133,   538,   425,   480,   366,   395,   158,
      43,   255,   395,   159,   -17,   260,   428,    32,   150,   133,
     195,   -17,   -17,   432,   433,   342,   395,   435,   477,   437,
     478,   439,   -17,   395,   441,   136,   137,   485,   193,   150,
     268,   204,  -174,   150,   448,   257,   479,   421,   150,   452,
     263,   453,    47,    48,    49,    50,    51,   276,    32,   480,
     150,   320,   283,    32,   460,  -104,   279,   462,   138,   323,
     468,   290,   345,   280,    53,   291,   489,   348,   150,   160,
     161,   359,   492,    32,   494,   395,   150,   367,   288,   497,
     463,   464,   291,   150,   500,   297,   379,   150,    32,   300,
     133,   395,   150,   389,   321,   504,    46,   395,    47,    48,
      49,    50,    51,    52,    53,   390,   391,   467,    47,    48,
      49,    50,    51,   488,  -174,  -174,   510,   397,  -174,  -174,
    -174,  -174,  -174,   150,   150,   346,   394,   150,   515,   411,
     409,   516,   188,   517,    47,    48,    49,    50,    51,   189,
    -238,   338,   413,   419,   540,  -238,   150,   358,   420,   150,
     424,   442,  -238,  -238,   486,  -238,  -238,     1,     2,     3,
     496,     4,     5,     6,   501,   498,   542,     7,   150,   544,
     454,   272,   150,   546,   466,   512,   490,   548,   491,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,   513,  -238,   484,   262,   387,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,   451,  -238,  -238,  -238,  -238,  -238,
     429,  -238,  -238,  -238,  -235,   245,  -238,   499,   539,  -238,
    -238,  -238,   364,   447,   143,   393,  -243,  -243,   190,  -243,
    -243,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   243,
     119,   120,   121,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,   281,
     444,   368,   427,   503,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,   378,  -243,
    -243,   150,  -235,  -235,  -230,   400,   247,  -243,   202,    32,
    -243,   493,   509,   248,  -243,  -243,    96,    97,   337,    98,
      99,    46,   244,    47,    48,    49,    50,    51,    52,    53,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,     0,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,     0,   124,
      85,  -230,  -230,  -230,     0,   245,     0,   125,    -2,   270,
     126,     0,     0,     0,   127,   128,  -243,  -243,     0,  -243,
    -243,    46,     0,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,     0,    58,     0,     0,     0,    59,
       0,     0,     0,    60,    61,     0,     0,   245,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -243,  -243,
       0,  -243,  -243,   271,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,     0,  -243,
    -243,   150,   -76,   -76,     0,     0,   247,  -243,     0,     0,
    -243,     0,     0,   248,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
       0,  -243,  -243,   150,   -79,   -79,     0,   245,   247,  -243,
       0,   -17,  -243,     0,     0,   248,  -243,  -243,  -243,  -243,
      32,  -243,  -243,     0,     0,     0,     0,     0,    46,     0,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,     0,    58,     0,     0,     0,    59,     0,     0,   245,
      60,    61,     0,     0,     0,     0,     0,     0,     0,     0,
    -243,  -243,     0,  -243,  -243,     0,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
       0,  -243,  -243,   150,     0,     0,     0,   -17,   247,  -243,
       0,     0,  -243,     0,     0,   248,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,     0,  -243,  -243,   150,   246,     0,     0,   245,
     247,  -243,     0,     0,  -243,     0,     0,   248,  -243,  -243,
    -243,  -243,     0,  -243,  -243,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   416,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,    96,    97,     0,    98,    99,     0,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,     0,  -243,  -243,   150,     0,     0,     0,   404,
     247,  -243,     0,     0,  -243,     0,     0,   248,  -243,  -243,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,     0,   124,    85,   -80,   -80,   -80,
       0,   332,     0,   125,     0,    32,   126,     0,     0,     0,
     127,   128,    96,    97,     0,    98,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,    96,    97,     0,    98,    99,     0,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,     0,   124,    85,     0,     0,     0,
       0,     0,     0,   125,     0,     0,   126,     0,     0,     0,
     127,   128,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,     0,   124,    85,     0,
     193,     0,     0,     0,  -177,   125,     0,     0,   126,  -224,
     495,     0,   127,   128,    47,    48,    49,    50,    51,   193,
       0,     0,     0,  -173,     0,     0,     0,     0,   193,     0,
       0,     0,  -176,    47,    48,    49,    50,    51,     0,     0,
       0,     0,    47,    48,    49,    50,    51,     0,  -224,  -224,
    -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,  -224,  -224,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,    97,     0,    98,    99,
       0,     0,     0,     0,     0,     0,  -177,  -177,     0,     0,
    -177,  -177,  -177,  -177,  -177,     0,  -224,  -224,  -224,     0,
       0,     0,     0,     0,     0,  -173,  -173,     0,     0,  -173,
    -173,  -173,  -173,  -173,  -176,  -176,     0,     0,  -176,  -176,
    -176,  -176,  -176,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,     0,   124,    85,
       0,     0,   -17,   324,     0,     0,   125,   -17,     0,   126,
       0,     0,     0,   127,   128,   -17,     0,     0,     0,     0,
    -211,   201,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    83,     0,     0,     0,     0,     0,     0,
       0,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,     0,   -17,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -17,   -17,
     -17,   326,     0,     0,  -215,   324,   353,   469,     0,     0,
       0,     0,     0,     0,     0,     0,    85,   150,  -211,    46,
       0,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,   353,    58,     0,     0,     0,    59,     0,     0,
       0,    60,    61,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,     0,
       0,   271,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,     0,     0,     0,
       0,     0,  -215,     0,   354,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     354
};

static const yytype_int16 yycheck[] =
{
       0,   169,    39,     5,    40,   268,     5,    87,     5,     9,
      10,    11,    12,    13,    14,    15,    13,    17,    18,    19,
      20,    21,    22,    23,    72,   273,     5,    87,    77,     5,
      74,     5,    76,    33,     5,    57,    58,     1,    37,     1,
      87,     5,   239,    17,     7,     8,     9,    10,    11,    13,
      26,    51,     5,     6,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    87,     5,     5,     5,   312,    90,     5,
      82,     1,    13,    14,    13,    87,    88,     1,     1,    87,
      59,     5,    79,    83,    84,     7,     8,     9,    10,    11,
      90,    43,     1,    93,    94,    97,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,    87,    97,   127,   128,   392,
      92,   328,   144,   133,    97,    98,   148,    89,   138,   187,
     385,   141,   191,   192,     0,   145,   190,     1,     0,   149,
      90,     5,    93,   153,   351,    96,   419,   402,    88,     1,
     160,   161,    92,    87,    88,     1,    89,     1,    92,    93,
      94,    95,     5,   418,     5,    97,    98,    13,    87,   179,
     180,     1,     5,    92,   184,   185,   186,     5,     5,   201,
       1,   431,     1,     5,     5,   195,     5,    17,     5,     5,
      12,     5,   239,   400,   204,   205,   469,   207,    17,    13,
       5,     5,   249,   165,     5,   167,     5,    12,   170,   416,
     172,     5,   390,   468,   472,     1,     5,     5,   431,     5,
     278,    87,    88,    87,    88,   431,    88,    13,    92,    93,
      94,    95,   505,   243,   484,    87,    87,   247,   248,   261,
      92,     5,    88,    87,    87,    89,   268,   257,    92,    92,
      91,     1,    12,   263,     5,     5,   266,    87,    91,   318,
      82,    89,     5,    13,    91,     5,    87,    17,    87,   279,
      56,   484,    88,    13,    91,   431,   549,   287,   484,    13,
       5,   328,   292,    87,   294,    89,    87,   542,    87,   299,
     497,     1,   302,   548,    88,     5,   306,     0,    87,    87,
      86,     1,    12,    13,   351,     5,    57,    58,   270,     5,
      21,   321,    12,   323,    57,    58,   326,    57,    58,    21,
     330,   331,    82,    87,    87,   431,    89,   431,   484,   339,
     340,   341,   342,     5,    59,    13,   346,    87,   348,    90,
     350,     5,   352,   431,    87,    79,    88,    90,    12,    13,
      90,   361,   362,   400,    88,   365,   431,   367,   320,    13,
       1,    88,   324,    17,     5,    88,   376,     5,    87,   416,
      89,    12,    82,   383,   384,    13,   338,   387,   484,   389,
     484,   391,    82,   345,   394,    57,    58,   433,     1,    87,
       1,    89,     5,    87,   404,    89,   484,   359,    87,   409,
      89,   411,    15,    16,    17,    18,    19,    13,     5,   484,
      87,     1,    89,     5,   424,    87,    13,   427,    90,    89,
     430,    13,     1,    20,    21,    17,   436,    89,    87,    83,
      84,     1,   442,     5,   444,   397,    87,    13,    89,   449,
      12,    13,    17,    87,   454,    89,    13,    87,     5,    89,
     497,   413,    87,    87,    89,   465,    13,   419,    15,    16,
      17,    18,    19,    20,    21,     5,    87,   429,    15,    16,
      17,    18,    19,   435,    87,    88,   486,     1,    91,    92,
      93,    94,    95,    87,    87,    89,    89,    87,   498,    89,
      59,   501,    13,   503,    15,    16,    17,    18,    19,    20,
       0,     1,     1,     1,   514,     5,    87,   469,    89,    87,
      81,    89,    12,    13,    88,    15,    16,    28,    29,    30,
      88,    32,    33,    34,    88,    91,   536,    38,    87,   539,
      89,   156,    87,   543,    89,    88,   437,   547,   439,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    88,    56,   432,   147,   303,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,   407,    85,    86,    87,    88,    89,
     377,    91,    92,    93,     0,     1,    96,   452,   511,    99,
     100,   101,   277,   403,    41,   313,    12,    13,    74,    15,
      16,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   163,
      56,   281,   368,   462,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,   290,    85,
      86,    87,    88,    89,     0,     1,    92,    93,    87,     5,
      96,   443,   484,    99,   100,   101,    12,    13,   249,    15,
      16,    13,   129,    15,    16,    17,    18,    19,    20,    21,
     156,   156,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,    85,
      86,    87,    88,    89,    -1,     1,    -1,    93,     0,     1,
      96,    -1,    -1,    -1,   100,   101,    12,    13,    -1,    15,
      16,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    35,    36,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      -1,    15,    16,    55,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,    85,
      86,    87,    88,    89,    -1,    -1,    92,    93,    -1,    -1,
      96,    -1,    -1,    99,   100,   101,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    85,    86,    87,    88,    89,    -1,     1,    92,    93,
      -1,     5,    96,    -1,    -1,    99,   100,   101,    12,    13,
       5,    15,    16,    -1,    -1,    -1,    -1,    -1,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,     1,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    -1,    15,    16,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    85,    86,    87,    -1,    -1,    -1,    91,    92,    93,
      -1,    -1,    96,    -1,    -1,    99,   100,   101,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    85,    86,    87,    88,    -1,    -1,     1,
      92,    93,    -1,    -1,    96,    -1,    -1,    99,   100,   101,
      12,    13,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    -1,    15,    16,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    85,    86,    87,    -1,    -1,    -1,    91,
      92,    93,    -1,    -1,    96,    -1,    -1,    99,   100,   101,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    85,    86,    87,    88,    89,
      -1,     1,    -1,    93,    -1,     5,    96,    -1,    -1,    -1,
     100,   101,    12,    13,    -1,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    -1,    15,    16,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    96,    -1,    -1,    -1,
     100,   101,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    85,    86,    -1,
       1,    -1,    -1,    -1,     5,    93,    -1,    -1,    96,     0,
       1,    -1,   100,   101,    15,    16,    17,    18,    19,     1,
      -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,     5,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    15,    16,    17,    18,    19,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    -1,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    -1,    -1,
      91,    92,    93,    94,    95,    -1,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    -1,    -1,    91,
      92,    93,    94,    95,    87,    88,    -1,    -1,    91,    92,
      93,    94,    95,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    85,    86,
      -1,    -1,     0,     1,    -1,    -1,    93,     5,    -1,    96,
      -1,    -1,    -1,   100,   101,    13,    -1,    -1,    -1,    -1,
       0,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    56,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,     0,     1,     0,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     0,    27,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    35,    36,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    30,    32,    33,    34,    38,   103,   104,
     105,   106,   107,   108,   109,   110,   111,    87,    87,    87,
      87,     5,    87,    87,     0,   111,   111,   111,   111,   111,
     111,   111,     5,    26,   113,   115,   111,   111,   111,   111,
     111,   111,   111,     1,   111,   112,    13,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    27,    31,
      35,    36,   117,   122,   123,   129,   141,   143,   149,   155,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     170,   174,     1,    13,    56,    86,   175,   176,   177,   178,
     184,    13,    79,   146,   147,   148,    12,    13,    15,    16,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    85,    93,    96,   100,   101,   158,
     180,   182,   183,   184,   185,   186,    57,    58,    90,   134,
     135,   137,   138,   160,     1,    13,   125,   126,   127,   128,
      87,    89,   190,    12,     5,     6,   116,    21,    13,    17,
      83,    84,    13,   111,    21,     1,   111,     1,   111,   111,
       1,   111,     1,   111,   111,   111,   111,   111,     1,    87,
      92,   164,     1,     5,    93,    94,    95,   156,    13,    20,
     165,   166,   166,     1,   167,    89,   190,   191,   111,   111,
      88,     1,   177,   191,    89,   191,     1,    17,   190,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,    78,   183,     1,    88,    92,    99,   181,
     191,   111,   111,   111,   111,    88,    88,    89,   191,   111,
      88,     1,   127,    89,   191,     1,    17,   111,     1,   111,
       1,    55,   117,   118,   188,   189,    13,   111,   111,    13,
      20,   163,   169,    89,   190,    12,    82,   131,    89,   190,
      13,    17,   150,   173,    87,   138,   140,    89,   190,    87,
      89,   190,    13,   130,    12,    13,   144,   139,   140,    37,
     124,    88,   111,   111,   111,   111,   111,   164,   166,   111,
       1,    89,   191,    89,     1,   111,    89,   111,   111,    88,
      87,    92,     1,   180,   111,   111,   111,   182,     1,    13,
     132,    59,    13,   142,   111,     1,    89,   191,    89,   111,
      89,   111,    87,     0,    88,   114,   191,    89,   190,     1,
     112,    13,    14,   157,   158,   164,   111,    13,   169,     7,
       8,     9,    10,    11,    97,    98,   171,   111,   173,    13,
     111,   111,     1,    87,    92,   111,   111,   131,   111,    87,
       5,    87,   175,   162,    89,   190,   111,     1,   111,   111,
       1,   180,   111,   111,    91,   111,   111,   111,   111,    59,
     136,    89,   111,     1,   111,   111,     1,   180,   111,     1,
      89,   190,   111,   111,    81,   111,    97,   171,   111,   139,
      87,   119,   111,   111,   175,   111,    87,   111,   140,   111,
     114,   111,    89,   180,    56,   179,   175,   148,   111,    17,
     133,   134,   111,   111,    89,   180,   175,   114,    91,    91,
     111,    91,   111,    12,    13,   172,    89,   190,   111,     1,
     114,   120,   121,   122,   123,   129,   141,   143,   149,   155,
     159,   187,   188,   189,   119,   138,    88,    89,   190,   111,
     125,   125,   111,   179,   111,     1,    88,   111,    91,   135,
     111,    88,    91,   172,   111,   151,   175,   114,   112,   187,
     111,   145,    88,    88,   180,   111,   111,   111,    97,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   114,   152,   154,    88,   146,
     111,    97,   111,   153,   111,   175,   111,    87,   111,   175,
     114
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 10:

/* Line 1455 of yacc.c  */
#line 303 "WebCore/css/CSSGrammar.y"
    {
        static_cast<CSSParser*>(parser)->m_rule = (yyvsp[(4) - (6)].rule);
    ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 309 "WebCore/css/CSSGrammar.y"
    {
        static_cast<CSSParser*>(parser)->m_keyframe = (yyvsp[(4) - (6)].keyframeRule);
    ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 315 "WebCore/css/CSSGrammar.y"
    {
        /* can be empty */
    ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 321 "WebCore/css/CSSGrammar.y"
    {
        /* can be empty */
    ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 327 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        if ((yyvsp[(4) - (5)].valueList)) {
            p->m_valueList = p->sinkFloatingValueList((yyvsp[(4) - (5)].valueList));
            int oldParsedProperties = p->m_numParsedProperties;
            if (!p->parseValue(p->m_id, p->m_important))
                p->rollbackLastProperties(p->m_numParsedProperties - oldParsedProperties);
            delete p->m_valueList;
            p->m_valueList = 0;
        }
    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 341 "WebCore/css/CSSGrammar.y"
    {
         CSSParser* p = static_cast<CSSParser*>(parser);
         p->m_mediaQuery = p->sinkFloatingMediaQuery((yyvsp[(4) - (5)].mediaQuery));
     ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 348 "WebCore/css/CSSGrammar.y"
    {
        if ((yyvsp[(4) - (5)].selectorList)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (p->m_selectorListForParseSelector)
                p->m_selectorListForParseSelector->adoptSelectorVector(*(yyvsp[(4) - (5)].selectorList));
        }
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 370 "WebCore/css/CSSGrammar.y"
    {
  ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 380 "WebCore/css/CSSGrammar.y"
    {
     CSSParser* p = static_cast<CSSParser*>(parser);
     (yyval.rule) = static_cast<CSSParser*>(parser)->createCharsetRule((yyvsp[(3) - (5)].string));
     if ((yyval.rule) && p->m_styleSheet)
         p->m_styleSheet->append((yyval.rule));
  ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 386 "WebCore/css/CSSGrammar.y"
    {
  ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 388 "WebCore/css/CSSGrammar.y"
    {
  ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 394 "WebCore/css/CSSGrammar.y"
    {
     CSSParser* p = static_cast<CSSParser*>(parser);
     if ((yyvsp[(2) - (3)].rule) && p->m_styleSheet)
         p->m_styleSheet->append((yyvsp[(2) - (3)].rule));
 ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 413 "WebCore/css/CSSGrammar.y"
    {
        static_cast<CSSParser*>(parser)->m_hadSyntacticallyValidCSSRule = true;
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 421 "WebCore/css/CSSGrammar.y"
    { (yyval.ruleList) = 0; ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 422 "WebCore/css/CSSGrammar.y"
    {
      (yyval.ruleList) = (yyvsp[(1) - (3)].ruleList);
      if ((yyvsp[(2) - (3)].rule)) {
          if (!(yyval.ruleList))
              (yyval.ruleList) = static_cast<CSSParser*>(parser)->createRuleList();
          (yyval.ruleList)->append((yyvsp[(2) - (3)].rule));
      }
  ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 451 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createImportRule((yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].mediaList));
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 454 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 457 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 460 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 466 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createVariablesRule((yyvsp[(3) - (7)].mediaList), true);
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 470 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createVariablesRule((yyvsp[(3) - (7)].mediaList), false);
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 476 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = static_cast<CSSParser*>(parser)->createMediaList();
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 480 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = (yyvsp[(3) - (3)].mediaList);
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 486 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (1)].boolean);
    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 489 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (2)].boolean);
        if ((yyvsp[(2) - (2)].boolean))
            (yyval.boolean) = (yyvsp[(2) - (2)].boolean);
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 494 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (1)].boolean);
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 497 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 500 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 503 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (2)].boolean);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 509 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (3)].boolean);
    ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 512 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 515 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 518 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 521 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (4)].boolean);
        if ((yyvsp[(2) - (4)].boolean))
            (yyval.boolean) = (yyvsp[(2) - (4)].boolean);
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 526 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (4)].boolean);
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 529 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (6)].boolean);
    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 535 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = static_cast<CSSParser*>(parser)->addVariable((yyvsp[(1) - (4)].string), (yyvsp[(4) - (4)].valueList));
    ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 539 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = static_cast<CSSParser*>(parser)->addVariableDeclarationBlock((yyvsp[(1) - (7)].string));
    ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 543 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 547 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 551 "WebCore/css/CSSGrammar.y"
    {
        /* @variables { varname: } Just reduce away this variable with no value. */
        (yyval.boolean) = false;
    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 556 "WebCore/css/CSSGrammar.y"
    {
        /* if we come across rules with invalid values like this case: @variables { varname: *; }, just discard the property/value pair */
        (yyval.boolean) = false;
    ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 563 "WebCore/css/CSSGrammar.y"
    {
        (yyval.string) = (yyvsp[(1) - (2)].string);
    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 569 "WebCore/css/CSSGrammar.y"
    {
    static_cast<CSSParser*>(parser)->addNamespace((yyvsp[(3) - (6)].string), (yyvsp[(4) - (6)].string));
    (yyval.rule) = 0;
;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 573 "WebCore/css/CSSGrammar.y"
    {
    (yyval.rule) = 0;
;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 576 "WebCore/css/CSSGrammar.y"
    {
    (yyval.rule) = 0;
;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 579 "WebCore/css/CSSGrammar.y"
    {
    (yyval.rule) = 0;
;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 585 "WebCore/css/CSSGrammar.y"
    { (yyval.string).characters = 0; ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 586 "WebCore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 595 "WebCore/css/CSSGrammar.y"
    {
        (yyval.string) = (yyvsp[(1) - (2)].string);
    ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 601 "WebCore/css/CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 604 "WebCore/css/CSSGrammar.y"
    {
        (yyval.valueList) = (yyvsp[(3) - (4)].valueList);
    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 610 "WebCore/css/CSSGrammar.y"
    {
        (yyvsp[(3) - (7)].string).lower();
        (yyval.mediaQueryExp) = static_cast<CSSParser*>(parser)->createFloatingMediaQueryExp((yyvsp[(3) - (7)].string), (yyvsp[(5) - (7)].valueList));
    ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 617 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.mediaQueryExpList) = p->createFloatingMediaQueryExpList();
        (yyval.mediaQueryExpList)->append(p->sinkFloatingMediaQueryExp((yyvsp[(1) - (1)].mediaQueryExp)));
    ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 622 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = (yyvsp[(1) - (5)].mediaQueryExpList);
        (yyval.mediaQueryExpList)->append(static_cast<CSSParser*>(parser)->sinkFloatingMediaQueryExp((yyvsp[(5) - (5)].mediaQueryExp)));
    ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 629 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = static_cast<CSSParser*>(parser)->createFloatingMediaQueryExpList();
    ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 632 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = (yyvsp[(3) - (3)].mediaQueryExpList);
    ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 638 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::None;
    ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 641 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::Only;
    ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 644 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::Not;
    ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 650 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.mediaQuery) = p->createFloatingMediaQuery(p->sinkFloatingMediaQueryExpList((yyvsp[(1) - (1)].mediaQueryExpList)));
    ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 655 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyvsp[(3) - (4)].string).lower();
        (yyval.mediaQuery) = p->createFloatingMediaQuery((yyvsp[(1) - (4)].mediaQueryRestrictor), (yyvsp[(3) - (4)].string), p->sinkFloatingMediaQueryExpList((yyvsp[(4) - (4)].mediaQueryExpList)));
    ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 663 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = static_cast<CSSParser*>(parser)->createMediaList();
     ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 670 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.mediaList) = p->createMediaList();
        (yyval.mediaList)->appendMediaQuery(p->sinkFloatingMediaQuery((yyvsp[(1) - (1)].mediaQuery)));
    ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 675 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = (yyvsp[(1) - (4)].mediaList);
        if ((yyval.mediaList))
            (yyval.mediaList)->appendMediaQuery(static_cast<CSSParser*>(parser)->sinkFloatingMediaQuery((yyvsp[(4) - (4)].mediaQuery)));
    ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 680 "WebCore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = 0;
    ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 686 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createMediaRule((yyvsp[(3) - (7)].mediaList), (yyvsp[(6) - (7)].ruleList));
    ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 689 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createMediaRule(0, (yyvsp[(5) - (6)].ruleList));
    ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 695 "WebCore/css/CSSGrammar.y"
    {
      (yyval.string) = (yyvsp[(1) - (2)].string);
  ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 701 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = (yyvsp[(7) - (8)].keyframesRule);
        (yyvsp[(7) - (8)].keyframesRule)->setNameInternal((yyvsp[(3) - (8)].string));
    ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 713 "WebCore/css/CSSGrammar.y"
    { (yyval.keyframesRule) = static_cast<CSSParser*>(parser)->createKeyframesRule(); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 714 "WebCore/css/CSSGrammar.y"
    {
        (yyval.keyframesRule) = (yyvsp[(1) - (3)].keyframesRule);
        if ((yyvsp[(2) - (3)].keyframeRule))
            (yyval.keyframesRule)->append((yyvsp[(2) - (3)].keyframeRule));
    ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 722 "WebCore/css/CSSGrammar.y"
    {
        (yyval.keyframeRule) = static_cast<CSSParser*>(parser)->createKeyframeRule((yyvsp[(1) - (6)].valueList));
    ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 728 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.valueList) = p->createFloatingValueList();
        (yyval.valueList)->addValue(p->sinkFloatingValue((yyvsp[(1) - (1)].value)));
    ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 733 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.valueList) = (yyvsp[(1) - (5)].valueList);
        if ((yyval.valueList))
            (yyval.valueList)->addValue(p->sinkFloatingValue((yyvsp[(5) - (5)].value)));
    ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 742 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = false; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 743 "WebCore/css/CSSGrammar.y"
    {
        (yyval.value).id = 0; (yyval.value).isInt = false; (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER;
        CSSParserString& str = (yyvsp[(1) - (1)].string);
        if (equalIgnoringCase("from", str.characters, str.length))
            (yyval.value).fValue = 0;
        else if (equalIgnoringCase("to", str.characters, str.length))
            (yyval.value).fValue = 100;
        else
            YYERROR;
    ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 757 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        if ((yyvsp[(3) - (8)].selector))
            (yyval.rule) = p->createPageRule(p->sinkFloatingSelector((yyvsp[(3) - (8)].selector)));
        else {
            // Clear properties in the invalid @page rule.
            p->clearProperties();
            // Also clear margin at-rules here once we fully implement margin at-rules parsing.
            (yyval.rule) = 0;
        }
    ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 768 "WebCore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 771 "WebCore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 777 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_tag = QualifiedName(nullAtom, (yyvsp[(1) - (1)].string), p->m_defaultNamespace);
        (yyval.selector)->setForPage();
    ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 783 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if ((yyval.selector)) {
            (yyval.selector)->m_tag = QualifiedName(nullAtom, (yyvsp[(1) - (2)].string), p->m_defaultNamespace);
            (yyval.selector)->setForPage();
        }
    ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 791 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
        if ((yyval.selector))
            (yyval.selector)->setForPage();
    ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 796 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->setForPage();
    ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 809 "WebCore/css/CSSGrammar.y"
    {
        static_cast<CSSParser*>(parser)->startDeclarationsForMarginBox();
    ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 811 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createMarginAtRule((yyvsp[(1) - (7)].marginBox));
    ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 817 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopLeftCornerMarginBox;
    ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 820 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopLeftMarginBox;
    ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 823 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopCenterMarginBox;
    ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 826 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopRightMarginBox;
    ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 829 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopRightCornerMarginBox;
    ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 832 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomLeftCornerMarginBox;
    ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 835 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomLeftMarginBox;
    ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 838 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomCenterMarginBox;
    ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 841 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomRightMarginBox;
    ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 844 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomRightCornerMarginBox;
    ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 847 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::LeftTopMarginBox;
    ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 850 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::LeftMiddleMarginBox;
    ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 853 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::LeftBottomMarginBox;
    ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 856 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::RightTopMarginBox;
    ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 859 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::RightMiddleMarginBox;
    ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 862 "WebCore/css/CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::RightBottomMarginBox;
    ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 869 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createFontFaceRule();
    ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 872 "WebCore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 875 "WebCore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 881 "WebCore/css/CSSGrammar.y"
    { (yyval.relation) = CSSSelector::DirectAdjacent; ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 882 "WebCore/css/CSSGrammar.y"
    { (yyval.relation) = CSSSelector::IndirectAdjacent; ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 883 "WebCore/css/CSSGrammar.y"
    { (yyval.relation) = CSSSelector::Child; ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 887 "WebCore/css/CSSGrammar.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 888 "WebCore/css/CSSGrammar.y"
    { (yyval.integer) = 1; ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 892 "WebCore/css/CSSGrammar.y"
    { (yyval.integer) = -1; ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 893 "WebCore/css/CSSGrammar.y"
    { (yyval.integer) = 1; ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 897 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.rule) = p->createStyleRule((yyvsp[(1) - (5)].selectorList));
    ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 904 "WebCore/css/CSSGrammar.y"
    {
        if ((yyvsp[(1) - (1)].selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selectorList) = p->reusableSelectorVector();
            deleteAllValues(*(yyval.selectorList));
            (yyval.selectorList)->shrink(0);
            (yyval.selectorList)->append(p->sinkFloatingSelector((yyvsp[(1) - (1)].selector)));
            p->updateLastSelectorLineAndPosition();
        }
    ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 914 "WebCore/css/CSSGrammar.y"
    {
        if ((yyvsp[(1) - (4)].selectorList) && (yyvsp[(4) - (4)].selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selectorList) = (yyvsp[(1) - (4)].selectorList);
            (yyval.selectorList)->append(p->sinkFloatingSelector((yyvsp[(4) - (4)].selector)));
            p->updateLastSelectorLineAndPosition();
        } else
            (yyval.selectorList) = 0;
    ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 923 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selectorList) = 0;
    ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 929 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (2)].selector);
    ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 935 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 939 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 943 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if (!(yyvsp[(1) - (2)].selector))
            (yyval.selector) = 0;
        else if ((yyval.selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            CSSSelector* end = (yyval.selector);
            while (end->tagHistory())
                end = end->tagHistory();
            end->m_relation = CSSSelector::Descendant;
            end->setTagHistory(p->sinkFloatingSelector((yyvsp[(1) - (2)].selector)));
            if (Document* doc = p->document())
                doc->setUsesDescendantRules(true);
        }
    ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 958 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(3) - (3)].selector);
        if (!(yyvsp[(1) - (3)].selector))
            (yyval.selector) = 0;
        else if ((yyval.selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            CSSSelector* end = (yyval.selector);
            while (end->tagHistory())
                end = end->tagHistory();
            end->m_relation = (yyvsp[(2) - (3)].relation);
            end->setTagHistory(p->sinkFloatingSelector((yyvsp[(1) - (3)].selector)));
            if ((yyvsp[(2) - (3)].relation) == CSSSelector::Child) {
                if (Document* doc = p->document())
                    doc->setUsesDescendantRules(true);
            } else if ((yyvsp[(2) - (3)].relation) == CSSSelector::DirectAdjacent || (yyvsp[(2) - (3)].relation) == CSSSelector::IndirectAdjacent) {
                if (Document* doc = p->document())
                    doc->setUsesSiblingRules(true);
            }
        }
    ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 978 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = 0;
    ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 984 "WebCore/css/CSSGrammar.y"
    { (yyval.string).characters = 0; (yyval.string).length = 0; ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 985 "WebCore/css/CSSGrammar.y"
    { static UChar star = '*'; (yyval.string).characters = &star; (yyval.string).length = 1; ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 986 "WebCore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 990 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_tag = QualifiedName(nullAtom, (yyvsp[(1) - (1)].string), p->m_defaultNamespace);
    ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 995 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if ((yyval.selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selector)->m_tag = QualifiedName(nullAtom, (yyvsp[(1) - (2)].string), p->m_defaultNamespace);
        }
    ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1002 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
        CSSParser* p = static_cast<CSSParser*>(parser);
        if ((yyval.selector) && p->m_defaultNamespace != starAtom)
            (yyval.selector)->m_tag = QualifiedName(nullAtom, starAtom, p->m_defaultNamespace);
    ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1008 "WebCore/css/CSSGrammar.y"
    {
        AtomicString namespacePrefix = (yyvsp[(1) - (2)].string);
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        if (p->m_styleSheet)
            (yyval.selector)->m_tag = QualifiedName(namespacePrefix, (yyvsp[(2) - (2)].string),
                                      p->m_styleSheet->determineNamespace(namespacePrefix));
        else // FIXME: Shouldn't this case be an error?
            (yyval.selector)->m_tag = QualifiedName(nullAtom, (yyvsp[(2) - (2)].string), p->m_defaultNamespace);
    ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1018 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(3) - (3)].selector);
        if ((yyval.selector)) {
            AtomicString namespacePrefix = (yyvsp[(1) - (3)].string);
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (p->m_styleSheet)
                (yyval.selector)->m_tag = QualifiedName(namespacePrefix, (yyvsp[(2) - (3)].string),
                                          p->m_styleSheet->determineNamespace(namespacePrefix));
            else // FIXME: Shouldn't this case be an error?
                (yyval.selector)->m_tag = QualifiedName(nullAtom, (yyvsp[(2) - (3)].string), p->m_defaultNamespace);
        }
    ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1030 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if ((yyval.selector)) {
            AtomicString namespacePrefix = (yyvsp[(1) - (2)].string);
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (p->m_styleSheet)
                (yyval.selector)->m_tag = QualifiedName(namespacePrefix, starAtom,
                                          p->m_styleSheet->determineNamespace(namespacePrefix));
        }
    ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1043 "WebCore/css/CSSGrammar.y"
    {
        CSSParserString& str = (yyvsp[(1) - (1)].string);
        CSSParser* p = static_cast<CSSParser*>(parser);
        Document* doc = p->document();
        if (doc && doc->isHTMLDocument())
            str.lower();
        (yyval.string) = str;
    ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1051 "WebCore/css/CSSGrammar.y"
    {
        static UChar star = '*';
        (yyval.string).characters = &star;
        (yyval.string).length = 1;
    ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1059 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    ;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1062 "WebCore/css/CSSGrammar.y"
    {
        if (!(yyvsp[(2) - (2)].selector))
            (yyval.selector) = 0;
        else if ((yyvsp[(1) - (2)].selector)) {
            (yyval.selector) = (yyvsp[(1) - (2)].selector);
            CSSParser* p = static_cast<CSSParser*>(parser);
            CSSSelector* end = (yyvsp[(1) - (2)].selector);
            while (end->tagHistory())
                end = end->tagHistory();
            end->m_relation = CSSSelector::SubSelector;
            end->setTagHistory(p->sinkFloatingSelector((yyvsp[(2) - (2)].selector)));
        }
    ;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1075 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = 0;
    ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1081 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::Id;
        if (!p->m_strict)
            (yyvsp[(1) - (1)].string).lower();
        (yyval.selector)->m_value = (yyvsp[(1) - (1)].string);
    ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1089 "WebCore/css/CSSGrammar.y"
    {
        if ((yyvsp[(1) - (1)].string).characters[0] >= '0' && (yyvsp[(1) - (1)].string).characters[0] <= '9') {
            (yyval.selector) = 0;
        } else {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selector) = p->createFloatingSelector();
            (yyval.selector)->m_match = CSSSelector::Id;
            if (!p->m_strict)
                (yyvsp[(1) - (1)].string).lower();
            (yyval.selector)->m_value = (yyvsp[(1) - (1)].string);
        }
    ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1107 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::Class;
        if (!p->m_strict)
            (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->m_value = (yyvsp[(2) - (2)].string);
    ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1118 "WebCore/css/CSSGrammar.y"
    {
        CSSParserString& str = (yyvsp[(1) - (2)].string);
        CSSParser* p = static_cast<CSSParser*>(parser);
        Document* doc = p->document();
        if (doc && doc->isHTMLDocument())
            str.lower();
        (yyval.string) = str;
    ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1129 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->setAttribute(QualifiedName(nullAtom, (yyvsp[(3) - (4)].string), nullAtom));
        (yyval.selector)->m_match = CSSSelector::Set;
    ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1134 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->setAttribute(QualifiedName(nullAtom, (yyvsp[(3) - (8)].string), nullAtom));
        (yyval.selector)->m_match = (CSSSelector::Match)(yyvsp[(4) - (8)].integer);
        (yyval.selector)->m_value = (yyvsp[(6) - (8)].string);
    ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1140 "WebCore/css/CSSGrammar.y"
    {
        AtomicString namespacePrefix = (yyvsp[(3) - (5)].string);
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->setAttribute(QualifiedName(namespacePrefix, (yyvsp[(4) - (5)].string),
                                   p->m_styleSheet->determineNamespace(namespacePrefix)));
        (yyval.selector)->m_match = CSSSelector::Set;
    ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1148 "WebCore/css/CSSGrammar.y"
    {
        AtomicString namespacePrefix = (yyvsp[(3) - (9)].string);
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->setAttribute(QualifiedName(namespacePrefix, (yyvsp[(4) - (9)].string),
                                   p->m_styleSheet->determineNamespace(namespacePrefix)));
        (yyval.selector)->m_match = (CSSSelector::Match)(yyvsp[(5) - (9)].integer);
        (yyval.selector)->m_value = (yyvsp[(7) - (9)].string);
    ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1160 "WebCore/css/CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Exact;
    ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1163 "WebCore/css/CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::List;
    ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1166 "WebCore/css/CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Hyphen;
    ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1169 "WebCore/css/CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Begin;
    ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1172 "WebCore/css/CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::End;
    ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1175 "WebCore/css/CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Contain;
    ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1186 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PagePseudoClass;
        (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->m_value = (yyvsp[(2) - (2)].string);
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
    ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1197 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoClass;
        (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->m_value = (yyvsp[(2) - (2)].string);
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoEmpty ||
                 type == CSSSelector::PseudoFirstChild ||
                 type == CSSSelector::PseudoFirstOfType ||
                 type == CSSSelector::PseudoLastChild ||
                 type == CSSSelector::PseudoLastOfType ||
                 type == CSSSelector::PseudoOnlyChild ||
                 type == CSSSelector::PseudoOnlyOfType) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            Document* doc = p->document();
            if (doc)
                doc->setUsesSiblingRules(true);
        } else if (type == CSSSelector::PseudoFirstLine) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (Document* doc = p->document())
                doc->setUsesFirstLineRules(true);
        } else if (type == CSSSelector::PseudoBefore ||
                   type == CSSSelector::PseudoAfter) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (Document* doc = p->document())
                doc->setUsesBeforeAfterRules(true);
        } else if (type == CSSSelector::PseudoLink || type == CSSSelector::PseudoVisited) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (Document* doc = p->document())
                doc->setUsesLinkRules(true);
        }
    ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1231 "WebCore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoElement;
        (yyvsp[(3) - (3)].string).lower();
        (yyval.selector)->m_value = (yyvsp[(3) - (3)].string);
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoFirstLine) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (Document* doc = p->document())
                doc->setUsesFirstLineRules(true);
        } else if (type == CSSSelector::PseudoBefore ||
                   type == CSSSelector::PseudoAfter) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (Document* doc = p->document())
                doc->setUsesBeforeAfterRules(true);
        }
    ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1251 "WebCore/css/CSSGrammar.y"
    {
        CSSParser *p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoClass;
        (yyval.selector)->setArgument((yyvsp[(4) - (6)].string));
        (yyval.selector)->m_value = (yyvsp[(2) - (6)].string);
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoNthChild ||
                 type == CSSSelector::PseudoNthOfType ||
                 type == CSSSelector::PseudoNthLastChild ||
                 type == CSSSelector::PseudoNthLastOfType) {
            if (p->document())
                p->document()->setUsesSiblingRules(true);
        }
    ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1269 "WebCore/css/CSSGrammar.y"
    {
        CSSParser *p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoClass;
        (yyval.selector)->setArgument(String::number((yyvsp[(4) - (7)].integer) * (yyvsp[(5) - (7)].number)));
        (yyval.selector)->m_value = (yyvsp[(2) - (7)].string);
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoNthChild ||
                 type == CSSSelector::PseudoNthOfType ||
                 type == CSSSelector::PseudoNthLastChild ||
                 type == CSSSelector::PseudoNthLastOfType) {
            if (p->document())
                p->document()->setUsesSiblingRules(true);
        }
    ;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1287 "WebCore/css/CSSGrammar.y"
    {
        CSSParser *p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoClass;
        (yyval.selector)->setArgument((yyvsp[(4) - (6)].string));
        (yyvsp[(2) - (6)].string).lower();
        (yyval.selector)->m_value = (yyvsp[(2) - (6)].string);
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoNthChild ||
                 type == CSSSelector::PseudoNthOfType ||
                 type == CSSSelector::PseudoNthLastChild ||
                 type == CSSSelector::PseudoNthLastOfType) {
            if (p->document())
                p->document()->setUsesSiblingRules(true);
        }
    ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1306 "WebCore/css/CSSGrammar.y"
    {
        if (!(yyvsp[(4) - (6)].selector) || !(yyvsp[(4) - (6)].selector)->isSimple())
            (yyval.selector) = 0;
        else {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selector) = p->createFloatingSelector();
            (yyval.selector)->m_match = CSSSelector::PseudoClass;
            (yyval.selector)->setSimpleSelector(p->sinkFloatingSelector((yyvsp[(4) - (6)].selector)));
            (yyvsp[(2) - (6)].string).lower();
            (yyval.selector)->m_value = (yyvsp[(2) - (6)].string);
        }
    ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1321 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (1)].boolean);
    ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1324 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (2)].boolean);
        if ( (yyvsp[(2) - (2)].boolean) )
            (yyval.boolean) = (yyvsp[(2) - (2)].boolean);
    ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1329 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (1)].boolean);
    ;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1332 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1335 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1338 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (2)].boolean);
    ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1341 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (2)].boolean);
    ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1347 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (3)].boolean);
    ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1350 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1353 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1356 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1359 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1362 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (4)].boolean);
        if ((yyvsp[(2) - (4)].boolean))
            (yyval.boolean) = (yyvsp[(2) - (4)].boolean);
    ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1367 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (4)].boolean);
    ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1370 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (6)].boolean);
    ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1376 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
        CSSParser* p = static_cast<CSSParser*>(parser);
        if ((yyvsp[(1) - (5)].integer) && (yyvsp[(4) - (5)].valueList)) {
            p->m_valueList = p->sinkFloatingValueList((yyvsp[(4) - (5)].valueList));
            int oldParsedProperties = p->m_numParsedProperties;
            (yyval.boolean) = p->parseValue((yyvsp[(1) - (5)].integer), (yyvsp[(5) - (5)].boolean));
            if (!(yyval.boolean))
                p->rollbackLastProperties(p->m_numParsedProperties - oldParsedProperties);
            delete p->m_valueList;
            p->m_valueList = 0;
        }
    ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1390 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        p->m_valueList = new CSSParserValueList;
        p->m_valueList->addValue(p->sinkFloatingValue((yyvsp[(1) - (2)].value)));
        int oldParsedProperties = p->m_numParsedProperties;
        (yyval.boolean) = p->parseValue(CSSPropertyWebkitVariableDeclarationBlock, false);
        if (!(yyval.boolean))
            p->rollbackLastProperties(p->m_numParsedProperties - oldParsedProperties);
        delete p->m_valueList;
        p->m_valueList = 0;
    ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1402 "WebCore/css/CSSGrammar.y"
    {
        (yyval.boolean) = false;
    ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1406 "WebCore/css/CSSGrammar.y"
    {
        /* The default movable type template has letter-spacing: .none;  Handle this by looking for
        error tokens at the start of an expr, recover the expr and then treat as an error, cleaning
        up and deleting the shifted expr.  */
        (yyval.boolean) = false;
    ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1413 "WebCore/css/CSSGrammar.y"
    {
        /* When we encounter something like p {color: red !important fail;} we should drop the declaration */
        (yyval.boolean) = false;
    ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1418 "WebCore/css/CSSGrammar.y"
    {
        /* Handle this case: div { text-align: center; !important } Just reduce away the stray !important. */
        (yyval.boolean) = false;
    ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1423 "WebCore/css/CSSGrammar.y"
    {
        /* div { font-family: } Just reduce away this property with no value. */
        (yyval.boolean) = false;
    ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1428 "WebCore/css/CSSGrammar.y"
    {
        /* if we come across rules with invalid values like this case: p { weight: *; }, just discard the rule */
        (yyval.boolean) = false;
    ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1433 "WebCore/css/CSSGrammar.y"
    {
        /* if we come across: div { color{;color:maroon} }, ignore everything within curly brackets */
        (yyval.boolean) = false;
    ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1440 "WebCore/css/CSSGrammar.y"
    {
        (yyval.integer) = cssPropertyID((yyvsp[(1) - (2)].string));
    ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1446 "WebCore/css/CSSGrammar.y"
    { (yyval.boolean) = true; ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1447 "WebCore/css/CSSGrammar.y"
    { (yyval.boolean) = false; ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1451 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.valueList) = p->createFloatingValueList();
        (yyval.valueList)->addValue(p->sinkFloatingValue((yyvsp[(1) - (1)].value)));
    ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1456 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.valueList) = (yyvsp[(1) - (3)].valueList);
        if ((yyval.valueList)) {
            if ((yyvsp[(2) - (3)].character)) {
                CSSParserValue v;
                v.id = 0;
                v.unit = CSSParserValue::Operator;
                v.iValue = (yyvsp[(2) - (3)].character);
                (yyval.valueList)->addValue(v);
            }
            (yyval.valueList)->addValue(p->sinkFloatingValue((yyvsp[(3) - (3)].value)));
        }
    ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1470 "WebCore/css/CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1473 "WebCore/css/CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1476 "WebCore/css/CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1482 "WebCore/css/CSSGrammar.y"
    {
        (yyval.character) = '/';
    ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1485 "WebCore/css/CSSGrammar.y"
    {
        (yyval.character) = ',';
    ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1488 "WebCore/css/CSSGrammar.y"
    {
        (yyval.character) = 0;
  ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1494 "WebCore/css/CSSGrammar.y"
    { (yyval.value) = (yyvsp[(1) - (1)].value); ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1495 "WebCore/css/CSSGrammar.y"
    { (yyval.value) = (yyvsp[(2) - (2)].value); (yyval.value).fValue *= (yyvsp[(1) - (2)].integer); ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1496 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_STRING; ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1497 "WebCore/css/CSSGrammar.y"
    {
      (yyval.value).id = cssValueKeywordID((yyvsp[(1) - (2)].string));
      (yyval.value).unit = CSSPrimitiveValue::CSS_IDENT;
      (yyval.value).string = (yyvsp[(1) - (2)].string);
  ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1503 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_DIMENSION; ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1504 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(2) - (3)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_DIMENSION; ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1505 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_URI; ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1506 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_UNICODE_RANGE; ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1507 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (1)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_PARSER_HEXCOLOR; ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1508 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = CSSParserString(); (yyval.value).unit = CSSPrimitiveValue::CSS_PARSER_HEXCOLOR; ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1510 "WebCore/css/CSSGrammar.y"
    {
      (yyval.value) = (yyvsp[(1) - (1)].value);
  ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1513 "WebCore/css/CSSGrammar.y"
    {
      (yyval.value) = (yyvsp[(1) - (2)].value);
  ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1516 "WebCore/css/CSSGrammar.y"
    { /* Handle width: %; */
      (yyval.value).id = 0; (yyval.value).unit = 0;
  ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1522 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = true; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1523 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = false; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1524 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PERCENTAGE; ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1525 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PX; ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1526 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_CM; ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1527 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_MM; ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1528 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_IN; ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1529 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PT; ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1530 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PC; ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1531 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_DEG; ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1532 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_RAD; ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1533 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_GRAD; ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1534 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_TURN; ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1535 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_MS; ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1536 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_S; ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1537 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_HZ; ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1538 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_KHZ; ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1539 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_EMS; ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1540 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSParserValue::Q_EMS; ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1541 "WebCore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_EXS; ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1542 "WebCore/css/CSSGrammar.y"
    {
      (yyval.value).id = 0;
      (yyval.value).fValue = (yyvsp[(1) - (2)].number);
      (yyval.value).unit = CSSPrimitiveValue::CSS_REMS;
      CSSParser* p = static_cast<CSSParser*>(parser);
      if (Document* doc = p->document())
          doc->setUsesRemUnits(true);
  ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1553 "WebCore/css/CSSGrammar.y"
    {
      (yyval.value).id = 0;
      (yyval.value).string = (yyvsp[(1) - (1)].string);
      (yyval.value).unit = CSSPrimitiveValue::CSS_PARSER_VARIABLE_FUNCTION_SYNTAX;
  ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1561 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        CSSParserFunction* f = p->createFloatingFunction();
        f->name = (yyvsp[(1) - (5)].string);
        f->args = p->sinkFloatingValueList((yyvsp[(3) - (5)].valueList));
        (yyval.value).id = 0;
        (yyval.value).unit = CSSParserValue::Function;
        (yyval.value).function = f;
    ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1570 "WebCore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        CSSParserFunction* f = p->createFloatingFunction();
        f->name = (yyvsp[(1) - (3)].string);
        f->args = 0;
        (yyval.value).id = 0;
        (yyval.value).unit = CSSParserValue::Function;
        (yyval.value).function = f;
  ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1586 "WebCore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1587 "WebCore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1594 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1597 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1603 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1606 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1612 "WebCore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1630 "WebCore/css/CSSGrammar.y"
    {
        static_cast<CSSParser*>(parser)->invalidBlockHit();
    ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1633 "WebCore/css/CSSGrammar.y"
    {
        static_cast<CSSParser*>(parser)->invalidBlockHit();
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 4696 "WebCore/DerivedSources/CSSGrammar.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1643 "WebCore/css/CSSGrammar.y"


