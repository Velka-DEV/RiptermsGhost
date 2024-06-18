#include "EntityPlayerSP.h"

#include <ImGuiNotify.hpp>

NetHandlerPlayClient EntityPlayerSP::getSendQueue()
{
	if (!instance)
		return NetHandlerPlayClient(nullptr, env);
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10)
		return NetHandlerPlayClient(env->GetObjectField(instance, EntityPlayerMPClass.getFieldID("sendQueue")), env);
	return NetHandlerPlayClient(env->GetObjectField(instance, EntityPlayerSPClass.getFieldID("sendQueue")), env);
}

void EntityPlayerSP::sendPlayerAbilities()
{
	if (!instance)
		return;
	env->CallVoidMethod(instance, EntityPlayerSPClass.getMethodID("sendPlayerAbilities"));
}

void EntityPlayerSP::setFlying(bool flying)
{
	if (!instance)
		return;

	PlayerCapabilities capabilities = getCapabilities();

	if (flying && !capabilities.isAllowFlying())
	{
		ImGui::InsertNotification({ImGuiToastType::Error, 3000, "You cannot fly in this world!"});
		return;
	}

	capabilities.setFlying(flying);
	sendPlayerAbilities();
}
