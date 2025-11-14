#pragma once
#include "sdk.h"

namespace SDK
{
    // Предварительное объявление классов
    struct Animator;

    struct GhostModelFields
    {
        MonoBehaviourPunFields MonoBehaviourPunFields;
        void* Fields0; // GhostAI*
        void* Fields1; // Renderer*[]
        void* Fields2; // Renderer*[]
        void* Fields3; // List<Material>*
        Animator* anim; // Animator*
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

    static const std::pair<HumanBodyBones, HumanBodyBones> kBoneConnections[] = {
        // Туловище
        { HumanBodyBones::Hips, HumanBodyBones::Spine },
        { HumanBodyBones::Spine, HumanBodyBones::Chest },
        { HumanBodyBones::Chest, HumanBodyBones::UpperChest },

        // Шея/голова
        { HumanBodyBones::UpperChest, HumanBodyBones::Neck },
        { HumanBodyBones::Neck, HumanBodyBones::Head },

        // Левая нога
        { HumanBodyBones::Hips, HumanBodyBones::LeftUpperLeg },
        { HumanBodyBones::LeftUpperLeg, HumanBodyBones::LeftLowerLeg },
        { HumanBodyBones::LeftLowerLeg, HumanBodyBones::LeftFoot },
        { HumanBodyBones::LeftFoot, HumanBodyBones::LeftToes },

        // Правая нога
        { HumanBodyBones::Hips, HumanBodyBones::RightUpperLeg },
        { HumanBodyBones::RightUpperLeg, HumanBodyBones::RightLowerLeg },
        { HumanBodyBones::RightLowerLeg, HumanBodyBones::RightFoot },
        { HumanBodyBones::RightFoot, HumanBodyBones::RightToes },

        // Левая рука
        { HumanBodyBones::UpperChest, HumanBodyBones::LeftShoulder },
        { HumanBodyBones::LeftShoulder, HumanBodyBones::LeftUpperArm },
        { HumanBodyBones::LeftUpperArm, HumanBodyBones::LeftLowerArm },
        { HumanBodyBones::LeftLowerArm, HumanBodyBones::LeftHand },

        // Правая рука
        { HumanBodyBones::UpperChest, HumanBodyBones::RightShoulder },
        { HumanBodyBones::RightShoulder, HumanBodyBones::RightUpperArm },
        { HumanBodyBones::RightUpperArm, HumanBodyBones::RightLowerArm },
        { HumanBodyBones::RightLowerArm, HumanBodyBones::RightHand },

        // Глаза/челюсть (как дополнение)
        { HumanBodyBones::Head, HumanBodyBones::Jaw },
        { HumanBodyBones::Head, HumanBodyBones::LeftEye },
        { HumanBodyBones::Head, HumanBodyBones::RightEye },
    };

    DECLARE_FUNCTION_POINTER(Animator_GetBoneTransform, Transform* (*)(Animator* anim, HumanBodyBones bone, MethodInfo* methodInfo), 0x4AA4DD0);
}