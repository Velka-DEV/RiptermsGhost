#pragma once
#include "MovingObjectPosition.h"
#include "../../../../java/lang/Object/Object.h"
#include "../../../../java/lang/String/String.h"
#include "MovingObjectType/MovingObjectType.h"

class MovingObjectPosition : public Object
{
public:
	using Object::Object;
	MovingObjectType getType();
	std::string toString();
protected:
	inline static Ripterms::JavaClassV2 MovingObjectPositionClass{ "net/minecraft/util/MovingObjectPosition" };
};