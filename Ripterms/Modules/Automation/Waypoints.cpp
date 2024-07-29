#include "../Modules.h"
#include "../../Cache/Cache.h"
#include <ImGui/imgui.h>
#include <vector>
#include <gl/GL.h>

#include "../../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"

#if ENABLE_MISC_MODULES

void Ripterms::Modules::Waypoints::run() {
    if (!enabled) return;

    // Get the player's position
    Maths::Vector3d playerPos = cache->thePlayer.getPosition();
    
    for (const auto& waypoint : waypoints) {
        const Maths::Vector3d waypointPos = waypoint.pos;
        if ((playerPos - waypointPos).distance() < 1.0) {
            executeActions(waypoint.actions);
        }
    }
}

void Ripterms::Modules::Waypoints::executeActions(const std::string& actions) {
    // Example actions
    if (actions.find("Press Button 1") != std::string::npos) {
        // Implement the logic for pressing button 1
    }
    if (actions.find("Move forward") != std::string::npos) {
        // Implement the logic for moving forward
    }
    // Add other actions here...
}

void Ripterms::Modules::Waypoints::renderGUI() {
    Maths::Vector3d playerPos = cache->thePlayer.getPosition();

    std::cout << "Player pos: " << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << '\n';
    
    static double x = playerPos.x, y = playerPos.y, z = playerPos.z;
    static char actions[128] = "";

    ImGui::InputDouble("X", &x);
    ImGui::InputDouble("Y", &y);
    ImGui::InputDouble("Z", &z);
    ImGui::InputText("Actions", actions, IM_ARRAYSIZE(actions));

    if (ImGui::Button("Clear Waypoints")) {
        waypoints.clear();
    }
    
    if (ImGui::Button("Add Waypoint")) {
        waypoints.push_back(Waypoint{ Maths::Vector3d(x, y, z), actions });
    }

    ImGui::Separator();
    for (size_t i = 0; i < waypoints.size(); ++i) {
        ImGui::Text("Waypoint %zu: (%f, %f, %f) - Actions: %s", i + 1, waypoints[i].pos.x, waypoints[i].pos.y, waypoints[i].pos.z, waypoints[i].actions.c_str());
    }
}

void Ripterms::Modules::Waypoints::render() {
    if (!enabled) return;

    renderWaypoints();
}

void Ripterms::Modules::Waypoints::renderWaypoints() {
    if (waypoints.empty()) return;

    // Get necessary data for rendering
    ImVec2 screenSize = ImGui::GetWindowSize();
    Ripterms::Maths::Matrix modelView = ActiveRenderInfo::get_cached_MODELVIEW();
    Ripterms::Maths::Matrix projection = ActiveRenderInfo::get_cached_PROJECTION();
    Ripterms::Maths::Vector3d cameraPos = ActiveRenderInfo::get_cached_cameraPos();

    std::cout << "Camera pos: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
    std::cout << "ModelView: " << modelView.to_string() << std::endl;
    std::cout << "Projection: " << projection.to_string() << std::endl;

    for (const auto& waypoint : waypoints) {
        // Define the corners of the waypoint block
        Ripterms::Maths::Vector3d corners[8] = {
            {waypoint.pos.x, waypoint.pos.y, waypoint.pos.z},
            {waypoint.pos.x + 1, waypoint.pos.y, waypoint.pos.z},
            {waypoint.pos.x + 1, waypoint.pos.y + 1, waypoint.pos.z},
            {waypoint.pos.x, waypoint.pos.y + 1, waypoint.pos.z},
            {waypoint.pos.x, waypoint.pos.y, waypoint.pos.z + 1},
            {waypoint.pos.x + 1, waypoint.pos.y, waypoint.pos.z + 1},
            {waypoint.pos.x + 1, waypoint.pos.y + 1, waypoint.pos.z + 1},
            {waypoint.pos.x, waypoint.pos.y + 1, waypoint.pos.z + 1},
        };

        // Convert world coordinates to screen coordinates
        ImVec2 screenCoords[8];
        bool allVisible = true;
        for (int i = 0; i < 8; ++i) {
            Ripterms::Maths::Vector2d screenPos;
            if (!Ripterms::Maths::worldToScreen(corners[i] - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, screenPos)) {
                allVisible = false;
                break;
            }
            screenCoords[i] = ImVec2((float)screenPos.x, (float)screenPos.y);
        }

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddCircle(ImVec2(screenSize.x / 2, screenSize.y / 2), 5.0f, IM_COL32(255, 0, 0, 255), 12, 2.0f);

        // If all corners are visible, render the quads
        if (allVisible) {
            ImU32 color = IM_COL32(255, 0, 0, 255); // Red color for the edges

            // Draw the quads of the waypoint block
            drawList->AddQuad(screenCoords[0], screenCoords[1], screenCoords[2], screenCoords[3], color, 2.0f);
            drawList->AddQuad(screenCoords[4], screenCoords[5], screenCoords[6], screenCoords[7], color, 2.0f);
            drawList->AddQuad(screenCoords[0], screenCoords[1], screenCoords[5], screenCoords[4], color, 2.0f);
            drawList->AddQuad(screenCoords[2], screenCoords[3], screenCoords[7], screenCoords[6], color, 2.0f);
            drawList->AddQuad(screenCoords[0], screenCoords[3], screenCoords[7], screenCoords[4], color, 2.0f);
            drawList->AddQuad(screenCoords[1], screenCoords[2], screenCoords[6], screenCoords[5], color, 2.0f);
        }
    }
}


void Ripterms::Modules::Waypoints::destroy() {
    waypoints.clear();
}

#endif
