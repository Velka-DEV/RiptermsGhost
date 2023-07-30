#pragma once
#include "../../../Ripterms/Ripterms.h"

class Object {
public:
	Object(jobject instance);
	Object(Object& other_Object);
	~Object();
private:
	inline static Ripterms::JavaClass javaClass{ "java/lang/Object" };
	jobject instance;
};