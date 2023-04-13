#pragma once
#include <Windows.h>
#include <d3d9.h>
#include "imgui/imgui_impl_dx9.h"

namespace Hooks {
	extern HRESULT(__stdcall *oEndScene)(IDirect3DDevice9* device);
	HRESULT __stdcall endScene(IDirect3DDevice9* device);

	void init();
}
