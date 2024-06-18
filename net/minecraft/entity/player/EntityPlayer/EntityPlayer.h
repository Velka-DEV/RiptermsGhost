#pragma once
#include "../../EntityLivingBase/EntityLivingBase.h"
#include "../PlayerCapabilities/PlayerCapabilities.h"

class EntityPlayer : public EntityLivingBase {
public:
	using EntityLivingBase::EntityLivingBase;

	PlayerCapabilities getCapabilities();
protected:
	inline static Ripterms::JavaClassV2 EntityPlayerClass{ "net/minecraft/entity/player/EntityPlayer" };
};
