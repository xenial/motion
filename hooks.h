#pragma once
#include <Windows.h>
#include <d3d9.h>

namespace Hooks {
	extern HRESULT(*oEndScene)(IDirect3DDevice9* device);
	HRESULT endScene(IDirect3DDevice9* device);

	void init();
}
