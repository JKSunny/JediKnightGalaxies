#include "bg_npcnames.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#if defined(_GAME)
    #include "g_local.h"
#elif defined(_CGAME)
    #include "../cgame/cg_local.h"
#endif

static std::vector<std::string> npcNames;

bool HumanNamesLoaded = false;

static void BG_LoadDefaultNames()
{
	npcNames.push_back("NONNAME");
	npcNames.push_back("R2D2 Droid");
	npcNames.push_back("R5D2 Droid");
	npcNames.push_back("Protocol Droid");
	npcNames.push_back("Weequay");
}

void BG_Load_NPC_Names()
{				// Load bot first names from external file.
	if (HumanNamesLoaded)
		return;

	fileHandle_t f = NULL_FILE;
	int len = trap->FS_Open( "npc_names_list.dat", &f, FS_READ );

	HumanNamesLoaded = true;
	
	BG_LoadDefaultNames();

	if ( !f || len < 0 )
	{
		return;
	}

	if ( !len )
	{			//empty file
		trap->FS_Close( f );
		return;
	}
	
	std::string buf( len, '\0' );
	trap->FS_Read( &buf[0], len, f );
	trap->FS_Close( f );
	std::istringstream input( buf );

	std::string line;
	while( std::getline( input, line ) )
	{
		auto slash = line.find( "//" );
		if( slash == 0 )
			continue;
		else if( slash != std::string::npos )
			line.erase( slash );

		npcNames.push_back( line );
	}

#if defined(_GAME)
	// We only display this on the server-side
	// Subtract one to exclude NONAME from the count
	trap->Print( "^5*** ^3%s^5: There are ^2%i^5 NPC names in the database.\n", GAME_VERSION, (int)npcNames.size()-1 );
#endif
}

const char* BG_Get_NPC_Name(const int index)
{
	assert(index >= 0 && index < npcNames.size());
	return npcNames[index].c_str();
}

int BG_Num_NPC_Names()
{
	return (int)npcNames.size();
}
