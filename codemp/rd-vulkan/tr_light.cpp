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
// tr_light.c

#include "tr_local.h"

#define	DLIGHT_AT_RADIUS		16
// at the edge of a dlight's influence, this amount of light will be added

#define	DLIGHT_MINIMUM_RADIUS	16
// never calculate a range less than this to prevent huge light numbers

/*
===============
R_TransformDlights

Transforms the origins of an array of dlights.
Used by both the front end (for DlightBmodel) and
the back end (before doing the lighting calculation)
===============
*/
void R_TransformDlights( int count, dlight_t *dl, orientationr_t *ori) {
	int		i;
	vec3_t	temp, temp2;

	for ( i = 0 ; i < count ; i++, dl++ ) {
		VectorSubtract( dl->origin, ori->origin, temp );
		dl->transformed[0] = DotProduct( temp, ori->axis[0] );
		dl->transformed[1] = DotProduct( temp, ori->axis[1] );
		dl->transformed[2] = DotProduct( temp, ori->axis[2] );
		if (dl->linear) {
			VectorSubtract(dl->origin2, ori->origin, temp2);
			dl->transformed2[0] = DotProduct(temp2, ori->axis[0]);
			dl->transformed2[1] = DotProduct(temp2, ori->axis[1]);
			dl->transformed2[2] = DotProduct(temp2, ori->axis[2]);
		}

	}
}

/*
=============================================================================

LIGHT SAMPLING

=============================================================================
*/

extern	cvar_t	*r_ambientScale;
extern	cvar_t	*r_directedScale;
extern	cvar_t	*r_debugLight;

//rwwRMG - VectorScaleVector is now a #define

/*
=================
R_SetupEntityLightingGrid

=================
*/
static void R_SetupEntityLightingGrid( trRefEntity_t *ent ) {
	vec3_t			lightOrigin;
	int				pos[3];
	int				i, j;
	float			frac[3];
	int				gridStep[3];
	vec3_t			direction;
	float			totalFactor;
	unsigned short	*startGridPos;

#ifdef RF_FULLBRIGHT
	if (r_fullbright->integer || r_ambientScale->integer == -1 || (ent->e.renderfx & RF_FULLBRIGHT))
#else
	if (r_fullbright->integer || r_ambientScale->integer == -1)
#endif
	{
		ent->ambientLight[0] = ent->ambientLight[1] = ent->ambientLight[2] = 255.0;
		ent->directedLight[0] = ent->directedLight[1] = ent->directedLight[2] = 255.0;
		VectorCopy( tr.sunDirection, ent->lightDir );
		return;
	}

	if ( ent->e.renderfx & RF_LIGHTING_ORIGIN ) {
		// seperate lightOrigins are needed so an object that is
		// sinking into the ground can still be lit, and so
		// multi-part models can be lit identically
		VectorCopy( ent->e.lightingOrigin, lightOrigin );
	} else {
		VectorCopy( ent->e.origin, lightOrigin );
	}

	VectorSubtract( lightOrigin, tr.world->lightGridOrigin, lightOrigin );
	for ( i = 0 ; i < 3 ; i++ ) {
		float	v;

		v = lightOrigin[i]*tr.world->lightGridInverseSize[i];
		pos[i] = floor( v );
		frac[i] = v - pos[i];
		if ( pos[i] < 0 ) {
			pos[i] = 0;
		} else if ( pos[i] >= tr.world->lightGridBounds[i] - 1 ) {
			pos[i] = tr.world->lightGridBounds[i] - 1;
		}
	}

	VectorClear( ent->ambientLight );
	VectorClear( ent->directedLight );
	VectorClear( direction );

	// trilerp the light value
	gridStep[0] = 1;
	gridStep[1] = tr.world->lightGridBounds[0];
	gridStep[2] = tr.world->lightGridBounds[0] * tr.world->lightGridBounds[1];
	startGridPos = tr.world->lightGridArray + (pos[0] * gridStep[0] + pos[1] * gridStep[1] + pos[2] * gridStep[2]);

	totalFactor = 0;
	for ( i = 0 ; i < 8 ; i++ ) {
		float			factor;
		mgrid_t			*data;
		unsigned short	*gridPos;
		int				lat, lng;
		vec3_t			normal;

		factor = 1.0;
		gridPos = startGridPos;
		for ( j = 0 ; j < 3 ; j++ ) {
			if ( i & (1<<j) ) {
				factor *= frac[j];
				gridPos += gridStep[j];
			} else {
				factor *= (1.0 - frac[j]);
			}
		}

		if (gridPos >= tr.world->lightGridArray + tr.world->numGridArrayElements)
		{//we've gone off the array somehow
			continue;
		}
		data = tr.world->lightGridData + *gridPos;

		if ( data->styles[0] == LS_LSNONE )
		{
			continue;	// ignore samples in walls
		}

		totalFactor += factor;

		for(j=0;j<MAXLIGHTMAPS;j++)
		{
			if (data->styles[j] != LS_LSNONE)
			{
				const byte	style= data->styles[j];

				ent->ambientLight[0] += factor * data->ambientLight[j][0] * styleColors[style][0] / 255.0f;
				ent->ambientLight[1] += factor * data->ambientLight[j][1] * styleColors[style][1] / 255.0f;
				ent->ambientLight[2] += factor * data->ambientLight[j][2] * styleColors[style][2] / 255.0f;

				ent->directedLight[0] += factor * data->directLight[j][0] * styleColors[style][0] / 255.0f;
				ent->directedLight[1] += factor * data->directLight[j][1] * styleColors[style][1] / 255.0f;
				ent->directedLight[2] += factor * data->directLight[j][2] * styleColors[style][2] / 255.0f;
			}
			else
			{
				break;
			}
		}

		lat = data->latLong[1];
		lng = data->latLong[0];
		lat *= (FUNCTABLE_SIZE/256);
		lng *= (FUNCTABLE_SIZE/256);

		// decode X as cos( lat ) * sin( long )
		// decode Y as sin( lat ) * sin( long )
		// decode Z as cos( long )

		normal[0] = tr.sinTable[(lat + (FUNCTABLE_SIZE / 4)) & FUNCTABLE_MASK] * tr.sinTable[lng];
		normal[1] = tr.sinTable[lat] * tr.sinTable[lng];
		normal[2] = tr.sinTable[(lng + (FUNCTABLE_SIZE / 4)) & FUNCTABLE_MASK];

		VectorMA( direction, factor, normal, direction );
	}

	if ( totalFactor > 0 && totalFactor < 0.99 )
	{
		totalFactor = 1.0 / totalFactor;
		VectorScale( ent->ambientLight, totalFactor, ent->ambientLight );
		VectorScale( ent->directedLight, totalFactor, ent->directedLight );
	}

	VectorScale( ent->ambientLight, r_ambientScale->value, ent->ambientLight );
	VectorScale( ent->directedLight, r_directedScale->value, ent->directedLight );

	VectorNormalize2( direction, ent->lightDir );
}

/*
===============
LogLight
===============
*/
static void LogLight( const trRefEntity_t *ent ) {
	int	max1, max2;

	if ( !(ent->e.renderfx & RF_FIRST_PERSON ) ) {
		return;
	}

	max1 = ent->ambientLight[0];
	if ( ent->ambientLight[1] > max1 ) {
		max1 = ent->ambientLight[1];
	} else if ( ent->ambientLight[2] > max1 ) {
		max1 = ent->ambientLight[2];
	}

	max2 = ent->directedLight[0];
	if ( ent->directedLight[1] > max2 ) {
		max2 = ent->directedLight[1];
	} else if ( ent->directedLight[2] > max2 ) {
		max2 = ent->directedLight[2];
	}

	ri->Printf( PRINT_ALL, "amb:%i  dir:%i\n", max1, max2 );
}

/*
=================
R_SetupEntityLighting

Calculates all the lighting values that will be used
by the Calc_* functions
=================
*/
void R_SetupEntityLighting( const trRefdef_t *refdef, trRefEntity_t *ent ) {
	int				i;
	const dlight_t	*dl;
	float			power;
	vec3_t			dir;
	float			d;
	vec3_t			lightDir;
	vec3_t			lightOrigin;
#ifdef USE_PMLIGHT
	vec3_t			shadowLightDir;
#endif

	// lighting calculations
	if (ent->lightingCalculated) {
		return;
	}
	ent->lightingCalculated = qtrue;

	//
	// trace a sample point down to find ambient light
	//
	if (ent->e.renderfx & RF_LIGHTING_ORIGIN) {
		// seperate lightOrigins are needed so an object that is
		// sinking into the ground can still be lit, and so
		// multi-part models can be lit identically
		VectorCopy(ent->e.lightingOrigin, lightOrigin);
	}
	else {
		VectorCopy(ent->e.origin, lightOrigin);
	}

	// if NOWORLDMODEL, only use dynamic lights (menu system, etc)
	if (!(refdef->rdflags & RDF_NOWORLDMODEL)
		&& tr.world->lightGridData) {
		R_SetupEntityLightingGrid(ent);
	}
	else {
		ent->ambientLight[0] = ent->ambientLight[1] =
			ent->ambientLight[2] = tr.identityLight * 150;
		ent->directedLight[0] = ent->directedLight[1] =
			ent->directedLight[2] = tr.identityLight * 150;
		VectorCopy(tr.sunDirection, ent->lightDir);
	}

	// bonus items and view weapons have a fixed minimum add
	if (1 /* ent->e.renderfx & RF_MINLIGHT */) {
		// give everything a minimum light add
		ent->ambientLight[0] += tr.identityLight * 32;
		ent->ambientLight[1] += tr.identityLight * 32;
		ent->ambientLight[2] += tr.identityLight * 32;
	}

	if (ent->e.renderfx & RF_MINLIGHT)
	{ //the minlight flag is now for items rotating on their holo thing
		if (ent->e.shaderRGBA[0] == 255 &&
			ent->e.shaderRGBA[1] == 255 &&
			ent->e.shaderRGBA[2] == 0)
		{
			ent->ambientLight[0] += tr.identityLight * 255;
			ent->ambientLight[1] += tr.identityLight * 255;
			ent->ambientLight[2] += tr.identityLight * 0;
		}
		else
		{
			ent->ambientLight[0] += tr.identityLight * 16;
			ent->ambientLight[1] += tr.identityLight * 96;
			ent->ambientLight[2] += tr.identityLight * 150;
		}
	}

	//
	// modify the light by dynamic lights
	//
	d = VectorLength(ent->directedLight);
	VectorScale(ent->lightDir, d, lightDir);

#ifdef USE_PMLIGHT
	if (r_dlightMode->integer == 2) {
		// only direct lights
		// but we need to deal with shadow light direction
		VectorCopy(lightDir, shadowLightDir);
		if (r_shadows->integer == 2) {
			for (i = 0; i < refdef->num_dlights; i++) {
				dl = &refdef->dlights[i];
				if (dl->linear) // no support for linear lights atm
					continue;
				VectorSubtract(dl->origin, lightOrigin, dir);
				d = VectorNormalize(dir);
				power = DLIGHT_AT_RADIUS * (dl->radius * dl->radius);
				if (d < DLIGHT_MINIMUM_RADIUS) {
					d = DLIGHT_MINIMUM_RADIUS;
				}
				d = power / (d * d);
				VectorMA(shadowLightDir, d, dir, shadowLightDir);
			}
		} // if ( r_shadows->integer == 2 )
	}  // if ( r_dlightMode->integer == 2 )
	else
#endif
	{
		for (i = 0; i < refdef->num_dlights; i++) {
			dl = &refdef->dlights[i];
			VectorSubtract(dl->origin, lightOrigin, dir);
			d = VectorNormalize(dir);

			power = DLIGHT_AT_RADIUS * (dl->radius * dl->radius);
			if (d < DLIGHT_MINIMUM_RADIUS) {
				d = DLIGHT_MINIMUM_RADIUS;
			}
			d = power / (d * d);

			VectorMA(ent->directedLight, d, dl->color, ent->directedLight);
			VectorMA(lightDir, d, dir, lightDir);
		}
	}

	// clamp ambient
	for ( i = 0 ; i < 3 ; i++ ) {
		if ( ent->ambientLight[i] > tr.identityLightByte ) {
			ent->ambientLight[i] = tr.identityLightByte;
		}
	}

	if ( r_debugLight->integer ) {
		LogLight( ent );
	}

	// save out the byte packet version
	((byte *)&ent->ambientLightInt)[0] = Q_ftol( ent->ambientLight[0] );
	((byte *)&ent->ambientLightInt)[1] = Q_ftol( ent->ambientLight[1] );
	((byte *)&ent->ambientLightInt)[2] = Q_ftol( ent->ambientLight[2] );
	((byte *)&ent->ambientLightInt)[3] = 0xff;

	// transform the direction to local space
	VectorNormalize( lightDir );
	VectorCopy(lightDir, ent->lightDir);

	ent->modelLightDir[0] = DotProduct( lightDir, ent->e.axis[0] );
	ent->modelLightDir[1] = DotProduct( lightDir, ent->e.axis[1] );
	ent->modelLightDir[2] = DotProduct( lightDir, ent->e.axis[2] );

#ifdef USE_PMLIGHT
	if (r_shadows->integer == 2 && r_dlightMode->integer == 2) {
		VectorNormalize(shadowLightDir);
		ent->shadowLightDir[0] = DotProduct(shadowLightDir, ent->e.axis[0]);
		ent->shadowLightDir[1] = DotProduct(shadowLightDir, ent->e.axis[1]);
		ent->shadowLightDir[2] = DotProduct(shadowLightDir, ent->e.axis[2]);
	}
#endif
}

/*
=================
R_LightForPoint
=================
*/
int R_LightForPoint( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir )
{
	trRefEntity_t ent;

	if ( tr.world->lightGridData == NULL )
		return qfalse;

	memset(&ent, 0, sizeof(ent));
	VectorCopy( point, ent.e.origin );
	R_SetupEntityLightingGrid( &ent );
	VectorCopy(ent.ambientLight, ambientLight);
	VectorCopy(ent.directedLight, directedLight);
	VectorCopy(ent.lightDir, lightDir);

	return qtrue;
}
