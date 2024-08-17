#include "Toggles.hpp"
#include "../../Patches/Patches.hpp"

void RenderToggles()
{
    ImGui::BeginChild("Toggles", ImVec2(520, 180), true);
    ImGui::Text("Debug");

    if (ImGui::Checkbox("Enable Forge Hidden Category", &forgeHiddenCategory))
    {
        Patches::ToggleForgeHiddenCategories();
    }

    if (ImGui::Checkbox("Enable Watermark", &watermarkEnabled))
    {
        Patches::ToggleWatermark();
    }

    if (ImGui::Checkbox("Disable HUD", &hudEnabled))
    {
        Patches::ToggleHUD();
    }

    if (ImGui::Checkbox("Disable Kill Volumes", &killVolumesEnabled))
    {
        Patches::ToggleKillVolumes();
    }

    ImGui::EndChild();
}
