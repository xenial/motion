#include "hooks.h"
#include "interfaces.h"
#include "vmt.h"

HRESULT (__stdcall *Hooks::oEndScene)(IDirect3DDevice9* device) = nullptr;

HRESULT __stdcall Hooks::endScene(IDirect3DDevice9* device) {
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	
	return Hooks::oEndScene(device);
}

void Hooks::init() {
	VMT vDevice(Interfaces::pDevice);
	Hooks::oEndScene = (HRESULT(__stdcall *)(IDirect3DDevice9* device))vDevice.get(42);
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui::GetIO().DisplaySize = ImVec2(1920.0f, 1080.0f);
	ImGui_ImplDX9_Init(Interfaces::pDevice);
	vDevice.hook(42, &(Hooks::endScene));
	return;
}