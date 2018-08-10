/*
	Orgia C-D v 1.1 - Client Hook - CD PROOF 18.11.2004
	by ORGANNER

	Credits:
	- Patrick
	- LTFXguy
	- Uall
	- panzer
	- Sruh
*/

/*
	Notes:
	- We need a plave where we can draw a stuff ( Client functions are called every 200ms, and that makes it blink )
	- Every small/big code chane run hack with CD, it will fix some errors ;)
	- We need a Opengl hookage
	- Do not hook more than 2 Client functions, that will make you detected.
	- When you runs hook, close all laging programs.
	- The Sleep function in ClientDllThread() is like the detection hadnler, if you will getected too often, try change it.
	- Sleep(200) looks good for me, i played 3 ( ~5 mins ) runds on server with 25 players and WINAMP + MIRC opened, without detection.

	BTW: Thats not LIGHT hack anymore :p
*/

#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLu32.lib")
#pragma comment(lib,"GLaux.lib")

#include <Windows.h>
#include <Gl/Gl.h>
#include "Engine.h"

// Engine love
engine_studio_api_s* pEngstudio	 = (engine_studio_api_s*) 0x1ECF1F0;
cl_enginefuncs_s*    pEngfuncs   = (cl_enginefuncs_s*)	  0x1EB32B0;
playermove_s*		 pPmove		 = (playermove_s*)		  0x2D5B160;
//==========================================================================
VOID ClientDllThread();
//==========================================================================
BOOL DllMain( HMODULE hDll, DWORD dwReason, LPVOID lpReserved )
{
	switch( dwReason ) 
	{ 
		case DLL_PROCESS_ATTACH :
		{
			MessageBox( NULL, "INJECTED", "Orgia C-D v 1.1", NULL );
			CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)ClientDllThread, NULL, NULL, NULL);
		}
		case DLL_PROCESS_DETACH :
		{
			break;
		}
	}
	
	return TRUE;
}
//==========================================================================