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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../rendererGLES/tr_local.h"
#include "../sys/sys_local.h"

#include <vitasdk.h>
#include "vitaGL.h"

#define GXM_PARAM_BUF_SIZE 16 * 1024 * 1024

void GLimp_SetGamma( unsigned char red[256], unsigned char green[256], unsigned char blue[256] )
{
}

/*
===============
GLimp_Shutdown
===============
*/
void GLimp_Shutdown( void )
{
	ri.IN_Shutdown();
}

/*
===============
GLimp_Minimize

Minimize the game so that user is back at the desktop
===============
*/
void GLimp_Minimize( void )
{
}


/*
===============
GLimp_LogComment
===============
*/
extern void log2file(const char *format, ...);
void GLimp_LogComment( char *comment )
{
#ifndef RELEASE
	log2file(comment);
#endif
}

#define R_MODE_FALLBACK 3 // 640 * 480

/*
===============
GLimp_Init

This routine is responsible for initializing the OS specific portions
of OpenGL
===============
*/
uint16_t* indices;
float *gVertexBuffer;
uint8_t *gColorBuffer;
uint8_t *gColorBuffer255;
float *gTexCoordBuffer;
float *gVertexBufferPtr;
uint8_t *gColorBufferPtr;
float *gTexCoordBufferPtr;
uint8_t inited = 0;

typedef struct vidmode_s
{
	const char *description;
	int width, height;
	float pixelAspect;		// pixel width / height
} vidmode_t;
vidmode_t r_vidModes[] =
{
	{ "Mode  0: 480x272",		480,	272,	1 },
	{ "Mode  1: 640x368",		640,	368,	1 },
	{ "Mode  2: 720x408",		720,	408,	1 },
	{ "Mode  3: 960x544",		960,	544,	1 },
	{ "Mode  4: 960x544",		960,	544,	1 },
	{ "Mode  5: 960x544",		960,	544,	1 },
	{ "Mode  6: 960x544",		960,	544,	1 },
	{ "Mode  7: 960x544",		960,	544,	1 },
	{ "Mode  8: 960x544",		960,	544,	1 },
	{ "Mode  9: 960x544",		960,	544,	1 },
	{ "Mode 10: 960x544",		960,	544,	1 },
	{ "Mode 11: 960x544", 		960, 	544, 	1 },
	{ "Mode 12:   640x360  (16:9)",     640,     360,    1 },
	{ "Mode 13:   640x400 (16:10)",     640,     400,    1 },
	{ "Mode 14:   800x450  (16:9)",     800,     450,    1 },
	{ "Mode 15:   800x500 (16:10)",     800,     500,    1 },
	{ "Mode 16:  1024x640 (16:10)",    1024,     640,    1 },
	{ "Mode 17:  1024x576  (16:9)",    1024,     576,    1 },
	{ "Mode 18:  1280x720  (16:9)",    1280,     720,    1 },
	{ "Mode 19:  1280x768 (16:10)",    1280,     768,    1 },
	{ "Mode 20:  1280x800 (16:10)",    1280,     800,    1 },
	{ "Mode 21:  1280x960   (4:3)",    1280,     960,    1 },
	{ "Mode 22:  1440x900 (16:10)",    1440,     900,    1 },
	{ "Mode 23:  1600x900  (16:9)",    1600,     900,    1 },
	{ "Mode 24: 1600x1000 (16:10)",    1600,    1000,    1 },
	{ "Mode 25: 1680x1050 (16:10)",    1680,    1050,    1 },
	{ "Mode 26: 1920x1080  (16:9)",    1920,    1080,    1 },
	{ "Mode 27: 1920x1200 (16:10)",    1920,    1200,    1 },
	{ "Mode 28: 1920x1440   (4:3)",    1920,    1440,    1 },
	{ "Mode 29: 2560x1600 (16:10)",    2560,    1600,    1 }
};

uint32_t cur_width;

cvar_t *r_allowSoftwareGL; // Don't abort out if a hardware visual can't be obtained
cvar_t *r_allowResize; // make window resizable

// Window cvars
cvar_t *r_fullscreen = 0;
cvar_t *r_noBorder;
cvar_t *r_centerWindow;
cvar_t *r_customwidth;
cvar_t *r_customheight;
cvar_t *r_swapInterval;
cvar_t *r_mode;
cvar_t *r_customaspect;
cvar_t *r_displayRefresh;
cvar_t *r_windowLocation;

// Window surface cvars
cvar_t *r_stencilbits;  // number of desired stencil bits
cvar_t *r_depthbits;  // number of desired depth bits
cvar_t *r_colorbits;  // number of desired color bits, only relevant for fullscreen
cvar_t *r_ignorehwgamma;
cvar_t *r_ext_multisample;

static void GLimp_InitCvars(void)
{
	//r_sdlDriver = Cvar_Get("r_sdlDriver", "", CVAR_ROM);
	r_allowSoftwareGL = Cvar_Get("r_allowSoftwareGL", "0", CVAR_LATCH);
	r_allowResize     = Cvar_Get("r_allowResize", "0", CVAR_ARCHIVE);

	// Window cvars
	r_fullscreen     = Cvar_Get("r_fullscreen", "1", CVAR_ARCHIVE | CVAR_LATCH);
	r_noBorder       = Cvar_Get("r_noborder", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_centerWindow   = Cvar_Get("r_centerWindow", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_customwidth    = Cvar_Get("r_customwidth", "1280", CVAR_ARCHIVE | CVAR_LATCH);
	r_customheight   = Cvar_Get("r_customheight", "720", CVAR_ARCHIVE | CVAR_LATCH);
	r_swapInterval   = Cvar_Get("r_swapInterval", "0", CVAR_ARCHIVE);
	r_mode           = Cvar_Get("r_mode", "-2", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE);
	r_customaspect   = Cvar_Get("r_customaspect", "1", CVAR_ARCHIVE | CVAR_LATCH);
	r_displayRefresh = Cvar_Get("r_displayRefresh", "0", CVAR_LATCH);
	Cvar_CheckRange(r_displayRefresh, 0, 240, qtrue);
	r_windowLocation = Cvar_Get("r_windowLocation", "0,-1,-1", CVAR_ARCHIVE | CVAR_PROTECTED);

	// Window render surface cvars
	r_stencilbits     = Cvar_Get("r_stencilbits", "0", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE);
	r_depthbits       = Cvar_Get("r_depthbits", "0", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE);
	r_colorbits       = Cvar_Get("r_colorbits", "0", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE);
	r_ignorehwgamma   = Cvar_Get("r_ignorehwgamma", "0", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE);
	r_ext_multisample = Cvar_Get("r_ext_multisample", "0", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE);
	Cvar_CheckRange(r_ext_multisample, 0, 4, qtrue);

	// Old modes (these are used by the UI code)
	Cvar_Get("r_oldFullscreen", "", CVAR_ARCHIVE);
	Cvar_Get("r_oldMode", "", CVAR_ARCHIVE);
}

void GLimp_Init(glconfig_t *glConfig, windowContext_t *context)
{
	Ren_Print("Initializing vitaGL\n");
	GLimp_InitCvars();
	
	if (r_mode->integer < 0) r_mode->integer = 3;
	
	glConfig->vidWidth = r_vidModes[r_mode->integer].width;
	glConfig->vidHeight = r_vidModes[r_mode->integer].height;
	glConfig->colorBits = 32;
	glConfig->depthBits = 32;
	glConfig->stencilBits = 8;
	glConfig->displayFrequency = 60;
	
	glConfig->driverType = GLDRV_ICD;
	glConfig->hardwareType = GLHW_GENERIC;
	glConfig->deviceSupportsGamma = qfalse;
	glConfig->textureCompression = TC_NONE;
	glConfig->textureEnvAddAvailable = qfalse;
	glConfig->windowAspect = ((float)r_vidModes[r_mode->integer].width) / ((float)r_vidModes[r_mode->integer].height);
	glConfig->isFullscreen = qtrue;
	
	if (!inited){
		SceKernelFreeMemorySizeInfo info;
		info.size = sizeof(SceKernelFreeMemorySizeInfo);
		sceKernelGetFreeMemorySize(&info);
		Ren_Print("Mem state: RAM: 0x%08X, CDRAM: 0x%08X, PHYCONT: 0x%08X\n", info.size_user, info.size_cdram, info.size_phycont);
		
		vglEnableRuntimeShaderCompiler(GL_FALSE);
		vglInitWithCustomSizes(0x10000, glConfig->vidWidth, glConfig->vidHeight, 1 * 1024 * 1024, info.size_cdram - 256 * 1024 - GXM_PARAM_BUF_SIZE, info.size_phycont - 1 * 1024 * 1024, SCE_GXM_MULTISAMPLE_4X);
		Ren_Print("vitaGL initialized successfully!\n");
		
		info.size = sizeof(SceKernelFreeMemorySizeInfo);
		sceKernelGetFreeMemorySize(&info);
		Ren_Print("Mem state: RAM: 0x%08X, CDRAM: 0x%08X, PHYCONT: 0x%08X\n", info.size_user, info.size_cdram, info.size_phycont);
		
		vglUseVram(GL_TRUE);
		vglUseExtraMem(GL_FALSE);
		inited = 1;
		cur_width = glConfig->vidWidth;
	}else if (glConfig->vidWidth != cur_width){ // Changed resolution in game, restarting the game
		sceAppMgrLoadExec("app0:/eboot.bin", NULL, NULL);
	}
	vglStartRendering();
	int i;
	indices = (uint16_t*)malloc(sizeof(uint16_t)*MAX_INDICES);
	for (i=0;i<MAX_INDICES;i++){
		indices[i] = i;
	}
	vglIndexPointerMapped(indices);
	glEnableClientState(GL_VERTEX_ARRAY);
	gVertexBufferPtr = (float*)malloc(0x800000);
	gColorBufferPtr = (uint8_t*)malloc(0x200000);
	gTexCoordBufferPtr = (float*)malloc(0x400000);
	gColorBuffer255 = (uint8_t*)malloc(0x6000);
	memset(gColorBuffer255, 0xFF, 0x6000);
	gVertexBuffer = gVertexBufferPtr;
	gColorBuffer = gColorBufferPtr;
	gTexCoordBuffer = gTexCoordBufferPtr;
	
	strncpy(glConfig->vendor_string, glGetString(GL_VENDOR), sizeof(glConfig->vendor_string));
	strncpy(glConfig->renderer_string, glGetString(GL_RENDERER), sizeof(glConfig->renderer_string));
	strncpy(glConfig->version_string, glGetString(GL_VERSION), sizeof(glConfig->version_string));
	strncpy(glConfig->extensions_string, glGetString(GL_EXTENSIONS), sizeof(glConfig->extensions_string));
	
	qglClearColor( 0, 0, 0, 1 );
	qglClear( GL_COLOR_BUFFER_BIT );
	
}


/*
===============
GLimp_EndFrame

Responsible for doing a swapbuffers
===============
*/
void GLimp_EndFrame( void )
{
	vglStopRendering();
	vglStartRendering();
	vglIndexPointerMapped(indices);
	gVertexBuffer = gVertexBufferPtr;
	gColorBuffer = gColorBufferPtr;
	gTexCoordBuffer = gTexCoordBufferPtr;
}
