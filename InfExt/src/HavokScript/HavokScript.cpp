#include "HavokScript.hpp"
#include "../Memory.hpp"
#include "HksCompilerSettings.hpp"

int Hks::GetGlobalHook(uintptr_t state, char* string) {
	LuaState = state;
	return GetGlobalA(state, string);
}

uint64_t Hks::PCallHook(uintptr_t state, int function, uint32_t i, int u) {
	__int64 result = PCallA(state, function, i, u);
	return result;
}


uint64_t Hks::LoadBufferHook(uintptr_t state,
	const struct HksCompilerSettings* compilerSettings,
	const char* buffer, __int64 length,
	const char* unknown1) {
	__int64 result =
		LoadBufferA(state, compilerSettings, buffer, length, unknown1);
	return result;
}


uint64_t Hks::DoString(const char* string) {

	size_t stringLength = std::strlen(string);
	if (Hks::LoadBufferHook(
		LuaState,
		(const struct HksCompilerSettings*)(*((uintptr_t*)LuaState + 2) +
			1368),
		string, stringLength, string)) {
		return 1;
	}

	uint64_t call_result = PCallHook(LuaState, 0, 0xFFFFFFFF, 0);
	if (call_result) {
		return 1;
	}
	return call_result;
}


uint64_t Hks::DoFile(const char* filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return 1;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string fileContents = buffer.str();
	file.close();

	return DoString(fileContents.c_str());
}

void Hks::HookHavokScript(uintptr_t ModuleBase) {
	const uintptr_t GetGlobalOffset = 0x80CB4C;
	GetGlobalH = hook_function<GetGlobal>(ModuleBase, GetGlobalOffset,
		&GetGlobalHook, &GetGlobalA);
	const uintptr_t PCallOffset = 0x764304;
	PCallH = hook_function<PCall>(ModuleBase, PCallOffset, &PCallHook, &PCallA);
	const uintptr_t LoadBufferOffset = 0xA484C0;
	LoadBufferH = hook_function<LoadBuffer>(ModuleBase, LoadBufferOffset,
		&LoadBufferHook, &LoadBufferA);
}
