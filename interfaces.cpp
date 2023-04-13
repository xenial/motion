#include "interfaces.h"
#include "patternscanner.h"

IDirect3DDevice9* Interfaces::pDevice = nullptr;

void Interfaces::init() {
	Interfaces::pDevice = **(patternScan<IDirect3DDevice9***>("A1 ? ? ? ? 8D 57 08 6A ? 52 FF 75 FC 8B 08 FF 75 F8 FF 75 F4 56 50 FF 51 6C 85 C0", "shaderapidx9.dll", 1));
}