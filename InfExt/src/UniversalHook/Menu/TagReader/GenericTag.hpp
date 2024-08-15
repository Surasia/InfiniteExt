#ifndef GENERICTAG_HPP
#define GENERICTAG_HPP

#include <imgui.h>
#include <string>
#include <vector>
#include <cstdint>
#include "../../../TagLoader/Types/InfiniteStructs.hpp"
#include "../../../TagLoader/TagLoader.hpp"

class GenericTag {
public:
	/* Public Functions */
	static void RenderTagReference(const char* label, tagReference* result);
	static void ShowTagsWidget(const std::map<std::string, std::map<uint32_t, TagStruct>>& tagsList);
private:
	/* Private Functions */
	static void RenderTagDetails(const TagStruct& tagStruct);
	static void RenderTagInfo(const TagStruct& tagStruct);
	/* Private Variables*/
	inline static bool isPopupOpen = false;
};

#endif
