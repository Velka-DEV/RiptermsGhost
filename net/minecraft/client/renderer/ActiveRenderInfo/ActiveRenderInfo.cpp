#include "ActiveRenderInfo.h"
#include "../../../util/Vec3/Vec3.h"
#include "../../../../../Ripterms/Cache/Cache.h"

FloatBuffer ActiveRenderInfo::getMODELVIEW(JNIEnv* env)
{
    jobject modelViewObj = env->GetStaticObjectField(ActiveRenderInfoClass.get_jclass(env), ActiveRenderInfoClass.getFieldID("MODELVIEW"));
    if (modelViewObj == nullptr) {
        std::cerr << "Failed to retrieve MODELVIEW object." << std::endl;
        return FloatBuffer(nullptr, env);
    }
    return FloatBuffer(modelViewObj, env);
}

FloatBuffer ActiveRenderInfo::getPROJECTION(JNIEnv* env)
{
    jobject projectionObj = env->GetStaticObjectField(ActiveRenderInfoClass.get_jclass(env), ActiveRenderInfoClass.getFieldID("PROJECTION"));
    if (projectionObj == nullptr) {
        std::cerr << "Failed to retrieve PROJECTION object." << std::endl;
        return FloatBuffer(nullptr, env);
    }
    return FloatBuffer(projectionObj, env);
}

void ActiveRenderInfo::update_cache(JNIEnv* env)
{
    FloatBuffer modelViewBuffer = ActiveRenderInfo::getMODELVIEW(env);
    FloatBuffer projectionBuffer = ActiveRenderInfo::getPROJECTION(env);

    if (modelViewBuffer.isValid() && projectionBuffer.isValid()) {
        MODELVIEW = modelViewBuffer.toMatrix(4, 4);
        PROJECTION = projectionBuffer.toMatrix(4, 4);
        cameraPos = Ripterms::cache->theMinecraft.getRenderViewEntity().getRenderPos(Ripterms::cache->timer.getRenderPartialTicks());
    } else {
        std::cerr << "Error retrieving MODELVIEW or PROJECTION matrix." << std::endl;
    }
}

Ripterms::Maths::Matrix ActiveRenderInfo::get_cached_MODELVIEW()
{
    return MODELVIEW;
}

Ripterms::Maths::Matrix ActiveRenderInfo::get_cached_PROJECTION()
{
    return PROJECTION;
}

Ripterms::Maths::Vector3d ActiveRenderInfo::get_cached_cameraPos()
{
    return cameraPos;
}
