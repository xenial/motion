#pragma once

#include "Recv.h"

class ClientClass
{
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int	m_ClassID;	// Managed by the engine.
};
