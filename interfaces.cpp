#include "interfaces.h"
#include "patternscanner.h"
#include <Windows.h>

IDirect3DDevice9* Interfaces::pDevice = nullptr;
IClientEntityList* Interfaces::pEntList = nullptr;
IBaseClientDLL* Interfaces::pBaseClientDLL = nullptr;
IClientMode* Interfaces::pClientMode = nullptr;

void Interfaces::init() {
	auto clientCI = (void* (*)(const char* pName, int* pReturnCode))GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
	auto engineCI = (void*(*)(const char* pName, int* pReturnCode))GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");

	Interfaces::pEntList = (IClientEntityList*)clientCI(VCLIENTENTITYLIST_INTERFACE_VERSION, NULL);
	Interfaces::pBaseClientDLL = (IBaseClientDLL*)clientCI(CLIENT_DLL_INTERFACE_VERSION, NULL);
	Interfaces::pClientMode = **(IClientMode***)((*(DWORD**)pBaseClientDLL)[10] + 5);

	Interfaces::pDevice = **(patternScan<IDirect3DDevice9***>("A1 ? ? ? ? 8D 57 08 6A ? 52 FF 75 FC 8B 08 FF 75 F8 FF 75 F4 56 50 FF 51 6C 85 C0", "shaderapidx9.dll", 1));
}