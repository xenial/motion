#include "hooks.h"
#include "interfaces.h"
#include "vmt.h"
#include "imgui/imgui_impl_dx9.h"

HRESULT (*Hooks::oEndScene)(IDirect3DDevice9* device) = nullptr;

HRESULT Hooks::endScene(IDirect3DDevice9* device) {
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	
	return oEndScene(device);
}

void Hooks::init() {
	VMT vDevice(Interfaces::pDevice);
	Hooks::oEndScene = (HRESULT(*)(IDirect3DDevice9* device))vDevice.get(42);
	vDevice.hook(42, &(Hooks::endScene));
	ImGui_ImplDX9_Init(Interfaces::pDevice);
}