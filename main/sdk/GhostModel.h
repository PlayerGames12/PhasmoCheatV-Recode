#pragma once
#include "sdk.h"

namespace SDK
{
    struct Animator;

    struct GhostModelFields
    {
        MonoBehaviourPunFields MonoBehaviourPunFields;
        void* Fields0;
        void* Fields1;
        void* Fields2;
        void* Fields3;
        Animator* anim;
    };

    struct GhostModel
    {
        void* Clazz;
        void* Monitor;
        GhostModelFields Fields;
    };

    enum class HumanBodyBones
    {
        Hips = 0,
        LeftUpperLeg,
        RightUpperLeg,
        LeftLowerLeg,
        RightLowerLeg,
        LeftFoot,
        RightFoot,
        Spine,
        Chest,
        Neck = 9,
        Head,
        LeftShoulder,
        RightShoulder,
        LeftUpperArm,
        RightUpperArm,
        LeftLowerArm,
        RightLowerArm,
        LeftHand,
        RightHand,
        LeftToes,
        RightToes,
        LeftEye,
        RightEye,
        Jaw,
        LeftThumbProximal,
        LeftThumbIntermediate,
        LeftThumbDistal,
        LeftIndexProximal,
        LeftIndexIntermediate,
        LeftIndexDistal,
        LeftMiddleProximal,
        LeftMiddleIntermediate,
        LeftMiddleDistal,
        LeftRingProximal,
        LeftRingIntermediate,
        LeftRingDistal,
        LeftLittleProximal,
        LeftLittleIntermediate,
        LeftLittleDistal,
        RightThumbProximal,
        RightThumbIntermediate,
        RightThumbDistal,
        RightIndexProximal,
        RightIndexIntermediate,
        RightIndexDistal,
        RightMiddleProximal,
        RightMiddleIntermediate,
        RightMiddleDistal,
        RightRingProximal,
        RightRingIntermediate,
        RightRingDistal,
        RightLittleProximal,
        RightLittleIntermediate,
        RightLittleDistal,
        UpperChest = 54,
        LastBone = 55
    };

    DEC_MET(Animator_GetBoneTransform, Transform* (*)(Animator* anim, HumanBodyBones bone, MethodInfo* methodInfo), "UnityEngine.AnimationModule", "UnityEngine", "Animator", "GetBoneTransform", 1);
}