#pragma once

namespace ret {
    class Vec3
    {
    public:
        float vector_[3];
        float& x, y, z, r, g, b;
    public:
        Vec3();
        Vec3(float);
        Vec3(float, float, float);
        void Normalize();
        float Magnitude();

        static float Magnitude(Vec3);
        static float Angle(Vec3, Vec3);
        static Vec3 Cross(Vec3, Vec3);
        static Vec3 Dot(Vec3, Vec3);
        static Vec3 Normalized(Vec3);

        Vec3 operator + (Vec3 const&);
        Vec3 operator * (Vec3 const&);
        Vec3 operator * (float const&);
    };
}

