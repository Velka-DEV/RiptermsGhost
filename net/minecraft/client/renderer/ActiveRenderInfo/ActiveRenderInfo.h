#pragma once
#include "../../../../../java/lang/Object/Object.h"
#include "../../../../../java/nio/FloatBuffer/FloatBuffer.h"

class ActiveRenderInfo : public Object
{
public:
	using Object::Object;
	static FloatBuffer getMODELVIEW(JNIEnv* env = Ripterms::p_env);
	static FloatBuffer getPROJECTION(JNIEnv* env = Ripterms::p_env);
	static void update_cache(JNIEnv* env = Ripterms::p_env);
	static Ripterms::Maths::Matrix get_cached_MODELVIEW();
	static Ripterms::Maths::Matrix get_cached_PROJECTION();
protected:
	inline static Ripterms::JavaClassV2 ActiveRenderInfoClass{ "net/minecraft/client/renderer/ActiveRenderInfo" };
private:
	inline static Ripterms::Maths::Matrix MODELVIEW = { {0} };
	inline static Ripterms::Maths::Matrix PROJECTION = { {0} };
};