#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
//https://www.symbolab.com/solver/step-by-step/%5Cbegin%7Bpmatrix%7D1%260%260%5C%5C%200%26cos%5Cleft(x%5Cright)%26-sin%5Cleft(x%5Cright)%5C%5C%200%26sin%5Cleft(x%5Cright)%26cos%5Cleft(x%5Cright)%5Cend%7Bpmatrix%7D%5Ccdot%5Cbegin%7Bpmatrix%7Dcos%5Cleft(y%5Cright)%260%26sin%5Cleft(y%5Cright)%5C%5C%200%261%260%5C%5C%20-sin%5Cleft(y%5Cright)%260%26cos%5Cleft(y%5Cright)%5Cend%7Bpmatrix%7D%5Ccdot%5Cbegin%7Bpmatrix%7Dcos%5Cleft(z%5Cright)%26-sin%5Cleft(z%5Cright)%260%5C%5C%20sin%5Cleft(z%5Cright)%26cos%5Cleft(z%5Cright)%260%5C%5C%200%260%261%5Cend%7Bpmatrix%7D?or=input

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   
   Matrix3 XYZ = *this;
   
   double theta = asin(XYZ.m13);
   double beta;
   double alpha;

   if (theta == PI/2){
      alpha = atan2(XYZ.m21, XYZ.m22);
      beta = 0;
   }else if (theta == (PI/2)*-1){
      alpha = atan2(XYZ.m32, XYZ.m22);
      beta = 0;
   }else{
      beta = atan2(XYZ.m12 * -1, XYZ.m11);
      alpha = atan2(XYZ.m23 * -1, XYZ.m33);
   }
   return Vector3(alpha, theta, beta);
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   Matrix3 XZY = *this;

   double beta = asin(XZY.m12 * -1);
   double theta;
   double alpha;

   if (beta == (PI/2)){
      theta = 0;
      alpha = atan2(XZY.m31, XZY.m21);
   }else if (beta == (PI/2)*-1){
      alpha = atan2(XZY.m31 * -1, XZY.m21 * -1);
      theta = 0;
   }else{
      theta = atan2(XZY.m13, XZY.m11);
      alpha = atan2(XZY.m32, XZY.m22);
   }
   return Vector3(alpha, theta, beta);
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   Matrix3 YXZ = *this;

   double alpha = asin(YXZ.m23 * -1);
   double beta;
   double theta;
   if (alpha == (PI/2)){
      theta = 0;
      beta = atan2(YXZ.m31, YXZ.m11);
   }else if (alpha == (PI/2)*-1){
      theta = 0;
      beta = atan2(YXZ.m31*-1, YXZ.m11);
   }else{
      beta = atan2(YXZ.m21, YXZ.m22);
      theta = atan2(YXZ.m13, YXZ.m33);
   }
   return Vector3(alpha, theta, beta);
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   Matrix3 YZX = *this;

   double beta = asin(YZX.m21);
   double alpha;
   double theta;
   if (beta == PI/2){
      theta = 0;
      alpha = atan2(YZX.m13, YZX.m33);
   }else if (beta == (PI/2)*-1){
      theta = 0;
      alpha = atan2(YZX.m32, YZX.m12);
   }else{
      alpha = atan2(YZX.m23 * -1, YZX.m22);
      theta = atan2(YZX.m31 * -1, YZX.m11);
   }
   return Vector3(alpha, theta, beta);
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   Matrix3 ZXY = *this;

   double alpha = asin(ZXY.m32);
   double theta;
   double beta;

   if (alpha == PI/2){
      theta = 0;
      beta = atan2(ZXY.m21, ZXY.m11);
   }else if (alpha == (PI/2)*-1){
      theta = 0;
      beta = atan2(ZXY.m21, ZXY.m11);
   }else{
      theta = atan2(ZXY.m31 * -1, ZXY.m33);
      beta = atan2(ZXY.m12 * -1, ZXY.m22);
   }
   return Vector3(alpha, theta, beta);
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   Matrix3 ZYX = *this;

   double theta = asin(ZYX.m31*-1);
   double beta;
   double alpha;
   if (theta == PI/2){
      beta = 0;
      alpha = atan2(ZYX.m12, ZYX.m13);
   }else if (theta == (PI/2)*-1){
      beta = 0;
      alpha = atan2(ZYX.m12*-1, ZYX.m13*-1);
   }else{
      beta = atan2(ZYX.m21, ZYX.m11);
      alpha = atan2(ZYX.m32, ZYX.m33);
   }

   return Vector3(alpha, theta, beta);
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
   //*this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationY(y);
   Matrix3 Z = rotationZ(z);

   Matrix3 XYZ = X*Y*Z;
   *this = XYZ;
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   //*this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationY(y);
   Matrix3 Z = rotationZ(z);

   Matrix3 XZY = X*Z*Y;
   *this = XZY;
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   //*this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationY(y);
   Matrix3 Z = rotationZ(z);

   Matrix3 YXZ = Y*X*Z;
   *this = YXZ;

}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   //*this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationY(y);
   Matrix3 Z = rotationZ(z);

   Matrix3 YZX = Y*Z*X;
   *this = YZX;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   //*this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationY(y);
   Matrix3 Z = rotationZ(z);

   Matrix3 ZXY = Z*X*Y;
   *this = ZXY;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   //*this = Identity;

   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];

   Matrix3 X = rotationX(x);
   Matrix3 Y = rotationY(y);
   Matrix3 Z = rotationZ(z);

   Matrix3 ZYX = Z*Y*X;
   *this = ZYX;

}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{

   Matrix3 m = *this;

   double margin = 0.01;
   double identity = 0.1;

   if ((abs(m[0][1]+m[1][0]) < identity)
		  && (abs(m[0][2]+m[2][0]) < identity)
		  && (abs(m[1][2]+m[2][1]) < identity)
		  && (abs(m[0][0]+m[1][1]+m[2][2]-3) < identity)) {
         angleRad = 0;
         axis[0] = 0;
         axis[1] = 0;
         axis[2] = 0;
		}

	double xx = (m[0][0]+1)/2;
	double yy = (m[1][1]+1)/2;
	double zz = (m[2][2]+1)/2;
	double xy = (m[0][1]+m[1][0])/4;
	double xz = (m[0][2]+m[2][0])/4;
	double yz = (m[1][2]+m[2][1])/4;
		if ((xx > yy) && (xx > zz)) { 
			if (xx < margin) {
				axis[0] = 0;
				axis[1] = 0.7071;
				axis[2] = 0.7071;
			} else {
				axis[0] = sqrt(xx);
				axis[1] = xy/axis[0];
				axis[2] = xz/axis[0];
			}
		} else if (yy > zz) { // m[1][1] is the largest diagonal term
			if (yy < margin) {
				axis[0] = 0.7071;
				axis[1] = 0;
				axis[2] = 0.7071;
			} else {
				axis[1] = sqrt(yy);
				axis[0] = xy/axis[1];
				axis[2] = yz/axis[1];
			}	
		} else { 
			if (zz < margin) {
				axis[0] = 0.7071;
				axis[1] = 0.7071;
				axis[2] = 0;
			} else {
				axis[2] = sqrt(zz);
				axis[0] = xz/axis[2];
				axis[1] = yz/axis[2];
			}
		}
	
	double s = sqrt((m[2][1] - m[1][2])*(m[2][1] - m[1][2])
		+(m[0][2] - m[2][0])*(m[0][2] - m[2][0])
		+(m[1][0] - m[0][1])*(m[1][0] - m[0][1])); 
      
	angleRad = acos(( m[0][0] + m[1][1] + m[2][2] - 1)/2);
	axis[0] = (m[2][1] - m[1][2])/s;
	axis[1] = (m[0][2] - m[2][0])/s;
	axis[2] = (m[1][0] - m[0][1])/s;


   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   double c = cos(angleRad);
   double s = sin(angleRad);
   double t = 1.0 - c;
	
   Matrix3 result;

   result.m11 = c + axis[0] * axis[0] * t;
   result.m22 = c + axis[1] * axis[1] * t;
   result.m33 = c + axis[2] * axis[2] * t;


   double tmp1 = axis[0] * axis[1] * t;
   double tmp2 = axis[2]*s;
   result.m21 = tmp1 + tmp2;
   result.m12 = tmp1 - tmp2;
    
   tmp1 = axis[0]*axis[2]*t;
   tmp2 = axis[1]*s;
   result.m31 = tmp1 - tmp2;
   result.m13 = tmp1 + tmp2;    
    
   tmp1 = axis[1]*axis[2]*t;
   tmp2 = axis[0]*s;
   result.m32 = tmp1 + tmp2;
   result.m23 = tmp1 - tmp2;
   *this = result;
}

}
