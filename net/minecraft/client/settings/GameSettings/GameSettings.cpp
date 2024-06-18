#include "GameSettings.h"
#include "../../OptionInstance/OptionInstance.h"
#include "../../../../../java/lang/Double/Double.h"

double GameSettings::getGammaSetting()
{
	if(!instance)
		return 0.0;
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5)
		return env->GetDoubleField(instance, GameSettingsClass.getFieldID("gammaSetting"));
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
	{
		OptionInstance optionInstance(env->GetObjectField(instance, GameSettingsClass.getFieldID("gammaSetting")), env);
		if (!optionInstance) return 0.0;
		return Double(optionInstance.getValue()).doubleValue();
	}
	return env->GetFloatField(instance, GameSettingsClass.getFieldID("gammaSetting"));
}

KeyBinding GameSettings::getKeyBindSneak()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindSneak")), env);
}

KeyBinding GameSettings::getKeyBindSprint()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindSprint")), env);
}

KeyBinding GameSettings::getKeyBindForward()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindForward")), env);
}

KeyBinding GameSettings::getKeyBindBack()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindBack")), env);
}

KeyBinding GameSettings::getKeyBindLeft()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindLeft")), env);
}

KeyBinding GameSettings::getKeyBindRight()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindRight")), env);
}

KeyBinding GameSettings::getKeyBindAttack()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindAttack")), env);
}

KeyBinding GameSettings::getKeyBindJump()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindJump")), env);
}

bool GameSettings::getPauseOnLostFocus()
{
	if (!instance)
		return false;
	return env->GetBooleanField(instance, GameSettingsClass.getFieldID("pauseOnLostFocus")) == JNI_TRUE;
}

void GameSettings::setPauseOnLostFocus(bool value)
{
	if (!instance)
		return;
	env->SetBooleanField(instance, GameSettingsClass.getFieldID("pauseOnLostFocus"), (value ? JNI_TRUE : JNI_FALSE));
}

void GameSettings::setGammaSetting(double value)
{
	if (!instance)
		return;
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5)
	{
		env->SetDoubleField(instance, GameSettingsClass.getFieldID("gammaSetting"), (jdouble)value);
		return;
	}
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
	{
		OptionInstance optionInstance(env->GetObjectField(instance, GameSettingsClass.getFieldID("gammaSetting")), env);
		optionInstance.setValue(Double::newObject(value, env));
		return;
	}
	env->SetFloatField(instance, GameSettingsClass.getFieldID("gammaSetting"), (jfloat)value);
}
