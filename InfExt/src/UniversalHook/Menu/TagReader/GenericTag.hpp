#ifndef GENERICTAG_HPP
#define GENERICTAG_HPP

#include "../../../TagLoader/TagLoader.hpp"
#include "../../../TagLoader/Types/InfiniteStructs.hpp"
#include <cstdint>
#include <imgui.h>
#include <string>
#include <vector>

class GenericTag
{
public:
    /* Public Functions */
    static void RenderTagReference(const char *label, tagReference *result);
    static void ShowTagsWidget(std::map<std::string, std::map<uint32_t, TagStruct>> &tagsList);

private:
    /* Private Functions */
    static void LoadAllTags();
    static void RenderTagDetails(TagStruct &tagStruct);
    static void RenderTagInfo(TagStruct &tagStruct);
    static void RenderTagEntry(const std::string &objectIdStr, TagStruct &tagStruct);
    static void RenderTagGroup(const std::string &tagGroup, std::map<uint32_t, TagStruct> &tagMap);
};

#endif
