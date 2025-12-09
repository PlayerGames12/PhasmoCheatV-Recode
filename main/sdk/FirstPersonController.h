#pragma once
#include "MouseLook.h"
#include "sdk.h"

namespace SDK
{
	struct FirstPersonControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		bool CanMove;
		bool CanTurn;
		bool IsSprinting;
		bool IsMoving;
		bool CanSprint;
		float RunstepLength;
		float StickToGroundForce;
		float GravityMultiplier;
		MouseLook* MouseLook;
		bool UseFovKick;
		void* FovKick;
		bool UseHeadBob;
		bool ToggleSprint;
		void* HeadBob;
		float StepInterval;
		Camera* Camera;
		Vector2 Input;
		Vector3 MoveDir;
		PhysicsCharacterController* PhysicsCharacterController;
		bool Crouching;
		float CurrentSpeed;
		Vector3 DesiredMove;
		RaycastHit HitInfo;
		void* OnStartSprint;
		void* OnStartWalk;
	};

	struct FirstPersonController
	{
		void* Clazz;
		void* Monitor;
		FirstPersonControllerFields Fields;
	};

	DEC_MET(FirstPersonController_Update, void(*)(FirstPersonController* firstPersonController, MethodInfo* methodInfo), "Assembly-CSharp", "", "FirstPersonController", "Update", 0);
}
