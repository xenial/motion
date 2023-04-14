#pragma once

namespace Logger {
	extern void(*conMsg)(const char* msg, ...);

	void init();
}
