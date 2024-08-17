#include "GenericTag.hpp"
#include "../../../Globals.hpp"
#include "Types/CmswMenu.hpp"

void GenericTag::RenderTagDetails(TagStruct &tagStruct)
{
    ImGui::Text("Datum: 0x%08x", tagStruct.Datum);
    ImGui::Text("GlobalId: 0x%08x", tagStruct.ObjectId);
    ImGui::Text("TagGroup: %s", tagStruct.TagGroup.c_str());
    ImGui::Text("TagData: 0x%016llx", tagStruct.TagData);
    ImGui::Text("TagType Desc: %s", tagStruct.TagTypeDesc.c_str());
}

void GenericTag::RenderTagInfo(TagStruct &tagStruct)
{
    if (ImGui::Begin(std::format("Editing: {}", tagStruct.ObjectId).c_str(), nullptr, ImGuiWindowFlags_NoCollapse))
    {
        if (tagStruct.TagGroup == "CoatingSwatch")
        {
            RenderCMSW(tagStruct.TagData);
        }
        ImGui::End();
    }
}

void GenericTag::RenderTagReference(const char *label, tagReference *result)
{
    if (ImGui::CollapsingHeader(label))
    {
        ImGui::InputScalar("Type Info", ImGuiDataType_U64, &result->TypeInfo);
        ImGui::InputScalar("Global Tag ID", ImGuiDataType_U32, &result->globalId);
        ImGui::InputScalar("Asset ID", ImGuiDataType_U32, &result->assetId);

        std::array<char, 5> tagClassStr = {{0}};
        strncpy_s(tagClassStr.data(), tagClassStr.size(), result->tagClassString.data(), 4);

        ImGui::Text("Class: %s", tagClassStr.data());
    }
}


void GenericTag::LoadAllTags()
{
    if (ImGui::Button("Load All Tags"))
    {
        uintptr_t ModuleBase = GetModuleBase();
        TagLoader::ReadTags(ModuleBase);
    }
}

void GenericTag::RenderTagEntry(const std::string &objectIdStr, TagStruct &tagStruct)
{
    if (ImGui::TreeNode(objectIdStr.c_str()))
    {
        ImGui::BeginChild(objectIdStr.c_str(), ImVec2(0, 0), true);
        RenderTagDetails(tagStruct);
        if (ImGui::Button("Edit Tag"))
        {
            ImGui::OpenPopup(std::format("EditPopup_{}", tagStruct.ObjectId).c_str());
        }
        if (ImGui::BeginPopup(std::format("EditPopup_{}", tagStruct.ObjectId).c_str()))
        {
            RenderTagInfo(tagStruct);
            ImGui::EndPopup();
        }
        ImGui::EndChild();
        ImGui::TreePop();
    }
}

void GenericTag::RenderTagGroup(const std::string &tagGroup, std::map<uint32_t, TagStruct> &tagMap)
{
    if (ImGui::CollapsingHeader(tagGroup.c_str()))
    {
        for (auto &[datum, tagStruct] : tagMap)
        {
            std::string objectIdStr = "ObjectId: 0x" + std::to_string(tagStruct.ObjectId);
            RenderTagEntry(objectIdStr, tagStruct);
        }
    }
}

void GenericTag::ShowTagsWidget(std::map<std::string, std::map<uint32_t, TagStruct>> &tagsList)
{
    LoadAllTags();

    ImGui::BeginChild("TagsList", ImVec2(0, 0), true);
    for (auto &[tagGroup, tagMap] : tagsList)
    {
        RenderTagGroup(tagGroup, tagMap);
    }
    ImGui::EndChild();
}
