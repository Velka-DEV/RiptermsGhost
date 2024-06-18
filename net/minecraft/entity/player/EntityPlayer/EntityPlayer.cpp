#include "EntityPlayer.h"

PlayerCapabilities EntityPlayer::getCapabilities()
{
    return PlayerCapabilities(env->GetObjectField(instance, EntityPlayerClass.getFieldID("capabilities")));
}