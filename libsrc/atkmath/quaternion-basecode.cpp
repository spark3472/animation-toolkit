#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	// TODO
	double angle = 0;
	if (Dot(q0, q1) > 1 || Dot(q0, q1) < -1)
	{
		angle = acos(Dot(q0, q1));
	}

	Quaternion result;
	double q0_top = sin(angle*(1-t));
	double denom = sin(angle);

	double q1_top = sin(angle*t);

	result = (q0_top/denom)*q0 + (q1_top/denom)*q1;

	return result;
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	
	Quaternion q = *this;
	if (acos(q.mW) < 0.01){
		angleRad = 0;
	}else{
		angleRad = acos(q.mW) * 2;
	}

	if (sin(angleRad/2) == 0){
		axis[0] = 0.01;
	}else if (sin(angleRad/2) < 0.01){
		axis[0] = 1;
	}else{
		axis[0] = q.mX/sin(angleRad/2);
	}

	if (sin(angleRad/2) == 0){
		axis[1] = 0.01;
	}else if (sin(angleRad/2) < 0.01){
		axis[1] = 1;
	}else{
		axis[1] = q.mY/sin(angleRad/2);
	}

	if (sin(angleRad/2) == 0){
		axis[2] = 0.01;
	}else if (sin(angleRad/2) < 0.01){
		axis[2] = 1;
	}else{
		axis[2] = q.mZ/sin(angleRad/2);
	}

	
	// TODO
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	
	Quaternion quat;
	quat[0] = sin(angleRad/2) * axis[0];
	quat[1] = sin(angleRad/2) * axis[1];
	quat[2] = sin(angleRad/2) * axis[2];
	quat[3] = cos(angleRad/2);
	
	quat.normalize();

	*this = quat;

	// TODO
}

Matrix3 Quaternion::toMatrix () const
{
	Quaternion q = *this;
    Vector3 v; double angle;
	q.toAxisAngle(v, angle);
	Matrix3 result;
	result.fromAxisAngle(v, angle);

	return result;
}

void Quaternion::fromMatrix(const Matrix3& rot)

{
	Quaternion q;

	Vector3 v;
	double angle;
	rot.toAxisAngle(v, angle);
	q.fromAxisAngle(v, angle);

	*this = q;
	

}

}