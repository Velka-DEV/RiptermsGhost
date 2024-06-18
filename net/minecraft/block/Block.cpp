#include "Block.h"



String Block::toString()
{
	if (!instance) return String(env);
	return String(env->CallObjectMethod(instance, ObjectClass.getMethodID("toString")), env);
}

std::string Block::getName()
{
	if (!instance)
		return "";
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10)
	{
		std::string name = String(env->GetObjectField(instance, BlockClass.getFieldID("unlocalizedName")), env).toStdString();
		for (char& c : name)
			c = std::tolower(c);
		return name;
	}
	return toString().toStdString();
}

bool Block::isBlock(std::string id)
{
	if (!instance)
		return false;

	std::string name = getName();

	if (name.empty())
		return false;

	std::string object_name = "Block{" + id + "}";

	return name == object_name;
}

