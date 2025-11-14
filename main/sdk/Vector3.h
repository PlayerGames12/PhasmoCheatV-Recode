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

        Vector3& operator*=(float f) { X *= f; Y *= f; Z *= f; return *this; }
        Vector3& operator/=(float f) { if (f != 0) { X /= f; Y /= f; Z /= f; } else { X = Y = Z = 0; } return *this; }
    };
}