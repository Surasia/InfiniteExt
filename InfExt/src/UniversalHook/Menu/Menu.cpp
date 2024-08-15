#include "Menu.hpp"
#include "Console.hpp"
#include "Toggles.hpp"
#include "TagReader/GenericTag.hpp"

void Menu::InitializeContext(HWND hwnd)
{
	if (ImGui::GetCurrentContext())
		return;

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(hwnd);

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = io.LogFilename = nullptr;
}

void Menu::Render()
{
	if (!shouldShowMenu)
		return;

	ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Menu", &shouldShowMenu)) {
		if (ImGui::CollapsingHeader("InfiniteExt", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::BeginChild("InfiniteExtChild", ImVec2(0, 400), true);
			RenderConsole();
			ImGui::Spacing();
			RenderToggles();
			ImGui::EndChild();
		}

		ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
		if (ImGui::CollapsingHeader("Tags", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::BeginChild("TagsChild", ImVec2(0, 0), true);
			auto tagsList = TagLoader::GetTagsList();
			GenericTag::ShowTagsWidget(tagsList);
			ImGui::EndChild();
		}

		ImGui::End();
	}
}
