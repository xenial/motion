#pragma once
#include <d3d9.h>
#include "sdk/IClientEntityList.h"

namespace Interfaces {
	extern IDirect3DDevice9* pDevice;
	extern IClientEntityList* pEntList;

	void init();
}
