#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../java/util/List/List.h"
#include "../../block/state/IBlockState.h"
#include "../../util/BlockPos/BlockPos.h"

class World : public Object
{
public:
	using Object::Object;
	IBlockState getBlockState(const BlockPos& blockPos);
	virtual List getPlayerEntities();
protected:
	inline static Ripterms::JavaClassV2 WorldClass{ "net/minecraft/world/World" };
	inline static Ripterms::JavaClassV2 IBlockAccessClass{ "net/minecraft/world/IBlockAccess" };
};