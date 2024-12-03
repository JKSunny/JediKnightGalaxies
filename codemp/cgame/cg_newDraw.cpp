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

#include "cg_local.h"
#include "../ui/ui_shared.h"

extern displayContextDef_t cgDC;


int CG_GetSelectedPlayer() {
	if (cg_currentSelectedPlayer.integer < 0 || cg_currentSelectedPlayer.integer >= numSortedTeamPlayers) {
		cg_currentSelectedPlayer.integer = 0;
	}
	return cg_currentSelectedPlayer.integer;
}

qhandle_t CG_StatusHandle(int task) {
	return NULL_HANDLE;
}


float CG_GetValue(int ownerDraw) {
	centity_t	*cent;
 	clientInfo_t *ci;
	playerState_t	*ps;

	cent = &cg_entities[cg.snap->ps.clientNum];
	ps = &cg.snap->ps;

	switch (ownerDraw) {
	case CG_SELECTEDPLAYER_ARMOR:
		ci = cgs.clientinfo + sortedTeamPlayers[CG_GetSelectedPlayer()];
		return ci->armor;
		break;
	case CG_SELECTEDPLAYER_HEALTH:
		ci = cgs.clientinfo + sortedTeamPlayers[CG_GetSelectedPlayer()];
		return ci->health;
		break;
	case CG_PLAYER_ARMOR_VALUE:
		return ps->stats[STAT_SHIELD];
		break;
	case CG_PLAYER_AMMO_VALUE:
		if ( cent->currentState.weapon ) 
		{
			return ps->stats[STAT_TOTALAMMO];
		}
		break;
	case CG_PLAYER_SCORE:
		return cg.snap->ps.persistant[PERS_SCORE];
		break;
	case CG_PLAYER_HEALTH:
		return ps->stats[STAT_HEALTH];
		break;
	case CG_RED_SCORE:
		return cgs.scores1;
		break;
	case CG_BLUE_SCORE:
		return cgs.scores2;
		break;
	case CG_PLAYER_FORCE_VALUE:
		return ps->forcePower;
		break;
	default:
		break;
	}
	return -1;
}

qboolean CG_OtherTeamHasFlag(void) {
	if (cgs.gametype == GT_CTF) {
		int team = cg.snap->ps.persistant[PERS_TEAM];
		if (team == TEAM_RED && cgs.redflag == FLAG_TAKEN) {
			return qtrue;
		} else if (team == TEAM_BLUE && cgs.blueflag == FLAG_TAKEN) {
			return qtrue;
		} else {
			return qfalse;
		}
	}
	return qfalse;
}

qboolean CG_YourTeamHasFlag(void) {
	if (cgs.gametype == GT_CTF) {
		int team = cg.snap->ps.persistant[PERS_TEAM];
		if (team == TEAM_RED && cgs.blueflag == FLAG_TAKEN) {
			return qtrue;
		} else if (team == TEAM_BLUE && cgs.redflag == FLAG_TAKEN) {
			return qtrue;
		} else {
			return qfalse;
		}
	}
	return qfalse;
}

// THINKABOUTME: should these be exclusive or inclusive.. 
// 
qboolean CG_OwnerDrawVisible(int flags) {

	if (flags & CG_SHOW_TEAMINFO) {
		return (cg_currentSelectedPlayer.integer == numSortedTeamPlayers);
	}

	if (flags & CG_SHOW_NOTEAMINFO) {
		return !(cg_currentSelectedPlayer.integer == numSortedTeamPlayers);
	}

	if (flags & CG_SHOW_OTHERTEAMHASFLAG) {
		return CG_OtherTeamHasFlag();
	}

	if (flags & CG_SHOW_YOURTEAMHASENEMYFLAG) {
		return CG_YourTeamHasFlag();
	}

	if (flags & (CG_SHOW_BLUE_TEAM_HAS_REDFLAG | CG_SHOW_RED_TEAM_HAS_BLUEFLAG)) {
		if (flags & CG_SHOW_BLUE_TEAM_HAS_REDFLAG && (cgs.redflag == FLAG_TAKEN || cgs.flagStatus == FLAG_TAKEN_RED)) {
			return qtrue;
		} else if (flags & CG_SHOW_RED_TEAM_HAS_BLUEFLAG && (cgs.blueflag == FLAG_TAKEN || cgs.flagStatus == FLAG_TAKEN_BLUE)) {
			return qtrue;
		}
		return qfalse;
	}

	if (flags & CG_SHOW_ANYTEAMGAME) {
		if( cgs.gametype >= GT_TEAM) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_ANYNONTEAMGAME) {
		if( cgs.gametype < GT_TEAM) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_CTF && cgs.gametype == GT_CTF) {
		return qtrue;
	}

	if (flags & CG_SHOW_HEALTHCRITICAL) {
		if (cg.snap->ps.stats[STAT_HEALTH] < 25) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_HEALTHOK) {
		if (cg.snap->ps.stats[STAT_HEALTH] >= 25) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_SINGLEPLAYER) {
		if( cgs.gametype == GT_SINGLE_PLAYER ) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_TOURNAMENT) {
		if( cgs.gametype == GT_DUEL || cgs.gametype == GT_POWERDUEL ) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_DURINGINCOMINGVOICE) {
	}

	if (flags & CG_SHOW_IF_PLAYER_HAS_FLAG) {
		if (cg.snap->ps.powerups[PW_REDFLAG] || cg.snap->ps.powerups[PW_BLUEFLAG]) {
			return qtrue;
		}
	}
	return qfalse;
}


const char *CG_GetKillerText(void) {
	static const char *s = "";
	if ( cg.killerName[0] ) {
		s = va("%s %s", CG_GetStringEdString("MP_INGAME", "KILLEDBY"), cg.killerName );
	}
	return s;
}


const char *CG_GetGameStatusText(void) {
	static const char *s = "";
	if (cgs.gametype == GT_POWERDUEL)
	{
		s = "";
	}	
	else if ( cgs.gametype < GT_TEAM)
	{
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR ) 
		{
			char sPlaceWith[256];
			trap->SE_GetStringTextString("MP_INGAME_PLACE_WITH", sPlaceWith, sizeof(sPlaceWith));

			s = va("%s %s %i",CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ), sPlaceWith, cg.snap->ps.persistant[PERS_SCORE] );
		}
	}
	else
	{
		if ( cg.teamScores[0] == cg.teamScores[1] ) {
			s = va("%s %i", CG_GetStringEdString("MP_INGAME", "TIEDAT"), cg.teamScores[0] );
		} else if ( cg.teamScores[0] >= cg.teamScores[1] ) {
			//s = va("%s, %i / %i", CG_GetStringEdString("MP_INGAME", "RED_LEADS"), cg.teamScores[0], cg.teamScores[1] );
			s = va("%s, %i / %i", CG_GetStringEdString2(bgGangWarsTeams[cgs.redTeam].leadstring), cg.teamScores[0], cg.teamScores[1] );
		} else {
			//s = va("%s, %i / %i", CG_GetStringEdString("MP_INGAME", "BLUE_LEADS"), cg.teamScores[1], cg.teamScores[0] );
			s = va("%s, %i / %i", CG_GetStringEdString2(bgGangWarsTeams[cgs.blueTeam].leadstring), cg.teamScores[0], cg.teamScores[1] );
		}
	}
	return s;
}
	
extern int MenuFontToHandle(int iMenuFont);

extern const char *CG_GetLocationString(const char *loc); //cg_main.c
	
//
void CG_OwnerDraw(void *alwaysNull, float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, int ownerDrawFlags, int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle,int font, int ownerDrawID) {
}

void CG_MouseEvent(int x, int y) {
	int n;

	if (cg.isChatting) {
		// Do nothing
	} else {
		// Disable the keycatcher
		if ( (cg.predictedPlayerState.pm_type == PM_NORMAL || cg.predictedPlayerState.pm_type == PM_JETPACK || cg.predictedPlayerState.pm_type == PM_FLOAT || cg.predictedPlayerState.pm_type == PM_SPECTATOR) && cg.showScores == qfalse) {
			trap->Key_SetCatcher(0);
			return;
		}
	}

	cgs.cursorX+= x;
	if (cgs.cursorX < 0)
		cgs.cursorX = 0;
	else if (cgs.cursorX > 640)
		cgs.cursorX = 640;

	cgs.cursorY += y;
	if (cgs.cursorY < 0)
		cgs.cursorY = 0;
	else if (cgs.cursorY > 480)
		cgs.cursorY = 480;

	n = Display_CursorType(cgs.cursorX, cgs.cursorY);
	cgs.activeCursor = 0;
	if (n == CURSOR_ARROW) {
		cgs.activeCursor = cgs.media.selectCursor;
	} else if (n == CURSOR_SIZER) {
		cgs.activeCursor = cgs.media.sizeCursor;
	}

	if (cgs.capturedItem) {
		Display_MouseMove(cgs.capturedItem, x, y);
	} else {
		Display_MouseMove(NULL, cgs.cursorX, cgs.cursorY);
	}

}

/*
==================
CG_HideTeamMenus
==================

*/
void CG_HideTeamMenu() {
	Menus_CloseByName("teamMenu");
	Menus_CloseByName("getMenu");
}

/*
==================
CG_ShowTeamMenus
==================

*/
void CG_ShowTeamMenu() {
	Menus_OpenByName("teamMenu");
}



void ChatBox_HandleKey(int key, qboolean down);


/*
==================
CG_EventHandling
==================
 type 0 - no event handling
      1 - team menu
      2 - hud editor

*/
void CG_EventHandling(int type) {
	cgs.eventHandling = type;
	if (type == CGAME_EVENT_NONE) {
		CG_HideTeamMenu();
	if (cg.isChatting) {
		// Pass this along to the chat system as an escape keystroke
		ChatBox_HandleKey(A_ESCAPE, qtrue);
	}
	} else if (type == CGAME_EVENT_TEAMMENU) {
		//CG_ShowTeamMenu();
	} else if (type == CGAME_EVENT_SCOREBOARD) {
	}

}



void CG_KeyEvent(int key, qboolean down) {

	if (cg.isChatting) {
		// Let the chat system handle it
		ChatBox_HandleKey(key, down);
	} else {
		// Disable the keycatcher
		if ( cg.predictedPlayerState.pm_type == PM_NORMAL || cg.predictedPlayerState.pm_type == PM_JETPACK || cg.predictedPlayerState.pm_type == PM_NORMAL || (cg.predictedPlayerState.pm_type == PM_SPECTATOR && cg.showScores == qfalse)) {
			CG_EventHandling(CGAME_EVENT_NONE);
			trap->Key_SetCatcher(0);
			return;
		}
	}

	if (!down) {
		return;
	}
	//if (key == trap->Key_GetKey("teamMenu") || !Display_CaptureItem(cgs.cursorX, cgs.cursorY)) {
	// if we see this then we should always be visible
	//  CG_EventHandling(CGAME_EVENT_NONE);
	//  trap->Key_SetCatcher(0);
	//}



	Display_HandleKey(key, down, cgs.cursorX, cgs.cursorY);

	if (cgs.capturedItem) {
		cgs.capturedItem = NULL;
	}	else {
		if (key == A_MOUSE2 && down) {
			cgs.capturedItem = Display_CaptureItem(cgs.cursorX, cgs.cursorY);
		}
	}
}

int CG_ClientNumFromName(const char *p) {
	int i;
	for (i = 0; i < cgs.maxclients; i++) {
		if (cgs.clientinfo[i].infoValid && Q_stricmp(cgs.clientinfo[i].name, p) == 0) {
			return i;
		}
	}
	return -1;
}

void CG_ShowResponseHead(void) {
	Menus_OpenByName("voiceMenu");
	trap->Cvar_Set("cl_conXOffset", "72");
	cg.voiceTime = cg.time;
}

void CG_RunMenuScript(char **args) {
}

qboolean CG_DeferMenuScript (char **args) 
{
	return qfalse;
}

void CG_GetTeamColor(vec4_t *color) {
	if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
		(*color)[0] = 1.0f;
		(*color)[3] = 0.25f;
		(*color)[1] = (*color)[2] = 0.0f;
	} else if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
		(*color)[0] = (*color)[1] = 0.0f;
		(*color)[2] = 1.0f;
		(*color)[3] = 0.25f;
	} else {
		(*color)[0] = (*color)[2] = 0.0f;
		(*color)[1] = 0.17f;
		(*color)[3] = 0.25f;
	}
}
