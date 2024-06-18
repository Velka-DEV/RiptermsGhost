#pragma once
#include "../../../../java/lang/Object/Object.h"

class EntityRenderer : public Object
{
public:
    using Object::Object;

    void getMouseOver(float partialTicks);
protected:
    inline static Ripterms::JavaClassV2 EntityRendererClass{ "net/minecraft/client/renderer/EntityRenderer" };
};