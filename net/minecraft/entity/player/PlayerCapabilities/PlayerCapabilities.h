#pragma once
#include "../../../../../java/lang/Object/Object.h"

class PlayerCapabilities : Object
{
public:
    using Object::Object;
    bool isFlying();
    void setFlying(bool flying);
    bool isAllowFlying();
protected:
    inline static Ripterms::JavaClassV2 PlayerCapabilitiesClass{ "net/minecraft/entity/player/PlayerCapabilities" };
};