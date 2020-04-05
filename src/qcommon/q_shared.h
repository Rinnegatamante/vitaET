/*
 * Wolfenstein: Enemy Territory GPL Source Code
 * Copyright (C) 1999-2010 id Software LLC, a ZeniMax Media company.
 *
 * ET: Legacy
 * Copyright (C) 2012-2018 ET:Legacy team <mail@etlegacy.com>
 *
 * This file is part of ET: Legacy - http://www.etlegacy.com
 *
 * ET: Legacy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ET: Legacy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ET: Legacy. If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, Wolfenstein: Enemy Territory GPL Source Code is also
 * subject to certain additional terms. You should have received a copy
 * of these additional terms immediately following the terms and conditions
 * of the GNU General Public License which accompanied the source code.
 * If not, please request a copy in writing from id Software at the address below.
 *
 * id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
 */
/**
 * @file q_shared.h
 * @brief Included first by ALL program modules.
 *        A user mod should never modify this file
 */

#ifndef INCLUDE_Q_SHARED_H
#define INCLUDE_Q_SHARED_H

#define PRODUCT_NAME            "etlegacy"
#define PRODUCT_LABEL           "ET Legacy"
#define ETLEGACY_VERSION        "2.76"
#define CPUSTRING               "Cortex A9"
#define CLIENT_WINDOW_TITLE     PRODUCT_LABEL
#define CLIENT_WINDOW_MIN_TITLE PRODUCT_LABEL

#define Q3_VERSION              PRODUCT_LABEL " " ETLEGACY_VERSION

#ifdef LEGACY_DEBUG
#define ET_VERSION              Q3_VERSION " " CPUSTRING " " __DATE__ " DEBUG"
#else
#define ET_VERSION              Q3_VERSION " " CPUSTRING " " __DATE__
#endif

#ifdef __APPLE__
#define FAKE_VERSION            "ET 2.60d OSX-universal JAN 20 2007" ///< ET 2.60c OSX-universal JAN 16 2007
#else
#define FAKE_VERSION            "ET 2.60b " CPUSTRING " May  8 2006"
#endif

#ifdef DEDICATED
#define CONFIG_NAME             "etconfig_server.cfg"
#else
#define CONFIG_NAME             "etconfig.cfg"
// widescreen monitor support
#define RATIO43     (4.0f / 3.0f)   ///< 4:3 aspectratio is the default for this game engine ...
#define RPRATIO43   (1 / RATIO43)   ///<
#endif

#define CONFIG_NAME_DEFAULT      "default.cfg"         ///< if you change this adjust files.c - name ist still hard coded in pk3 checks
#define CONFIG_NAME_DEFAULT_LEFT "default_left.cfg"

#define DEMOEXT "dm_"          ///< standard demo extension
#define SVDEMOEXT "sv_"        ///< standard server demo extension

#define MAX_MASTER_SERVERS 5   ///< number of supported master servers

#define SLASH_COMMAND 1        ///< Will the client require a '/' sign in front of commands

/// Added after 272 release these are used by mod code
#define MOD_VERSION_DATA_CHECK(x) (x && x >= 272 && x < 3000)
#define MOD_CHECK_LEGACY(islegacy, versionNum, outputValue) outputValue = (islegacy == qtrue ? qtrue : qfalse); \
	if (outputValue && MOD_VERSION_DATA_CHECK(versionNum)) { outputValue = versionNum; }

#ifdef _MSC_VER
#pragma warning(disable : 4018) // signed/unsigned mismatch
#pragma warning(disable : 4068) // unknown pragma warning
#pragma warning(disable : 4244) // number conversion (possible loss of data)
#pragma warning(disable : 4305) // truncation from const double to float
#pragma warning(disable : 4711) // selected for automatic inline expansion
#pragma warning(disable : 4996) // deprecated POSIX function names
#endif

// Ignore __attribute__ on non-gcc platforms
#ifndef __GNUC__
#ifndef __attribute__
#define __attribute__(x)
#endif
#endif

#ifdef __GNUC__
#define UNUSED_VAR __attribute__((unused))
#else
#define UNUSED_VAR
#endif

#if (defined _MSC_VER)
#define Q_EXPORT __declspec(dllexport)
#elif (defined __SUNPRO_C)
#define Q_EXPORT __global
#elif ((__GNUC__ >= 3) && (!__EMX__) && (!sun))
#define Q_EXPORT __attribute__((visibility("default")))
#else
#define Q_EXPORT
#endif

// FIXME: required for MinGW. Find a better way to handle this (<float.h>?)
#ifdef __MINGW32__
#   ifndef FLT_EPSILON
#       define FLT_EPSILON __FLT_EPSILON__
#   endif
#endif

/**********************************************************************
  VM Considerations

  The VM can not use the standard system headers because we aren't really
  using the compiler they were meant for.  We use bg_lib.h which contains
  prototypes for the functions we define for our own use in bg_lib.c.

  When writing mods, please add needed headers HERE, do not start including
  stuff like <stdio.h> in the various .c files that make up each of the VMs
  since you will be including system headers files can will have issues.

  Remember, if you use a C library function that is not defined in bg_lib.c,
  you will have to add your own version for support in the VM.

 **********************************************************************/

#ifdef Q3_VM

#include "bg_lib.h"

typedef int intptr_t;

#else

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <sys/stat.h>
#include <float.h>

#if defined (_MSC_VER) && (_MSC_VER >= 1600)
#include <stdint.h>

// vsnprintf is ISO/IEC 9899:1999
// abstracting this to make it portable
int Q_vsnprintf(char *str, size_t size, const char *format, va_list args);
#elif defined (_MSC_VER)
#include <io.h>

typedef signed __int64 int64_t;
typedef signed __int32 int32_t;
typedef signed __int16 int16_t;
typedef signed __int8 int8_t;
typedef unsigned __int64 uint64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;

// vsnprintf is ISO/IEC 9899:1999
// abstracting this to make it portable
int Q_vsnprintf(char *str, size_t size, const char *format, va_list args);
#else // not using MSVC
#include <stdint.h>
#define Q_vsnprintf vsnprintf
#endif // defined (_MSC_VER) && (_MSC_VER >= 1600)
#endif // Q3_VM

#include "q_platform.h"

//======================= WIN32 DEFINES =================================

#ifdef _WIN32

#undef QDECL
#define QDECL   __cdecl

/**
 * @def CPUSTRING
 * @brief Platform and architecture string incorporated into the version string.
 *
 * To maintain compatibility with ET 2.60b mods these values must be set:
 *      windows: win-x86
 *      linux:   linux-i386
 *      mac:     ?
 *
 * See FAKE_VERSION
 */
#ifdef _WIN64
#define CPUSTRING   "win-x64"
#else
#define CPUSTRING   "win-x86"
#endif

#define PATH_SEP '\\'

#endif // _WIN32

//======================= MAC OS X DEFINES =====================

#if defined(__APPLE__)

#define CPUSTRING   "MacOS_X" // TODO: check if some mods depend on the old Mac CPUSTRING
// #define CPUSTRING   "OSX-universal" // old

#define PATH_SEP    '/'

/*

// Vanilla PPC code, but since PPC has a reciprocal square root estimate instruction,
// runs *much* faster than calling sqrt(). We'll use two Newton-Raphson
// refinement steps to get bunch more precision in the 1/sqrt() value for very little cost.
// We'll then multiply 1/sqrt times the original value to get the sqrt.
// This is about 12.4 times faster than sqrt() and according to my testing (not exhaustive)
// it returns fairly accurate results (error below 1.0e-5 up to 100000.0 in 0.1 increments).

// Note ET:L uses BSD Library functions for this

static ID_INLINE float idSqrt(float x)
{
    const float half = 0.5;
    const float one  = 1.0;
    float       B, y0, y1;

    // This'll NaN if it hits frsqrte. Handle both +0.0 and -0.0
    if (Q_fabs(x) == 0.0)
    {
        return x;
    }
    B = x;

#ifdef __GNUC__
    asm ("frsqrte %0,%1" : "=f" (y0) : "f" (B));
#else
    y0 = __frsqrte(B);
#endif
    // First refinement step

    y1 = y0 + half * y0 * (one - B * y0 * y0);

    // Second refinement step -- copy the output of the last step to the input of this step

    y0 = y1;
    y1 = y0 + half * y0 * (one - B * y0 * y0);

    // Get sqrt(x) from x * 1/sqrt(x)
    return x * y1;
}
#define sqrt idSqrt
*/

#endif // defined(__APPLE__)

//======================= LINUX DEFINES =================================

// the mac compiler can't handle >32k of locals, so we
// just waste space and make big arrays static...
#ifdef __linux__

#ifdef __i386__
#define CPUSTRING   "linux-i386"
#elif defined __x86_64__
#define CPUSTRING   "linux-x86_64"
#elif defined __axp__
#define CPUSTRING   "linux-alpha"
#elif defined ARM
#define CPUSTRING   "linux-arm"
#else
#define CPUSTRING   "linux-other"
#endif

#define PATH_SEP '/'

#endif // __linux__

//======================= OPENBSD DEFINES =================================

// the mac compiler can't handle >32k of locals, so we
// just waste space and make big arrays static...
#ifdef __OpenBSD__

#ifdef __i386__
#define CPUSTRING   "openbsd-i386"
#elif defined __x86_64__
#define CPUSTRING   "openbsd-x86_64"
#else
#define CPUSTRING   "openbsd-other"
#endif

#define PATH_SEP '/'

#endif // __OpenBSD__

//======================= FREEBSD DEFINES =================================

// the mac compiler can't handle >32k of locals, so we
// just waste space and make big arrays static...
#ifdef __FreeBSD__

#ifdef __i386__
#define CPUSTRING   "freebsd-i386"
#elif defined __x86_64__
#define CPUSTRING   "freebsd-x86_64"
#else
#define CPUSTRING   "freebsd-other"
#endif

#define PATH_SEP '/'

#endif // __FreeBSD__

//======================= NETBSD DEFINES =================================

// the mac compiler can't handle >32k of locals, so we
// just waste space and make big arrays static...
#ifdef __NetBSD__

#ifdef __i386__
#define CPUSTRING   "netbsd-i386"
#elif defined __x86_64__
#define CPUSTRING   "netbsd-x86_64"
#else
#define CPUSTRING   "netbsd-other"
#endif

#define PATH_SEP '/'

#endif //  __NetBSD__

//=============================================================

typedef unsigned char byte;

/**
 * @enum qboolean
 * @brief Boolean definition
 */
typedef enum { qfalse, qtrue }    qboolean;

/**
 * @union floatint_t
 * @brief
 */
typedef union
{
	float f;
	int i;
	unsigned int ui;
} floatint_t;

typedef int qhandle_t;
typedef int sfxHandle_t;
typedef int fileHandle_t;
typedef int clipHandle_t;

#define PAD(base, alignment)    (((base) + (alignment) - 1) & ~((alignment) - 1))
#define PADLEN(base, alignment) (PAD((base), (alignment)) - (base))

#define PADP(base, alignment)   ((void *) PAD((intptr_t) (base), (alignment)))

#ifdef __GNUC__
#define QALIGN(x) __attribute__((aligned(x)))
#else
#define QALIGN(x)
#endif

#ifndef BIT
#ifdef _WIN64
#define BIT(x)              (1i64 << x)
#else
#define BIT(x)              (1 << x)
#endif
#endif

#define SIZE_KB(bytes) ((bytes) >> 10)
#define SIZE_MB(bytes) ((bytes) >> 20)
#define SIZE_GB(bytes) ((bytes) >> 30)

#define SIZE_KB_FLOAT(bytes) ((bytes) * (1.0f / 1024.0f))
#define SIZE_MB_FLOAT(bytes) ((bytes) * (1.0f / 1048576.0f))
#define SIZE_GB_FLOAT(bytes) ((bytes) * (1.0f / 1073741824.0f))

#define ENABLEBIT(x, y) x |= BIT(y)
#define CLEARBIT(x, y) x  &= ~BIT(y)
#define TOGGLEBIT(x, y) x ^= BIT(y)
#define CHECKBIT(x, y) (x & BIT(y))

/**
 * @def Check whether input value is present or not in given bitwise.
 */
#define CHECKBITWISE(x, y) (((x) & (y)) == (y))

//#define   SND_NORMAL          0x000   ///< (default) Allow sound to be cut off only by the same sound on this channel
#define     SND_OKTOCUT         0x001   ///< Allow sound to be cut off by any following sounds on this channel
#define     SND_REQUESTCUT      0x002   ///< Allow sound to be cut off by following sounds on this channel only for sounds who request cutoff
#define     SND_CUTOFF          0x004   ///< Cut off sounds on this channel that are marked 'SND_REQUESTCUT'
#define     SND_CUTOFF_ALL      0x008   ///< Cut off all sounds on this channel
#define     SND_NOCUT           0x010   ///< Don't cut off.  Always let finish (overridden by SND_CUTOFF_ALL)
#define     SND_NO_ATTENUATION  0x020   ///< don't attenuate (even though the sound is in voice channel, for example)

#ifndef NULL
#define NULL ((void *)0)
#endif

#define STRING(s)           # s
// expand constants before stringifying them
#define XSTRING(s)          STRING(s)

#define MAX_QINT            0x7fffffff
#define MIN_QINT            (-MAX_QINT - 1)

#define ARRAY_LEN(x)        (sizeof(x) / sizeof(*(x)))
#define STRARRAY_LEN(x)     (ARRAY_LEN(x) - 1)

// angle indexes
#define PITCH               0       ///< up / down
#define YAW                 1       ///< left / right
#define ROLL                2       ///< fall over

// the game guarantees that no string from the network will ever
// exceed MAX_STRING_CHARS
#define MAX_STRING_CHARS    1024    ///< max length of a string passed to Cmd_TokenizeString
#define MAX_STRING_TOKENS   256     ///< max tokens resulting from Cmd_TokenizeString
#define MAX_TOKEN_CHARS     1024    ///< max length of an individual token

#define MAXPRINTMSG 4096 ///< max string you can send to a Com_Printf / Com_DPrintf (above gets truncated)

#define MAX_INFO_STRING     1024
#define MAX_INFO_KEY        1024
#define MAX_INFO_VALUE      1024

#define BIG_INFO_STRING     8192    ///< used for system info key only
#define BIG_INFO_KEY        8192
#define BIG_INFO_VALUE      8192

#define MAX_QPATH           64      ///< max length of a quake game pathname
#define MAX_OSPATH          256     ///< max length of a filesystem pathname
#define MAX_CMD             1024    ///< max length of a command line

#define MAX_IP4_LENGTH      16      ///< 15 + 1 (string terminator)
#define MAX_GUID_LENGTH     32

// increased to 36 to match MAX_NETNAME
// UI stuff breaks with very long names
#define MAX_NAME_LENGTH            36   ///< max length of a client name
#define MAX_SERVER_NAME_LENGTH     72   ///< max length of a server name

#define MAX_SAY_TEXT        150     ///< max length of a chat message

#define MAX_BINARY_MESSAGE  32768   ///< max length of binary message

#define MAX_VA_STRING       32000

/**
 * @enum messageStatus_t
 * @brief
 */
typedef enum
{
	MESSAGE_EMPTY = 0,
	MESSAGE_WAITING,            ///< rate/packet limited
	MESSAGE_WAITING_OVERFLOW,   ///< packet too large with message
} messageStatus_t;

/**
 * @enum cbufExec_t
 * @brief Parameters for command buffer stuffing
 */
typedef enum
{
	EXEC_NOW,           ///< don't return until completed, a VM should NEVER use this,
	                    ///< because some commands might cause the VM to be unloaded...
	EXEC_INSERT,        ///< insert at current position, but don't run yet
	EXEC_APPEND         ///< add to end of the command buffer (normal case)
} cbufExec_t;

/// these aren't needed by any of the VMs.  put in another header?
#define MAX_MAP_AREA_BYTES      32      ///< bit vector of area visibility

/**
 * @enum printParm_t
 * @brief print levels from renderer (FIXME: set up for game / cgame?)
 */
typedef enum
{
	PRINT_ALL,
	PRINT_DEVELOPER,        ///< only print when "developer 1"
	PRINT_WARNING,
	PRINT_ERROR
} printParm_t;

#ifdef  ERR_FATAL
#undef  ERR_FATAL               // this is be defined in malloc.h
#endif

/**
 * @enum errorParm_t
 *
 * @brief Parameters to the main Error routine
 */
typedef enum
{
	ERR_FATAL,                  ///< exit the entire game with a popup window
	ERR_VID_FATAL,              ///< exit the entire game with a popup window and doesn't delete profile.pid
	ERR_DROP,                   ///< print to console and disconnect from game
	ERR_SERVERDISCONNECT,       ///< don't kill server
	ERR_DISCONNECT,             ///< client disconnected from the server
	ERR_AUTOUPDATE
} errorParm_t;

// font rendering values used by ui and cgame

#define PROP_GAP_WIDTH          3
#define PROP_SPACE_WIDTH        8
#define PROP_HEIGHT             27
#define PROP_SMALL_SIZE_SCALE   0.75

#define BLINK_DIVISOR           200
#define PULSE_DIVISOR           75.0

#define UI_LEFT         0x00000000      ///< default
#define UI_CENTER       0x00000001
#define UI_RIGHT        0x00000002
#define UI_FORMATMASK   0x00000007
#define UI_SMALLFONT    0x00000010
#define UI_BIGFONT      0x00000020      ///< default
//#define UI_GIANTFONT    0x00000040
#define UI_DROPSHADOW   0x00000800
//#define UI_BLINK        0x00001000
#define UI_INVERSE      0x00002000
#define UI_PULSE        0x00004000
//#define UI_MENULEFT     0x00008000
//#define UI_MENURIGHT    0x00010000
#define UI_EXSMALLFONT  0x00020000
//#define UI_MENUFULL     0x00080000
//#define UI_SMALLFONT75  0x00100000

#ifdef LEGACY_DEBUG
#define HUNK_DEBUG
#endif

/**
 * @enum ha_pref
 * @brief
 */
typedef enum
{
	h_high,
	h_low,
	h_dontcare
} ha_pref;

#ifdef HUNK_DEBUG
#define Hunk_Alloc(size, preference)              Hunk_AllocDebug(size, preference, # size, __FILE__, __LINE__)
void *Hunk_AllocDebug(unsigned int size, ha_pref preference, char *label, char *file, int line);
#else
void *Hunk_Alloc(unsigned int size, ha_pref preference);
#endif

#define Com_Memset memset
#define Com_Memcpy memcpy

#define Com_Allocate malloc
#define Com_Dealloc free

/**
 * @enum CIN_Flags
 * @brief
 */
typedef enum
{
	CIN_system = BIT(0),
	CIN_loop   = BIT(1),
	CIN_hold   = BIT(2),
	CIN_silent = BIT(3),
	CIN_shader = BIT(4)
} CIN_Flags;

/*
==============================================================
MATHLIB
==============================================================
*/

#include "q_math.h"

//=============================================

qboolean Com_PowerOf2(int x);

#define Com_ByteClamp(x) ((x < 0) ? 0 : (x > 255) ? 255 : x)
#define Com_Clamp(min, max, value) ((value < min) ? min : (value > max) ? max : value)
#define Com_Nelem(a) (int)(sizeof(a) / sizeof(a)[0])
void *Com_AnyOf(void **ptr, int n);

char *COM_SkipPath(char *pathname);
void COM_FixPath(char *pathname);
const char *COM_GetExtension(const char *name);
void COM_StripExtension(const char *in, char *out, int destsize);
qboolean COM_CompareExtension(const char *in, const char *ext);
void COM_StripFilename(const char *in, char *out);

void COM_DefaultExtension(char *path, size_t maxSize, const char *extension);

void COM_BeginParseSession(const char *name);
void COM_RestoreParseSession(char **data_p);
void COM_SetCurrentParseLine(int line);
int COM_GetCurrentParseLine(void);
char *COM_Parse(char **data_p);
char *COM_ParseExt(char **data_p, qboolean allowLineBreaks);

/// added COM_Parse2 for having a Doom 3 style tokenizer.
char *COM_Parse2(char **data_p);
char *COM_ParseExt2(char **data_p, qboolean allowLineBreaks);

int COM_Compress(char *data_p);
void COM_ParseError(const char *format, ...) __attribute__ ((format(printf, 1, 2)));
//void COM_ParseWarning(const char *format, ...) __attribute__ ((format(printf, 1, 2))); // Unused

qboolean COM_BitCheck(const int array[], unsigned int bitNum);
void COM_BitSet(int array[], unsigned int bitNum);
void COM_BitClear(int array[], unsigned int bitNum);

#define MAX_TOKENLENGTH     1024

#ifndef TT_STRING
//token types
#define TT_STRING                   1           ///< string
#define TT_LITERAL                  2           ///< literal
#define TT_NUMBER                   3           ///< number
#define TT_NAME                     4           ///< name
#define TT_PUNCTUATION              5           ///< punctuation
#endif

/**
 * @struct pc_token_s
 * @typedef pc_token_t
 * @brief
 */
typedef struct pc_token_s
{
	int type;
	int subtype;
	int intvalue;
	float floatvalue;
	char string[MAX_TOKENLENGTH];
	int line;
	int linescrossed;
} pc_token_t;

// data is an in/out parm, returns a parsed out token

//void COM_MatchToken(char **buf_p, char *match);

void SkipBracedSection(char **program);
void SkipBracedSection_Depth(char **program, int depth);    ///< start at given depth if already
void SkipRestOfLine(char **data);

void Parse1DMatrix(char **buf_p, int x, float *m);
void Parse2DMatrix(char **buf_p, int y, int x, float *m);
void Parse3DMatrix(char **buf_p, int z, int y, int x, float *m);

int QDECL Com_sprintf(char *dest, unsigned int size, const char *fmt, ...) __attribute__ ((format(printf, 3, 4)));

char *Com_SkipTokens(char *s, int numTokens, const char *sep);
char *Com_SkipCharset(char *s, char *sep);

/**
 * @enum fsMode_t
 * @brief Mode parm for FS_FOpenFile
 */
typedef enum
{
	FS_READ,
	FS_WRITE,
	FS_APPEND,
	FS_APPEND_SYNC
} fsMode_t;

/**
 * @enum fsOrigin_t
 * @brief
 */
typedef enum
{
	FS_SEEK_CUR,
	FS_SEEK_END,
	FS_SEEK_SET
} fsOrigin_t;

int Com_HexStrToInt(const char *str);

//=============================================

int Q_isprint(int c);
int Q_islower(int c);
int Q_isupper(int c);
int Q_isalpha(int c);
int Q_isnumeric(int c);
int Q_isalphanumeric(int c);
qboolean Q_isanumber(const char *s);
qboolean Q_isintegral(float f);
int Q_isforfilename(int c);

// portable case insensitive compare
int Q_stricmp(const char *s1, const char *s2);
int Q_strncmp(const char *s1, const char *s2, size_t n);
int Q_stricmpn(const char *s1, const char *s2, size_t n);
char *Q_strlwr(char *s1);
char *Q_strupr(char *s1);
const char *Q_stristr(const char *s, const char *find);

#define Q_strcpy(dest, src) strcpy(dest, src)

/// buffer size safe library replacements
void Q_strncpyz(char *dest, const char *src, size_t destsize);

/// buffer size safe library replacements
void Q_strcat(char *dest, size_t size, const char *src);

/// strlen that discounts Quake color sequences
int Q_PrintStrlen(const char *string);

/// Encodes a plain un-colored string so that it'll be drawn with the given color code.
void Q_ColorizeString(char colorCode, const char *inStr, char *outStr, size_t outBufferLen);

/// removes color sequences from string
char *Q_CleanStr(char *string);

/// removes color sequences from string using multiple passes
void Q_StripColor(char *string);

/// Count the number of char tocount encountered in string
int Q_CountChar(const char *string, char tocount);

/// removes whitespaces and other bad directory characters
char *Q_CleanDirName(char *dirname);

/// replace all occuraces in haystack if needle with new
char *Q_StrReplace(char *haystack, const char *needle, const char *newVal);

/// generate hashvalue from filename for set hashmap size
long Q_GenerateHashValue(const char *fname, int size, qboolean fullPath, qboolean ignoreCase);

//=============================================

float *tv(float x, float y, float z);

#define rc(x) va("%s^7", x) ///< shortcut for color reset after printing variable

//char *QDECL va(char *format, ...) __attribute__ ((format(printf, 1, 2)));
char *QDECL va(const char *format, ...) __attribute__ ((format(printf, 1, 2)));

#define TRUNCATE_LENGTH 64
void Com_TruncateLongString(char *buffer, const char *s);

//=============================================

// key / value info strings
char *Info_ValueForKey(const char *s, const char *key);
void Info_RemoveKey(char *s, const char *key);
void Info_RemoveKey_big(char *s, const char *key);
void Info_SetValueForKey(char *s, const char *key, const char *value);
void Info_SetValueForKey_Big(char *s, const char *key, const char *value);
qboolean Info_Validate(const char *s);
qboolean Info_NextPair(const char **head, char *key, char *value);

// this is only here so the functions in q_shared.c and bg_*.c can link
void QDECL Com_Error(int code, const char *fmt, ...) __attribute__ ((noreturn, format(printf, 2, 3)));
void QDECL Com_Printf(const char *fmt, ...) __attribute__ ((format(printf, 1, 2)));

/*
==========================================================
CVARS (console variables)

Many variables can be used for cheating purposes, so when
cheats is zero, force all unspecified variables to their
default values.
==========================================================
*/

#define CVAR_ARCHIVE        1                    ///< set to cause it to be saved to vars.rc
                                                 ///< used for system variables, not for player
                                                 ///< specific configurations
#define CVAR_USERINFO       2                    ///< sent to server on connect or change
#define CVAR_SERVERINFO     4                    ///< sent in response to front end requests
#define CVAR_SYSTEMINFO     8                    ///< these cvars will be duplicated on all clients
#define CVAR_INIT           16                   ///< don't allow change from console at all,
                                                 ///< but can be set from the command line
#define CVAR_LATCH          32                   ///< will only change when C code next does
                                                 ///< a Cvar_Get(), so it can't be changed without proper initialization.
                                                 ///< will be set, even though the value hasn't changed yet
#define CVAR_ROM                    64           ///< display only, cannot be set by user at all
#define CVAR_USER_CREATED           128          ///< created by a set command
#define CVAR_TEMP                   256          ///< can be set even when cheats are disabled, but is not archived
#define CVAR_CHEAT                  512          ///< can not be changed if cheats are disabled
#define CVAR_NORESTART              1024         ///< do not clear when a cvar_restart is issued
#define CVAR_WOLFINFO               2048         ///< like userinfo, but for wolf multiplayer info
#define CVAR_UNSAFE                 4096         ///< unsafe system cvars (renderer, sound settings, anything that might cause a crash)
#define CVAR_SERVERINFO_NOUPDATE    8192         ///< WONT automatically send this to clients, but server browsers will see it
#define CVAR_SERVER_CREATED         16384        ///< cvar was created by a server the client connected to.
#define CVAR_VM_CREATED             32768        ///< cvar was created exclusively in one of the VMs.
#define CVAR_PROTECTED              65536        ///< prevent modifying this var from VMs or the server
#define CVAR_SHADER                 131072       ///< we need to recompile the glsl shaders
#define CVAR_MODIFIED               1073741824   ///< Cvar was modified
#define CVAR_NONEXISTENT            2147483648U  ///< Cvar doesn't exist.

/**
 * @struct cvar_s
 * @typedef cvar_t
 * @brief
 *
 * @note Nothing outside the Cvar_*() functions should modify these fields!
 */
typedef struct cvar_s
{
	char *name;
	char *string;
	char *resetString;              ///< cvar_restart will reset to this value
	char *latchedString;            ///< for CVAR_LATCH vars
	int flags;
	qboolean modified;              ///< set each time the cvar is changed
	int modificationCount;          ///< incremented each time the cvar is changed
	float value;                    ///< atof( string )
	int integer;                    ///< atoi( string )
	qboolean validate;
	qboolean integral;
	float min;
	float max;
	char *description;

	struct cvar_s *next;
	struct cvar_s *prev;
	struct cvar_s *hashNext;
	struct cvar_s *hashPrev;
	int hashIndex;
} cvar_t;

#define MAX_CVAR_VALUE_STRING   256

typedef int cvarHandle_t;

/**
 * @struct vmCvar_t
 * @brief The modules that run in the virtual machine can't access the cvar_t directly,
 * so they must ask for structured updates
 */
typedef struct
{
	cvarHandle_t handle;
	int modificationCount;
	float value;
	int integer;
	char string[MAX_CVAR_VALUE_STRING];
} vmCvar_t;

/*
==============================================================
COLLISION DETECTION
==============================================================
*/

#include "../game/surfaceflags.h"

// plane types are used to speed some tests
// 0-2 are axial planes
#define PLANE_X             0
#define PLANE_Y             1
#define PLANE_Z             2
#define PLANE_NON_AXIAL     3
#define PLANE_NON_PLANAR    4

/*
=================
PlaneTypeForNormal
=================
*/

//#define PlaneTypeForNormal(x) (x[0] == 1.0 ? PLANE_X : (x[1] == 1.0 ? PLANE_Y : (x[2] == 1.0 ? PLANE_Z : PLANE_NON_AXIAL) ) )
#define PlaneTypeForNormal(x) (x[0] == 1.0f ? PLANE_X : (x[1] == 1.0f ? PLANE_Y : (x[2] == 1.0f ? PLANE_Z : (x[0] == 0.f && x[1] == 0.f && x[2] == 0.f ? PLANE_NON_PLANAR : PLANE_NON_AXIAL))))

/**
 * @struct cplane_s
 * @typedef cplane_t
 * @brief
 *
 * @note !!! if this is changed, it must be changed in asm code too !!!
 */
typedef struct cplane_s
{
	vec3_t normal;
	float dist;
	byte type;              ///< for fast side tests: 0,1,2 = axial, 3 = nonaxial
	byte signbits;          ///< signx + (signy<<1) + (signz<<2), used as lookup during collision
	byte pad[2];
} cplane_t;

/**
 * @struct trace_t
 * @brief A trace is returned when a box is swept through the world
 */
typedef struct
{
	qboolean allsolid;      ///< if true, plane is not valid
	qboolean startsolid;    ///< if true, the initial point was in a solid area
	float fraction;         ///< time completed, 1.0 = didn't hit anything
	vec3_t endpos;          ///< final position
	cplane_t plane;         ///< surface normal at impact, transformed to world space
	int surfaceFlags;       ///< surface hit
	int contents;           ///< contents on other side of surface hit
	int entityNum;          ///< entity the contacted sirface is a part of
} trace_t;

// trace->entityNum can also be 0 to (MAX_GENTITIES-1)
// or ENTITYNUM_NONE, ENTITYNUM_WORLD

// markfragments are returned by re.MarkFragments()

/**
 * @struct markFragment_t
 */
typedef struct
{
	int firstPoint;
	int numPoints;
} markFragment_t;

/**
 * @struct orientation_t
 */
typedef struct
{
	vec3_t origin;
	vec3_t axis[3];
} orientation_t;

//=====================================================================

// in order from highest priority to lowest
// if none of the catchers are active, bound key strings will be executed
#define KEYCATCH_CONSOLE        0x0001
#define KEYCATCH_UI             0x0002
//#define KEYCATCH (unused)     0x0004
#define KEYCATCH_CGAME          0x0008

/**
 * @enum soundChannel_t
 *
 * @brief sound channels
 * channel 0 never willingly overrides
 * other channels will allways override a playing sound on that channel
 */
typedef enum
{
	CHAN_AUTO,
	CHAN_LOCAL,         ///< menu sounds, etc
	CHAN_WEAPON,
	CHAN_VOICE,
	CHAN_ITEM,
	CHAN_BODY,
	CHAN_LOCAL_SOUND,   ///< chat messages, etc
	CHAN_ANNOUNCER,     ///< announcer voices, etc
	CHAN_VOICE_BG,      ///< unused. Background sound for voice (radio static, etc.)
} soundChannel_t;

/*
========================================================================
  ELEMENTS COMMUNICATED ACROSS THE NET
========================================================================
*/
#define ANIM_BITS       10

#define ANGLE2SHORT(x)  ((int)((x) * 65536 / 360) & 65535)
#define SHORT2ANGLE(x)  ((x) * (360.0f / 65536))

#define SNAPFLAG_RATE_DELAYED   1
#define SNAPFLAG_NOT_ACTIVE     2   ///< snapshot used during connection and for zombies
#define SNAPFLAG_SERVERCOUNT    4   ///< toggled every map_restart so transitions can be detected

// per-level limits
#define MAX_CLIENTS         64      ///< back to q3ta default was 128        // absolute limit

#define GENTITYNUM_BITS     10      ///< put q3ta default back for testing  // don't need to send any more
#define MAX_GENTITIES       (1 << GENTITYNUM_BITS)

// entitynums are communicated with GENTITY_BITS, so any reserved
// values thatare going to be communcated over the net need to
// also be in this range
#define ENTITYNUM_NONE      (MAX_GENTITIES - 1)
#define ENTITYNUM_WORLD     (MAX_GENTITIES - 2)
#define ENTITYNUM_MAX_NORMAL    (MAX_GENTITIES - 2)

#define NULL_MODEL          0

#define MAX_MODELS          256     // these are sent over the net as 8 bits (upped to 9 bits, erm actually it was already at 9 bits, wtf? NEVAR TRUST GAMECODE COMMENTS, comments are evil :E, lets hope it doesn't horribly break anything....)
#define MAX_SOUNDS          256     // so they cannot be blindly increased
#define MAX_CS_SKINS        64
#define MAX_CSSTRINGS       32

#define MAX_CS_SHADERS      32
#define MAX_SERVER_TAGS     256
#define MAX_TAG_FILES       64

#define MAX_MULTI_SPAWNTARGETS  16

#define MAX_CONFIGSTRINGS   1024

#define MAX_DLIGHT_CONFIGSTRINGS    16
#define MAX_SPLINE_CONFIGSTRINGS    8

// these are the only configstrings that the system reserves, all the
// other ones are strictly for servergame to clientgame communication
#define CS_SERVERINFO       0       ///< an info string with all the serverinfo cvars
#define CS_SYSTEMINFO       1       ///< an info string for server system to client system configuration (timescale, etc)

#define RESERVED_CONFIGSTRINGS  2   ///< game can't modify below this, only the system can

#define MAX_GAMESTATE_CHARS 16000

/**
 * @struct gameState_t
 * @brief
 */
typedef struct
{
	int stringOffsets[MAX_CONFIGSTRINGS];
	char stringData[MAX_GAMESTATE_CHARS];
	int dataCount;
} gameState_t;

/**
 * @struct aistateEnum_t
 * @brief
 */
typedef enum
{
	AISTATE_RELAXED,
	AISTATE_QUERY,
	AISTATE_ALERT,
	AISTATE_COMBAT,

	MAX_AISTATES
} aistateEnum_t;

#define REF_FORCE_DLIGHT    (1 << 31)   ///< passed in through overdraw parameter, force this dlight under all conditions
#define REF_JUNIOR_DLIGHT   (1 << 30)   ///< this dlight does not light surfaces.  it only affects dynamic light grid
#define REF_DIRECTED_DLIGHT (1 << 29)   ///< global directional light, origin should be interpreted as a normal vector

// bit field limits
#define MAX_STATS               16
#define MAX_PERSISTANT          16
#define MAX_POWERUPS            16
#define MAX_HOLDABLE            16
#define MAX_WEAPONS             64

#define MAX_EVENTS              4   ///< max events per frame before we drop events

#define PS_PMOVEFRAMECOUNTBITS  6

/**
 * @struct playerState_s
 * @typedef playerState_t
 * @brief playerState_t is the information needed by both the client and server
 * to predict player motion and actions
 * nothing outside of pmove should modify these, or some degree of prediction error
 * will occur
 *
 * you can't add anything to this without modifying the code in msg.c
 * (unless it doesnt need transmitted over the network, in which case it should
 * prolly go in the new pmext struct anyway)
 *
 * playerState_t is a full superset of entityState_t as it is used by players,
 * so if a playerState_t is transmitted, the entityState_t can be fully derived
 * from it.
 *
 * @note All fields in here must be 32 bits (or those within sub-structures)
 */
typedef struct playerState_s
{
	int commandTime;            ///< cmd->serverTime of last executed command
	int pm_type;                ///<
	int bobCycle;               ///< for view bobbing and footstep generation
	int pm_flags;               ///< ducked, jump_held, etc
	int pm_time;

	vec3_t origin;
	vec3_t velocity;
	int weaponTime;
	int weaponDelay;            ///< for weapons that don't fire immediately when 'fire' is hit (grenades, venom, ...)
	int grenadeTimeLeft;        ///< for delayed grenade throwing.  this is set to a \#define for grenade
	                            ///< lifetime when the attack button goes down, then when attack is released
	                            ///< this is the amount of time left before the grenade goes off (or if it
	                            ///< gets to 0 while in players hand, it explodes)

	int gravity;
	float leanf;                ///< amount of 'lean' when player is looking around corner

	int speed;
	int delta_angles[3];        ///< add to command angles to get view direction
	                            ///< changed by spawns, rotating objects, and teleporters

	int groundEntityNum;        ///< ENTITYNUM_NONE = in air

	int legsTimer;              ///< don't change low priority animations until this runs out
	int legsAnim;               ///< mask off ANIM_TOGGLEBIT

	int torsoTimer;             ///< don't change low priority animations until this runs out
	int torsoAnim;              ///< mask off ANIM_TOGGLEBIT

	int movementDir;            ///< a number 0 to 7 that represents the reletive angle
	                            ///< of movement to the view angle (axial and diagonals)
	                            ///< when at rest, the value will remain unchanged
	                            ///< used to twist the legs during strafing

	int eFlags;                 ///< copied to entityState_t->eFlags

	int eventSequence;          ///< pmove generated events
	int events[MAX_EVENTS];
	int eventParms[MAX_EVENTS];
	int oldEventSequence;       ///< so we can see which events have been added since we last converted to entityState_t

	int externalEvent;          ///< events set on player from another source
	int externalEventParm;
	int externalEventTime;

	int clientNum;              ///< ranges from 0 to MAX_CLIENTS-1

	int weapon;                 ///< weapon info, copied to entityState_t->weapon
	int weaponstate;            ///< weapon info

	int item;                   ///< item info

	vec3_t viewangles;          ///< for fixed views
	int viewheight;

	// damage feedback
	int damageEvent;            ///< when it changes, latch the other parms
	int damageYaw;
	int damagePitch;
	int damageCount;

	int stats[MAX_STATS];
	int persistant[MAX_PERSISTANT];                 ///< stats that aren't cleared on death
	int powerups[MAX_POWERUPS];                     ///< level.time that the powerup runs out
	int ammo[MAX_WEAPONS];                          ///< total amount of ammo
	int ammoclip[MAX_WEAPONS];                      ///< ammo in clip
	int holdable[MAX_HOLDABLE];
	int holding;                                    ///< the current item in holdable[] that is selected (held)
	int weapons[MAX_WEAPONS / (sizeof(int) * 8)];   ///< 64 bits for weapons held

	// allow for individual bounding boxes
	vec3_t mins, maxs;
	float crouchMaxZ;
	float crouchViewHeight, standViewHeight, deadViewHeight;
	// variable movement speed
	float runSpeedScale, sprintSpeedScale, crouchSpeedScale;

	// view locking for mg42
	int viewlocked;
	int viewlocked_entNum;

	float friction;

	int nextWeapon;

	// player class
	int teamNum;

	// RF, burning effect is required for view blending effect
	int onFireStart;

	int serverCursorHint;               ///< what type of cursor hint the server is dictating
	int serverCursorHintVal;            ///< a value (0-255) associated with the above

	trace_t serverCursorHintTrace;      ///< not communicated over net, but used to store the current server-side cursorhint trace

	// ----------------------------------------------------------------------
	// So to use persistent variables here, which don't need to come from the server,
	// we could use a marker variable, and use that to store everything after it
	// before we read in the new values for the predictedPlayerState, then restore them
	// after copying the structure recieved from the server.

	// use the pmoveExt_t structure in bg_public.h to store this kind of data now (persistant on client, not network transmitted)

	int ping;                       ///< server to game info for scoreboard
	int pmove_framecount;
	int entityEventSequence;

	int sprintExertTime;

	// value for all multiplayer classes with regenerating "class weapons" -- ie LT artillery, medic medpack, engineer build points, etc
	int classWeaponTime;            ///< DOES get send over the network
	int jumpTime;                   ///< used in MP to prevent jump accel

	int weapAnim;                   ///< mask off ANIM_TOGGLEBIT, DOES get send over the network

	qboolean releasedFire;

	float aimSpreadScaleFloat;      ///< the server-side aimspreadscale that lets it track finer changes but still only
	                                ///< transmit the 8bit int to the client
	int aimSpreadScale;             ///< 0 - 255 increases with angular movement. DOES get send over the network
	int lastFireTime;               ///< used by server to hold last firing frame briefly when randomly releasing trigger (AI)
	                                ///< Set, but never used?

	int quickGrenTime;              ///< Unused
	int leanStopDebounceTime;       ///< Unused

	// seems like heat and aimspread could be tied together somehow, however, they (appear to) change at different rates and
	// I can't currently see how to optimize this to one server->client transmission "weapstatus" value.
	int weapHeat[MAX_WEAPONS];          ///< some weapons can overheat.  this tracks (server-side) how hot each weapon currently is.
	int curWeapHeat;                    ///< value for the currently selected weapon (for transmission to client). DOES get send over the network
	int identifyClient;
	int identifyClientHealth;

	aistateEnum_t aiState;
} playerState_t;

//====================================================================

// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game/cgame only definitions

#define BUTTON_ATTACK       1
#define BUTTON_TALK         2           ///< displays talk balloon and disables actions
//#define   BUTTON_USE_HOLDABLE 4       ///< obsolete/unused
#define BUTTON_GESTURE      8
#define BUTTON_WALKING      16          ///< walking can't just be infered from MOVE_RUN
// because a key pressed late in the frame will
// only generate a small move value for that frame
// walking will use different animations and
// won't generate footsteps

#define BUTTON_SPRINT       32
#define BUTTON_ACTIVATE     64
#define BUTTON_ANY          128         ///< any key whatsoever

#define WBUTTON_ATTACK2     1
#define WBUTTON_ZOOM        2
#define WBUTTON_RELOAD      8
#define WBUTTON_LEANLEFT    16
#define WBUTTON_LEANRIGHT   32
#define WBUTTON_DROP        64
#define WBUTTON_PRONE       128 ///< wbutton now

#define MOVE_RUN            120         ///< if forwardmove or rightmove are >= MOVE_RUN,
// then BUTTON_WALKING should be set

/**
 * @enum dtType_t
 * @brief doubleTap buttons - DT_NUM can be max 8
 */
typedef enum
{
	DT_NONE,
	DT_MOVELEFT,
	DT_MOVERIGHT,
	DT_FORWARD,
	DT_BACK,
	DT_LEANLEFT,
	DT_LEANRIGHT,
	DT_UP,
	DT_NUM
} dtType_t;

/**
 * @struct usercmd_s
 * @typedef usercmd_t
 * @brief usercmd_t is sent to the server each client frame
 */
typedef struct usercmd_s
{
	int serverTime;
	byte buttons;
	byte wbuttons;
	byte weapon;
	byte flags;
	int angles[3];

	signed char forwardmove, rightmove, upmove;
	byte doubleTap;             // only 3 bits used

	// in ET, this can be any entity, and it's used as an array
	// index, so make sure it's unsigned
	byte identClient;
} usercmd_t;

//===================================================================

/// if entityState->solid == SOLID_BMODEL, modelindex is an inline model number
#define SOLID_BMODEL    0xffffff

/**
 * @enum trType_t
 * @brief
 */
typedef enum
{
	TR_STATIONARY,
	TR_INTERPOLATE,             ///< non-parametric, but interpolate between snapshots
	TR_LINEAR,
	TR_LINEAR_STOP,
	TR_LINEAR_STOP_BACK,        ///< unused in ET - so reverse movement can be different than forward
	TR_SINE,                    ///< value = base + sin( time / duration ) * delta
	TR_GRAVITY,
	TR_GRAVITY_LOW,
	TR_GRAVITY_FLOAT,           ///< super low grav with no gravity acceleration (floating feathers/fabric/leaves/...)
	TR_GRAVITY_PAUSED,          ///< has stopped, but will still do a short trace to see if it should be switched back to TR_GRAVITY
	TR_ACCELERATE,
	TR_DECCELERATE,
	TR_SPLINE,
	TR_LINEAR_PATH
} trType_t;

/**
 * @struct trajectory_t
 */
typedef struct
{
	trType_t trType;
	int trTime;
	int trDuration;             ///< if non 0, trTime + trDuration = stop time
	vec3_t trBase;
	vec3_t trDelta;             ///< velocity, etc
} trajectory_t;

/**
 * @enum entityType_t
 *
 * @brief entityState_t is the information conveyed from the server
 * in an update message about entities that the client will
 * need to render in some way
 * Different eTypes may use the information in different ways
 * The messages are delta compressed, so it doesn't really matter if
 * the structure size is fairly large
 *
 * @note All fields in here must be 32 bits (or those within sub-structures)
 */
typedef enum
{
	ET_GENERAL = 0,
	ET_PLAYER,
	ET_ITEM,
	ET_MISSILE,
	ET_MOVER,
	ET_BEAM,
	ET_PORTAL,
	ET_SPEAKER,
	//ET_PUSH_TRIGGER,          /// unused
	ET_TELEPORT_TRIGGER = 9,
	ET_INVISIBLE,               ///< 10
	//ET_CONCUSSIVE_TRIGGER,    ///< unused - trigger for concussive dust particles
	ET_OID_TRIGGER = 12,        ///< Objective Info Display
	ET_EXPLOSIVE_INDICATOR,

	ET_EXPLOSIVE,               ///< brush that will break into smaller bits when damaged
	//ET_EF_SPOTLIGHT,          ///< unused
	ET_ALARMBOX = 16,
	ET_CORONA,
	ET_TRAP,

	ET_GAMEMODEL,               ///< misc_gamemodel.  similar to misc_model, but it's a dynamic model so we have LOD
	//ET_FOOTLOCKER,            ///< 20 - unused

	ET_FLAMEBARREL = 21,
	//ET_FP_PARTS,

	// FIRE PROPS
	//ET_FIRE_COLUMN,
	//ET_FIRE_COLUMN_SMOKE,
	ET_RAMJET = 25,

	ET_FLAMETHROWER_CHUNK,      ///< used in server side collision detection for flamethrower

	//ET_EXPLO_PART,

	ET_PROP = 28,

	//ET_AI_EFFECT,             ///< unused

	ET_CAMERA = 30,             ///< 30
	//ET_MOVERSCALED,           // unused

	ET_CONSTRUCTIBLE_INDICATOR = 32,
	ET_CONSTRUCTIBLE,
	ET_CONSTRUCTIBLE_MARKER,
	//ET_BOMB,                  ///< obsolete/unused (tripmines)
	//ET_WAYPOINT,              ///< obsolete/unused
	ET_BEAM_2 = 37,
	ET_TANK_INDICATOR,
	ET_TANK_INDICATOR_DEAD,
	//ET_BOTGOAL_INDICATOR,     ///< obsolete/unused - An indicator object created by the bot code to show where the bots are moving to
	ET_CORPSE = 41,             ///< 40 - dead player
	ET_SMOKER,                  ///< target_smoke entity

	ET_TEMPHEAD,                ///< temporary head for clients for bullet traces
	ET_MG42_BARREL,             ///< MG42 barrel
	ET_TEMPLEGS,                ///< temporary leg for clients for bullet traces
	ET_TRIGGER_MULTIPLE,
	ET_TRIGGER_FLAGONLY,
	ET_TRIGGER_FLAGONLY_MULTIPLE,
	ET_GAMEMANAGER,
	ET_AAGUN,                   ///< 50
	ET_CABINET_H,
	ET_CABINET_A,
	ET_HEALER,
	ET_SUPPLIER,

	//ET_LANDMINE_HINT,         ///< obsolete/unused (landmine hint for botsetgoalstate filter)
	//ET_ATTRACTOR_HINT,        ///< obsolete/unused (attractor hint for botsetgoalstate filter)
	//ET_SNIPER_HINT,           ///< obsolete/unused (sniper hint for botsetgoalstate filter)
	//ET_LANDMINESPOT_HINT,     ///< obsolete/unused (landminespot hint for botsetgoalstate filter)

	ET_COMMANDMAP_MARKER = 59,

	ET_WOLF_OBJECTIVE,

	ET_AIRSTRIKE_PLANE,

	ET_EVENTS                   ///< any of the EV_* events can be added freestanding
	                            ///< by setting eType to ET_EVENTS + eventNum
	                            ///< this avoids having to set eFlags and eventNum
} entityType_t;

/**
 * @struct entityState_s
 * @typedef entityState_t
 * @brief
 */
typedef struct entityState_s
{
	int number;             ///< entity index
	entityType_t eType;     ///< entityType_t
	int eFlags;

	trajectory_t pos;       ///< for calculating position
	trajectory_t apos;      ///< for calculating angles

	int time;
	int time2;

	vec3_t origin;
	vec3_t origin2;

	vec3_t angles;
	vec3_t angles2;

	int otherEntityNum;     ///< shotgun sources, etc
	int otherEntityNum2;

	int groundEntityNum;    ///< -1 = in air

	int constantLight;      ///< r + (g<<8) + (b<<16) + (intensity<<24)
	int dl_intensity;       ///< used for coronas
	int loopSound;          ///< constantly loop this sound

	int modelindex;
	int modelindex2;
	int clientNum;          ///< 0 to (MAX_CLIENTS - 1), for players and corpses
	int frame;

	int solid;              ///< for client side prediction, trap_linkentity sets this properly

	// old style events, in for compatibility only
	int event;
	int eventParm;

	int eventSequence;      ///< pmove generated events
	int events[MAX_EVENTS];
	int eventParms[MAX_EVENTS];

	// for players
	int powerups;           ///< bit flags. Used to store entState_t for non-player entities (so we know to draw them translucent clientsided)
	int weapon;             ///< determines weapon and flash model, etc
	                        ///< OR fps to animate with (misc_gamemodel ents)
	                        ///< which is the time in ms the model is updated (20 fps = default)
	int legsAnim;           ///< mask off ANIM_TOGGLEBIT
	int torsoAnim;          ///< mask off ANIM_TOGGLEBIT

	int density;            ///< for particle effects

	int dmgFlags;           ///< to pass along additional information for damage effects for players/ Also used for cursorhints for non-player entities

	int onFireStart, onFireEnd;

	int nextWeapon;
	int teamNum;

	int effect1Time, effect2Time, effect3Time;

	aistateEnum_t aiState;
	int animMovetype;       ///< clients can't derive movetype of other clients for anim scripting system

} entityState_t;

/**
 * @enum connstate_t
 * @brief
 */
typedef enum
{
	CA_UNINITIALIZED,   ///< obsolete; not used anymore
	CA_DISCONNECTED,    ///< not talking to a server
	CA_AUTHORIZING,     ///< deprecated (cd key check), but ET:L will use it in the future
	CA_CONNECTING,      ///< sending request packets to the server
	CA_CHALLENGING,     ///< sending challenge packets to the server
	CA_CONNECTED,       ///< netchan_t established, getting gamestate
	CA_LOADING,         ///< only during cgame initialization, never during main loop
	CA_PRIMED,          ///< got gamestate, waiting for first frame
	CA_ACTIVE,          ///< game views should be displayed
	CA_CINEMATIC        ///< playing a cinematic or a static pic, not connected to a server
} connstate_t;

/**
 * @enum challengeState_t
 * @brief CA_CHALLENGING substates
 */
typedef enum
{
	CA_CHALLENGING_INFO,  ///< acquiring server info
	CA_CHALLENGING_REQUEST ///< requesting connection
} challengeState_t;

// font support

#define GLYPH_START 0
#define GLYPH_ASCII_END 255
#define GLYPH_UTF_END 1327 // (Cyrillic U+052F)
#define GLYPH_END(ext) (ext ? GLYPH_UTF_END : GLYPH_ASCII_END)
#define GLYPHS_ASCII_PER_FONT GLYPH_ASCII_END - GLYPH_START + 1
#define GLYPHS_UTF_PER_FONT GLYPH_UTF_END - GLYPH_START + 1
#define GLYPHS_PER_FONT(ext) GLYPH_END(ext) + 1

/**
 * @struct glyphInfo_t
 * @brief
 */
typedef struct
{
	int height;       ///< number of scan lines
	int top;          ///< top of glyph in buffer
	int bottom;       ///< bottom of glyph in buffer
	int pitch;        ///< width for copying
	int xSkip;        ///< x adjustment
	int imageWidth;   ///< width of actual image
	int imageHeight;  ///< height of actual image
	float s;          ///< x offset in image where glyph starts
	float t;          ///< y offset in image where glyph starts
	float s2;
	float t2;
	qhandle_t glyph;  ///< handle to the shader with the glyph
	char shaderName[32];
} glyphInfo_t;

/**
 * @struct fontInfo_t
 * @brief
 */
typedef struct
{
	glyphInfo_t glyphs[GLYPHS_ASCII_PER_FONT];
	float glyphScale;
	char datName[MAX_QPATH];

} fontInfo_t;

/**
 * @struct fontInfo_extra_t
 * @brief
 */
typedef struct
{
	glyphInfo_t glyphs[GLYPHS_ASCII_PER_FONT];
	float glyphScale;
	char datName[MAX_QPATH];
	glyphInfo_t glyphsUTF8[GLYPHS_UTF_PER_FONT];

} fontInfo_extra_t;

/**
 * @struct fontHelper_t
 * @brief
 */
typedef struct
{
	void *fontData;
	glyphInfo_t *(*GetGlyph)(void *fontdata, unsigned long codepoint);

} fontHelper_t;

// SQR
#define Square(x) ((x) * (x))

// real time
//=============================================

/**
 * @struct qtime_s
 * @typedef qtime_t
 * @brief
 */
typedef struct qtime_s
{
	int tm_sec;     ///< seconds after the minute - [0,59]
	int tm_min;     ///< minutes after the hour - [0,59]
	int tm_hour;    ///< hours since midnight - [0,23]
	int tm_mday;    ///< day of the month - [1,31]
	int tm_mon;     ///< months since January - [0,11]
	int tm_year;    ///< years since 1900
	int tm_wday;    ///< days since Sunday - [0,6]
	int tm_yday;    ///< days since January 1 - [0,365]
	int tm_isdst;   ///< daylight savings time flag
} qtime_t;

// server browser sources
#define AS_LOCAL        0
#define AS_GLOBAL       1
#define AS_FAVORITES    2

#define AS_LOCAL_ALL     -1
#define AS_GLOBAL_ALL    -2
#define AS_FAVORITES_ALL -3

/**
 * @struct e_status
 * @brief Cinematic states
 */
typedef enum
{
	FMV_IDLE,
	FMV_PLAY,       ///< play
	FMV_EOF,        ///< all other conditions, i.e. stop/EOF/abort
	FMV_ID_BLT,
	FMV_ID_IDLE,
	FMV_LOOPED,
	FMV_ID_WAIT
} e_status;

/**
 * @enum demoState_t
 * @brief Cinematic states
 */
typedef enum
{
	DS_NONE,

	DS_WAITINGPLAYBACK, ///< demo will play after map_restart)
	DS_PLAYBACK,        ///< a demo is playing
	DS_WAITINGSTOP,     ///< demo is stopped but we must move clients over their normal slots

	DS_RECORDING,       ///< a demo is being recorded

	DS_NUM_DEMO_STATES

} demoState_t;

#define MAX_GLOBAL_SERVERS          4096
#define MAX_OTHER_SERVERS           128 // local servers
#define MAX_FAVOURITE_SERVERS       128
#define MAX_PINGREQUESTS            16
#define MAX_SERVERSTATUSREQUESTS    16

/**
 * @enum demoState_t
 * @brief server/game states
 */
typedef enum
{
	GS_INITIALIZE = -1,
	GS_PLAYING,
	GS_WARMUP_COUNTDOWN,
	GS_WARMUP,
	GS_INTERMISSION,
	GS_WAITING_FOR_PLAYERS,
	GS_RESET
} gamestate_t;

/**
 * @struct rectDef_s
 * @typedef rectDef_t
 * @brief server/game states
 */
typedef struct rectDef_s
{
	float x;    ///< horiz position
	float y;    ///< vert position
	float w;    ///< width
	float h;    ///< height;
} rectDef_t;

//typedef rectDef_t Rectangle;

#define RectangleSet(rect, v1, v2, v3, v4) ((rect.x) = (v1), (rect.y) = (v2), (rect.w) = (v3), (rect.h) = (v4))

#if defined(_MSC_VER) && (_MSC_VER < 1800)
float rint(float v);
#endif

// this should be used to convert a floating-point value to an integer
//#define ROUND_INT(x) (x >= 0 ? (int)(x + 0.5) : (int)(x - 0.5)) // Unused

/**
 * @struct demoPlayInfo_s
 * @typedef demoPlayInfo_t
 * @brief
 */
typedef struct demoPlayInfo_s
{
	int firstTime;
	int lastTime;
} demoPlayInfo_t;

/**
 * @struct userAgent_s
 * @typedef userAgent_t
 * @brief Holds information about server/client engine on the other end
 */
typedef struct userAgent_s
{
	int compatible;      ///< is it compatible with the engine? note: this can be flag based in future.
	char string[64];     ///< holds engine name and version string
	char version[18];    ///< holds engine version
} userAgent_t;

void Com_ParseUA(userAgent_t *ua, const char *string);
#define Com_IsCompatible(ua, flag) ((ua)->compatible & flag)

//c99 issue pre 2013 VS do not have support for this
#if defined(_MSC_VER) && (_MSC_VER < 1800)
// source http://smackerelofopinion.blogspot.fi/2011/10/determining-number-of-arguments-in-c.html
#define NUMARGSFAST PP_NARG_FAST
#define NUMARGS PP_NARG
#define PP_NARG(...)  EXPAND((PP_NARG_(__VA_ARGS__, PP_RSEQ_N()) - (sizeof("" #__VA_ARGS__) == 1)))
#define PP_NARG_FAST(...)  EXPAND(PP_NARG_(__VA_ARGS__, PP_RSEQ_N()))
#define PP_NARG_(...)  EXPAND(PP_ARG_N(__VA_ARGS__))

#define PP_ARG_N( \
	    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
	    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
	    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
	    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
	    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
	    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
	    _61, _62, _63, N, ...) N

#define PP_RSEQ_N() \
	63, 62, 61, 60,          \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
	9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#else
#define NUMARGS(...)  (sizeof((int[]) { 0, ## __VA_ARGS__ }) / sizeof(int) - 1)
#endif

#ifdef LEGACY_DEBUG
#if defined(_MSC_VER)
#define etl_assert(x) if (!(x)) __debugbreak()
#elif defined(_WIN32)
#define etl_assert(x) if (!(x)) __asm("int {$}3" :)
#else
#define etl_assert(cond) assert(cond)
#endif
#else
#define etl_assert(x) {}
#endif

typedef int (*cmpFunc_t)(const void *a, const void *b);

void *Q_LinearSearch(const void *key, const void *ptr, size_t count, size_t size, cmpFunc_t cmp);

int GetIPLength(char const *ip);
qboolean CompareIPNoPort(char const *ip1, char const *ip2);

#define LERP(a, b, w) ((a) * (1.0 - (w)) + (b) * (w))
#define LUMA(red, green, blue) (0.2126f * (red) + 0.7152f * (green) + 0.0722f * (blue))

#endif  // #ifndef INCLUDE_Q_SHARED_H
