#include "Vec3.h"
#include <math.h>

ret::Vec3::Vec3() : vector_{0,0,0}, 
    r(vector_[0]), g(vector_[1]), b(vector_[2]), x(vector_[0]), y(vector_[1]), z(vector_[2])
{
}

ret::Vec3::Vec3(float x) : vector_{x,x,x},
    r(vector_[0]), g(vector_[1]), b(vector_[2]), x(vector_[0]), y(vector_[1]), z(vector_[2])
{
}

ret::Vec3::Vec3(float x, float y, float z) : vector_{x,y,z},
    r(vector_[0]), g(vector_[1]), b(vector_[2]), x(vector_[0]), y(vector_[1]), z(vector_[2])
{
}

float ret::Vec3::Magnitude()
{
    double result = (x * x) + (y * y) + (z * z);
    return (float)sqrt(result);
}

float ret::Vec3::Magnitude(Vec3 vector)
{
    return vector.Magnitude();
}

float ret::Vec3::Angle(Vec3, Vec3)
{
    return 0.0f;
}

ret::Vec3 ret::Vec3::Cross(ret::Vec3 vec1, ret::Vec3 vec2)
{
    ret::Vec3 result;
    result.x = vec1.y * vec2.z - vec1.z * vec2.y;
    result.y = vec1.z * vec2.x - vec1.x * vec2.z;
    result.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return result;
}

ret::Vec3 ret::Vec3::Normalized(ret::Vec3)
{


    return ret::Vec3();
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




