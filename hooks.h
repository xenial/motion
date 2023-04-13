#pragma once
#include <Windows.h>
#include <d3d9.h>
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

namespace Hooks {
	extern HRESULT(__stdcall *oEndScene)(IDirect3DDevice9* device);
	extern LRESULT(*oWndProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	HRESULT __stdcall endScene(IDirect3DDevice9* device);
	LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void init();
}
