#include "AutomationStage.h"

#include "../../../Modules.h"


Ripterms::Modules::Automation::AutomationStage::AutomationStage(int id, const Ripterms::Maths::Vector3d& triggerBlockPosition) :
	id(id),
	triggerBlockPosition(triggerBlockPosition),
	renderData(triggerBlockPosition, this)
{

}

Ripterms::Modules::Automation::AutomationStage::RenderData::RenderData(const Ripterms::Maths::Vector3d& blockPos, AutomationStage* stage, ImColor color) :
	quads
	{ 
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x, blockPos.y, blockPos.z + 1}},
		RenderData::Quad{{blockPos.x, blockPos.y + 1, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}},
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}, {blockPos.x, blockPos.y + 1, blockPos.z}},
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}},
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x, blockPos.y, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z}},
		RenderData::Quad{{blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}}
	},
	color(color),
	stage(stage)
{

}

void Ripterms::Modules::Automation::AutomationStage::runStage()
{
}