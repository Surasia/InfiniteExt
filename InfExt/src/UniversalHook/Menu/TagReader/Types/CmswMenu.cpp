#include "CmswMenu.hpp"


void RenderCMSW(uintptr_t tagLocation)
{
    CoatingSwatchPODTag *CMSW = reinterpret_cast<CoatingSwatchPODTag *>(tagLocation);

    if (ImGui::CollapsingHeader("AnyTag"))
    {
        ImGui::InputScalar("VTable Space", ImGuiDataType_U64, &CMSW->anyTagEnt.vtableSpace);

        if (ImGui::TreeNode("Internal Struct"))
        {
            ImGui::InputScalar("Global Tag ID", ImGuiDataType_U32, &CMSW->anyTagEnt.internalStructEnt.globalTagID);
            ImGui::InputScalar("Local Tag Handle", ImGuiDataType_U32, &CMSW->anyTagEnt.internalStructEnt.localTagHandle);
            ImGui::TreePop();
        }
    }

    GenericTag::RenderTagReference("Parent", &CMSW->parent);

    if (ImGui::CollapsingHeader("Base Properties"))
    {
        ImGui::InputFloat2("Color & Roughness Texture Transform", &CMSW->colorAndRoughnessTextureTransform.x);
        ImGui::InputFloat2("Normal Texture Transform", &CMSW->normalTextureTransform.x);
        GenericTag::RenderTagReference("Color Gradient Map", &CMSW->colorGradientMap);
        ImGui::ColorEdit3("Gradient Top Color", &CMSW->gradientTopColor.r);
        ImGui::ColorEdit3("Gradient Mid Color", &CMSW->gradientMidColor.r);
        ImGui::ColorEdit3("Gradient Bottom Color", &CMSW->gradientBottomColor.r);
        ImGui::InputFloat("Roughness White", &CMSW->roughnessWhite);
        ImGui::InputFloat("Roughness Black", &CMSW->roughnessBlack);
        GenericTag::RenderTagReference("Normal Detail Map", &CMSW->normalDetailMap);
        ImGui::InputFloat("Metallic", &CMSW->metallic);
        ImGui::InputFloat("IOR", &CMSW->ior);
        ImGui::InputFloat("Albedo Tint Spec", &CMSW->albedoTintSpec);
    }

    if (ImGui::CollapsingHeader("Scratch Properties"))
    {
        ImGui::ColorEdit3("Scratch Color", &CMSW->scratchColor.r);
        ImGui::InputFloat("Scratch Brightness", &CMSW->scratchBrightness);
        ImGui::InputFloat("Scratch Roughness", &CMSW->scratchRoughness);
        ImGui::InputFloat("Scratch Metallic", &CMSW->scratchMetallic);
        ImGui::InputFloat("Scratch IOR", &CMSW->scratchIOR);
        ImGui::InputFloat("Scratch Albedo Tint Spec", &CMSW->scratchAlbedoTintSpec);
    }

    if (ImGui::CollapsingHeader("Subsurface Properties"))
    {
        ImGui::InputFloat("SSS Intensity", &CMSW->sssIntensity);
    }

    if (ImGui::CollapsingHeader("Emissive Properties"))
    {
        ImGui::InputFloat("Emissive Intensity", &CMSW->emissiveIntensity);
        ImGui::InputFloat("Emissive Amount", &CMSW->emissiveAmount);
    }
}
