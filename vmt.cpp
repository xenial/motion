#include "vmt.h"

VMT::VMT(void* pClass) {
	VMT::p = (void***)pClass;	
}

void* VMT::get(int index) {
	DWORD op;
	VirtualProtectEx(GetCurrentProcess(), VMT::p, 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), *(VMT::p), 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), *(VMT::p)[index], 4, PAGE_EXECUTE_READWRITE, &op);
	return *(VMT::p)[index];
	//VirtualProtectEx(GetCurrentProcess(), *(VMT::p)[index], 4, op, NULL);
}

void VMT::hook(int index, void* func) {
	DWORD op;
	VirtualProtectEx(GetCurrentProcess(), VMT::p, 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), *(VMT::p), 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), *(VMT::p)[index], 4, PAGE_EXECUTE_READWRITE, &op);
	*(VMT::p)[index] = func;
	//VirtualProtectEx(GetCurrentProcess(), *(VMT::p)[index], 4, op, NULL);
}