///////////////////////////////////
//
// JKG - Chat command processing
//
// Heavilly based on the engine's command tokenizer
//
//////////////////////////////////

#ifndef GAME_JKG_CHATCMDS_H
#define GAME_JKG_CHATCMDS_H

typedef void (*xccommand_t) (void);


int		CCmd_Argc( void );
char	*CCmd_Argv( int arg );
void	CCmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
char	*CCmd_Args( void );
char *CCmd_ArgsFrom( int arg );
void	CCmd_ArgsBuffer( char *buffer, int bufferLength );
char *CCmd_Cmd();
void CCmd_TokenizeString( const char *text_in );
void	CCmd_AddCommand( const char *cmd_name, xccommand_t function );
void	CCmd_RemoveCommand( const char *cmd_name );
int CCmd_Caller( void );
char *CCmd_ConcatArgs( int start );

#endif