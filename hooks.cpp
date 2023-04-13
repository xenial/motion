#include "hooks.h"
#include "interfaces.h"
#include "vmt.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT (__stdcall *Hooks::oEndScene)(IDirect3DDevice9* device) = nullptr;
LRESULT(*Hooks::oWndProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = nullptr;

HRESULT __stdcall Hooks::endScene(IDirect3DDevice9* device) {
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	
	return Hooks::oEndScene(device);
}

LRESULT Hooks::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	
	return Hooks::oWndProc(hwnd, msg, wparam, lparam);
}

void Hooks::init() {
	VMT vDevice(Interfaces::pDevice);
	Hooks::oEndScene = (HRESULT(__stdcall *)(IDirect3DDevice9* device))vDevice.get(42);
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplDX9_Init(Interfaces::pDevice);
	
	D3DDEVICE_CREATION_PARAMETERS cp;
	Interfaces::pDevice->GetCreationParameters(&cp);

	ImGui_ImplWin32_Init(cp.hFocusWindow);
	Hooks::oWndProc = (LRESULT(*)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam))SetWindowLongPtr(cp.hFocusWindow, GWLP_WNDPROC, (LONG_PTR)Hooks::wndProc);
	vDevice.hook(42, &(Hooks::endScene));
	return;
}