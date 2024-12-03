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

// bg_weapons.c -- part of bg_pmove functionality

#include "qcommon/q_shared.h"
#include "bg_public.h"
#include "bg_local.h"
#include "bg_ammo.h"

#if defined(_GAME)
	#include "g_local.h"
#elif defined(_CGAME)
	#include "cgame/cg_local.h"
#elif defined(IN_UI)
	#include "ui/ui_local.h"
#endif

weaponAmmo_t xweaponAmmo [] =
{
	/* Ammo Index		  Cost	  Size	  Max */
	{ AMMO_NONE			, -1	, -1	, -1	},
	{ AMMO_FORCE		, 0		, 0		, 1000	},
	{ AMMO_BLASTER		, 0		, 60	, 3000	},
	{ AMMO_POWERCELL	, 0		, 50	, 3000	},
	{ AMMO_METAL_BOLTS	, 0		, 150	, 3000	},
	{ AMMO_CONCUSSION   , 0     , 10    , 500   },
	{ AMMO_ROCKETS		, 0		, 1		, 25	},
	{ AMMO_EMPLACED		, 0		, 0		, 800	},
	{ AMMO_THERMAL		, 0		, 0		, 10	},
	{ AMMO_TRIPMINE		, 0		, 0		, 10	},
	{ AMMO_DETPACK		, 0		, 0		, 10	}
};

weaponData_t* weaponDataTable;
static unsigned int numLoadedWeapons;
static unsigned int numWeapons[MAX_WEAPONS];

g2WeaponInstance_s g2WeaponInstances[MAX_WEAPON_TABLE_SIZE];

unsigned int BG_NumberOfLoadedWeapons ( void )
{
    return numLoadedWeapons;
}

unsigned int BG_NumberOfWeaponVariations ( unsigned char weaponId )
{
    return numWeapons[weaponId];
}

weaponData_t *BG_GetWeaponDataByIndex( int index )
{
	if(index >= 0 && index < numLoadedWeapons)
	{
		return &weaponDataTable[index];
	}
	return NULL;
}

//Xycaleth/eezstreet add
qboolean BG_GetWeaponByIndex ( int index, int *weapon, int *variation ) { 
	weaponData_t *weaponData = NULL;

	if(index >= MAX_WEAPON_TABLE_SIZE || index < 0)
		return qfalse;
		
	weaponData = &weaponDataTable[index]; 

	*weapon = weaponData->weaponBaseIndex; 
	*variation = weaponData->weaponModIndex; 
	return qtrue;
}
//Xycaleth end

int BG_GetWeaponIndexFromClass ( int weapon, int variation )
{
    static int lastWeapon = 0;
    static int lastVariation = 0;
    static int lastIndex = -1;
    
    if ( lastIndex != -1 && weapon == lastWeapon && variation == lastVariation )
    {
        return lastIndex;
    }
    else
    {
        int i = 0;
        for ( i = 0; i < numLoadedWeapons; i++ )
        {
            if ( weapon == weaponDataTable[i].weaponBaseIndex &&
                variation == weaponDataTable[i].weaponModIndex )
            {
                lastIndex = i;
                lastWeapon = weapon;
                lastVariation = variation;
                
                return i;
            }
        }
    }
    
    return -1;
}

weaponData_t *BG_GetWeaponByClassName ( const char *className )
{
    static char lastClassName[MAX_QPATH] = { 0 };
    static weaponData_t *lastWeaponData = NULL;
    
    if ( lastWeaponData != NULL && Q_stricmp (className, lastClassName) == 0 )
    {
        return lastWeaponData;
    }
    else
    {
        int i = 0;
        for ( i = 0; i < numLoadedWeapons; i++ )
        {
            if ( Q_stricmp (weaponDataTable[i].classname, className) == 0 )
            {
                lastWeaponData = &weaponDataTable[i];
                Q_strncpyz (lastClassName, className, sizeof (lastClassName));
                
                return &weaponDataTable[i];
            }
        }
    }
    
    return NULL;
}

int BG_GetWeaponIndex ( unsigned int weapon, unsigned int variation )
{
    int i;
    for ( i = 0; i < numLoadedWeapons; i++ )
    {
        if ( weaponDataTable[i].weaponBaseIndex == weapon && weaponDataTable[i].weaponModIndex == variation )
        {
            break;
        }
    }
    
    return i;
}

qboolean BG_WeaponVariationExists ( unsigned int weaponId, unsigned int variation )
{
    return BG_GetWeaponIndex (weaponId, variation) != numLoadedWeapons;
}

qboolean BG_WeaponCanUseSpecialAmmo (weaponData_t* wp) {
	if (wp->weaponBaseIndex == WP_NONE || wp->weaponBaseIndex == WP_MELEE || wp->weaponBaseIndex == WP_SABER) {
		return qfalse; // Can't cycle ammo on these weapons
	}

	if (wp->numFiringModes == 0) {
		return qfalse; // No firing modes on this weapon
	}

	if (wp->firemodes[0].useQuantity) {
		return qfalse; // It drains quantity from the item stack, so it's not a weapon that can have its ammo cycled
	}

	return qtrue;
}

weaponData_t *GetWeaponDataUnsafe ( unsigned char weapon, unsigned char variation )
{
    static weaponData_t *lastWeapon = NULL;
	unsigned int i;

	/* Remember the last weapon to cut down in the number of lookups required */
	if ( lastWeapon && lastWeapon->weaponBaseIndex == weapon && lastWeapon->weaponModIndex == variation )
	{
		return lastWeapon;
	}

	/* Check the table to see if we can find a match, remember it and return it! */
	for ( i = 0; i < numLoadedWeapons; i++ )
	{
		if ( weaponDataTable[i].weaponBaseIndex == weapon && weaponDataTable[i].weaponModIndex == variation )
		{
			lastWeapon = &weaponDataTable[i];
			return lastWeapon;
		}
	}
	
	return NULL;
}

/**************************************************
* GetWeaponData
*
* This is the main routine used in the new weapon
* table. It will search for the provided base weapon
* and its possible variation (note that the variation
* field might be bitwise). Upon failure, the client
* is dropped.
**************************************************/

weaponData_t *GetWeaponData( unsigned char baseIndex, unsigned char modIndex )
{
	weaponData_t *weapon = GetWeaponDataUnsafe (baseIndex, modIndex);
	if ( weapon )
	{
	    return weapon;
	}

	/* This is a serious error, this is a weapon we don't know! */
	Com_Error( ERR_DROP, "No weapon with base %i and variation %i could be found.", baseIndex, modIndex );
	return NULL;
}

short GetAmmoMax ( unsigned char ammoIndex )
{
    return ammoTable[ammoIndex].ammoMax;
}

// Just in case we need to initialize the struct any other way,
// it's easier to have it's own function.
void BG_InitializeWeaponData ( weaponData_t *weaponData )
{
    memset (weaponData, 0, sizeof (*weaponData));
    weaponData->speedModifier = 1.0f;
	weaponData->anims.ready.torsoAnim = BOTH_STAND1;
	weaponData->anims.ready.legsAnim = BOTH_STAND1;

	weaponData->anims.forwardWalk.legsAnim = BOTH_WALK1;
	weaponData->anims.crouchWalkBack.legsAnim = BOTH_CROUCH1WALKBACK;
	weaponData->anims.crouchWalk.legsAnim = BOTH_CROUCH1WALK;
	weaponData->anims.jump.legsAnim = weaponData->anims.jump.torsoAnim = BOTH_JUMP1;
	weaponData->anims.land.legsAnim = weaponData->anims.land.torsoAnim = BOTH_LAND1;
	weaponData->anims.run.legsAnim = BOTH_RUN1;
	weaponData->anims.sprint.legsAnim = weaponData->anims.sprint.torsoAnim = BOTH_SPRINT;
}

void BG_AddWeaponData ( weaponData_t *weaponData )
{
    if ( numLoadedWeapons >= MAX_WEAPON_TABLE_SIZE )
    {
        Com_Printf (S_COLOR_RED "ERROR: Too many weapons trying to be loaded. %s was not loaded.", weaponData->classname);
        return;
    }
    
    weaponDataTable[numLoadedWeapons] = *weaponData;
    
    numLoadedWeapons++;
    numWeapons[weaponData->weaponBaseIndex]++;
}

void BG_InitializeWeapons ( void )
{
    weaponData_t predefinedWeapons;

	weaponDataTable = (weaponData_t*)malloc(sizeof(weaponData_t) * MAX_WEAPON_TABLE_SIZE);
	if (weaponDataTable == nullptr)
	{
		Com_Error(ERR_FATAL, "couldn't allocate memory for weapon data table...");
		return;
	}
    
    //BG_InitializeAmmo();
    numLoadedWeapons = 0;

    memset (numWeapons, 0, sizeof (numWeapons));
    memset (weaponDataTable, 0, sizeof (weaponData_t) * MAX_WEAPON_TABLE_SIZE);
    
    BG_InitializeWeaponData (&predefinedWeapons);
    
    predefinedWeapons.weaponBaseIndex = WP_NONE;
    BG_AddWeaponData (&predefinedWeapons);
    
    predefinedWeapons.weaponBaseIndex = WP_EMPLACED_GUN;
    BG_AddWeaponData (&predefinedWeapons);
    
    predefinedWeapons.weaponBaseIndex = WP_TURRET;
    BG_AddWeaponData (&predefinedWeapons);
    
    if ( !BG_LoadWeapons (weaponDataTable, &numLoadedWeapons, numWeapons) )
    {
        #ifdef _DEBUG
        Com_Printf (S_COLOR_RED "No weapons were loaded.\n");
        #endif
        return;
    }
}

void BG_ShutdownWeapons()
{
	if (weaponDataTable != nullptr)
	{
		free(weaponDataTable);
	}
}

qboolean BG_DumpWeaponList ( const char *filename )
{
    char buffer[8192] = { 0 };
    char *classnames[MAX_WEAPON_TABLE_SIZE] = { NULL };
    int i;
    fileHandle_t f;
    
    Com_sprintf (buffer, sizeof (buffer), "%-64s | %s\n", "Display Name", "Class Name");
    Q_strcat (buffer, sizeof (buffer), "-----------------------------------------------------------------+----------------------------------\n");
    for ( i = 0; i < numLoadedWeapons; i++ )
    {
        weaponData_t *w = &weaponDataTable[i];
        Q_strcat (buffer, sizeof (buffer), va ("%-64s | %s\n", w->displayName, w->classname));
        classnames[i] = w->classname;
    }
    
    Q_strcat (buffer, sizeof (buffer), "\n");
    //qsort (classnames, numLoadedWeapons, sizeof (char *), strcmp);
    i = 0;
    while ( i < numLoadedWeapons )
    {
        int duplicates = 0;
        int j = i + 1;
        while ( j < numLoadedWeapons && strcmp (classnames[i], classnames[j]) == 0 )
        {
            duplicates++;
            j++;
        }
        
        if ( duplicates > 0 )
        {
            Q_strcat (buffer, sizeof (buffer), va ("%s has %d duplicates.\n", classnames[i], duplicates));
        }
        
        i = j;
    }
    
    trap->FS_Open (filename, &f, FS_WRITE);
    if ( f )
    {
        trap->FS_Write (buffer, strlen (buffer), f);
        trap->FS_Close (f);
        
        return qtrue;
    }
    
    return qfalse;
}

void BG_PrintWeaponList( void )
{
	int i = 0;
	Com_Printf("----------------------------------------------------------------------------------------------------\n");
	for ( i = 0; i < numLoadedWeapons; i++ )
    {
        weaponData_t *w = &weaponDataTable[i];
		Com_Printf("%-64s | %s\n", w->displayName, w->classname);
    }
	Com_Printf("----------------------------------------------------------------------------------------------------\n");
}
