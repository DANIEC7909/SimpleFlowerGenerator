#pragma once
#include <valarray>
#include <cmath>


constexpr double pi = 3.14159265358979323846;
//Simply math header that contains most common functions that I used in this project. 
namespace Math
{
    struct Vector3
    {
        
        float x;
        float y;
        float z;
        Vector3(float _x, float _y, float _z)
        {
            x=_x;
            y=_y;
            z=_z;
        }
       static float Distance(const Vector3& a, const Vector3& b) {
            float dx = b.x - a.x;
            float dy = b.y - a.y;
            float dz = b.z - a.z;
            return std::sqrt(dx * dx + dy * dy + dz * dz);
        }
        static Vector3 Zero() { return {0, 0, 0}; }
    };

    //Axis must be normalized.
    inline void Rotate(Vector3& vertex, const Vector3& axis, float angle )
    {
        //calculate radians from angle
        angle = (angle * pi)/180;

        float cosOfAngle = std::cos(angle);
        float sinOfAngle = std::sin(angle);
        float one_minus_cos = 1.0f - cosOfAngle;

        float ux = axis.x;
        float uy = axis.y;
        float uz = axis.z;

        vertex = {
            (cosOfAngle + ux*ux*one_minus_cos)     * vertex.x + (ux*uy*one_minus_cos - uz*sinOfAngle) * vertex.y + (ux*uz*one_minus_cos + uy*sinOfAngle) * vertex.z,
            (uy*ux*one_minus_cos + uz*sinOfAngle)  * vertex.x + (cosOfAngle + uy*uy*one_minus_cos)    * vertex.y + (uy*uz*one_minus_cos - ux*sinOfAngle) * vertex.z,
            (uz*ux*one_minus_cos - uy*sinOfAngle)  * vertex.x + (uz*uy*one_minus_cos + ux*sinOfAngle) * vertex.y + (cosOfAngle + uz*uz*one_minus_cos)    * vertex.z
        };
      
    }
    inline void AddOffset(Vector3& vertex,const Vector3& offset)
    {
        vertex.x += offset.x;
        vertex.y += offset.y;
        vertex.z += offset.z;
    }
    inline void Scale(Vector3& vertex, const Vector3& scale)
    {
        vertex.x *= scale.x;
        vertex.y *= scale.y;
        vertex.z *= scale.z;
    }

   inline float CalculateApotema(float sideLength,int sideCount)
    {
        return sideLength / (2 * (std::tan(pi/sideCount)));
    }
}
