#include "CBasePlayer.h"
#include "../interfaces.h"

/*
Vector CBasePlayer::getBonePos(int id) {
	matrix3x4_t boneMatrix[128];
	this->SetupBones(boneMatrix, 128, 128, Interfaces::engineClient->GetLastTimeStamp());
	Vector pos(boneMatrix[id][0][3], boneMatrix[id][1][3], boneMatrix[id][2][3]);
	return pos;
}
*/