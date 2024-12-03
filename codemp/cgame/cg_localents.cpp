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

// cg_localents.c -- every frame, generate renderer commands for locally
// processed entities, like smoke puffs, gibs, shells, etc.

#include "cg_local.h"

#define	MAX_LOCAL_ENTITIES	2048 //Raz: was 512
localEntity_t	cg_localEntities[MAX_LOCAL_ENTITIES];
localEntity_t	cg_activeLocalEntities;		// double linked list
localEntity_t	*cg_freeLocalEntities;		// single linked list

/*
===================
CG_InitLocalEntities

This is called at startup and for tournement restarts
===================
*/
void	CG_InitLocalEntities( void ) {
	int		i;

	memset( cg_localEntities, 0, sizeof( cg_localEntities ) );
	cg_activeLocalEntities.next = &cg_activeLocalEntities;
	cg_activeLocalEntities.prev = &cg_activeLocalEntities;
	cg_freeLocalEntities = cg_localEntities;
	for ( i = 0 ; i < MAX_LOCAL_ENTITIES - 1 ; i++ ) {
		cg_localEntities[i].next = &cg_localEntities[i+1];
	}
}


/*
==================
CG_FreeLocalEntity
==================
*/
void CG_FreeLocalEntity( localEntity_t *le ) {
	if ( !le->prev ) {
		trap->Error( ERR_DROP, "CG_FreeLocalEntity: not active" );
		return;
	}

	// remove from the doubly linked active list
	le->prev->next = le->next;
	le->next->prev = le->prev;

	// the free list is only singly linked
	le->next = cg_freeLocalEntities;
	cg_freeLocalEntities = le;
}

/*
===================
CG_AllocLocalEntity

Will allways succeed, even if it requires freeing an old active entity
===================
*/
localEntity_t	*CG_AllocLocalEntity( void ) {
	localEntity_t	*le;

	if ( !cg_freeLocalEntities ) {
		// no free entities, so free the one at the end of the chain
		// remove the oldest active entity
		CG_FreeLocalEntity( cg_activeLocalEntities.prev );
	}

	le = cg_freeLocalEntities;
	cg_freeLocalEntities = cg_freeLocalEntities->next;

	memset( le, 0, sizeof( *le ) );

	// link into the active list
	le->next = cg_activeLocalEntities.next;
	le->prev = &cg_activeLocalEntities;
	cg_activeLocalEntities.next->prev = le;
	cg_activeLocalEntities.next = le;
	return le;
}


/*
====================================================================================

FRAGMENT PROCESSING

A fragment localentity interacts with the environment in some way (hitting walls),
or generates more localentities along a trail.

====================================================================================
*/

/*
================
CG_FragmentBounceSound
================
*/
void CG_FragmentBounceSound( localEntity_t *le, trace_t *trace ) {
	// half the fragments will make a bounce sounds
	if ( rand() & 1 ) 
	{
		sfxHandle_t	s = 0;

		switch( le->leBounceSoundType )
		{
		case LEBS_ROCK:
			s = cgs.media.rockBounceSound[Q_irand(0,1)];
			break;
		case LEBS_METAL:
			s = cgs.media.metalBounceSound[Q_irand(0,1)];// FIXME: make sure that this sound is registered properly...might still be rock bounce sound....
			break;
		default:
			return;
		}

		if ( s )
		{
			trap->S_StartSound( trace->endpos, ENTITYNUM_WORLD, CHAN_AUTO, s );
		}

		// bouncers only make the sound once...
		// FIXME: arbitrary...change if it bugs you
		le->leBounceSoundType = LEBS_NONE;
	} 
	else if ( rand() & 1 )
	{
		// we may end up bouncing again, but each bounce reduces the chance of playing the sound again or they may make a lot of noise when they settle
		// FIXME: maybe just always do this??
		le->leBounceSoundType = LEBS_NONE;
	}
}


/*
================
CG_ReflectVelocity
================
*/
void CG_ReflectVelocity( localEntity_t *le, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = cg.time - cg.frametime + cg.frametime * trace->fraction;
	BG_EvaluateTrajectoryDelta( &le->pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, le->pos.trDelta );

	VectorScale( le->pos.trDelta, le->bounceFactor, le->pos.trDelta );

	VectorCopy( trace->endpos, le->pos.trBase );
	le->pos.trTime = cg.time;

	// check for stop, making sure that even on low FPS systems it doesn't bobble
	if ( trace->allsolid || 
		( trace->plane.normal[2] > 0 && 
		( le->pos.trDelta[2] < 40 || le->pos.trDelta[2] < -cg.frametime * le->pos.trDelta[2] ) ) ) {
		le->pos.trType = TR_STATIONARY;
	} else {

	}
}

/*
================
CG_AddFragment
================
*/
void CG_AddFragment( localEntity_t *le ) {
	vec3_t	newOrigin;
	trace_t	trace;

	if (le->forceAlpha)
	{
		le->refEntity.renderfx |= RF_FORCE_ENT_ALPHA;
		le->refEntity.shaderRGBA[3] = le->forceAlpha;
	}

	if ( le->pos.trType == TR_STATIONARY ) {
		// sink into the ground if near the removal time
		int		t;
		float	t_e;
		
		t = le->endTime - cg.time;
		if ( t < (SINK_TIME*2) ) {
			le->refEntity.renderfx |= RF_FORCE_ENT_ALPHA;
			t_e = (float)((float)(le->endTime - cg.time)/(SINK_TIME*2));
			t_e = (int)((t_e)*255);

			if (t_e > 255)
			{
				t_e = 255;
			}
			if (t_e < 1)
			{
				t_e = 1;
			}

			if (le->refEntity.shaderRGBA[3] && t_e > le->refEntity.shaderRGBA[3])
			{
				t_e = le->refEntity.shaderRGBA[3];
			}

			le->refEntity.shaderRGBA[3] = t_e;

			trap->R_AddRefEntityToScene( &le->refEntity );
		} else {
			trap->R_AddRefEntityToScene( &le->refEntity );
		}

		return;
	}

	// calculate new position
	BG_EvaluateTrajectory( &le->pos, cg.time, newOrigin );

	// trace a line from previous position to new position
	CG_Trace( &trace, le->refEntity.origin, NULL, NULL, newOrigin, -1, CONTENTS_SOLID );
	if ( trace.fraction == 1.0 ) {
		// still in free fall
		VectorCopy( newOrigin, le->refEntity.origin );

		if ( le->leFlags & LEF_TUMBLE ) {
			vec3_t angles;

			BG_EvaluateTrajectory( &le->angles, cg.time, angles );
			AnglesToAxis( angles, le->refEntity.axis );
			ScaleModelAxis(&le->refEntity);
		}

		trap->R_AddRefEntityToScene( &le->refEntity );

		return;
	}

	// if it is in a nodrop zone, remove it
	// this keeps gibs from waiting at the bottom of pits of death
	// and floating levels
	if ( CG_PointContents( trace.endpos, 0 ) & CONTENTS_NODROP ) {
		CG_FreeLocalEntity( le );
		return;
	}

	if (!trace.startsolid)
	{
		// do a bouncy sound
		CG_FragmentBounceSound( le, &trace );

		if (le->bounceSound)
		{ //specified bounce sound (debris)
			trap->S_StartSound(le->pos.trBase, ENTITYNUM_WORLD, CHAN_AUTO, le->bounceSound);
		}

		// reflect the velocity on the trace plane
		CG_ReflectVelocity( le, &trace );

		trap->R_AddRefEntityToScene( &le->refEntity );
	}
}

/*
=====================================================================

TRIVIAL LOCAL ENTITIES

These only do simple scaling or modulation before passing to the renderer
=====================================================================
*/

/*
==================
CG_AddPuff
==================
*/
static void CG_AddPuff( localEntity_t *le ) {
	refEntity_t	*re;
	float		c;
	vec3_t		delta;
	float		len;

	re = &le->refEntity;

	// fade / grow time
	c = ( le->endTime - cg.time ) / (float)( le->endTime - le->startTime );

	re->shaderRGBA[0] = le->color[0] * c;
	re->shaderRGBA[1] = le->color[1] * c;
	re->shaderRGBA[2] = le->color[2] * c;

	if ( !( le->leFlags & LEF_PUFF_DONT_SCALE ) ) {
		re->radius = le->radius * ( 1.0 - c ) + 8;
	}

	BG_EvaluateTrajectory( &le->pos, cg.time, re->origin );

	// if the view would be "inside" the sprite, kill the sprite
	// so it doesn't add too much overdraw
	VectorSubtract( re->origin, cg.refdef.vieworg, delta );
	len = VectorLength( delta );
	if ( len < le->radius ) {
		CG_FreeLocalEntity( le );
		return;
	}

	trap->R_AddRefEntityToScene( re );
}

/*
===================
CG_AddScorePlum
===================
*/
#define NUMBER_SIZE		8

void CG_AddScorePlum( localEntity_t *le ) {
	refEntity_t	*re;
	vec3_t		origin, delta, dir, vec, up = {0, 0, 1};
	float		c, len;
	int			i, score, digits[10], numdigits, negative;

	re = &le->refEntity;

	c = ( le->endTime - cg.time ) * le->lifeRate;

	score = le->radius;
	if (score < 0) {
		re->shaderRGBA[0] = 0xff;
		re->shaderRGBA[1] = 0x11;
		re->shaderRGBA[2] = 0x11;
	}
	else {
		re->shaderRGBA[0] = 0xff;
		re->shaderRGBA[1] = 0xff;
		re->shaderRGBA[2] = 0xff;
		if (score >= 50) {
			re->shaderRGBA[1] = 0;
		} else if (score >= 20) {
			re->shaderRGBA[0] = re->shaderRGBA[1] = 0;
		} else if (score >= 10) {
			re->shaderRGBA[2] = 0;
		} else if (score >= 2) {
			re->shaderRGBA[0] = re->shaderRGBA[2] = 0;
		}

	}
	if (c < 0.25)
		re->shaderRGBA[3] = 0xff * 4 * c;
	else
		re->shaderRGBA[3] = 0xff;

	re->radius = NUMBER_SIZE / 2;

	VectorCopy(le->pos.trBase, origin);
	origin[2] += 110 - c * 100;

	VectorSubtract(cg.refdef.vieworg, origin, dir);
	CrossProduct(dir, up, vec);
	VectorNormalize(vec);

	VectorMA(origin, -10 + 20 * sin(c * 2 * M_PI), vec, origin);

	// if the view would be "inside" the sprite, kill the sprite
	// so it doesn't add too much overdraw
	VectorSubtract( origin, cg.refdef.vieworg, delta );
	len = VectorLength( delta );
	if ( len < 20 ) {
		CG_FreeLocalEntity( le );
		return;
	}

	negative = qfalse;
	if (score < 0) {
		negative = qtrue;
		score = -score;
	}

	for (numdigits = 0; !(numdigits && !score); numdigits++) {
		digits[numdigits] = score % 10;
		score = score / 10;
	}

	if (negative) {
		digits[numdigits] = 10;
		numdigits++;
	}

	for (i = 0; i < numdigits; i++) {
		VectorMA(origin, (float) (((float) numdigits / 2) - i) * NUMBER_SIZE, vec, re->origin);
		re->customShader = cgs.media.numberShaders[digits[numdigits-1-i]];
		trap->R_AddRefEntityToScene( re );
	}
}

/*
===================
CG_AddDamagePlum
===================
*/

void CG_AddDamagePlum( localEntity_t *le ) {
	refEntity_t	*re;
	vec3_t		origin, delta, dir, vec, up = {0, 0, 1};
	float		c, len;
	int			i, dmg, digits[10], numdigits, negative;

	re = &le->refEntity;

	c = ( le->endTime - cg.time ) * le->lifeRate;

	dmg = le->radius;

	// If we got no damage to report, dont show the plum
	if (!dmg) {
		return;
	}

	// If the damage is positive, it means we actually healed instead of sustaining damage
	if (dmg < 0) {
		// Show it as green if we healed
		re->shaderRGBA[0] = 0x11;
		re->shaderRGBA[1] = 0xff;
		re->shaderRGBA[2] = 0x11;
	} else {
		// Show it as red if we sustained damage
		re->shaderRGBA[0] = le->color[0];
		re->shaderRGBA[1] = le->color[1];
		re->shaderRGBA[2] = le->color[2];
	}
	
	if (c < 0.25)
		re->shaderRGBA[3] = 0xff * 4 * c;
	else
		re->shaderRGBA[3] = 0xff;

	//re->radius = 4;

	VectorCopy(le->pos.trBase, origin);
	origin[2] += 110 - c * 100;

	VectorSubtract(cg.refdef.vieworg, origin, dir);
	CrossProduct(dir, up, vec);
	VectorNormalize(vec);

	VectorMA(origin, -10 + 20 * sin(c * 2 * M_PI), vec, origin);

	// if the view would be "inside" the sprite, kill the sprite
	// so it doesn't add too much overdraw
	VectorSubtract( origin, cg.refdef.vieworg, delta );
	len = VectorLength( delta );
	if (len < 250) {
		re->radius = 2;
	} else if (len > 750) {
		re->radius = 4;
	} else {
		re->radius = 2 + ((float)(len-250)/250);
	}
	/*if ( len < 20 ) {
		CG_FreeLocalEntity( le );
		return;
	}*/

	negative = qfalse;
	if (dmg < 0) {
		//negative = qtrue;  (Dont show - either way, just change color)
		dmg = -dmg;
	}

	for (numdigits = 0; !(numdigits && !dmg); numdigits++) {
		digits[numdigits] = dmg % 10;
		dmg /= 10;
	}

	if (negative) {
		digits[numdigits] = 10;
		numdigits++;
	}

	for (i = 0; i < numdigits; i++) {
		VectorMA(origin, (float) (((float) numdigits / 2) - i) * (2*re->radius), vec, re->origin);
		re->customShader = cgs.media.plumShaders[digits[numdigits-1-i]];
		trap->R_AddRefEntityToScene( re );
	}
}

/*
===================
CG_AddLine

for beams and the like.
===================
*/
void CG_AddLine( localEntity_t *le )
{
	refEntity_t	*re;

	re = &le->refEntity;

	re->reType = RT_LINE;

	trap->R_AddRefEntityToScene( re );
}

//==============================================================================

/*
===================
CG_AddLocalEntities

===================
*/
void CG_AddLocalEntities( void ) {
	localEntity_t	*le, *next;

	// walk the list backwards, so any new local entities generated
	// (trails, marks, etc) will be present this frame
	le = cg_activeLocalEntities.prev;
	for ( ; le != &cg_activeLocalEntities ; le = next ) {
		// grab next now, so if the local entity is freed we
		// still have it
		next = le->prev;

		if ( cg.time >= le->endTime ) {
			CG_FreeLocalEntity( le );
			continue;
		}
		switch ( le->leType ) {
		default:
			trap->Error( ERR_DROP, "Bad leType: %i", le->leType );
			break;

		case LE_MARK:
			break;

		case LE_FRAGMENT:			// gibs and brass
			CG_AddFragment( le );
			break;

		case LE_PUFF:
			CG_AddPuff( le );
			break;

		case LE_SCOREPLUM:
			CG_AddScorePlum( le );
			break;

		case LE_DAMAGEPLUM:
			CG_AddDamagePlum( le );
			break;

		case LE_LINE:					// oriented lines for FX
			CG_AddLine( le );
			break;
		}
	}
}




