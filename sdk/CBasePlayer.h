#pragma once

#include "IClientEntity.h"

#define NETVAR(type, name, offset)	\
type name##() {						\
	return *(type*)(this + offset);	\
}

class CBasePlayer : public IClientEntity {
public:
	NETVAR(int, team, 0xF4);
	NETVAR(int, health, 0x100);
	NETVAR(Vector, viewOffset, 0x108);
	NETVAR(Vector, origin, 0x138);
	NETVAR(int, lifeState, 0x25F);
	
	Vector getBonePos(int id);
};
