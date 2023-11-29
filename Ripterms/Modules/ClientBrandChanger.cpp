#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::ClientBrandChanger::renderGUI()
{
	static bool runonce = true;
	if (runonce)
	{
		old_ClientModName = getClientModName();
		std::strcpy(name, old_ClientModName.toStdString().c_str());
		runonce = false;
	}
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	ImGui::Text("Client Brand Changer:");
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	ImGui::InputText("name", name, sizeof(name));
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	if (ImGui::Button("change"))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button("reset"))
	{
		std::strcpy(name, old_ClientModName.toStdString().c_str());
		disable();
	}
}

void Ripterms::Modules::ClientBrandChanger::disable()
{
}

String Ripterms::Modules::ClientBrandChanger::getClientModName()
{
	Ripterms::JavaClassV2 ClientBrandRetrieverClass("net/minecraft/client/ClientBrandRetriever");
	return Ripterms::p_env->CallStaticObjectMethod(ClientBrandRetrieverClass.getJClass(), ClientBrandRetrieverClass.getMethodID("getClientModName"));
}
