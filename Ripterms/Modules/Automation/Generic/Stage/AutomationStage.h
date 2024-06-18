#pragma once
#include <imgui.h>

#include "../../../../Maths/Maths.h"

namespace Ripterms::Modules::Automation
{
    class AutomationStage
    {
    public:
        struct RenderData
        {
            RenderData(const Ripterms::Maths::Vector3d& triggerBlockPosition, AutomationStage* stage, ImColor color = ImColor(1.0f, 0.0f, 0.0f, 1.0f));
            struct Quad
            {
                Ripterms::Maths::Vector3d p1, p2, p3, p4;
            } quads[6];
            ImColor color;
            AutomationStage* stage;
        };
        
        int id;
        Ripterms::Maths::Vector3d triggerBlockPosition;
        RenderData renderData;

        AutomationStage(int id, const Ripterms::Maths::Vector3d& triggerBlockPosition);
        
        void runStage();

        bool operator==(const AutomationStage& other) const {
            return id == other.id; 
        }
    private:
        
    };
}
