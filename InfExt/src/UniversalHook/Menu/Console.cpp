#include "Console.hpp"
#include "../../Logger/Logger.hpp"
#include "../../HavokScript/HavokScript.hpp"

void RenderConsole()
{
	Logger& logger = Logger::GetInstance(false);
	static char inputBuf[1024 * 16] = "";

	ImGui::BeginChild("Console", ImVec2(520, 175), true);
	ImGui::Text("HavokScript Console");
	ImGui::InputTextMultiline("##Input", inputBuf, IM_ARRAYSIZE(inputBuf), ImVec2(-1, ImGui::GetTextLineHeight() * 4));

	if (ImGui::Button("Execute")) {
		uint64_t result = Hks::DoString(inputBuf);
		logger.Log(Logger::INFO, "Executed String: {}", inputBuf);
		memset(inputBuf, 0, sizeof(inputBuf));
	}
	ImGui::EndChild();
}