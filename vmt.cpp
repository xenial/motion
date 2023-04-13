#include "vmt.h"

VMT::VMT(void* pClass) {
	this->p = (void***)pClass;	
}

void* VMT::get(int index) {
	DWORD op;
	VirtualProtectEx(GetCurrentProcess(), ((this->p)), 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), (*(this->p)), 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), (*(this->p))[index], 4, PAGE_EXECUTE_READWRITE, &op);
	return (*(this->p))[index];
	//VirtualProtectEx(GetCurrentProcess(), *(VMT::p)[index], 4, op, NULL);
}

void VMT::hook(int index, void* func) {
	DWORD op;	
	VirtualProtectEx(GetCurrentProcess(), ((this->p)), 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), (*(this->p)), 4, PAGE_EXECUTE_READWRITE, &op);
	VirtualProtectEx(GetCurrentProcess(), (*(this->p))[index], 4, PAGE_EXECUTE_READWRITE, &op);
	(*(this->p))[index] = func;
	//VirtualProtectEx(GetCurrentProcess(), *(VMT::p)[index], 4, op, NULL);
	return;
}