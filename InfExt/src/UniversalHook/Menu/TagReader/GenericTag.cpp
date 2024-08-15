#include "GenericTag.hpp"
#include "../../../Globals.hpp"
#include "Types/CmswMenu.hpp"


void GenericTag::RenderTagDetails(const TagStruct& tagStruct)
{
	ImGui::Text("Datum: 0x%08x", tagStruct.Datum);
	ImGui::Text("GlobalId: 0x%08x", tagStruct.ObjectId);
	ImGui::Text("TagGroup: %s", tagStruct.TagGroup.c_str());
	ImGui::Text("TagData: 0x%016llx", tagStruct.TagData);
	ImGui::Text("TagType Desc: %s", tagStruct.TagTypeDesc.c_str());
}

void GenericTag::RenderTagInfo(const TagStruct& tagStruct)
{
	if (ImGui::Button("Edit Tag")) {
		isPopupOpen = true;
	}

	if (isPopupOpen)
	{
		if (ImGui::Begin("Tag Editor", &isPopupOpen))
		{
			if (tagStruct.TagGroup == "CoatingSwatch") {
				RenderCMSW(tagStruct.TagData);
			}
		}
		ImGui::End();
	}
}




void GenericTag::RenderTagReference(const char* label, tagReference* result)
{
	if (ImGui::CollapsingHeader(label)) {
		ImGui::InputScalar("Type Info", ImGuiDataType_U64, &result->TypeInfo);
		ImGui::InputScalar("Global Tag ID", ImGuiDataType_U32, &result->globalId);
		ImGui::InputScalar("Asset ID", ImGuiDataType_U32, &result->assetId);
		char tagClassStr[5] = { 0 };
		strncpy_s(tagClassStr, result->tagClassc, 4);
		std::reverse(tagClassStr, tagClassStr + strlen(tagClassStr));
		ImGui::Text("Class: %s", tagClassStr);
	}
}


void GenericTag::ShowTagsWidget(const std::map<std::string, std::map<uint32_t, TagStruct>>& tagsList)
{
	if (ImGui::Button("Load All Tags")) {
		uintptr_t ModuleBase = GetModuleBase();
		TagLoader::ReadTags(ModuleBase);
	}

	ImGui::BeginChild("TagsList", ImVec2(0, 0), true);
	for (const auto& [tagGroup, tagMap] : tagsList) {
		if (ImGui::CollapsingHeader(tagGroup.c_str())) {
			for (const auto& [datum, tagStruct] : tagMap) {
				std::string objectIdStr = "ObjectId: 0x" + std::to_string(tagStruct.ObjectId);
				if (ImGui::TreeNode(objectIdStr.c_str())) {
					ImGui::BeginChild(objectIdStr.c_str(), ImVec2(0, 0), true);
					RenderTagDetails(tagStruct);
					RenderTagInfo(tagStruct);
					ImGui::EndChild();
					ImGui::TreePop();
				}
			}
		}
	}
	ImGui::EndChild();
}