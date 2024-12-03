// jkg_chatcmds.h
// JKG - Chat command processing
// Heavily based on the engine's command tokenizer
// Copyright (c) 2013 Jedi Knight Galaxies

#ifndef CGAME_JKG_CHATCMDS_H
#define CGAME_JKG_CHATCMDS_H

typedef void (*xccommand_t) ( void );


int		CCmd_Argc( void );
char	*CCmd_Argv( int arg );
void	CCmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
char	*CCmd_Args( void );
char *CCmd_ArgsFrom( int arg );
void	CCmd_ArgsBuffer( char *buffer, int bufferLength );
char *CCmd_Cmd();
qboolean CCmd_Execute(const char *command);
void CCmd_TokenizeString( const char *text_in );
void	CCmd_AddCommand( const char *cmd_name, xccommand_t function );
void	CCmd_RemoveCommand( const char *cmd_name );

void Text_DrawText(int x, int y, const char *text, const float* rgba, int iFontIndex, const int limit, float scale);

#endif
