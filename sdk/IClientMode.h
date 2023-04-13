#pragma once


class CViewSetup;
class C_BaseEntity;
class C_BasePlayer;
class CUserCmd;
class KeyValues;

struct HeadtrackMovementMode_t;
struct ButtonCode_t;

namespace vgui
{
	class Panel;
	class AnimationController;
}

// Message mode types
enum
{
	MM_NONE = 0,
	MM_SAY,
	MM_SAY_TEAM,
};

class IClientMode
{

};	
