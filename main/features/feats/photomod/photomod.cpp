#include "photomod.h"

using namespace PhasmoCheatV::Features::Misc;

PhotoModifier::PhotoModifier() : FeatureCore(LANG("PhotoModifier_Header"), TYPE_MISC)
{
	DECLARE_CONFIG(GetConfigManager(), "AutoPhoto", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "x5photo", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "nodelayphoto", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "skipanimationphoto", bool, false);
}

void PhotoModifier::OnActivate()
{
	bool skipanimationphoto = CONFIG_BOOL(GetConfigManager(), "skipanimationphoto");
	if (skipanimationphoto) SDK::HandCamera_AnimatePhotoCall_nop(5);
}

void PhotoModifier::OnDeactivate()
{
	if (SDK::HandCamera_AnimatePhotoCall_is_replaced) SDK::HandCamera_AnimatePhotoCall_restore();
}

void PhotoModifier::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();

	if (ImGui::Checkbox(LANG("PhotoModifierEnable"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (enabled)
	{
		bool AutoPhoto = CONFIG_BOOL(GetConfigManager(), "AutoPhoto");
		bool x5photo = CONFIG_BOOL(GetConfigManager(), "x5photo");
		bool nodelayphoto = CONFIG_BOOL(GetConfigManager(), "nodelayphoto");
		bool skipanimationphoto = CONFIG_BOOL(GetConfigManager(), "skipanimationphoto");

		if (ImGui::Checkbox(LANG("AutoPhoto"), &AutoPhoto))
			SET_CONFIG_VALUE(GetConfigManager(), "AutoPhoto", bool, AutoPhoto);
		if (ImGui::Checkbox(LANG("X5Photo"), &x5photo))
			SET_CONFIG_VALUE(GetConfigManager(), "x5photo", bool, x5photo);
		if (ImGui::Checkbox(LANG("NoDelayPhoto"), &nodelayphoto))
			SET_CONFIG_VALUE(GetConfigManager(), "nodelayphoto", bool, nodelayphoto);
		if (ImGui::Checkbox(LANG("SkipAnimationPhoto"), &skipanimationphoto))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "skipanimationphoto", bool, skipanimationphoto);
			skipanimationphoto ? SDK::HandCamera_AnimatePhotoCall_nop(5) : SDK::HandCamera_AnimatePhotoCall_restore();
		}
	}

	ImGui::PopStyleVar();
}

void PhotoModifier::PhotoModifierAutoPhoto()
{
	if (!IsActive() || !Globals::isHunting || !CONFIG_BOOL(GetConfigManager(), "AutoPhoto"))
		return;

	auto* localPlayer = Utils::GetLocalPlayer();
	if (!localPlayer) return;

	auto* ghostAI = InGame::ghostAI;
	if (!ghostAI) return;

	auto* ghostTransform = ghostAI->Fields.raycastPoint;
	if (!ghostTransform) return;

	auto* PhotoCamera = Utils::get_PlayerHandCamera(localPlayer);
	if (!PhotoCamera) return;

	if (!Utils::IsPlayerVisibleGhost(localPlayer->Fields.LocalPlayer->Fields.Camera, ghostTransform))
		return;

	if (!Utils::IsGhostVisible(ghostAI))
		return;

	auto* g_obj_camera = SDK::Component_Get_GameObject(
		reinterpret_cast<SDK::Component*>(PhotoCamera), nullptr);
	if (!g_obj_camera) return;

	auto photonViewType = SDK::System_Type_GetType(
		Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
	if (!photonViewType) return;

	auto* photonViewComp = SDK::GameObject_GetComponent(
		g_obj_camera, photonViewType, nullptr);
	if (!photonViewComp) return;

	auto* photonView = reinterpret_cast<SDK::PhotonView*>(photonViewComp);
	if (!photonView) return;

	bool state = true;

	auto boolClass = il2cpp_get_class("mscorlib", "System", "Boolean");
	if (!boolClass) return;

	void* boxedBool = il2cpp_value_box(boolClass, &state);
	if (!boxedBool) return;

	std::vector<void*> params;
	params.push_back(boxedBool);

	auto parameters = Utils::VectorToIl2CppArray<void*>(
		params, "mscorlib", "System", "Object");
	if (!parameters) return;

	auto* methodName = Utils::SysStrToUnityStr("UseNetworked");
	if (!methodName) return;

	SDK::PhotonView_RPC(
		photonView,
		methodName,
		SDK::RpcTarget::All,
		parameters,
		nullptr
	);
}

void PhotoModifier::PhotoModifierX5Photo(SDK::PhotonView* photonView, SDK::String* methodName, SDK::RpcTarget target, void* parameters, SDK::MethodInfo* methodInfo)
{
	if (!IsActive() || !SDK::PhotonView_get_IsMine(photonView, nullptr))
		return;

	bool x5photo = CONFIG_BOOL(GetConfigManager(), "x5photo");

	if (x5photo)
	{
		if (Utils::UnityStrToSysStr(*methodName) == "AddPhotoToJournal")
		{
			for (int i = 0; i < 5; i++)
			{
				SDK::PhotonView_RPC(photonView, methodName, target, parameters, methodInfo);
			}
		}
	}
}

void PhotoModifier::PhotoModifierMain(SDK::HandCamera* handCamera)
{
	if (!IsActive())
		return;

	uintptr_t base = (uintptr_t)handCamera;
	uintptr_t HandCamera1 = *reinterpret_cast<uintptr_t*>(base + 0x38);
	float* useDelay = reinterpret_cast<float*>(HandCamera1 + 0x13C);

	if (useDelay)
	{
		if (CONFIG_BOOL(GetConfigManager(), "nodelayphoto"))
			*useDelay = 0.f;
		else
			*useDelay = 2.f;
	}
}