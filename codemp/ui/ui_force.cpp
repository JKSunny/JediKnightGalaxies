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

/*
=======================================================================

FORCE INTERFACE 

=======================================================================
*/

// use this to get a demo build without an explicit demo build, i.e. to get the demo ui files to build
#include "ui_local.h"
#include "qcommon/qfiles.h"
#include "ui_force.h"

int uiMaxPoints = 20;

extern const char *UI_TeamName(int team);

void Menu_ShowItemByName(menuDef_t *menu, const char *p, qboolean bShow);

extern int	uiSkinColor;
extern int	uiHoldSkinColor;

int uiSaberColorShaders[NUM_SABER_COLORS];

qboolean UI_SkinColor_HandleKey(int flags, float *special, int key, int num, int min, int max, int type) 
{
  if (key == A_MOUSE1 || key == A_MOUSE2 || key == A_ENTER || key == A_KP_ENTER) 
  {
  	int i = num;

	if (key == A_MOUSE2)
	{
	    i--;
	}
	else
	{
	    i++;
	}

    if (i < min)
	{
		i = max;
	}
	else if (i > max)
	{
      i = min;
    }

    num = i;

	uiSkinColor = num;

	uiHoldSkinColor = uiSkinColor;

	UI_FeederSelection(FEEDER_Q3HEADS, uiInfo.q3SelectedHead, NULL);

    return qtrue;
  }
  return qfalse;
}
