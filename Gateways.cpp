// Keeps original slots address to own CD's crc check :)
// Credits goes to LTFX guy for the gateways and slots method.
#include <Windows.h>
#include "Client.h"

DWORD* Slots = (DWORD*)0x01EB34C0;

DWORD dwTempEntUpdate	= NULL;
DWORD dwCreateMove		= NULL;
DWORD dwRedraw			= NULL;
DWORD dwPlayerMove		= NULL;
DWORD dwAddEnt			= NULL;
DWORD dwPostRunCmd		= NULL;

DWORD dwOriginal_HUD_Redraw			= NULL;
DWORD dwOriginal_CL_CreateMove		= NULL;
DWORD dwOriginal_HUD_PlayerMove		= NULL;
DWORD dwOriginal_HUD_PostRunCmd		= NULL;
DWORD dwOriginal_HUD_TempEntUpdate	= NULL;
DWORD dwOriginal_HUD_AddEntity		= NULL;
DWORD dwOriginal_HUD_Key_Event		= NULL;

int AddEntResult	= 1;
int KeyEventResult	= 1;
DWORD dwRetAddress  = NULL;
//=====================================================================
__declspec(naked) void Gateway2_CL_CreateMove(void)
{
  __asm
  {
    call CL_CreateMove;
    jmp dwRetAddress;
  }
}
//=====================================================================
__declspec(naked) void Gateway1_CL_CreateMove(void)
{
  __asm
  {
    push esi;
    mov esi,dword ptr ss:[esp+0x28];
    mov dwRetAddress,esi;
    push dwCreateMove;
    pop esi;
    mov dword ptr ss:[esp+0x28],esi;
    pop esi;
    ret;
  }
}
//=====================================================================
__declspec(naked) void Gateway2_HUD_Redraw(void)
{
  __asm
  {
    call HUD_Redraw;
    jmp dwRetAddress;
  }
}
//=====================================================================
__declspec(naked) void Gateway1_HUD_Redraw(void)
{
  __asm
  {
    push esi;
    mov esi,dword ptr ss:[esp+0x10];
    mov dwRetAddress,esi;
    push dwRedraw
    pop esi;
    mov dword ptr ss:[esp+0x10],esi;
    pop esi;
    ret;
  }
}
//=====================================================================
__declspec(naked) void Gateway2_HUD_PlayerMove(void)
{
  __asm
  {
    call HUD_PlayerMove;
    jmp dwRetAddress;
  }
}
//=====================================================================
__declspec(naked) void Gateway1_HUD_PlayerMove(void)
{
  __asm
  {
    push esi;
    mov esi,dword ptr ss:[esp+0x10];
    mov dwRetAddress,esi;
    push dwPlayerMove
    pop esi;
    mov dword ptr ss:[esp+0x10],esi;
    pop esi;
    ret;
  }
}
//=====================================================================
__declspec(naked) void Gateway2_HUD_AddEntity(void)
{
  __asm
  {
    mov AddEntResult, eax;
    call HUD_AddEntity;
    mov eax, AddEntResult;
    jmp dwRetAddress;
  }
}
//=====================================================================
__declspec(naked) void Gateway1_HUD_AddEntity(void)
{	
  __asm
  {
    push esi;
    mov esi,dword ptr ss:[esp+0x14];
    mov dwRetAddress,esi;
    push dwAddEnt
    pop esi;
    mov dword ptr ss:[esp+0x14],esi;
    pop esi;
    ret;
  }
}
//=====================================================================
__declspec(naked) void Gateway2_HUD_Key_Event(void)
{
  __asm
  {
    mov KeyEventResult, eax;
    call HUD_Key_Event;
    mov eax, KeyEventResult;
    jmp dwRetAddress;
  }
}
//==============================================================================
DWORD KeyEvent=(DWORD)&Gateway2_HUD_Key_Event;
__declspec(naked) void Gateway1_HUD_Key_Event(void)
{
  __asm
  {
    push esi;
    mov esi,dword ptr ss:[esp+0x14];
    mov dwRetAddress,esi;
    push KeyEvent
    pop esi;
    mov dword ptr ss:[esp+0x14],esi;
    pop esi;
    ret;
  }
}
//==============================================================================	
__declspec(naked) void Gateway2_HUD_PostRunCmd(void)
{
  __asm
  {
    nop;
    nop; 
    nop;
    call HUD_PostRunCmd;
    nop;
    nop;
    nop;
    jmp dwRetAddress;
  }
}
//==============================================================================
__declspec(naked) void Gateway1_HUD_PostRunCmd(void)
{
  __asm
  {
    nop;
    nop;
    nop;
    push esi;
    mov esi,dword ptr ss:[esp+0x38];
    mov dwRetAddress,esi;
    push dwPostRunCmd
    pop esi;
    mov dword ptr ss:[esp+0x38],esi;
    pop esi;
    ret;
  }
}
//==============================================================================
__declspec(naked) void Gateway2_HUD_TempEntUpdate(void)
{
  __asm
  {
    nop;
    nop;
    nop;
    call HUD_TempEntUpdate;
    nop;
    nop;
    nop;
    jmp dwRetAddress;
  }
}
//==============================================================================
__declspec(naked) void Gateway1_HUD_TempEntUpdate(void)
{
  __asm
  {
    nop;
    nop;
    nop;
    push esi;
    mov esi,dword ptr ss:[esp+0x100];
    mov dwRetAddress,esi;
    push dwTempEntUpdate;
    pop esi;
    mov dword ptr ss:[esp+0x100],esi;
    pop esi;
    ret;
  }
}
//=====================================================================
VOID TakeGatewaysAddress()
{
	dwTempEntUpdate		= (DWORD)&Gateway2_HUD_TempEntUpdate;
	dwCreateMove		= (DWORD)&Gateway2_CL_CreateMove;
	dwRedraw			= (DWORD)&Gateway2_HUD_Redraw;
	dwPlayerMove		= (DWORD)&Gateway2_HUD_PlayerMove;
	dwAddEnt			= (DWORD)&Gateway2_HUD_AddEntity;
	dwPostRunCmd		= (DWORD)&Gateway2_HUD_PostRunCmd;
}
//=====================================================================
VOID ClientDllThread()
{
	TakeGatewaysAddress();

	dwOriginal_HUD_Redraw			= Slots[3];
	dwOriginal_CL_CreateMove		= Slots[14];
	dwOriginal_HUD_PlayerMove		= Slots[6];
	dwOriginal_HUD_PostRunCmd		= Slots[25];
	dwOriginal_HUD_TempEntUpdate	= Slots[35];
	dwOriginal_HUD_AddEntity		= Slots[20];
	dwOriginal_HUD_Key_Event		= Slots[34];

	for( ; ; Sleep(200) )
	{
		//Slots[3]	= (DWORD)&Gateway1_HUD_Redraw;
		//Slots[6]	= (DWORD)&Gateway1_HUD_PlayerMove;
		Slots[14]	= (DWORD)&Gateway1_CL_CreateMove;
		Slots[20]	= (DWORD)&Gateway1_HUD_AddEntity;
		//Slots[25]	= (DWORD)&Gateway1_HUD_PostRunCmd;
		//Slots[34]	= (DWORD)&Gateway1_HUD_Key_Event;
		//Slots[35]	= (DWORD)&Gateway1_HUD_TempEntUpdate;
	}

}
//=====================================================================
VOID UnHookFunction( int iFunction ) // Teh cd ownage with 20 lines of code, lel
{
	switch( iFunction )
	{
		case 1:
		{
			Slots[3] = dwOriginal_HUD_Redraw;
			break;
		}
		case 2:
		{
			Slots[6] = dwOriginal_HUD_PlayerMove;
			break;
		}
		case 3:
		{
			Slots[14] = dwOriginal_CL_CreateMove;
			break;
		}
		case 4:
		{
			Slots[20] = dwOriginal_HUD_AddEntity;
			break;
		}
		case 5:
		{
			Slots[25] = dwOriginal_HUD_AddEntity;
			break;
		}
		case 6:
		{
			Slots[34] = dwOriginal_HUD_Key_Event;
			break;
		}
		case 7:
		{
			Slots[35] = dwOriginal_HUD_TempEntUpdate;
			break;
		}
	}

}
//================================================================
