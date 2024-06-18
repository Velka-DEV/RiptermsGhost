#include "PlayerCapabilities.h"

bool PlayerCapabilities::isFlying()
{
    return env->GetBooleanField(instance, PlayerCapabilitiesClass.getFieldID("isFlying")) == JNI_TRUE;
}

void PlayerCapabilities::setFlying(bool flying)
{
    env->SetBooleanField(instance, PlayerCapabilitiesClass.getFieldID("isFlying"), flying ? JNI_TRUE : JNI_FALSE);
}

bool PlayerCapabilities::isAllowFlying()
{
    return env->GetBooleanField(instance, PlayerCapabilitiesClass.getFieldID("allowFlying")) == JNI_TRUE;
}