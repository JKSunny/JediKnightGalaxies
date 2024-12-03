/*
===========================================================================
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

#pragma once

#include "client/cl_cgameapi.h"
#include "ghoul2/G2.h"

#ifndef ENGINE
#include "cgame/cg_local.h"
#endif

extern cvar_t	*fx_debug;

#ifdef _DEBUG
extern cvar_t	*fx_freeze;
#endif

extern cvar_t	*fx_countScale;
extern cvar_t	*fx_nearCull;
extern cvar_t	*fx_optimizedParticles;

#ifdef ENGINE
static inline void Vector2Clear(vec2_t a)
{
	a[0] = 0.0f;
	a[1] = 0.0f;
}

static inline void Vector2Set(vec2_t a,float b,float c)
{
	a[0] = b;
	a[1] = c;
}

static inline void Vector2Copy(vec2_t src,vec2_t dst)
{
	dst[0] = src[0];
	dst[1] = src[1];
}

static inline void Vector2MA(vec2_t src, float m, vec2_t v, vec2_t dst)
{
	dst[0] = src[0] + (m*v[0]);
	dst[1] = src[1] + (m*v[1]);
}

static inline void Vector2Scale(vec2_t src,float b,vec2_t dst)
{
	dst[0] = src[0] * b;
	dst[1] = src[1] * b;
}
#endif
class SFxHelper
{
public:
	int		mTime;
	int		mOldTime;
	int		mFrameTime;
	bool	mTimeFrozen;
	float	mRealTime;
	refdef_t*	refdef;
#ifdef _DEBUG
	int		mMainRefs;
	int		mMiniRefs;
#endif

public:
	SFxHelper(void);

	int	GetTime(void) { return mTime; }
	int	GetFrameTime(void) { return mFrameTime; }

	void	ReInit(refdef_t* pRefdef);
	void	AdjustTime( int time );

	// These functions are wrapped and used by the fx system in case it makes things a bit more portable
	void	Print( const char *msg, ... );

	// File handling
	int		OpenFile( const char *path, fileHandle_t *fh, int mode )
	{
#ifdef ENGINE
		return FS_FOpenFileByMode( path, fh, FS_READ );
#else
		return trap->FS_Open( path, fh, FS_READ );
#endif
	}
	int		ReadFile( void *data, int len, fileHandle_t fh )
	{
#ifdef ENGINE
		FS_Read( data, len, fh );
#else
		trap->FS_Read( data, len, fh );
#endif
		return 1;
	}
	void	CloseFile( fileHandle_t fh )
	{
#ifdef ENGINE
		FS_FCloseFile( fh );
#else
		trap->FS_Close( fh );
#endif
	}

	// Sound
	void	PlaySound( vec3_t origin, int entityNum, int entchannel, sfxHandle_t sfxHandle, int volume, int radius )
	{
		//S_StartSound( origin, ENTITYNUM_NONE, CHAN_AUTO, sfxHandle, volume, radius );
#ifdef ENGINE
		S_StartSound( origin, ENTITYNUM_NONE, CHAN_AUTO, sfxHandle );
#else
		trap->S_StartSound( origin, ENTITYNUM_NONE, CHAN_AUTO, sfxHandle );
#endif
	}
	void	PlayLocalSound(sfxHandle_t sfxHandle, int entchannel)
	{
		//S_StartSound( origin, ENTITYNUM_NONE, CHAN_AUTO, sfxHandle, volume, radius );
#ifdef ENGINE
		S_StartLocalSound(sfxHandle, entchannel);
#else
		trap->S_StartLocalSound( sfxHandle, entchannel );
#endif
	}
	int		RegisterSound( const char *sound )
	{
#ifdef ENGINE
		return S_RegisterSound( sound );
#else
		return trap->S_RegisterSound( sound );
#endif
	}

	// Physics/collision
	void	Trace( trace_t &tr, vec3_t start, vec3_t min, vec3_t max, vec3_t end, int skipEntNum, int flags )
	{
#ifdef ENGINE
		TCGTrace		*td = (TCGTrace *)cl.mSharedMemory;
#else
		TCGTrace		*td = (TCGTrace *)trap->FX_GetSharedMemory();
#endif

		if ( !min )
		{
			min = vec3_origin;
		}

		if ( !max )
		{
			max = vec3_origin;
		}

		memset(td, 0, sizeof(*td));
		VectorCopy(start, td->mStart);
		VectorCopy(min, td->mMins);
		VectorCopy(max, td->mMaxs);
		VectorCopy(end, td->mEnd);
		td->mSkipNumber = skipEntNum;
		td->mMask = flags;

#ifdef ENGINE
		CGVM_Trace();
#else
		C_Trace();
#endif

		tr = td->mResult;
	}

	void	G2Trace( trace_t &tr, vec3_t start, vec3_t min, vec3_t max, vec3_t end, int skipEntNum, int flags )
	{
#ifdef ENGINE
		TCGTrace		*td = (TCGTrace *)cl.mSharedMemory;
#else
		TCGTrace		*td = (TCGTrace *)trap->FX_GetSharedMemory();
#endif

		if ( !min )
		{
			min = vec3_origin;
		}

		if ( !max )
		{
			max = vec3_origin;
		}

		memset(td, 0, sizeof(*td));
		VectorCopy(start, td->mStart);
		VectorCopy(min, td->mMins);
		VectorCopy(max, td->mMaxs);
		VectorCopy(end, td->mEnd);
		td->mSkipNumber = skipEntNum;
		td->mMask = flags;

#ifdef ENGINE
		CGVM_G2Trace();
#else
		C_G2Trace();
#endif

		tr = td->mResult;
	}

	void	AddGhoul2Decal(int shader, vec3_t start, vec3_t dir, float size)
	{
#ifdef ENGINE
		TCGG2Mark		*td = (TCGG2Mark *)cl.mSharedMemory;
#else
		TCGG2Mark		*td = (TCGG2Mark *)trap->FX_GetSharedMemory();
#endif

		td->size = size;
		td->shader = shader;
		VectorCopy(start, td->start);
		VectorCopy(dir, td->dir);

#ifdef ENGINE
		CGVM_G2Mark();
#else
		C_G2Mark();
#endif
	}

	void	AddFxToScene( refEntity_t *ent )
	{
#ifdef _DEBUG
		mMainRefs++;

		assert(!ent || ent->renderfx >= 0);
#endif
#ifdef ENGINE
		re->AddRefEntityToScene( ent );
#else
		trap->R_AddRefEntityToScene( ent );
#endif
	}
	void	AddFxToScene( miniRefEntity_t *ent )
	{
#ifdef _DEBUG
		mMiniRefs++;

		assert(!ent || ent->renderfx >= 0);
#endif
#ifdef ENGINE
		re->AddMiniRefEntityToScene( ent );
#else
		trap->R_AddMiniRefEntityToScene( ent );
#endif
	}
	inline	void	AddLightToScene( vec3_t org, float radius, float red, float green, float blue )
	{
#ifdef ENGINE
		re->AddLightToScene(	org, radius, red, green, blue );
#else
		trap->R_AddLightToScene( org, radius, red, green, blue );
#endif
	}

	int		RegisterShader( const char *shader )
	{
#ifdef ENGINE
		return re->RegisterShader( shader );
#else
		return (int)trap->R_RegisterShader( shader );
#endif
	}
	int		RegisterModel( const char *modelFile )
	{
#ifdef ENGINE
		return re->RegisterModel( modelFile );
#else
		return (int)trap->R_RegisterModel( modelFile );
#endif
	}

	void	AddPolyToScene( int shader, int count, polyVert_t *verts )
	{
#ifdef ENGINE
		re->AddPolyToScene( shader, count, verts, 1 );
#else
		trap->R_AddPolysToScene( shader, count, verts, 1 );
#endif
	}

	void AddDecalToScene ( qhandle_t shader, const vec3_t origin, const vec3_t dir, float orientation, float r, float g, float b, float a, qboolean alphaFade, float radius, qboolean temporary )
	{
#ifdef ENGINE
		re->AddDecalToScene ( shader, origin, dir, orientation, r, g, b, a, alphaFade, radius, temporary );
#else
		trap->R_AddDecalToScene ( shader, origin, dir, orientation, r, g, b, a, alphaFade, radius, temporary );
#endif
	}

	void	CameraShake( vec3_t origin, float intensity, int radius, int time );
	qboolean GetOriginAxisFromBolt(CGhoul2Info_v *pGhoul2, int mEntNum, int modelNum, int boltNum, vec3_t /*out*/origin, vec3_t /*out*/axis[3]);
};

extern SFxHelper	theFxHelper;
