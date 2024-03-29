/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#include <signal.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <vitasdk.h>

#include "sys_local.h"
#include "sys_loadlib.h"

#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"

int _newlib_heap_size_user = 158 * 1024 * 1024;

static char binaryPath[ MAX_OSPATH ] = { 0 };
static char installPath[ MAX_OSPATH ] = { 0 };

/*
=================
Sys_SetBinaryPath
=================
*/
void Sys_SetBinaryPath(const char *path)
{
	Q_strncpyz(binaryPath, path, sizeof(binaryPath));
}

/*
=================
Sys_BinaryPath
=================
*/
char *Sys_BinaryPath(void)
{
	return binaryPath;
}

/*
=================
Sys_SetDefaultInstallPath
=================
*/
void Sys_SetDefaultInstallPath(const char *path)
{
	Q_strncpyz(installPath, path, sizeof(installPath));
}

/*
=================
Sys_DefaultInstallPath
=================
*/
char *Sys_DefaultInstallPath(void)
{
	if (*installPath)
		return installPath;
	else
		return Sys_Cwd();
}

/*
=================
Sys_DefaultAppPath
=================
*/
char *Sys_DefaultAppPath(void)
{
	return Sys_BinaryPath();
}

/*
=================
Sys_In_Restart_f

Restart the input subsystem
=================
*/
void Sys_In_Restart_f( void )
{
	IN_Restart( );
}

/*
=================
Sys_ConsoleInput

Handle new console input
=================
*/
char *Sys_ConsoleInput(void)
{
	return CON_Input( );
}

/*
==================
Sys_GetClipboardData
==================
*/
char *Sys_GetClipboardData(void)
{
#ifdef DEDICATED
	return NULL;
#else
	char *data = NULL;
	char *cliptext;

	/*if ( ( cliptext = SDL_GetClipboardText() ) != NULL ) {
		if ( cliptext[0] != '\0' ) {
			size_t bufsize = strlen( cliptext ) + 1;

			data = Z_Malloc( bufsize );
			Q_strncpyz( data, cliptext, bufsize );

			// find first listed char and set to '\0'
			strtok( data, "\n\r\b" );
		}
		SDL_free( cliptext );
	}*/
	return data;
#endif
}

#ifdef DEDICATED
#	define PID_FILENAME "iowolfsp_server.pid"
#else
#	define PID_FILENAME "iowolfsp.pid"
#endif

/*
=================
Sys_RemovePIDFile
=================
*/
void Sys_RemovePIDFile(const char *gamedir) {}

/*
=================
Sys_InitPIDFile
=================
*/
void Sys_InitPIDFile(const char *gamedir) {}

/*
=================
Sys_Exit

Single exit point (regular exit or in case of error)
=================
*/
static __attribute__ ((noreturn)) void Sys_Exit( int exitCode )
{
	CON_Shutdown( );

	NET_Shutdown( );

	Sys_PlatformExit( );

	exit( exitCode );
}

/*
=================
Sys_Quit
=================
*/
void Sys_Quit( void )
{
	Sys_Exit( 0 );
}

/*
=================
Sys_Init
=================
*/
void Sys_Init(void)
{
	Cmd_AddCommand( "in_restart", Sys_In_Restart_f );
	Cvar_Set( "arch", OS_STRING " " ARCH_STRING );
	Cvar_Set( "username", Sys_GetCurrentUser( ) );
}

/*
=================
Sys_AnsiColorPrint

Transform Q3 colour codes to ANSI escape sequences
=================
*/
void Sys_AnsiColorPrint( const char *msg )
{
}

/*
=================
Sys_Print
=================
*/
void Sys_Print( const char *msg )
{
	CON_Print( msg );
}

/*
=================
Sys_Error
=================
*/
void Sys_Error( const char *error, ... )
{
	va_list argptr;
	char    string[1024];

	va_start (argptr,error);
	Q_vsnprintf (string, sizeof(string), error, argptr);
	va_end (argptr);

	Sys_ErrorDialog( string );

	Sys_Exit( 3 );
}

/*
============
Sys_FileTime

returns -1 if not present
============
*/
int Sys_FileTime( char *path )
{
	struct stat buf;

	if (stat (path,&buf) == -1)
		return -1;

	return buf.st_mtime;
}

/*
=================
Sys_UnloadDll
=================
*/
void Sys_UnloadDll( void *dllHandle )
{
	if( !dllHandle )
	{
		Com_Printf("Sys_UnloadDll(NULL)\n");
		return;
	}

	Sys_UnloadLibrary(dllHandle);
}

/*
=================
Sys_LoadDll

First try to load library name from system library path,
from executable path, then fs_basepath.
=================
*/

void *Sys_LoadDll(const char *name, qboolean useSystemLib) {
    void *dllhandle = NULL;
	
	char full_lib[128];
	sprintf(full_lib, "%s.mp.arm.suprx", name);
	
	if(!Sys_DllExtension(full_lib))
	{
		Com_Printf("Refusing to attempt to load library \"%s\": Extension not allowed.\n", full_lib);
		return NULL;
	}
	
	if(useSystemLib)
	{
		Com_Printf("Trying to load \"%s\"...\n", full_lib);
		dllhandle = Sys_LoadLibrary(full_lib);
	}

	if(!dllhandle)
	{
		const char *topDir;
		char libPath[MAX_OSPATH];
		int len;

		topDir = Sys_BinaryPath();

		if(!*topDir)
			topDir = ".";

		len = Com_sprintf(libPath, sizeof(libPath), "%s%c%s", topDir, PATH_SEP, full_lib);
		if(len < sizeof(libPath))
		{
			Com_Printf("Trying to load \"%s\" from \"%s\"...\n", full_lib, topDir);
			dllhandle = Sys_LoadLibrary(libPath);
		}
		else
		{
			Com_Printf("Skipping trying to load \"%s\" from \"%s\", file name is too long.\n", full_lib, topDir);
		}

		if(!dllhandle)
		{
			const char *basePath = Cvar_VariableString("fs_basepath");
			
			if(!basePath || !*basePath)
				basePath = ".";
			
			if(FS_FilenameCompare(topDir, basePath))
			{
				len = Com_sprintf(libPath, sizeof(libPath), "%s%c%s", basePath, PATH_SEP, full_lib);
				if(len < sizeof(libPath))
				{
					Com_Printf("Trying to load \"%s\" from \"%s\"...\n", full_lib, basePath);
					dllhandle = Sys_LoadLibrary(libPath);
				}
				else
				{
					Com_Printf("Skipping trying to load \"%s\" from \"%s\", file name is too long.\n", full_lib, basePath);
				}
			}
			
			if(!dllhandle)
				Com_Printf("Loading \"%s\" failed\n", full_lib);
		}
	}
	
	return dllhandle;
}

/*
=================
Sys_LoadGameDll

Used to load a development dll instead of a virtual machine
=================
*/
void *Sys_LoadGameDll(const char *name, qboolean extract,
	intptr_t (QDECL **entryPoint)(intptr_t, ...),
	intptr_t (*systemcalls)(intptr_t, ...))
{
	void *libHandle;
	void (*dllEntry)(intptr_t (*syscallptr)(intptr_t, ...));

	char full_lib[128];
	sprintf(full_lib, "%s.mp.arm.suprx", name);

	if(!Sys_DllExtension(full_lib))
	{
		Com_Printf("Refusing to attempt to load library \"%s\": Extension not allowed.\n", full_lib);
		return NULL;
	}

	Com_DPrintf( "Loading DLL file: %s\n", full_lib);
	libHandle = Sys_LoadLibrary(full_lib);

	if(!libHandle)
	{
		Com_Printf("Sys_LoadGameDll(%s) failed:\n\"%s\"\n", full_lib, Sys_LibraryError());
		return NULL;
	}

	dllEntry = Sys_LoadFunction( libHandle, "dllEntry" );
	*entryPoint = Sys_LoadFunction( libHandle, "vmMain" );

	if ( !*entryPoint || !dllEntry )
	{
		Com_Printf ( "Sys_LoadGameDll(%s) failed to find vmMain function:\n\"%s\" !\n", full_lib, Sys_LibraryError( ) );
		Sys_UnloadLibrary(libHandle);

		return NULL;
	}

	Com_DPrintf ( "Sys_LoadGameDll(%s) found vmMain function at %p\n", full_lib, *entryPoint );
	dllEntry( systemcalls );

	return libHandle;
}

/*
=================
Sys_ParseArgs
=================
*/
void Sys_ParseArgs( int argc, char **argv )
{
	if( argc == 2 )
	{
		if( !strcmp( argv[1], "--version" ) ||
				!strcmp( argv[1], "-v" ) )
		{
#ifdef DEDICATED
			fprintf( stdout, Q3_VERSION " dedicated server \n" );
#else
			fprintf( stdout, Q3_VERSION " client \n" );
#endif
			Sys_Exit( 0 );
		}
	}
}

/*
=================
Sys_SigHandler
=================
*/
void Sys_SigHandler( int signal )
{
	static qboolean signalcaught = qfalse;

	if( signalcaught )
	{
		fprintf( stderr, "DOUBLE SIGNAL FAULT: Received signal %d, exiting...\n",
			signal );
	}
	else
	{
		signalcaught = qtrue;
#ifndef DEDICATED
		CL_Shutdown();
#endif
		SV_Shutdown(va("Received signal %d", signal) );
	}

	if( signal == SIGTERM || signal == SIGINT )
		Sys_Exit( 1 );
	else
		Sys_Exit( 2 );
}

void Sys_SnapVector(float *v)
{
	v[0] = rint(v[0]);
	v[1] = rint(v[1]);
	v[2] = rint(v[2]);
}

/**
 * @brief Writes pid to profile or to the homepath root if running a server
 * @return qtrue  if pid file successfully created
 *         otherwise qfalse if it wasn't possible to create a new pid file
 */
qboolean Sys_WritePIDFile(void)
{
	fileHandle_t f;

	// First, check if the pid file is already there
	if (FS_FileInPathExists(com_pidfile->string))
	{
		// TODO: check if we are hijacking live pid file
		/*
		FS_FOpenFileRead(com_pidfile->string, &f, qtrue);
		if(Sys_PIDIsRunning(pid))
		{
		    Com_Printf("WARNING: another instance of ET:L is using this path!\n");
		    return qfalse;
		}
		*/
		if (FS_Delete(com_pidfile->string) == 0) // stale pid from previous run
		{
			Com_Printf("WARNING: unable to delete old PID file!\n");
		}
	}

	f = FS_FOpenFileWrite(com_pidfile->string);
	if (f < 0)
	{
		Com_Printf("WARNING: can't write PID file!\n");
		return qfalse;
	}
	else
	{
		Com_Printf("Creating PID file '%s'\n", com_pidfile->string);
	}

	FS_Printf(f, "%d", com_pid->integer);

	FS_FCloseFile(f);

	// track profile changes
	Com_TrackProfile(com_pidfile->string);

	return qtrue;
}

/*
=================
main
=================
*/
int wolfet_main( int argc, char **argv )
{
	int   i;
	char  commandLine[ MAX_STRING_CHARS ] = { 0 };

	Sys_PlatformInit( );

	// Set the initial time base
	Sys_Milliseconds( );

	sceIoMkdir("ux0:data/ETLegacy", 777);
	Sys_SetBinaryPath( "ux0:data/ETLegacy" );
	Sys_SetDefaultInstallPath( "ux0:data/ETLegacy" );

	CON_Init( );
	Com_Init( commandLine );
	NET_Init( );

	while( 1 )
	{
		// Prevent screen power-off
		sceKernelPowerTick(0);
		
		Com_Frame( );
	}

	return 0;
}

extern void IN_Init();

int main(int argc, char **argv) {
	
	// Setting maximum clocks
	scePowerSetArmClockFrequency(444);
	scePowerSetBusClockFrequency(222);
	scePowerSetGpuClockFrequency(222);
	scePowerSetGpuXbarClockFrequency(166);
	
	// Checking for libshacccg.suprx existence
	SceIoStat st1, st2;
	if (!(sceIoGetstat("ur0:/data/libshacccg.suprx", &st1) >= 0 || sceIoGetstat("ur0:/data/external/libshacccg.suprx", &st2) >= 0)) {
		vglInit(0);
		SceMsgDialogUserMessageParam msg_param;
		sceClibMemset(&msg_param, 0, sizeof(SceMsgDialogUserMessageParam));
		msg_param.buttonType = SCE_MSG_DIALOG_BUTTON_TYPE_OK;
		msg_param.msg = (const SceChar8*)"Error: Runtime shader compiler (libshacccg.suprx) is not installed.";
		SceMsgDialogParam param;
		sceMsgDialogParamInit(&param);
		param.mode = SCE_MSG_DIALOG_MODE_USER_MSG;
		param.userMsgParam = &msg_param;
		sceMsgDialogInit(&param);
		while (sceMsgDialogGetStatus() != SCE_COMMON_DIALOG_STATUS_FINISHED) {
			vglSwapBuffers(1);
		}
		sceKernelExitProcess(0);
	}
	
	// Starting input
	IN_Init();
	
	// We need a bigger stack to run Wolf:ET, so we create a new thread with a proper stack size
	SceUID main_thread = sceKernelCreateThread("Wolf:ET", wolfet_main, 0x40, 0x200000, 0, 0, NULL);
	if (main_thread >= 0){
		sceKernelStartThread(main_thread, 0, NULL);
		sceKernelWaitThreadEnd(main_thread, NULL, NULL);
	}
	return 0;
	
}
