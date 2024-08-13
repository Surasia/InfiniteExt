#include "Menu.hpp"
#include "../../HavokScript/HavokScript.hpp"
#include "../../Forge/Forge.hpp"
#include "../../Logger/Logger.hpp"


namespace Menu {
	void InitializeContext(HWND hwnd) {
		if (ImGui::GetCurrentContext())
			return;

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hwnd);

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = io.LogFilename = nullptr;
	}

    void Render() {
        Logger& logger = Logger::GetInstance(false);
        if (!shouldShowMenu)
            return;

        static char inputBuf[1024 * 16] = "";

        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("InfiniteExt", nullptr, ImGuiWindowFlags_NoCollapse)) {

            ImGui::BeginChild("Console", ImVec2(520, 175), true);
            ImGui::Text("HavokScript Console");
            ImGui::InputTextMultiline("##Input", inputBuf, IM_ARRAYSIZE(inputBuf), ImVec2(-1, ImGui::GetTextLineHeight() * 4));

            if (ImGui::Button("Execute")) {
                uint64_t result = Hks::DoString(inputBuf);
                logger.Log(Logger::INFO, "Executed String: {}", inputBuf);
                memset(inputBuf, 0, sizeof(inputBuf));
            }
            ImGui::EndChild();

            ImGui::Spacing();

            ImGui::BeginChild("Button", ImVec2(520, 50), true);
            if (ImGui::Button("Toggle Forge Hidden Category")) {
                Forge::ToggleForgeHiddenCategories();
            }
            ImGui::EndChild();

            ImGui::End();
        }
    }
}
