#include "Vec3.h"
#include <iostream>
#include <math.h>

ret::Vec3::Vec3() : x(0), y(0), z(0)
{
}

ret::Vec3::Vec3(float num) : x(num), y(num), z(num)
{
}

ret::Vec3::Vec3(float t_x, float t_y, float t_z) : x(t_x), y(t_y), z(t_z)
{
}

void ret::Vec3::Normalize()
{
    float magnitude = Magnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

float ret::Vec3::Magnitude()
{
    double result = ((double)x * (double)x) + ((double)y * (double)y) + ((double)z * (double)z);
    return (float)sqrt(result);
}

float ret::Vec3::Magnitude(Vec3 vector)
{
    return vector.Magnitude();
}

float ret::Vec3::Angle(Vec3 vec1, Vec3 vec2)
{
    float temp = Dot(vec1, vec2) / vec1.Magnitude() * vec2.Magnitude();
    return acos(temp);
}

ret::Vec3 ret::Vec3::Cross(ret::Vec3 vec1, ret::Vec3 vec2)
{
    ret::Vec3 result;
    result.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
    result.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
    result.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
    std::cout << "VEC3: " << result.x << " " << result.y << " " << result.z << std::endl;
    return result;
}

float ret::Vec3::Dot(Vec3 vec1, Vec3 vec2)
{
    return ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
}

ret::Vec3 ret::Vec3::Normalized(ret::Vec3 vec)
{
    return vec/vec.Magnitude();
}

ret::Vec3 ret::Vec3::operator+(Vec3 const& vec)
{
    return ret::Vec3(x + vec.x, y + vec.y, z + vec.z);
}

ret::Vec3 ret::Vec3::operator*(Vec3 const& vec)
{
    return ret::Vec3(x * vec.x, y * vec.y, z * vec.z);
}

ret::Vec3 ret::Vec3::operator*(float const& num)
{
    return ret::Vec3(x * num, y * num, z * num);
}

ret::Vec3 ret::Vec3::operator /(float const& num)
{
    return ret::Vec3(x/num, y/num, z/num);
}



