// jkg_gangwars.h
// Contains crap about the TDM/"Gang Wars" gametype proposed by Pande
// Copyright (c) 2013 Jedi Knight Galaxies

#ifndef __JKG_GANGWARS_H
#define __JKG_GANGWARS_H

#pragma once

typedef struct {
	char name[512];			// Display Name
	char refPtr[512];		// Reference/Internal name
	qhandle_t teamIcon;		// Not used by _GAME
	char modelStore[32][64];	// Parsed separately.
	char defaultModel[64];	// The default model for this team
	unsigned char numModelsInStore;
	qboolean useTeamColors;	// Use team colors for this team? (ie force red team/blue team colors

	// STRINGS
	char longname[64];
	char joinstring[64];
	char toomanystring[64];
	char leadstring[64];
	char menujoinstring[64];
	char menustring[64];
	char flagtakenstring[64];
	char flagreturnedstring[64];
	char flagcapturedstring[64];

	// Scoreboard / Join Screen colors
	vec4_t teamColor;
} gangWarsTeam_t;

// UQ1: Moved to q_shared.c to stop compile header issues...
extern gangWarsTeam_t bgGangWarsTeams[32];
extern int bgnumGangWarTeams;

void JKG_BG_GangWarsInit(void);
void JKG_BG_GangWarsExit(void);

int JKG_GetTeamByReference(char *reference);
gangWarsTeam_t *JKG_GetTeamPtrByReference(char *reference);

#endif
