#pragma once
#include <string>
#include <Windows.h>
#include <Psapi.h>
#include <vector>

template <typename T>
T patternScan(std::string s, LPCSTR m, int offset) {
	std::vector<std::pair<BYTE, bool>> pattern;
	MODULEINFO modInfo;

	int i = 0;
	while (i < s.size()) {
		if (s[i] == ' ') {
			i++;
		}
		else if (s[i] == '?') {
			pattern.push_back(std::pair<BYTE, bool>(0, 1));
			i++;
		}
		else {
			std::string temp;
			temp.push_back(s[i]);
			temp.push_back(s[i + 1]);

			BYTE b = std::stoi(temp, nullptr, 16);
			pattern.push_back(std::pair<BYTE, bool>(b, 0));

			i += 2;
		}
	}

	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(m), &modInfo, sizeof(MODULEINFO));

	DWORD op;
	VirtualProtectEx(GetCurrentProcess(), modInfo.lpBaseOfDll, modInfo.SizeOfImage, PAGE_EXECUTE_READWRITE, &op);
	T address = nullptr;

	for (int i = 0; i < modInfo.SizeOfImage; i++) {

		if ((BYTE*)(modInfo.lpBaseOfDll) + i == (BYTE*)0x7AEC9037) {
			i++;
			i--;
		}

		bool found = 1;
		for (int j = 0; j < pattern.size(); j++) {
			if (!pattern[j].second && *((BYTE*)(modInfo.lpBaseOfDll) + i + j) != pattern[j].first) {
				found = 0;
				break;
			}
		}

		if (found) {
			address = (T)((BYTE*)(modInfo.lpBaseOfDll) + i + offset);
			break;
		}
	}

	//VirtualProtectEx(GetCurrentProcess(), modInfo.lpBaseOfDll, modInfo.SizeOfImage, op, NULL);
	return address;
}

