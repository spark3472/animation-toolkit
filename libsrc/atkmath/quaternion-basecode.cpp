#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	// TODO
	return Quaternion(1,0,0,0);
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	
	Quaternion q = *this;
	angleRad = acos(q.mW) * 2;

	if (isnan(q.mX/sin(angleRad/2))){
		axis[0] = 0;
	}else if (isinf(q.mX/sin(angleRad/2))){
		axis[0] = 1;
	}else{
		axis[0] = q.mX/sin(angleRad/2);
	}

	if (isnan(q.mY/sin(angleRad/2))){
		axis[1] = 0;
	}else if (isinf(q.mY/sin(angleRad/2))){
		axis[1] = 1;
	}else{
		axis[1] = q.mY/sin(angleRad/2);
	}

	if (isnan(q.mZ/sin(angleRad/2))){
		axis[2] = 0;
	}else if (isinf(q.mZ/sin(angleRad/2))){
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
	Vector3 v;
	double angle;

	rot.toAxisAngle(v, angle);

	Quaternion q;
	q.fromAxisAngle(v, angle);

	*this = q;

}

}