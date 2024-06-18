#include <ImGuiNotify.hpp>

#include "../../Modules.h"
#include <ImGui/imgui.h>

#include "../../../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"
#include "../../../Cache/Cache.h"

#include "Stage/AutomationStage.h"

void Ripterms::Modules::GenericAutomation::run()
{
    if (!enabled || !Ripterms::cache->is_valid)
    {
        return;
    }

    for (Automation::AutomationStage& stage : stages)
    {
        stage.runStage();
    }
}

void Ripterms::Modules::GenericAutomation::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
    if (!enabled || !this_player.isOnGround())
        return;

}

void Ripterms::Modules::GenericAutomation::renderGUI()
{
    ImGui::Checkbox("Generic automation (Beta)", &enabled);

    
    ImGui::SliderFloat("Yaw", &yaw, -180.0f, 180.0f, "%.1f");
    ImGui::SliderFloat("Pitch", &pitch, -90.0f, 90.0f, "%.1f");

    ImGui::TextColored(ImVec4(1,1,0,1), "Stages");
    if (ImGui::Button("Create stage"))
    {
        createStage();
    }
    ImGui::BeginChild("Stages");
    for (Automation::AutomationStage& stage : stages)
    {
        ImGui::Text("Stage %d", stage.id);
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            stages.erase(std::remove(stages.begin(), stages.end(), stage), stages.end());
        }
    }
    ImGui::EndChild();
}

void Ripterms::Modules::GenericAutomation::createStage()
{
    auto position = cache->thePlayer.getPosition();

    stages.push_back(Automation::AutomationStage(stages.size(), position));
}

void Ripterms::Modules::GenericAutomation::render()
{
    if (!enabled || !Ripterms::cache->is_valid)
    {
        return;
    }

    ImVec2 screenSize = ImGui::GetWindowSize();

    Ripterms::Maths::Matrix modelView = ActiveRenderInfo::get_cached_MODELVIEW();
    Ripterms::Maths::Matrix projection = ActiveRenderInfo::get_cached_PROJECTION();
    Ripterms::Maths::Vector3d cameraPos = ActiveRenderInfo::get_cached_cameraPos();

        for (Automation::AutomationStage& stage : stages)
        {
            for (Automation::AutomationStage::RenderData::Quad& quad : stage.renderData.quads)
            {
                std::clog << "Rendering quad" << std::endl;
                
                Ripterms::Maths::Vector2d p1{}, p2{}, p3{}, p4{};
                if
                (
                    !Ripterms::Maths::worldToScreen(quad.p1 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p1)
                    || !Ripterms::Maths::worldToScreen(quad.p2 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p2)
                    || !Ripterms::Maths::worldToScreen(quad.p3 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p3)
                    || !Ripterms::Maths::worldToScreen(quad.p4 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p4)
                )
                {
                    std::clog << "Failed to render quad" << std::endl;
                    continue;
                }
                
                ImGui::GetWindowDrawList()->AddQuad(ImVec2((float)p1.x, (float)p1.y), ImVec2((float)p2.x, (float)p2.y), ImVec2((float)p3.x, (float)p3.y), ImVec2((float)p4.x, (float)p4.y), stage.renderData.color, 2.0f);
            }
        }
}

void Ripterms::Modules::GenericAutomation::disable()
{

}