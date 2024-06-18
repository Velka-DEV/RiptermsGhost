#include "EntityRenderer.h"

void EntityRenderer::getMouseOver(float partialTicks)
{
    if (!instance) return;

    env->CallVoidMethod(instance, EntityRendererClass.getMethodID("getMouseOver"), (jfloat) partialTicks);
}