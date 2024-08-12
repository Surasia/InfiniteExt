#ifndef HKSCOMPILERSETTINGS_HPP
#define HKSCOMPILERSETTINGS_HPP
#include <cstdint>

struct HksCompilerSettings {
public:
	/* Operators */
	HksCompilerSettings() = default;
	~HksCompilerSettings() = default;

private:
	uint32_t ignore_debug;
	uint32_t emitStruct;
	uint32_t enableIntLiteral;
	uint32_t emitMemo;
	uint32_t skipMemo;
	uint32_t strip;
	const char* stripNames;
};

#endif
