#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   return Vector3();
}
Matrix3 rotationX(float x){
   Matrix3 X;
   X[0][0] = 1;
   X[0][1] = 0;
   X[0][2] = 0;
   X[1][0] = 0;
   X[1][1] = cos(x);
   X[1][2] = -sin(x);
   X[2][0] = 0;
   X[2][1] = sin(x);
   X[2][2] = cos(x);
   return X;
}
Matrix3 rotationY(float y){
   Matrix3 Y;
   Y[0][0] = cos(y);
   Y[0][1] = 0;
   Y[0][2] = sin(y);
   Y[1][0] = 0;
   Y[1][1] = 1;
   Y[1][2] = 0;
   Y[2][0] = -sin(y);
   Y[2][1] = 0;
   Y[2][2] = cos(y);
   return Y;
}
Matrix3 rotationZ(float z){
   Matrix3 Z;
   Z[0][0] = cos(z);
   Z[0][1] = -sin(z);
   Z[0][2] = 0;
   Z[1][0] = sin(z);
   Z[1][1] = cos(z);
   Z[1][2] = 0;
   Z[2][0] = 0;
   Z[2][1] = 0;
   Z[2][2] = 1;
   return Z;
}
void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   *this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationX(y);
   Matrix3 Z = rotationX(z);

   Matrix3 XYZ = X*Y*Z;
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   *this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationX(y);
   Matrix3 Z = rotationX(z);

   Matrix3 XZY = X*Z*Y;
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   *this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationX(y);
   Matrix3 Z = rotationX(z);

   Matrix3 YXZ = Y*X*Z;
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   *this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationX(y);
   Matrix3 Z = rotationX(z);

   Matrix3 YZX = Y*Z*X;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   *this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationX(y);
   Matrix3 Z = rotationX(z);

   Matrix3 ZXY = Z*X*Y;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   *this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationX(y);
   Matrix3 Z = rotationX(z);

   Matrix3 ZYX = Z*Y*X;

}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
}

}