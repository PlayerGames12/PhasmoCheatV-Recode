#include "sdk.h"

namespace SDK
{
    struct Vector3
    {
        float X, Y, Z;

        Vector3 operator+(const Vector3& o) const { return { X + o.X, Y + o.Y, Z + o.Z }; }
        Vector3 operator-(const Vector3& o) const { return { X - o.X, Y - o.Y, Z - o.Z }; }
        Vector3 operator*(const Vector3& o) const { return { X * o.X, Y * o.Y, Z * o.Z }; }
        Vector3 operator/(const Vector3& o) const
        {
            return {
                o.X != 0 ? X / o.X : 0,
                o.Y != 0 ? Y / o.Y : 0,
                o.Z != 0 ? Z / o.Z : 0
            };
        }

        Vector3& operator+=(const Vector3& o) { X += o.X; Y += o.Y; Z += o.Z; return *this; }
        Vector3& operator-=(const Vector3& o) { X -= o.X; Y -= o.Y; Z -= o.Z; return *this; }
        Vector3& operator*=(const Vector3& o) { X *= o.X; Y *= o.Y; Z *= o.Z; return *this; }
        Vector3& operator/=(const Vector3& o)
        {
            if (o.X != 0) X /= o.X; else X = 0;
            if (o.Y != 0) Y /= o.Y; else Y = 0;
            if (o.Z != 0) Z /= o.Z; else Z = 0;
            return *this;
        }

        Vector3 operator*(float f) const { return { X * f, Y * f, Z * f }; }
        Vector3 operator/(float f) const { return f != 0 ? Vector3{ X / f, Y / f, Z / f } : Vector3{ 0,0,0 }; }
        // Made with love
        Vector3& operator*=(float f) { X *= f; Y *= f; Z *= f; return *this; }
        Vector3& operator/=(float f) { if (f != 0) { X /= f; Y /= f; Z /= f; } else { X = Y = Z = 0; } return *this; }
    };

    DEC_MET(Vector3_get_magnitude, float(*)(Vector3* vec3, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Vector3", "get_magnitude", 0);
    DEC_MET(Vector3_get_normalized, Vector3(*)(Vector3* vec3, MethodInfo*), "UnityEngine.CoreModule", "UnityEngine", "Vector3", "get_normalized", 0);
	DEC_MET(Vector3_ProjectOnPlane, Vector3(*)(Vector3 vec, Vector3 planeNormal, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Vector3", "ProjectOnPlane", 2);
	DEC_MET(Vector3_up, Vector3(*)(MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Vector3", "get_up", 0);
	DEC_MET(Vector3_Normalize, Vector3(*)(Vector3 value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Vector3", "Normalize", 1);
}