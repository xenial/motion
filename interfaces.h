#pragma once
#include <d3d9.h>
#include "sdk/IClientEntityList.h"
#include "sdk/IClientMode.h"
#include "sdk/IBaseClientDLL.h"

namespace Interfaces {
	extern IDirect3DDevice9* pDevice;
	extern IClientEntityList* pEntList;
	extern IBaseClientDLL* pBaseClientDLL;
	extern IClientMode* pClientMode;

	void init();
}
