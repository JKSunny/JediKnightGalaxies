/*
===========================================================================
Copyright (C) 1999 - 2005, Id Software, Inc.
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

// tr_init.c -- functions that are not called every frame

#include "tr_local.h"

#include <algorithm>
#include "../rd-common/tr_common.h"
#include "tr_WorldEffects.h"
#include "qcommon/MiniHeap.h"
#include "ghoul2/g2_local.h"

glconfig_t	glConfig;
glconfigExt_t glConfigExt;
glstate_t	glState;
window_t	window;
glstatic_t	gls;

cvar_t	*r_verbose;
cvar_t	*r_ignore;

cvar_t	*r_detailTextures;

cvar_t	*r_znear;
cvar_t	*r_zproj;

cvar_t	*r_skipBackEnd;

cvar_t	*r_measureOverdraw;

cvar_t	*r_inGameVideo;
cvar_t	*r_fastsky;
cvar_t	*r_drawSun;
cvar_t	*r_dynamiclight;
// rjr - removed for hacking
cvar_t	*r_dlightBacks;

cvar_t	*r_lodbias;
cvar_t	*r_lodscale;
cvar_t	*r_autolodscalevalue;

cvar_t	*r_norefresh;
cvar_t	*r_drawentities;
cvar_t	*r_drawworld;
cvar_t	*r_drawfog;
cvar_t	*r_speeds;
cvar_t	*r_fullbright;
cvar_t	*r_novis;
cvar_t	*r_nocull;
cvar_t	*r_facePlaneCull;
cvar_t	*r_cullRoofFaces; //attempted smart method of culling out upwards facing surfaces on roofs for automap shots -rww
cvar_t	*r_roofCullCeilDist; //ceiling distance cull tolerance -rww
cvar_t	*r_roofCullFloorDist; //floor distance cull tolerance -rww
cvar_t	*r_showcluster;
cvar_t	*r_nocurves;

cvar_t	*r_autoMap; //automap renderside toggle for debugging -rww
cvar_t	*r_autoMapBackAlpha; //alpha of automap bg -rww
cvar_t	*r_autoMapDisable; //don't calc it (since it's slow in debug) -rww

cvar_t	*r_dlightStyle;
cvar_t	*r_surfaceSprites;
cvar_t	*r_surfaceWeather;

cvar_t	*r_windSpeed;
cvar_t	*r_windAngle;
cvar_t	*r_windGust;
cvar_t	*r_windDampFactor;
cvar_t	*r_windPointForce;
cvar_t	*r_windPointX;
cvar_t	*r_windPointY;

cvar_t	*r_allowExtensions;

cvar_t	*r_ext_compressed_textures;
cvar_t	*r_ext_compressed_lightmaps;
cvar_t	*r_ext_preferred_tc_method;
cvar_t	*r_ext_gamma_control;
cvar_t	*r_ext_multitexture;
cvar_t	*r_ext_compiled_vertex_array;
cvar_t	*r_ext_texture_env_add;
cvar_t	*r_ext_texture_filter_anisotropic;
cvar_t	*r_gammaShaders;

cvar_t	*r_environmentMapping;

cvar_t	*r_DynamicGlow;
cvar_t	*r_DynamicGlowAllStages;
cvar_t	*r_DynamicGlowPasses;
cvar_t	*r_DynamicGlowDelta;
cvar_t	*r_DynamicGlowIntensity;
cvar_t	*r_DynamicGlowSoft;
cvar_t	*r_DynamicGlowWidth;
cvar_t	*r_DynamicGlowHeight;
cvar_t	*r_DynamicGlowScale;

cvar_t	*r_smartpicmip;

cvar_t	*r_ignoreGLErrors;
cvar_t	*r_logFile;

cvar_t	*r_primitives;
cvar_t	*r_texturebits;
cvar_t	*r_texturebitslm;

cvar_t	*r_lightmap;
cvar_t	*r_distanceCull;
cvar_t	*r_vertexLight;
cvar_t	*r_uiFullScreen;
cvar_t	*r_shadows;
cvar_t	*r_shadowRange;


cvar_t	*r_flares;
//cvar_t	*r_flareSize;
//cvar_t	*r_flareFade;
//cvar_t	*r_flareCoeff;

cvar_t	*r_nobind;
cvar_t	*r_singleShader;
cvar_t	*r_colorMipLevels;
cvar_t	*r_picmip;
cvar_t	*r_showtris;
cvar_t	*r_showsky;
cvar_t	*r_shownormals;
cvar_t	*r_finish;
cvar_t	*r_clear;
cvar_t	*r_markcount;
cvar_t	*r_textureMode;
cvar_t	*r_offsetFactor;
cvar_t	*r_offsetUnits;
cvar_t	*r_gamma;
cvar_t	*r_intensity;
cvar_t	*r_lockpvs;
cvar_t	*r_noportals;
cvar_t	*r_portalOnly;

cvar_t	*r_subdivisions;
cvar_t	*r_lodCurveError;



cvar_t	*r_overBrightBits;
cvar_t	*r_mapOverBrightBits;

cvar_t	*r_debugSurface;
cvar_t	*r_simpleMipMaps;

cvar_t	*r_showImages;

cvar_t	*r_ambientScale;
cvar_t	*r_directedScale;
cvar_t	*r_debugLight;
cvar_t	*r_debugSort;

cvar_t	*r_marksOnTriangleMeshes;

cvar_t	*r_aspectCorrectFonts;
cvar_t	*cl_ratioFix;
cvar_t	*r_patchStitching;

// Vulkan
cvar_t	*r_defaultImage;
cvar_t	*r_device;
//cvar_t	*r_stencilbits;
cvar_t	*r_ext_multisample;
cvar_t	*r_ext_supersample;
cvar_t	*r_ext_alpha_to_coverage;
cvar_t	*r_fbo;
cvar_t	*r_hdr;
cvar_t	*r_ext_max_anisotropy;
cvar_t	*r_mapGreyScale;
cvar_t	*r_greyscale;
cvar_t	*r_dither;
cvar_t	*r_presentBits;
cvar_t	*r_bloom;
cvar_t	*r_bloom_threshold;
cvar_t	*r_bloom_intensity;
cvar_t	*r_bloom_threshold_mode;
cvar_t	*r_bloom_modulate; 
cvar_t	*r_renderWidth;
cvar_t	*r_renderHeight;
cvar_t	*r_renderScale;
cvar_t	*r_ignorehwgamma;

#ifdef USE_PMLIGHT
cvar_t	*r_dlightMode;
cvar_t	*r_dlightScale;
cvar_t	*r_dlightIntensity;
#endif
cvar_t	*r_dlightSaturation;
cvar_t	*r_roundImagesDown;
cvar_t	*r_nomip;
#ifdef USE_VBO
cvar_t	*r_vbo;
cvar_t	*r_vbo_models;
#endif

// the limits apply to the sum of all scenes in a frame --
// the main view, all the 3D icons, etc
#define	DEFAULT_MAX_POLYS		600
#define	DEFAULT_MAX_POLYVERTS	3000
static cvar_t	*r_maxpolys;
static cvar_t	*r_maxpolyverts;
int		max_polys;
int		max_polyverts;

cvar_t	*r_modelpoolmegs;

/*
Ghoul2 Insert Start
*/
#ifdef _DEBUG
cvar_t	*r_noPrecacheGLA;
#endif

cvar_t	*r_noServerGhoul2;
cvar_t	*r_Ghoul2AnimSmooth=0;
cvar_t	*r_Ghoul2UnSqashAfterSmooth=0;
//cvar_t	*r_Ghoul2UnSqash;
//cvar_t	*r_Ghoul2TimeBase=0; from single player
//cvar_t	*r_Ghoul2NoLerp;
//cvar_t	*r_Ghoul2NoBlend;
//cvar_t	*r_Ghoul2BlendMultiplier=0;

cvar_t	*broadsword=0;
cvar_t	*broadsword_kickbones=0;
cvar_t	*broadsword_kickorigin=0;
cvar_t	*broadsword_playflop=0;
cvar_t	*broadsword_dontstopanim=0;
cvar_t	*broadsword_waitforshot=0;
cvar_t	*broadsword_smallbbox=0;
cvar_t	*broadsword_extra1=0;
cvar_t	*broadsword_extra2=0;

cvar_t	*broadsword_effcorr=0;
cvar_t	*broadsword_ragtobase=0;
cvar_t	*broadsword_dircap=0;

/*
Ghoul2 Insert End
*/

cvar_t *se_language;

cvar_t *r_aviMotionJpegQuality;
cvar_t *r_screenshotJpegQuality;

// Vulkan
#include "vk_local.h"
Vk_Instance vk;
Vk_World	vk_world;

#if 0
#if !defined(__APPLE__)
PFNGLSTENCILOPSEPARATEPROC qglStencilOpSeparate;
#endif

PFNGLACTIVETEXTUREARBPROC qglActiveTextureARB;
PFNGLCLIENTACTIVETEXTUREARBPROC qglClientActiveTextureARB;
PFNGLMULTITEXCOORD2FARBPROC qglMultiTexCoord2fARB;
#if !defined(__APPLE__)
PFNGLTEXIMAGE3DPROC qglTexImage3D;
PFNGLTEXSUBIMAGE3DPROC qglTexSubImage3D;
#endif

PFNGLCOMBINERPARAMETERFVNVPROC qglCombinerParameterfvNV;
PFNGLCOMBINERPARAMETERIVNVPROC qglCombinerParameterivNV;
PFNGLCOMBINERPARAMETERFNVPROC qglCombinerParameterfNV;
PFNGLCOMBINERPARAMETERINVPROC qglCombinerParameteriNV;
PFNGLCOMBINERINPUTNVPROC qglCombinerInputNV;
PFNGLCOMBINEROUTPUTNVPROC qglCombinerOutputNV;

PFNGLFINALCOMBINERINPUTNVPROC qglFinalCombinerInputNV;
PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC qglGetCombinerInputParameterfvNV;
PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC qglGetCombinerInputParameterivNV;
PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC qglGetCombinerOutputParameterfvNV;
PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC qglGetCombinerOutputParameterivNV;
PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC qglGetFinalCombinerInputParameterfvNV;
PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC qglGetFinalCombinerInputParameterivNV;

PFNGLPROGRAMSTRINGARBPROC qglProgramStringARB;
PFNGLBINDPROGRAMARBPROC qglBindProgramARB;
PFNGLDELETEPROGRAMSARBPROC qglDeleteProgramsARB;
PFNGLGENPROGRAMSARBPROC qglGenProgramsARB;
PFNGLPROGRAMENVPARAMETER4DARBPROC qglProgramEnvParameter4dARB;
PFNGLPROGRAMENVPARAMETER4DVARBPROC qglProgramEnvParameter4dvARB;
PFNGLPROGRAMENVPARAMETER4FARBPROC qglProgramEnvParameter4fARB;
PFNGLPROGRAMENVPARAMETER4FVARBPROC qglProgramEnvParameter4fvARB;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC qglProgramLocalParameter4dARB;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC qglProgramLocalParameter4dvARB;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC qglProgramLocalParameter4fARB;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC qglProgramLocalParameter4fvARB;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC qglGetProgramEnvParameterdvARB;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC qglGetProgramEnvParameterfvARB;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC qglGetProgramLocalParameterdvARB;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC qglGetProgramLocalParameterfvARB;
PFNGLGETPROGRAMIVARBPROC qglGetProgramivARB;
PFNGLGETPROGRAMSTRINGARBPROC qglGetProgramStringARB;
PFNGLISPROGRAMARBPROC qglIsProgramARB;

PFNGLLOCKARRAYSEXTPROC qglLockArraysEXT;
PFNGLUNLOCKARRAYSEXTPROC qglUnlockArraysEXT;
#endif

bool g_bTextureRectangleHack = false;

void RE_SetLightStyle( int style, int color );
void RE_GetBModelVerts( int bmodelIndex, vec3_t *verts, vec3_t normal );

void R_Set2DRatio( void ) {
	if (cl_ratioFix->integer)
		tr.widthRatioCoef = ((float)(SCREEN_WIDTH * gls.windowHeight) / (float)(SCREEN_HEIGHT * gls.windowWidth));
	else
		tr.widthRatioCoef = 1.0f;

	if (tr.widthRatioCoef > 1)
		tr.widthRatioCoef = 1.0f;
}

/*
==============================================================================

						SCREEN SHOTS

==============================================================================
*/

/*
==================
RB_ReadPixels

Reads an image but takes care of alignment issues for reading RGB images.

Reads a minimum offset for where the RGB data starts in the image from
integer stored at pointer offset. When the function has returned the actual
offset was written back to address offset. This address will always have an
alignment of packAlign to ensure efficient copying.

Stores the length of padding after a line of pixels to address padlen

Return value must be freed with Hunk_FreeTempMemory()
==================
*/

byte *RB_ReadPixels( int x, int y, int width, int height, size_t *offset, int *padlen, int lineAlign )
{
	byte *buffer, *bufstart;
	int bufAlign, linelen;
	int packAlign = 1;

	linelen = width * 3;

	bufAlign = MAX(packAlign, 16); // for SIMD

	// Allocate a few more bytes so that we can choose an alignment we like
	//buffer = ri->Hunk_AllocateTempMemory(padwidth * height + *offset + bufAlign - 1);
	buffer = (byte*)Hunk_AllocateTempMemory(width * height * 4 + *offset + bufAlign - 1);
	bufstart = (byte*)PADP((intptr_t)buffer + *offset, bufAlign);

	vk_read_pixels(bufstart, width, height);

	*offset = bufstart - buffer;
	*padlen = PAD(linelen, packAlign) - linelen;

	return buffer;
}

/*
==================
R_TakeScreenshot
==================
*/
void R_TakeScreenshot( int x, int y, int width, int height, char *fileName ) {
	byte *allbuf, *buffer;
	byte *srcptr, *destptr;
	byte *endline, *endmem;
	byte temp;

	int linelen, padlen;
	size_t offset = 18, memcount;

	allbuf = RB_ReadPixels(x, y, width, height, &offset, &padlen, 0);
	buffer = allbuf + offset - 18;

	Com_Memset (buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = width & 255;
	buffer[13] = width >> 8;
	buffer[14] = height & 255;
	buffer[15] = height >> 8;
	buffer[16] = 24;	// pixel size

	// swap rgb to bgr and remove padding from line endings
	linelen = width * 3;

	srcptr = destptr = allbuf + offset;
	endmem = srcptr + (linelen + padlen) * height;

	while(srcptr < endmem)
	{
		endline = srcptr + linelen;

		while(srcptr < endline)
		{
			temp = srcptr[0];
			*destptr++ = srcptr[2];
			*destptr++ = srcptr[1];
			*destptr++ = temp;

			srcptr += 3;
		}

		// Skip the pad
		srcptr += padlen;
	}

	memcount = linelen * height;

	// gamma correct
	if(glConfig.deviceSupportsGamma && !glConfigExt.doGammaCorrectionWithShaders)
		R_GammaCorrect(allbuf + offset, memcount);

	ri->FS_WriteFile(fileName, buffer, memcount + 18);

	ri->Hunk_FreeTempMemory(allbuf);
}

/*
==================
R_TakeScreenshotPNG
==================
*/
void R_TakeScreenshotPNG( int x, int y, int width, int height, char *fileName ) {
	byte *buffer=NULL;
	size_t offset=0;
	int padlen=0;

	buffer = RB_ReadPixels( x, y, width, height, &offset, &padlen, 0);
	RE_SavePNG( fileName, buffer, width, height, 3 );
	ri->Hunk_FreeTempMemory( buffer );
}

/*
==================
R_TakeScreenshotJPEG
==================
*/
void R_TakeScreenshotJPEG( int x, int y, int width, int height, char *fileName ) {
	byte *buffer;
	size_t offset = 0, memcount;
	int padlen;

	buffer = RB_ReadPixels(x, y, width, height, &offset, &padlen, 0);
	memcount = (width * 3 + padlen) * height;

	// gamma correct
	if(glConfig.deviceSupportsGamma && !glConfigExt.doGammaCorrectionWithShaders)
		R_GammaCorrect(buffer + offset, memcount);

	RE_SaveJPG(fileName, r_screenshotJpegQuality->integer, width, height, buffer + offset, padlen);
	ri->Hunk_FreeTempMemory(buffer);
}

/*
==================
R_ScreenshotFilename
==================
*/
void R_ScreenshotFilename( char *buf, int bufSize, const char *ext ) {
	time_t rawtime;
	char timeStr[32] = {0}; // should really only reach ~19 chars

	time( &rawtime );
	strftime( timeStr, sizeof( timeStr ), "%Y-%m-%d_%H-%M-%S", localtime( &rawtime ) ); // or gmtime

	Com_sprintf( buf, bufSize, "screenshots/shot%s.%s", timeStr, ext );
}

/*
====================
R_LevelShot

levelshots are specialized 256*256 thumbnails for
the menu system, sampled down from full screen distorted images
====================
*/
#define LEVELSHOTSIZE 256
static void R_LevelShot( void ) {
	char		checkname[MAX_OSPATH];
	byte		*buffer;
	byte		*source, *allsource;
	byte		*src, *dst;
	size_t		offset = 0;
	int			padlen;
	int			x, y;
	int			r, g, b;
	float		xScale, yScale;
	int			xx, yy;

	Com_sprintf( checkname, sizeof(checkname), "levelshots/%s.tga", tr.world->baseName );

	allsource = RB_ReadPixels(0, 0, gls.captureWidth, gls.captureHeight, &offset, &padlen, 0);
	source = allsource + offset;

	buffer = (byte *)ri->Hunk_AllocateTempMemory(LEVELSHOTSIZE * LEVELSHOTSIZE*3 + 18);
	Com_Memset (buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = LEVELSHOTSIZE & 255;
	buffer[13] = LEVELSHOTSIZE >> 8;
	buffer[14] = LEVELSHOTSIZE & 255;
	buffer[15] = LEVELSHOTSIZE >> 8;
	buffer[16] = 24;	// pixel size

	// resample from source
	xScale = glConfig.vidWidth / (4.0*LEVELSHOTSIZE);
	yScale = glConfig.vidHeight / (3.0*LEVELSHOTSIZE);
	for ( y = 0 ; y < LEVELSHOTSIZE ; y++ ) {
		for ( x = 0 ; x < LEVELSHOTSIZE ; x++ ) {
			r = g = b = 0;
			for ( yy = 0 ; yy < 3 ; yy++ ) {
				for ( xx = 0 ; xx < 4 ; xx++ ) {
					src = source + 3 * ( glConfig.vidWidth * (int)( (y*3+yy)*yScale ) + (int)( (x*4+xx)*xScale ) );
					r += src[0];
					g += src[1];
					b += src[2];
				}
			}
			dst = buffer + 18 + 3 * ( y * LEVELSHOTSIZE + x );
			dst[0] = b / 12;
			dst[1] = g / 12;
			dst[2] = r / 12;
		}
	}

	// gamma correct
	if ( ( tr.overbrightBits > 0 ) && glConfig.deviceSupportsGamma && !glConfigExt.doGammaCorrectionWithShaders ) {
		R_GammaCorrect( buffer + 18, LEVELSHOTSIZE * LEVELSHOTSIZE * 3 );
	}

	ri->FS_WriteFile( checkname, buffer, LEVELSHOTSIZE * LEVELSHOTSIZE*3 + 18 );

	ri->Hunk_FreeTempMemory( buffer );
	ri->Hunk_FreeTempMemory( allsource );

	vk_debug("[skipnotify]Wrote %s\n", checkname );
}

void R_ScreenShot_f ( void ) {
	char checkname[MAX_OSPATH] = {0};
	qboolean silent = qfalse;
	int			typeMask;
	const char *ext;

	if (ri->VK_IsMinimized() && !R_CanMinimize()) {
		ri->Printf(PRINT_WARNING, "WARNING: unable to take screenshot when minimized because FBO is not available/enabled.\n");
		return;
	}

	if ( !strcmp( ri->Cmd_Argv(1), "levelshot" ) ) {
		R_LevelShot();
		return;
	}

	if (Q_stricmp(ri->Cmd_Argv(0), "screenshot_tga") == 0) {
		typeMask = SCREENSHOT_TGA;
		ext = "tga";
	}
	else if (Q_stricmp(ri->Cmd_Argv(0), "screenshot_png") == 0) {
		typeMask = SCREENSHOT_PNG;
		ext = "png";
	}
	else {
		typeMask = SCREENSHOT_JPG;
		ext = "jpg";
	}

	// check if already scheduled
	if (backEnd.screenshotMask & typeMask)
		return;

	if ( !strcmp( ri->Cmd_Argv(1), "silent" ) )
		silent = qtrue;

	if ( ri->Cmd_Argc() == 2 && !silent ) {
		// explicit filename
		Com_sprintf( checkname, sizeof( checkname ), "screenshots/%s.%s", ri->Cmd_Argv( 1 ), ext );
	}
	else {
		// timestamp the filename
		R_ScreenshotFilename( checkname, sizeof( checkname ), ext );

		if ( ri->FS_FileExists( checkname ) ) {
			vk_debug("ScreenShot: Couldn't create a file\n" );
			return;
 		}
	}

	// we will make the screenshot right at the end of RE_EndFrame()
	backEnd.screenshotMask |= typeMask;
	if (typeMask == SCREENSHOT_JPG) {
		backEnd.screenShotJPGsilent = silent;
		Q_strncpyz(backEnd.screenshotJPG, checkname, sizeof(backEnd.screenshotJPG));
	}
	else if (typeMask == SCREENSHOT_PNG) {
		backEnd.screenShotPNGsilent = silent;
		Q_strncpyz(backEnd.screenshotPNG, checkname, sizeof(backEnd.screenshotPNG));
	}
	else {
		backEnd.screenShotTGAsilent = silent;
		Q_strncpyz(backEnd.screenshotTGA, checkname, sizeof(backEnd.screenshotTGA));
	}
}

/*
==================
RB_TakeVideoFrameCmd
==================
*/
const void *RB_TakeVideoFrameCmd( const void *data )
{
	const videoFrameCommand_t *cmd;
	byte		*cBuf;
	size_t		memcount, linelen;
	int			padwidth, avipadwidth, padlen, avipadlen;
	int			packAlign;

	cmd = (const videoFrameCommand_t*)data;

	packAlign = 1;

	linelen = cmd->width * 3;

	// Alignment stuff for glReadPixels
	padwidth = PAD(linelen, packAlign);
	padlen = padwidth - linelen;
	// AVI line padding
	avipadwidth = PAD(linelen, AVI_LINE_PADDING);
	avipadlen = avipadwidth - linelen;

	cBuf = (byte*)PADP(cmd->captureBuffer, packAlign);

	vk_read_pixels(cBuf, cmd->width, cmd->height);

	memcount = padwidth * cmd->height;

	// gamma correct
	if (glConfig.deviceSupportsGamma)
		R_GammaCorrect(cBuf, memcount);

	if (cmd->motionJpeg)
	{
		memcount = RE_SaveJPGToBuffer(cmd->encodeBuffer, linelen * cmd->height,
			r_aviMotionJpegQuality->integer,
			cmd->width, cmd->height, cBuf, padlen);
		ri->CL_WriteAVIVideoFrame(cmd->encodeBuffer, memcount);
	}
	else
	{
		byte* lineend, * memend;
		byte* srcptr, * destptr;

		srcptr = cBuf;
		destptr = cmd->encodeBuffer;
		memend = srcptr + memcount;

		// swap R and B and remove line paddings
		while (srcptr < memend)
		{
			lineend = srcptr + linelen;
			while (srcptr < lineend)
			{
				*destptr++ = srcptr[2];
				*destptr++ = srcptr[1];
				*destptr++ = srcptr[0];
				srcptr += 3;
			}

			Com_Memset(destptr, '\0', avipadlen);
			destptr += avipadlen;

			srcptr += padlen;
		}

		ri->CL_WriteAVIVideoFrame(cmd->encodeBuffer, avipadwidth * cmd->height);
	}

	return (const void*)(cmd + 1);
}

void R_RemapSkyShader_f ( void ) {
	int num;

	if (ri->Cmd_Argc() != 2 || !strlen(ri->Cmd_Argv(1))) {
		vk_debug("Usage: /remapSky <new>\n");
		return;
	}

	for (num = 0; num < tr.numShaders; num++) {
		if (tr.shaders[num]->sky)
		{
			R_RemapShader(tr.shaders[num]->name, ri->Cmd_Argv(1), NULL);
		}
	}
}

void R_ClearRemaps_f( void ) {
	int num;

	for (num = 0; num < tr.numShaders; num++) {
		tr.shaders[num]->remappedShader = NULL;
	}
}

typedef struct consoleCommand_s {
	const char	*cmd;
	xcommand_t	func;
} consoleCommand_t;

static consoleCommand_t	commands[] = {
	{ "imagelist",			R_ImageList_f },
	{ "shaderlist",			R_ShaderList_f },
	{ "skinlist",			R_SkinList_f },
	{ "fontlist",			R_FontList_f },
	{ "screenshot",			R_ScreenShot_f },
	{ "screenshot_png",		R_ScreenShot_f },
	{ "screenshot_tga",		R_ScreenShot_f },
	{ "gfxinfo",			GfxInfo_f },
	{ "r_we",				R_WorldEffect_f },
	{ "imagecacheinfo",		RE_RegisterImages_Info_f },
	{ "modellist",			R_Modellist_f },
	{ "modelcacheinfo",		RE_RegisterModels_Info_f },
	{ "r_cleardecals",		RE_ClearDecals },
	{ "remapSky",			R_RemapSkyShader_f },
	{ "clearRemaps",		R_ClearRemaps_f },
	{ "vkinfo",				vk_info_f }
};

static const size_t numCommands = ARRAY_LEN( commands );

#ifdef _DEBUG
#define MIN_PRIMITIVES -1
#else
#define MIN_PRIMITIVES 0
#endif
#define MAX_PRIMITIVES 3

/*
===============
R_Register
===============
*/
void R_Register( void )
{
	//FIXME: lol badness
	se_language = ri->Cvar_Get("se_language", "english", CVAR_ARCHIVE | CVAR_NORESTART);
	//
	// latched and archived variables
	//
	r_allowExtensions					= ri->Cvar_Get( "r_allowExtensions",				"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_compressed_textures			= ri->Cvar_Get( "r_ext_compress_textures",			"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_compressed_lightmaps			= ri->Cvar_Get( "r_ext_compress_lightmaps",			"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_preferred_tc_method			= ri->Cvar_Get( "r_ext_preferred_tc_method",		"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_gamma_control					= ri->Cvar_Get( "r_ext_gamma_control",				"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_multitexture					= ri->Cvar_Get( "r_ext_multitexture",				"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_compiled_vertex_array			= ri->Cvar_Get( "r_ext_compiled_vertex_array",		"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_texture_env_add				= ri->Cvar_Get( "r_ext_texture_env_add",			"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_ext_texture_filter_anisotropic	= ri->Cvar_Get( "r_ext_texture_filter_anisotropic",	"16",						CVAR_ARCHIVE );
	r_gammaShaders						= ri->Cvar_Get( "r_gammaShaders",					"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_environmentMapping				= ri->Cvar_Get( "r_environmentMapping",				"1",						CVAR_ARCHIVE );
	r_DynamicGlow						= ri->Cvar_Get( "r_DynamicGlow",					"0",						CVAR_ARCHIVE );
	r_DynamicGlowAllStages				= ri->Cvar_Get( "r_DynamicGlowAllStages",			"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_DynamicGlowPasses					= ri->Cvar_Get( "r_DynamicGlowPasses",				"5",						CVAR_ARCHIVE );
	r_DynamicGlowDelta					= ri->Cvar_Get( "r_DynamicGlowDelta",				"0.8f",						CVAR_ARCHIVE );
	r_DynamicGlowIntensity				= ri->Cvar_Get( "r_DynamicGlowIntensity",			"1.13f",					CVAR_ARCHIVE );
	r_DynamicGlowSoft					= ri->Cvar_Get( "r_DynamicGlowSoft",				"1",						CVAR_ARCHIVE );
	r_DynamicGlowWidth					= ri->Cvar_Get( "r_DynamicGlowWidth",				"320",						CVAR_ARCHIVE|CVAR_LATCH );
	r_DynamicGlowHeight					= ri->Cvar_Get( "r_DynamicGlowHeight",				"240",						CVAR_ARCHIVE|CVAR_LATCH );
	r_picmip							= ri->Cvar_Get( "r_picmip",							"0",						CVAR_ARCHIVE|CVAR_LATCH );
	ri->Cvar_CheckRange( r_picmip, 0, 16, qtrue );
	r_smartpicmip						= ri->Cvar_Get( "r_smartpicmip",						"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_colorMipLevels					= ri->Cvar_Get( "r_colorMipLevels",					"0",						CVAR_LATCH );
	r_detailTextures					= ri->Cvar_Get( "r_detailtextures",					"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_texturebits						= ri->Cvar_Get( "r_texturebits",					"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_texturebitslm						= ri->Cvar_Get( "r_texturebitslm",					"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_overBrightBits					= ri->Cvar_Get( "r_overBrightBits",					"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_mapOverBrightBits					= ri->Cvar_Get( "r_mapOverBrightBits",				"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_simpleMipMaps						= ri->Cvar_Get( "r_simpleMipMaps",					"1",						CVAR_ARCHIVE|CVAR_LATCH );
	r_vertexLight						= ri->Cvar_Get( "r_vertexLight",					"0",						CVAR_ARCHIVE|CVAR_LATCH );
	r_uiFullScreen						= ri->Cvar_Get( "r_uifullscreen",					"0",						CVAR_NONE );
	r_subdivisions						= ri->Cvar_Get( "r_subdivisions",					"4",						CVAR_ARCHIVE|CVAR_LATCH );
	ri->Cvar_CheckRange( r_subdivisions, 4, 80, qfalse );
	
	r_fullbright						= ri->Cvar_Get( "r_fullbright",						"0",						CVAR_CHEAT );
	r_intensity							= ri->Cvar_Get( "r_intensity",						"1",						CVAR_LATCH );
	r_singleShader						= ri->Cvar_Get( "r_singleShader",					"0",						CVAR_CHEAT|CVAR_LATCH );
	r_lodCurveError						= ri->Cvar_Get( "r_lodCurveError",					"250",						CVAR_ARCHIVE );
	r_lodbias							= ri->Cvar_Get( "r_lodbias",						"0",						CVAR_ARCHIVE );
	r_autolodscalevalue					= ri->Cvar_Get( "r_autolodscalevalue",				"0",						CVAR_ROM );
	r_flares							= ri->Cvar_Get( "r_flares",							"1",						CVAR_ARCHIVE );
	r_znear								= ri->Cvar_Get( "r_znear",							"4",						CVAR_ARCHIVE );
	ri->Cvar_CheckRange( r_znear, 0.001f, 10, qfalse );
	r_zproj								= ri->Cvar_Get("r_zproj",							"64",						CVAR_ARCHIVE );
	r_ignoreGLErrors					= ri->Cvar_Get( "r_ignoreGLErrors",					"1",						CVAR_ARCHIVE );
	r_fastsky							= ri->Cvar_Get( "r_fastsky",						"0",						CVAR_ARCHIVE );
	r_inGameVideo						= ri->Cvar_Get( "r_inGameVideo",					"1",						CVAR_ARCHIVE );
	r_drawSun							= ri->Cvar_Get( "r_drawSun",						"0",						CVAR_ARCHIVE );
	r_dynamiclight						= ri->Cvar_Get( "r_dynamiclight",					"1",						CVAR_ARCHIVE );
	// rjr - removed for hacking
//	r_dlightBacks						= ri->Cvar_Get( "r_dlightBacks",					"1",						CVAR_CHEAT );
	r_finish							= ri->Cvar_Get( "r_finish",							"0",						CVAR_ARCHIVE );
	r_textureMode						= ri->Cvar_Get( "r_textureMode",					"GL_LINEAR_MIPMAP_NEAREST",	CVAR_ARCHIVE );
	r_markcount							= ri->Cvar_Get( "r_markcount",						"100",						CVAR_ARCHIVE );
	r_gamma								= ri->Cvar_Get( "r_gamma",							"1",						CVAR_ARCHIVE );
	r_facePlaneCull						= ri->Cvar_Get( "r_facePlaneCull",					"1",						CVAR_ARCHIVE );
	r_cullRoofFaces						= ri->Cvar_Get( "r_cullRoofFaces",					"0",						CVAR_CHEAT ); //attempted smart method of culling out upwards facing surfaces on roofs for automap shots -rww
	r_roofCullCeilDist					= ri->Cvar_Get( "r_roofCullCeilDist",				"256",						CVAR_CHEAT ); //attempted smart method of culling out upwards facing surfaces on roofs for automap shots -rww
	r_roofCullFloorDist					= ri->Cvar_Get( "r_roofCeilFloorDist",				"128",						CVAR_CHEAT ); //attempted smart method of culling out upwards facing surfaces on roofs for automap shots -rww
	r_primitives						= ri->Cvar_Get( "r_primitives",						"0",						CVAR_ARCHIVE );
	ri->Cvar_CheckRange( r_primitives, MIN_PRIMITIVES, MAX_PRIMITIVES, qtrue );
	r_ambientScale						= ri->Cvar_Get( "r_ambientScale",					"0.6",						CVAR_CHEAT );
	r_directedScale						= ri->Cvar_Get( "r_directedScale",					"1",						CVAR_CHEAT );
	r_autoMap							= ri->Cvar_Get( "r_autoMap",						"0",						CVAR_ARCHIVE ); //automap renderside toggle for debugging -rww
	r_autoMapBackAlpha					= ri->Cvar_Get( "r_autoMapBackAlpha",				"0",						CVAR_NONE ); //alpha of automap bg -rww
	r_autoMapDisable					= ri->Cvar_Get( "r_autoMapDisable",					"1",						CVAR_NONE );
	r_showImages						= ri->Cvar_Get( "r_showImages",						"0",						CVAR_CHEAT );
	r_debugLight						= ri->Cvar_Get( "r_debuglight",						"0",						CVAR_TEMP );
	r_debugSort							= ri->Cvar_Get( "r_debugSort",						"0",						CVAR_CHEAT );
	r_dlightStyle						= ri->Cvar_Get( "r_dlightStyle",					"1",						CVAR_TEMP );
	r_surfaceSprites					= ri->Cvar_Get( "r_surfaceSprites",					"1",						CVAR_ARCHIVE );
	r_surfaceWeather					= ri->Cvar_Get( "r_surfaceWeather",					"0",						CVAR_TEMP );
	r_windSpeed							= ri->Cvar_Get( "r_windSpeed",						"0",						CVAR_NONE );
	r_windAngle							= ri->Cvar_Get( "r_windAngle",						"0",						CVAR_NONE );
	r_windGust							= ri->Cvar_Get( "r_windGust",						"0",						CVAR_NONE );
	r_windDampFactor					= ri->Cvar_Get( "r_windDampFactor",					"0.1",						CVAR_NONE );
	r_windPointForce					= ri->Cvar_Get( "r_windPointForce",					"0",						CVAR_NONE );
	r_windPointX						= ri->Cvar_Get( "r_windPointX",						"0",						CVAR_NONE );
	r_windPointY						= ri->Cvar_Get( "r_windPointY",						"0",						CVAR_NONE );
	r_nocurves							= ri->Cvar_Get( "r_nocurves",						"0",						CVAR_CHEAT );
	r_drawworld							= ri->Cvar_Get( "r_drawworld",						"1",						CVAR_CHEAT );
	r_drawfog							= ri->Cvar_Get( "r_drawfog",						"2",						CVAR_CHEAT );
	r_lightmap							= ri->Cvar_Get( "r_lightmap",						"0",						CVAR_CHEAT );
	r_portalOnly						= ri->Cvar_Get( "r_portalOnly",						"0",						CVAR_CHEAT );
	r_skipBackEnd						= ri->Cvar_Get( "r_skipBackEnd",					"0",						CVAR_CHEAT );
	r_measureOverdraw					= ri->Cvar_Get( "r_measureOverdraw",				"0",						CVAR_CHEAT );
	r_lodscale							= ri->Cvar_Get( "r_lodscale",						"5",						CVAR_NONE );
	r_norefresh							= ri->Cvar_Get( "r_norefresh",						"0",						CVAR_CHEAT );
	r_drawentities						= ri->Cvar_Get( "r_drawentities",					"1",						CVAR_CHEAT );
	r_ignore							= ri->Cvar_Get( "r_ignore",							"1",						CVAR_CHEAT );
	r_nocull							= ri->Cvar_Get( "r_nocull",							"0",						CVAR_CHEAT );
	r_novis								= ri->Cvar_Get( "r_novis",							"0",						CVAR_CHEAT );
	r_showcluster						= ri->Cvar_Get( "r_showcluster",					"0",						CVAR_CHEAT );
	r_speeds							= ri->Cvar_Get( "r_speeds",							"0",						CVAR_CHEAT );
	r_verbose							= ri->Cvar_Get( "r_verbose",						"0",						CVAR_CHEAT );
	r_logFile							= ri->Cvar_Get( "r_logFile",						"0",						CVAR_CHEAT );
	r_debugSurface						= ri->Cvar_Get( "r_debugSurface",					"0",						CVAR_CHEAT );
	r_nobind							= ri->Cvar_Get( "r_nobind",							"0",						CVAR_CHEAT );
	r_showtris							= ri->Cvar_Get( "r_showtris",						"0",						CVAR_CHEAT );
	r_showsky							= ri->Cvar_Get( "r_showsky",						"0",						CVAR_CHEAT );
	r_shownormals						= ri->Cvar_Get( "r_shownormals",					"0",						CVAR_CHEAT );
	r_clear								= ri->Cvar_Get( "r_clear",							"0",						CVAR_CHEAT );
	r_offsetFactor						= ri->Cvar_Get( "r_offsetfactor",					"-1",						CVAR_CHEAT );
	r_offsetUnits						= ri->Cvar_Get( "r_offsetunits",					"-2",						CVAR_CHEAT );
	r_lockpvs							= ri->Cvar_Get( "r_lockpvs",						"0",						CVAR_CHEAT );
	r_noportals							= ri->Cvar_Get( "r_noportals",						"0",						CVAR_CHEAT );
	r_shadows							= ri->Cvar_Get( "cg_shadows",						"1",						CVAR_NONE );
	r_shadowRange						= ri->Cvar_Get( "r_shadowRange",					"1000",						CVAR_NONE );
	r_marksOnTriangleMeshes				= ri->Cvar_Get( "r_marksOnTriangleMeshes",			"0",						CVAR_ARCHIVE );
	r_maxpolys							= ri->Cvar_Get( "r_maxpolys",						XSTRING( DEFAULT_MAX_POLYS ),		CVAR_NONE );
	r_maxpolyverts						= ri->Cvar_Get( "r_maxpolyverts",					XSTRING( DEFAULT_MAX_POLYVERTS ),	CVAR_NONE );

	// Additions
	r_aspectCorrectFonts				= ri->Cvar_Get( "r_aspectCorrectFonts",				"0",						CVAR_ARCHIVE);
	cl_ratioFix							= ri->Cvar_Get( "cl_ratioFix",						"1",						CVAR_ARCHIVE);
	r_patchStitching					= ri->Cvar_Get( "r_patchStitching",					"1",						CVAR_ARCHIVE );

	// Vulkan
	r_defaultImage						= ri->Cvar_Get("r_defaultImage",						"",						CVAR_ARCHIVE | CVAR_LATCH);
	r_device							= ri->Cvar_Get("r_device",							"-1",						CVAR_ARCHIVE | CVAR_LATCH);
	ri->Cvar_CheckRange(r_device, -2, 8, qtrue);
	r_device->modified					= qfalse;

	//r_stencilbits						= ri->Cvar_Get("r_stencilbits",						"8",						CVAR_ARCHIVE | CVAR_LATCH);
	r_ext_multisample					= ri->Cvar_Get("r_ext_multisample",					"0",						CVAR_ARCHIVE | CVAR_LATCH);
	ri->Cvar_CheckRange(r_ext_multisample, 0, 64, qtrue);
	r_ext_supersample					= ri->Cvar_Get("r_ext_supersample",					"0",						CVAR_ARCHIVE | CVAR_LATCH);
	ri->Cvar_CheckRange(r_ext_supersample, 0, 1, qtrue);
	r_ext_alpha_to_coverage				= ri->Cvar_Get("r_ext_alpha_to_coverage",			"0",						CVAR_ARCHIVE | CVAR_LATCH);
	ri->Cvar_CheckRange(r_ext_alpha_to_coverage, 0, 1, qtrue);
	r_fbo								= ri->Cvar_Get("r_fbo",								"0",						CVAR_ARCHIVE | CVAR_LATCH);
	r_hdr								= ri->Cvar_Get("r_hdr",								"1",						CVAR_ARCHIVE | CVAR_LATCH);
	r_mapGreyScale						= ri->Cvar_Get("r_mapGreyScale",						"0",					CVAR_ARCHIVE | CVAR_LATCH);
	ri->Cvar_CheckRange(r_mapGreyScale, -1, 1, qfalse);
	r_ext_max_anisotropy				= ri->Cvar_Get("r_ext_max_anisotropy",				"2",						CVAR_ARCHIVE | CVAR_LATCH);
	ri->Cvar_CheckRange(r_ext_max_anisotropy, 1, 16, qtrue);
	r_greyscale							= ri->Cvar_Get("r_greyscale",						"0",						CVAR_ARCHIVE);
	ri->Cvar_CheckRange(r_greyscale, -1, 1, qfalse);
	r_dither							= ri->Cvar_Get("r_dither",							"0",						CVAR_ARCHIVE);
	ri->Cvar_CheckRange(r_dither, 0, 1, qtrue);
	r_presentBits						= ri->Cvar_Get("r_presentBits",						"24",						CVAR_ARCHIVE | CVAR_LATCH );
	ri->Cvar_CheckRange(r_presentBits, 16, 30, qtrue);
	r_bloom								= ri->Cvar_Get("r_bloom",							"0",						CVAR_ARCHIVE | CVAR_LATCH );
	ri->Cvar_CheckRange(r_bloom, 0, 1, qtrue);
	r_bloom_threshold					= ri->Cvar_Get("r_bloom_threshold",					"0.05",						CVAR_ARCHIVE | CVAR_LATCH );
	ri->Cvar_CheckRange(r_bloom_threshold, 0.01f, 1, qfalse);
	r_bloom_threshold_mode				= ri->Cvar_Get("r_bloom_threshold_mode",				"0",					CVAR_ARCHIVE);
	r_bloom_intensity					= ri->Cvar_Get("r_bloom_intensity",					"0.15",						CVAR_ARCHIVE | CVAR_LATCH );
	ri->Cvar_CheckRange(r_bloom_intensity, 0.01f, 2, qfalse);
	r_bloom_modulate					= ri->Cvar_Get("r_bloom_modulate",					"0",						CVAR_ARCHIVE );
#ifdef USE_PMLIGHT
	r_dlightMode						= ri->Cvar_Get("r_dlightMode",						"2",						CVAR_ARCHIVE);
	ri->Cvar_CheckRange(r_dlightMode, 0, 2, qtrue);
	r_dlightScale						= ri->Cvar_Get("r_dlightScale",						"0.8",						CVAR_ARCHIVE);
	ri->Cvar_CheckRange(r_dlightScale, 0.1f, 1, qfalse);
	r_dlightIntensity					= ri->Cvar_Get("r_dlightIntensity",					"1.0",						CVAR_ARCHIVE);
	ri->Cvar_CheckRange(r_dlightIntensity, 0.1f, 1, qfalse);
#endif

	r_dlightSaturation					= ri->Cvar_Get("r_dlightSaturation",					"1",					CVAR_ARCHIVE );
	ri->Cvar_CheckRange(r_dlightSaturation, 0, 1, qfalse);

	r_roundImagesDown					= ri->Cvar_Get("r_roundImagesDown",					"1",						CVAR_ARCHIVE | CVAR_LATCH );
	r_nomip								= ri->Cvar_Get("r_nomip",							"0",						CVAR_ARCHIVE | CVAR_LATCH );
	ri->Cvar_CheckRange(r_nomip, 0, 1, qtrue);
#ifdef USE_VBO
	r_vbo								= ri->Cvar_Get("r_vbo",								"0",						CVAR_ARCHIVE | CVAR_LATCH );
	r_vbo_models						= ri->Cvar_Get("r_vbo_models",						"1",						CVAR_ARCHIVE | CVAR_LATCH );
#endif
	r_renderWidth						= ri->Cvar_Get("r_renderWidth",						"800",						CVAR_ARCHIVE | CVAR_LATCH );
	r_renderHeight						= ri->Cvar_Get("r_renderHeight",						"600",					CVAR_ARCHIVE | CVAR_LATCH);
	r_renderScale						= ri->Cvar_Get("r_renderScale",						"0",						CVAR_ARCHIVE | CVAR_LATCH );
	ri->Cvar_CheckRange(r_renderScale, 0, 4, qtrue);
	r_ignorehwgamma						= ri->Cvar_Get("r_ignorehwgamma",					"0",						CVAR_ARCHIVE | CVAR_LATCH);
	ri->Cvar_CheckRange(r_ignorehwgamma, 0, 1, qtrue);


/*
Ghoul2 Insert Start
*/
#ifdef _DEBUG
	r_noPrecacheGLA						= ri->Cvar_Get( "r_noPrecacheGLA",					"0",						CVAR_CHEAT);
#endif
	r_noServerGhoul2					= ri->Cvar_Get( "r_noserverghoul2",					"0",						CVAR_CHEAT);
	r_Ghoul2AnimSmooth					= ri->Cvar_Get( "r_ghoul2animsmooth",				"0.3",						CVAR_NONE);
	r_Ghoul2UnSqashAfterSmooth			= ri->Cvar_Get( "r_ghoul2unsqashaftersmooth",		"1",						CVAR_NONE);
	broadsword							= ri->Cvar_Get( "broadsword",						"0",						CVAR_ARCHIVE);
	broadsword_kickbones				= ri->Cvar_Get( "broadsword_kickbones",				"1",						CVAR_NONE);
	broadsword_kickorigin				= ri->Cvar_Get( "broadsword_kickorigin",				"1",					CVAR_NONE);
	broadsword_dontstopanim				= ri->Cvar_Get( "broadsword_dontstopanim",			"0",						CVAR_NONE);
	broadsword_waitforshot				= ri->Cvar_Get( "broadsword_waitforshot",			"0",						CVAR_NONE);
	broadsword_playflop					= ri->Cvar_Get( "broadsword_playflop",				"1",						CVAR_NONE);
	broadsword_smallbbox				= ri->Cvar_Get( "broadsword_smallbbox",				"0",						CVAR_NONE);
	broadsword_extra1					= ri->Cvar_Get( "broadsword_extra1",					"0",					CVAR_NONE);
	broadsword_extra2					= ri->Cvar_Get( "broadsword_extra2",					"0",					CVAR_NONE);
	broadsword_effcorr					= ri->Cvar_Get( "broadsword_effcorr",				"1",						CVAR_NONE);
	broadsword_ragtobase				= ri->Cvar_Get( "broadsword_ragtobase",				"2",						CVAR_NONE);
	broadsword_dircap					= ri->Cvar_Get( "broadsword_dircap",					"64",					CVAR_NONE);
/*
Ghoul2 Insert End
*/
	r_modelpoolmegs = ri->Cvar_Get("r_modelpoolmegs", "20", CVAR_ARCHIVE);
	if (ri->Sys_LowPhysicalMemory() )
		ri->Cvar_Set("r_modelpoolmegs", "0");

	r_aviMotionJpegQuality				= ri->Cvar_Get( "r_aviMotionJpegQuality",			"100",						CVAR_ARCHIVE);
	r_screenshotJpegQuality				= ri->Cvar_Get( "r_screenshotJpegQuality",			"100",						CVAR_ARCHIVE);

	ri->Cvar_CheckRange( r_aviMotionJpegQuality, 10, 100, qtrue );
	ri->Cvar_CheckRange( r_screenshotJpegQuality, 10, 100, qtrue );

	for ( size_t i = 0; i < numCommands; i++ )
		ri->Cmd_AddCommand( commands[i].cmd, commands[i].func);
}

/*
===============
R_Init
===============
*/
extern void R_InitWorldEffects( void ); //tr_WorldEffects.cpp
void R_Init( void ) {
	int i;
	byte *ptr;

	vk_debug("----- R_Init -----\n" );
	ri->Printf(PRINT_ALL, "----- R_Init -----\n");
	// clear all our internal state
	Com_Memset( &tr, 0, sizeof( tr ) );
	Com_Memset( &backEnd, 0, sizeof( backEnd ) );
	Com_Memset( &tess, 0, sizeof( tess ) );
	//Com_Memset( &glState, 0, sizeof( glState ) );

#ifndef FINAL_BUILD
	if ( (intptr_t)tess.xyz & 15 ) {
		ri->Printf(PRINT_WARNING, "tess.xyz not 16 byte aligned\n");
	}
#endif
	//
	// init function tables
	//
	for (i = 0; i < FUNCTABLE_SIZE; i++) {
#if 0
		if (i == 0) {
			tr.sinTable[i] = EPSILON;
		}
		else if (i == (FUNCTABLE_SIZE - 1)) {
			tr.sinTable[i] = -EPSILON;
		}
		else {
			tr.sinTable[i] = sin(DEG2RAD(i * 360.0f / ((float)(FUNCTABLE_SIZE - 1))));
		}
#else
		tr.sinTable[i] = sin( DEG2RAD( i * 360.0f / FUNCTABLE_SIZE ) + 0.0001f );
#endif
		tr.squareTable[i] = (i < FUNCTABLE_SIZE / 2) ? 1.0f : -1.0f;
		if (i == 0) {
			tr.sawToothTable[i] = EPSILON;
		}
		else {
			tr.sawToothTable[i] = (float)i / FUNCTABLE_SIZE;
		}
		tr.inverseSawToothTable[i] = 1.0f - tr.sawToothTable[i];
		if (i < FUNCTABLE_SIZE / 2) {
			if (i < FUNCTABLE_SIZE / 4) {
				if (i == 0) {
					tr.triangleTable[i] = EPSILON;
				}
				else {
					tr.triangleTable[i] = (float)i / (FUNCTABLE_SIZE / 4);
				}
			}
			else {
				tr.triangleTable[i] = 1.0f - tr.triangleTable[i - FUNCTABLE_SIZE / 4];
			}
		}
		else {
			tr.triangleTable[i] = -tr.triangleTable[i - FUNCTABLE_SIZE / 2];
		}
	}

	R_InitFogTable();
	R_ImageLoader_Init();
	R_NoiseInit();
	R_Register();

	max_polys = Q_min( r_maxpolys->integer, DEFAULT_MAX_POLYS );
	max_polyverts = Q_min( r_maxpolyverts->integer, DEFAULT_MAX_POLYVERTS );

	ptr = (byte *)Hunk_Alloc( sizeof( *backEndData ) + sizeof(srfPoly_t) * max_polys + sizeof(polyVert_t) * max_polyverts, h_low);
	backEndData = (backEndData_t *) ptr;
	backEndData->polys = (srfPoly_t *) ((char *) ptr + sizeof( *backEndData ));
	backEndData->polyVerts = (polyVert_t *) ((char *) ptr + sizeof( *backEndData ) + sizeof(srfPoly_t) * max_polys);

	R_InitNextFrame();

	for(i = 0; i < MAX_LIGHT_STYLES; i++)
	{
		RE_SetLightStyle(i, -1);
	}

	vk_create_window();		// Vulkan

#ifdef USE_VBO
	vk_release_world_vbo();
	vk_release_model_vbo();
#endif

	R_Set2DRatio();
	R_InitImages();	

#ifdef _G2_GORE
	R_CreateGoreVBO();
#endif
	vk_create_pipelines();	// Vulkan
	vk_set_clearcolor();

	R_InitShaders(qfalse);
	R_InitSkins();
	R_InitFonts();
	R_ModelInit();
	R_InitDecals();
	R_InitWorldEffects();
	RestoreGhoul2InfoArray();

	vk_debug("----- finished R_Init -----\n" );
}


// This need some tlc
/*
===============
RE_Shutdown
===============
*/
void RE_Shutdown( qboolean destroyWindow, qboolean restarting ) {
	vk_debug("RE_Shutdown( %i, %i )\n", destroyWindow, restarting);

	for (size_t i = 0; i < numCommands; i++)
		ri->Cmd_RemoveCommand(commands[i].cmd);

	R_ShutdownWorldEffects();
	R_ShutdownFonts();

	// contains vulkan resources/state, reinitialized on a map change.
	//if (tr.registered) {

		if (destroyWindow){
			//vk_delete_textures();

			if (restarting)
				SaveGhoul2InfoArray();
		}

		vk_delete_textures();
		vk_release_resources();
	//}

	//vk_release_resources(); not merged yet (https://github.com/ec-/Quake3e/commit/d31b84ebf2ab702686e98dff40b7673473026b30)

	if (destroyWindow) {
		vk_shutdown();

		Com_Memset(&glState, 0, sizeof(glState));

		if (destroyWindow && !restarting) {
			ri->VK_destroyWindow();
			Com_Memset(&glConfig, 0, sizeof(glConfig));
		}
	}

	tr.registered = qfalse;
	tr.inited = qfalse;
}

/*
=============
RE_EndRegistration

Touch all images to make sure they are resident
=============
*/
void RE_EndRegistration( void ) {
	vk_wait_idle();

	// command buffer is not in recording state at this stage
	// so we can't issue RB_ShowImages() here.
	// moved to RB_SwapBuffers
}

void RE_GetLightStyle( int style, color4ub_t color )
{
	if (style >= MAX_LIGHT_STYLES)
	{
	    Com_Error( ERR_FATAL, "RE_GetLightStyle: %d is out of range", (int)style );
		return;
	}

	byteAlias_t *baDest = (byteAlias_t *)&color, 
				*baSource = (byteAlias_t *)&styleColors[style];
	baDest->i = baSource->i;
}

void RE_SetLightStyle( int style, int color )
{
	if (style >= MAX_LIGHT_STYLES)
	{
	    Com_Error( ERR_FATAL, "RE_SetLightStyle: %d is out of range", (int)style );
		return;
	}

	byteAlias_t *ba = (byteAlias_t *)&styleColors[style];
	if ( ba->i != color) {
		ba->i = color;
	}
}

static void SetRangedFog( float range ) { tr.rangedFog = range; }

extern qboolean gG2_GBMNoReconstruct;
extern qboolean gG2_GBMUseSPMethod;
static void G2API_BoltMatrixReconstruction( qboolean reconstruct ) { gG2_GBMNoReconstruct = (qboolean)!reconstruct; }
static void G2API_BoltMatrixSPMethod( qboolean spMethod ) { gG2_GBMUseSPMethod = spMethod; }

//extern float tr_distortionAlpha; //opaque
//extern float tr_distortionStretch; //no stretch override
//extern qboolean tr_distortionPrePost; //capture before postrender phase?
//extern qboolean tr_distortionNegate; //negative blend mode
static void SetRefractionProperties( float distortionAlpha, float distortionStretch, qboolean distortionPrePost, qboolean distortionNegate ) {
	//tr_distortionAlpha = distortionAlpha;
	//tr_distortionStretch = distortionStretch;
	//tr_distortionPrePost = distortionPrePost;
	//tr_distortionNegate = distortionNegate;
}

static float GetDistanceCull( void ) { return tr.distanceCull; }

static void GetRealRes( int *w, int *h ) {
	*w = glConfig.vidWidth;
	*h = glConfig.vidHeight;
}

extern void R_SVModelInit( void ); //tr_model.cpp
extern void R_AutomapElevationAdjustment( float newHeight ); //tr_world.cpp
extern qboolean R_InitializeWireframeAutomap( void ); //tr_world.cpp

extern qhandle_t RE_RegisterServerSkin( const char *name );

#ifdef USE_JKG
// Jedi Knight Galaxies
extern void R_OverrideShaderFrame( qhandle_t shader, int desiredFrame, int time );
#endif

/*
@@@@@@@@@@@@@@@@@@@@@
GetRefAPI

@@@@@@@@@@@@@@@@@@@@@
*/
extern "C" {
Q_EXPORT refexport_t* QDECL GetRefAPI( int apiVersion, refimport_t *rimp ) {
	static refexport_t re;

	assert( rimp );
#ifdef USE_JKG
	ri = rimp;
#else
	ri = *rimp;
#endif
	memset( &re, 0, sizeof( re ) );

	if ( apiVersion != REF_API_VERSION ) {
		vk_debug("Mismatched REF_API_VERSION: expected %i, got %i\n", REF_API_VERSION, apiVersion );
		return NULL;
	}

	// the RE_ functions are Renderer Entry points

	re.Shutdown = RE_Shutdown;
	re.BeginRegistration					= RE_BeginRegistration;
	re.RegisterModel						= RE_RegisterModel;
	re.RegisterServerModel					= RE_RegisterServerModel;
	re.RegisterSkin							= RE_RegisterSkin;
	re.RegisterServerSkin					= RE_RegisterServerSkin;
	re.RegisterShader						= RE_RegisterShader;
	re.RegisterShaderNoMip					= RE_RegisterShaderNoMip;
	re.ShaderNameFromIndex					= RE_ShaderNameFromIndex;
	re.LoadWorld							= RE_LoadWorldMap;
	re.SetWorldVisData						= RE_SetWorldVisData;
	re.EndRegistration						= RE_EndRegistration;
	re.BeginFrame							= RE_BeginFrame;
	re.EndFrame								= RE_EndFrame;
	re.MarkFragments						= R_MarkFragments;
	re.LerpTag								= R_LerpTag;
	re.ModelBounds							= R_ModelBounds;
	re.DrawRotatePic						= RE_RotatePic;
	re.DrawRotatePic2						= RE_RotatePic2;
	re.ClearScene							= RE_ClearScene;
	re.ClearDecals							= RE_ClearDecals;
	re.AddRefEntityToScene					= RE_AddRefEntityToScene;
	re.AddMiniRefEntityToScene				= RE_AddMiniRefEntityToScene;
	re.AddPolyToScene						= RE_AddPolyToScene;
	re.AddDecalToScene						= RE_AddDecalToScene;
	re.LightForPoint						= R_LightForPoint;
	re.AddLightToScene						= RE_AddLightToScene;
	re.AddAdditiveLightToScene				= RE_AddAdditiveLightToScene;

	re.RenderScene							= RE_RenderScene;
	re.SetColor								= RE_SetColor;
	re.DrawStretchPic						= RE_StretchPic;
	re.DrawStretchRaw						= RE_StretchRaw;
	re.UploadCinematic						= RE_UploadCinematic;

	re.RegisterFont							= RE_RegisterFont;
	re.Font_StrLenPixels					= RE_Font_StrLenPixels;
	re.Font_StrLenChars						= RE_Font_StrLenChars;
	re.Font_HeightPixels					= RE_Font_HeightPixels;
	re.Font_DrawString						= RE_Font_DrawString;
	re.Language_IsAsian						= Language_IsAsian;
	re.Language_UsesSpaces					= Language_UsesSpaces;
	re.AnyLanguage_ReadCharFromString		= AnyLanguage_ReadCharFromString;

	re.RemapShader							= R_RemapShader;
	re.GetEntityToken						= R_GetEntityToken;
	re.inPVS								= R_inPVS;
	re.GetLightStyle						= RE_GetLightStyle;
	re.SetLightStyle						= RE_SetLightStyle;
	re.GetBModelVerts						= RE_GetBModelVerts;

	// missing from 1.01
	re.SetRangedFog							= SetRangedFog;
	re.SetRefractionProperties				= SetRefractionProperties;
	re.GetDistanceCull						= GetDistanceCull;
	re.GetRealRes							= GetRealRes;
	re.AutomapElevationAdjustment			= R_AutomapElevationAdjustment; //tr_world.cpp
	re.InitializeWireframeAutomap			= R_InitializeWireframeAutomap; //tr_world.cpp
	re.AddWeatherZone						= RE_AddWeatherZone;
	re.WorldEffectCommand					= RE_WorldEffectCommand;
	re.RegisterMedia_LevelLoadBegin			= RE_RegisterMedia_LevelLoadBegin;
	re.RegisterMedia_LevelLoadEnd			= RE_RegisterMedia_LevelLoadEnd;
	re.RegisterMedia_GetLevel				= RE_RegisterMedia_GetLevel;
	re.RegisterImages_LevelLoadEnd			= RE_RegisterImages_LevelLoadEnd;
	re.RegisterModels_LevelLoadEnd			= RE_RegisterModels_LevelLoadEnd;

	// AVI recording
	re.TakeVideoFrame						= RE_TakeVideoFrame;

	// G2 stuff
	re.InitSkins							= R_InitSkins;
	re.InitShaders							= R_InitShaders;
	re.SVModelInit							= R_SVModelInit;
	re.HunkClearCrap						= RE_HunkClearCrap;

	// G2API
	re.G2API_AddBolt						= G2API_AddBolt;
	re.G2API_AddBoltSurfNum					= G2API_AddBoltSurfNum;
	re.G2API_AddSurface						= G2API_AddSurface;
	re.G2API_AnimateG2ModelsRag				= G2API_AnimateG2ModelsRag;
	re.G2API_AttachEnt						= G2API_AttachEnt;
	re.G2API_AttachG2Model					= G2API_AttachG2Model;
	re.G2API_AttachInstanceToEntNum			= G2API_AttachInstanceToEntNum;
	re.G2API_AbsurdSmoothing				= G2API_AbsurdSmoothing;
	re.G2API_BoltMatrixReconstruction		= G2API_BoltMatrixReconstruction;
	re.G2API_BoltMatrixSPMethod				= G2API_BoltMatrixSPMethod;
	re.G2API_CleanEntAttachments			= G2API_CleanEntAttachments;
	re.G2API_CleanGhoul2Models				= G2API_CleanGhoul2Models;
	re.G2API_ClearAttachedInstance			= G2API_ClearAttachedInstance;
	re.G2API_CollisionDetect				= G2API_CollisionDetect;
	re.G2API_CollisionDetectCache			= G2API_CollisionDetectCache;
	re.G2API_CopyGhoul2Instance				= G2API_CopyGhoul2Instance;
	re.G2API_CopySpecificG2Model			= G2API_CopySpecificG2Model;
	re.G2API_DetachG2Model					= G2API_DetachG2Model;
	re.G2API_DoesBoneExist					= G2API_DoesBoneExist;
	re.G2API_DuplicateGhoul2Instance		= G2API_DuplicateGhoul2Instance;
	re.G2API_FreeSaveBuffer					= G2API_FreeSaveBuffer;
	re.G2API_GetAnimFileName				= G2API_GetAnimFileName;
	re.G2API_GetAnimFileNameIndex			= G2API_GetAnimFileNameIndex;
	re.G2API_GetAnimRange					= G2API_GetAnimRange;
	re.G2API_GetBoltMatrix					= G2API_GetBoltMatrix;
	re.G2API_GetBoneAnim					= G2API_GetBoneAnim;
	re.G2API_GetBoneIndex					= G2API_GetBoneIndex;
	re.G2API_GetGhoul2ModelFlags			= G2API_GetGhoul2ModelFlags;
	re.G2API_GetGLAName						= G2API_GetGLAName;
	re.G2API_GetModelName					= G2API_GetModelName;
	re.G2API_GetParentSurface				= G2API_GetParentSurface;
	re.G2API_GetRagBonePos					= G2API_GetRagBonePos;
	re.G2API_GetSurfaceIndex				= G2API_GetSurfaceIndex;
	re.G2API_GetSurfaceName					= G2API_GetSurfaceName;
#ifdef USE_JKG
	// Jedi Knight Galaxies
	re.G2API_GetSurfaceCount				= G2API_GetSurfaceCount;
#endif
	re.G2API_GetSurfaceOnOff				= G2API_GetSurfaceOnOff;
	re.G2API_GetSurfaceRenderStatus			= G2API_GetSurfaceRenderStatus;
	re.G2API_GetTime						= G2API_GetTime;
	re.G2API_Ghoul2Size						= G2API_Ghoul2Size;
	re.G2API_GiveMeVectorFromMatrix			= G2API_GiveMeVectorFromMatrix;
	re.G2API_HasGhoul2ModelOnIndex			= G2API_HasGhoul2ModelOnIndex;
	re.G2API_HaveWeGhoul2Models				= G2API_HaveWeGhoul2Models;
	re.G2API_IKMove							= G2API_IKMove;
	re.G2API_InitGhoul2Model				= G2API_InitGhoul2Model;
	re.G2API_IsGhoul2InfovValid				= G2API_IsGhoul2InfovValid;
	re.G2API_IsPaused						= G2API_IsPaused;
	re.G2API_ListBones						= G2API_ListBones;
	re.G2API_ListSurfaces					= G2API_ListSurfaces;
	re.G2API_LoadGhoul2Models				= G2API_LoadGhoul2Models;
	re.G2API_LoadSaveCodeDestructGhoul2Info	= G2API_LoadSaveCodeDestructGhoul2Info;
	re.G2API_OverrideServerWithClientData	= G2API_OverrideServerWithClientData;
	re.G2API_PauseBoneAnim					= G2API_PauseBoneAnim;
	re.G2API_PrecacheGhoul2Model			= G2API_PrecacheGhoul2Model;
	re.G2API_RagEffectorGoal				= G2API_RagEffectorGoal;
	re.G2API_RagEffectorKick				= G2API_RagEffectorKick;
	re.G2API_RagForceSolve					= G2API_RagForceSolve;
	re.G2API_RagPCJConstraint				= G2API_RagPCJConstraint;
	re.G2API_RagPCJGradientSpeed			= G2API_RagPCJGradientSpeed;
	re.G2API_RemoveBolt						= G2API_RemoveBolt;
	re.G2API_RemoveBone						= G2API_RemoveBone;
	re.G2API_RemoveGhoul2Model				= G2API_RemoveGhoul2Model;
	re.G2API_RemoveGhoul2Models				= G2API_RemoveGhoul2Models;
	re.G2API_RemoveSurface					= G2API_RemoveSurface;
	re.G2API_ResetRagDoll					= G2API_ResetRagDoll;
	re.G2API_SaveGhoul2Models				= G2API_SaveGhoul2Models;
	re.G2API_SetBoltInfo					= G2API_SetBoltInfo;
	re.G2API_SetBoneAngles					= G2API_SetBoneAngles;
	re.G2API_SetBoneAnglesIndex				= G2API_SetBoneAnglesIndex;
	re.G2API_SetBoneAnglesMatrix			= G2API_SetBoneAnglesMatrix;
	re.G2API_SetBoneAnglesMatrixIndex		= G2API_SetBoneAnglesMatrixIndex;
	re.G2API_SetBoneAnim					= G2API_SetBoneAnim;
	re.G2API_SetBoneAnimIndex				= G2API_SetBoneAnimIndex;
	re.G2API_SetBoneIKState					= G2API_SetBoneIKState;
	re.G2API_SetGhoul2ModelIndexes			= G2API_SetGhoul2ModelIndexes;
	re.G2API_SetGhoul2ModelFlags			= G2API_SetGhoul2ModelFlags;
	re.G2API_SetLodBias						= G2API_SetLodBias;
	re.G2API_SetNewOrigin					= G2API_SetNewOrigin;
	re.G2API_SetRagDoll						= G2API_SetRagDoll;
	re.G2API_SetRootSurface					= G2API_SetRootSurface;
	re.G2API_SetShader						= G2API_SetShader;
	re.G2API_SetSkin						= G2API_SetSkin;
	re.G2API_SetSurfaceOnOff				= G2API_SetSurfaceOnOff;
	re.G2API_SetTime						= G2API_SetTime;
	re.G2API_SkinlessModel					= G2API_SkinlessModel;
	re.G2API_StopBoneAngles					= G2API_StopBoneAngles;
	re.G2API_StopBoneAnglesIndex			= G2API_StopBoneAnglesIndex;
	re.G2API_StopBoneAnim					= G2API_StopBoneAnim;
	re.G2API_StopBoneAnimIndex				= G2API_StopBoneAnimIndex;

	#ifdef _G2_GORE
	re.G2API_GetNumGoreMarks				= G2API_GetNumGoreMarks;
	re.G2API_AddSkinGore					= G2API_AddSkinGore;
	re.G2API_ClearSkinGore					= G2API_ClearSkinGore;
	#endif // _SOF2

	// this is set in R_Init
	//re.G2VertSpaceServer	= G2VertSpaceServer;

#ifndef USE_JKG
	re.ext.Font_StrLenPixels				= RE_Font_StrLenPixelsNew;
#endif
#ifdef USE_JKG
	// Jedi Knight Galaxies
	re.OverrideShaderFrame					= R_OverrideShaderFrame;
#endif
	return &re;
}

} //extern "C"
