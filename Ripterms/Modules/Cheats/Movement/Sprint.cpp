#include "../../Modules.h"

#if ENABLE_MOVEMENT_MODULES
#include <ImGui/imgui.h>
#include "../../../Cache/Cache.h"

void Ripterms::Modules::Sprint::run()
{
	if (!enabled)
		return;
	cache->gameSettings.getKeyBindSprint().setPressed(true);
}
#endif