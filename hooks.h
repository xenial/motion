#pragma once
#include <Windows.h>
#include <d3d9.h>
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "sdk/CUserCmd.h"
#include "sdk/IClientMode.h"

namespace Hooks {
	extern HRESULT(__stdcall* oEndScene)(IDirect3DDevice9* device);
	extern LRESULT(__stdcall* oWndProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	extern bool(__stdcall* oCreateMove)(float flInputSampleTime, CUserCmd* cmd);

	HRESULT __stdcall endScene(IDirect3DDevice9* device);
	LRESULT __stdcall wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	bool __stdcall createMove(float flInputSampleTime, CUserCmd* cmd);

	void init();
}
