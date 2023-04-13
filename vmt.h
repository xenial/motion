#pragma once
#include <Windows.h>

class VMT {
	void*** p;

public:
	VMT(void* pClass);
	
	void* get(int index);
	void hook(int index, void* func);
};
