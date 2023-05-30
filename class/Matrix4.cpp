#include "Matrix4.h"
//#include <Novice.h>
#include <cmath>
#include <cassert>

/// ・｡・・・・・・ｮ・・・・・・・ｿ・・・・・・｢・・ｰ
Matrix4x4 Matrix4::Add(Matrix4x4 m1, Matrix4x4 m2) {

	return Matrix4x4{
		m1.m[0][0] + m2.m[0][0],m1.m[0][1] + m2.m[0][1],m1.m[0][2] + m2.m[0][2],m1.m[0][3] + m2.m[0][3],
		m1.m[1][0] + m2.m[1][0],m1.m[1][1] + m2.m[1][1],m1.m[1][2] + m2.m[1][2],m1.m[1][3] + m2.m[1][3],
		m1.m[2][0] + m2.m[2][0],m1.m[2][1] + m2.m[2][1],m1.m[2][2] + m2.m[2][2],m1.m[2][3] + m2.m[2][3],
		m1.m[3][0] + m2.m[3][0],m1.m[3][1] + m2.m[3][1],m1.m[3][2] + m2.m[3][2],m1.m[3][3] + m2.m[3][3],
	};

}

/// ・｡・・・・・・ｮ・ｷｮ・・・・ｿ・・・・・・｢・・ｰ
Matrix4x4 Matrix4::Subtract(Matrix4x4 m1, Matrix4x4 m2) {

	return Matrix4x4{
		m1.m[0][0] - m2.m[0][0],m1.m[0][1] - m2.m[0][1],m1.m[0][2] - m2.m[0][2],m1.m[0][3] - m2.m[0][3],
		m1.m[1][0] - m2.m[1][0],m1.m[1][1] - m2.m[1][1],m1.m[1][2] - m2.m[1][2],m1.m[1][3] - m2.m[1][3],
		m1.m[2][0] - m2.m[2][0],m1.m[2][1] - m2.m[2][1],m1.m[2][2] - m2.m[2][2],m1.m[2][3] - m2.m[2][3],
		m1.m[3][0] - m2.m[3][0],m1.m[3][1] - m2.m[3][1],m1.m[3][2] - m2.m[3][2],m1.m[3][3] - m2.m[3][3],
	};

}

/// ・｡・・・・・・ｮ・ｩ・・・・・ｿ・・・・・・｢・・ｰ
Matrix4x4 Matrix4::Multiply(Matrix4x4 m1, Matrix4x4 m2) {

	return Matrix4x4{
	m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
	m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
	m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
	m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],
	m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
	m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
	m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
	m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],
	m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
	m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
	m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
	m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],
	m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
	m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
	m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
	m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3],
	};

}

/// ・・・｡・・・・・・・・ｽ・・・・・・・・・・
Matrix4x4 Matrix4::Inverse(Matrix4x4 m) {

	float im = (
		(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0])
		);

	return Matrix4x4{

		(1 / im) * ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2]) -
					(m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2])),
		(1 / im) * (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2]) +
					(m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2])),
		(1 / im) * ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2]) -
					(m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2])),
		(1 / im) * (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2]) +
					(m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2])),

		(1 / im) * ((m.m[1][0] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][2]) -
					(m.m[1][3] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][2])),
		(1 / im) * (-(m.m[0][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][2]) +
					(m.m[0][3] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][2])),
		(1 / im) * ((m.m[0][0] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][2]) -
					(m.m[0][3] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][2])) ,
		(1 / im) * (-(m.m[0][0] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][2]) +
					(m.m[0][3] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][2])),

		(1 / im) * ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1]) -
					(m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1]) +
					(m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1])),
		(1 / im) * ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1]) -
					(m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1]) +
					(m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1])),

		(1 / im) * ((m.m[1][0] * m.m[2][1] * m.m[3][2]) + (m.m[1][1] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][1]) -
					(m.m[1][2] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][2]) - (m.m[1][0] * m.m[2][2] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[2][1] * m.m[3][2]) - (m.m[0][1] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][1]) +
					(m.m[0][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][2]) + (m.m[0][0] * m.m[2][2] * m.m[3][1])),
		(1 / im) * ((m.m[0][0] * m.m[1][1] * m.m[3][2]) + (m.m[0][1] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][1]) -
					(m.m[0][2] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][2]) - (m.m[0][0] * m.m[1][2] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[1][1] * m.m[2][2]) - (m.m[0][1] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][1]) +
					(m.m[0][2] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][2]) + (m.m[0][0] * m.m[1][2] * m.m[2][1])),

	};

}

/// ・ｻ｢・ｽｮ・｡・・・・・・ｮ・ｨ・・ｮ・
Matrix4x4 Matrix4::Transpose(Matrix4x4 m) {

	return Matrix4x4{
		m.m[0][0],m.m[1][0],m.m[2][0],m.m[3][0],
		m.m[0][1],m.m[1][1],m.m[2][1],m.m[3][1],
		m.m[0][2],m.m[1][2],m.m[2][2],m.m[3][2],
		m.m[0][3],m.m[1][3],m.m[2][3],m.m[3][3]
	};

}

/// ・・・・ｽ・・｡・・・・・・ｮ・ｽ・・・・
Matrix4x4 Matrix4::MakeIdentity() {

	return Matrix4x4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};

}


// ・ｹｳ・｡・・ｧｻ・・・・｡・・・・・・ｮ・ｽ・・・・
Matrix4x4 Matrix4::MakeTranslateMatrix(const Vector3 translate) {

	return Matrix4x4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		translate.x,translate.y,translate.z,1
	};

}

// ・・｡・､ｧ・ｸｮ・ｰ・・｡・・・・・・ｮ・ｽ・・・・
Matrix4x4 Matrix4::MakeScaleMatrix(const Vector3 scale) {

	return Matrix4x4{
		scale.x,0,0,0,
		0,scale.y,0,0,
		0,0,scale.z,0,
		0,0,0,1,
	};

}


// ・・・・ｻ｢・｡・・・・・・ｮ・ｽ・・・・(X・ｻｸ・・ｨ・・・・ｼ・YZ・ｹｳ・・｢)
Matrix4x4 Matrix4::MakeRoatateXMatrix(float rad) {

	return Matrix4x4{
		1,0,0,0,
		0,std::cos(rad),std::sin(rad), 0,
		0,-std::sin(rad),std::cos(rad),0,
		0,0,0,1,
	};

}

// ・・・・ｻ｢・｡・・・・・・ｮ・ｽ・・・・(Y・ｻｸ・・ｨ・・・・ｼ・XZ・ｹｳ・・｢)
Matrix4x4 Matrix4::MakeRoatateYMatrix(float rad) {

	return Matrix4x4{
		std::cos(rad),0,-std::sin(rad),0,
		0,1,0,0,
		std::sin(rad),0,std::cos(rad),0,
		0,0,0,1,
	};

}

// ・・・・ｻ｢・｡・・・・・・ｮ・ｽ・・・・(Z・ｻｸ・・ｨ・・・・ｼ・XY・ｹｳ・・｢)
Matrix4x4 Matrix4::MakeRoatateZMatrix(float rad) {

	return Matrix4x4{
		std::cos(rad),std::sin(rad),0,0,
		-std::sin(rad),std::cos(rad),0,0,
		0,0,1,0,
		0,0,0,1,
	};

}


// ・ｺｧ・ｨ・・､・・・・
Vector3 Matrix4::Transform(const Vector3& v, const Matrix4x4& m) {
	Vector3 result;
	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.0f * m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.0f * m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.0f * m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1.0f * m.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

// ・・｢・・・・・｣・・ｳ・｡・・・・・・ｮ・ｽ・・・・
Matrix4x4 Matrix4::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	// ・・・・ｻ｢・｡・・・・・・・・ｽ・・・・
	Matrix4x4 rotateXMatrix = Matrix4::MakeRoatateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = Matrix4::MakeRoatateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = Matrix4::MakeRoatateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Matrix4::Multiply(rotateXMatrix, Matrix4::Multiply(rotateYMatrix, rotateZMatrix));

	return Matrix4x4{
		scale.x * rotateXYZMatrix.m[0][0],	scale.x * rotateXYZMatrix.m[0][1],	scale.x * rotateXYZMatrix.m[0][2],0,
		scale.y * rotateXYZMatrix.m[1][0],	scale.y * rotateXYZMatrix.m[1][1],	scale.y * rotateXYZMatrix.m[1][2],0,
		scale.z * rotateXYZMatrix.m[2][0],	scale.z * rotateXYZMatrix.m[2][1],	scale.z * rotateXYZMatrix.m[2][2],0,
		translate.x,translate.y,translate.z,1
	};

}


// ・・・ｦ・・・・・ｽｱ・｡・・・・・・ｮ・ｽ・・・・
Matrix4x4 Matrix4::MakePerspectiveMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	
	return Matrix4x4{
	(1 / aspectRatio) * (1 / std::tan(fovY / 2)),0,0,0,
	0,(1 / std::tan(fovY / 2)),0,0,
	0,0,farClip / (farClip - nearClip),1,
	0,0,nearClip / (nearClip - farClip),0
	};

}

// ・ｭ｣・ｰ・・ｽｱ・｡・・・・・・ｮ・ｽ・・・・
Matrix4x4 Matrix4::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {

	return Matrix4x4{
		2 / (right - left),0,0,0,
		0,2 / (top - bottom),0,0,
		0,0,1 / (farClip - nearClip),0,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1
	};

}

// ・・・・・･・・ｼ・・・・・ｼ・・・・､・・・・・｡・・・・・・ｮ・ｽ・・・・
Matrix4x4 Matrix4::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {

	// minD <= maxD ・・ｧ・・ｪ・・・・・・・・ｰ・ｮ・・｡・・・・・・ｪ・・・
	assert(minDepth <= maxDepth);
	return Matrix4x4{
		width / 2,0,0,0,
		0,-height / 2,0,0,
		0,0,maxDepth - minDepth,0,
		left + (width / 2),top + (height / 2),minDepth,1
	};

}


/// ・・・・・ｻ・・｢・・ｰ ///

//
///// 4x4・｡・・・・・・ｮ・・ｰ・､・｡ｨ・､ｺ
//void Matrix4::MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* label) {
//
//	// ・・ｩ・・・・・ｫ・・ｮ・｡ｨ・､ｺ
//	Novice::ScreenPrintf(x, y, "%s", label);
//
//	// ・｡・・・・・・ｮ・・ｰ・､・・・・｡ｨ・､ｺ
//
//	// Y・ｺｧ・ｨ・・・・・ｽ・
//	for (int h = 0; h < 4; h++) {
//		// X・ｺｧ・ｨ・・・・・ｽ・
//		for (int w = 0; w < 4; w++) {
//
//			Novice::ScreenPrintf(x + 80 * w, (y + 20 * h) + 20, "%6.02f", matrix.m[h][w]);
//
//		}
//	}
//
//}
//
///// 3・ｬ｡・・・・・・・・ｯ・・・・・ｫ・・ｮ・・ｰ・､・｡ｨ・､ｺ
//	/// <summary>
//void Matrix4::VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {
//
//	// ・・ｩ・・・・・ｫ・・ｮ・｡ｨ・､ｺ
//	Novice::ScreenPrintf(x, y, "%s", label);
//
//	// 3・ｬ｡・・・・・・・・ｯ・・・・・ｫ・・ｮ・｡ｨ・､ｺ
//	Novice::ScreenPrintf(x, y + 20, "%6.02f", vector.x);
//	Novice::ScreenPrintf(x + 80, y + 20, "%6.02f", vector.y);
//	Novice::ScreenPrintf(x + 160, y + 20, "%6.02f", vector.z);
//
//}