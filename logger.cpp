#include "logger.h"
#include <Windows.h>

void(*Logger::conMsg)(const char* msg, ...) = nullptr;

void Logger::init() {
	Logger::conMsg = (void(*)(const char* msg, ...))GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg");
}