#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "luaplayer.h"


static lua_State *L;


const char * runScript(const char* script, bool isStringBuffer )
{	
	printf("Creating luaVM... \n");

	L = luaL_newstate ();
	
	// Init Standard libraries
	luaL_openlibs(L);

        printf("Loading libs... ");
	 // init graphics
    	luaGraphics_init(L);
    
    	// init controls
    	luaControls_init(L);
    	
    	//init Timer
    	luaTimer_init(L);
    	
    	// init System
    	luaSystem_init(L);
    
    	// init sound
    	luaSound_init(L);
    	
    	printf("done !\n");
     
        printf("Loading script : `%s'\n", script);
        dbgprintf("Loading script : `%s'\n", script);
		
	int s = 0;
	const char * errMsg = NULL;

	if(!isStringBuffer) 
		s = luaL_loadfile(L, script);
	else 
		s = luaL_loadbuffer(L, script, strlen(script), NULL);
		
	if (s == 0) {
		s = lua_pcall(L, 0, LUA_MULTRET, 0);
	}
	if (s) {
		errMsg = lua_tostring(L, -1);
		printf("error: %s\n", lua_tostring(L, -1));
		//dbgprintf("error: %s\n", lua_tostring(L, -1));
		lua_pop(L, 1); // remove error message
	}
	lua_close(L);
	
	return errMsg;
}
