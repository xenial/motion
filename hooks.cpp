#include "hooks.h"
#include "interfaces.h"
#include "vmt.h"
#include "logger.h"
#include <string>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT(__stdcall* Hooks::oEndScene)(IDirect3DDevice9* device) = nullptr;
LRESULT(__stdcall* Hooks::oWndProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = nullptr;
bool(__stdcall* Hooks::oCreateMove)(float flInputSampleTime, CUserCmd* cmd) = nullptr;

HRESULT __stdcall Hooks::endScene(IDirect3DDevice9* device) {
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	
	return Hooks::oEndScene(device);
}

LRESULT __stdcall Hooks::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	
	return Hooks::oWndProc(hwnd, msg, wparam, lparam);
}

bool __stdcall Hooks::createMove(float flInputSampleTime, CUserCmd* cmd) {
	Logger::conMsg((std::string("[motion] Forward velocity: ") + std::to_string(cmd->forwardmove) + "\n").c_str());
	
	return Hooks::oCreateMove(flInputSampleTime, cmd);
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
	Hooks::oWndProc = (LRESULT(__stdcall*)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam))SetWindowLongPtr(cp.hFocusWindow, GWLP_WNDPROC, (LONG_PTR)Hooks::wndProc);
	vDevice.hook(42, &(Hooks::endScene));

	VMT vClientMode(Interfaces::pClientMode);
	Hooks::oCreateMove = (bool(__stdcall*)(float f, CUserCmd * cmd))vClientMode.get(24);
	vClientMode.hook(24, &(Hooks::createMove));
	return;
}