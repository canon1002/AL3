#pragma once
#include"Vector3.h"
#include"Matrix4x4.h"

class Matrix4 {

public: // 4x4・｡・・・・ ・・｡・・ｾ・・・・・・

	/// <summary>
	/// ・｡・・・・・・ｮ・・・・・・・ｿ・・・・・・｢・・ｰ
	/// </summary>
	/// <param name="matrix1">・｡・・・・1</param>
	/// <param name="matrix2">・｡・・・・2</param>
	/// <returns>"・｡・・・・1"・・ｨ"・｡・・・・2"・・ｮ・ｩ・・・・・ｿ・・・・</returns>
	static Matrix4x4 Add(Matrix4x4 matrix1, Matrix4x4 matrix2);

	/// <summary>
	/// ・｡・・・・・・ｮ・ｷｮ・・・・ｿ・・・・・・｢・・ｰ
	/// </summary>
	/// <param name="matrix1">・｡・・・・1</param>
	/// <param name="matrix2">・｡・・・・2</param>
	/// <returns>"・｡・・・・1"・・ｨ"・｡・・・・2"・・ｮ・ｩ・・・・・ｿ・・・・</returns>
	static Matrix4x4 Subtract(Matrix4x4 matrix1, Matrix4x4 matrix2);

	/// <summary>
	/// ・｡・・・・・・ｮ・ｩ・・・・・ｿ・・・・・・｢・・ｰ
	/// </summary>
	/// <param name="matrix1">・｡・・・・1</param>
	/// <param name="matrix2">・｡・・・・2</param>
	/// <returns>"・｡・・・・1"・・ｨ"・｡・・・・2"・・ｮ・ｩ・・・・・ｿ・・・・</returns>
	static Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2);


	/// <summary>
	/// ・・・｡・・・・・・・・ｽ・・・・・・・・・・
	/// </summary>
	/// <param name="matrix">4x4・・ｮ・ｭ｣・・ｹ・｡・・・・</param>
	/// <returns>・ｼ・・・ｰ・・ｮ・・・｡・・・・・・・・ｿ・・・・</returns>
	static Matrix4x4 Inverse(Matrix4x4 m);


	/// <summary>
	/// ・ｻ｢・ｽｮ・｡・・・・・・ｮ・ｨ・・ｮ・
	/// </summary>
	/// <param name="matrix">4x4・・ｮ・｡・・・・</param>
	/// <returns>・ｼ・・・ｰ・・ｮ・｡・・・・・・ｮ"・・・"・・ｨ"・｡・"・・・・・･・・・・・ｿ・・・・・・・ｻ｢・ｽｮ・｡・・・・・・・・ｿ・・・・</returns>
	static Matrix4x4 Transpose(Matrix4x4 m);

	/// <summary>
	/// ・・・・ｽ・・｡・・・・・・ｮ・ｽ・・・・
	/// </summary>
	/// <returns>・ｽ・・・・・・・・・・4x4・・ｮ・・・・ｽ・・｡・・・・・・・・ｿ・・・・</returns>
	static Matrix4x4 MakeIdentity();

	/// <summary>
	/// ・ｹｳ・｡・・ｧｻ・・・・｡・・・・・・ｮ・ｽ・・・・
	/// <summary>
	static Matrix4x4 MakeTranslateMatrix(const Vector3 translate);

	/// <summary>
	/// ・・｡・､ｧ・ｸｮ・ｰ・・｡・・・・・・ｮ・ｽ・・・・
	/// <summary>
	static Matrix4x4 MakeScaleMatrix(const Vector3 scale);

	/// <summary>
	/// ・・・・ｻ｢・｡・・・・・・ｮ・ｽ・・・・(X)
	/// <summary>
	static Matrix4x4 MakeRoatateXMatrix(float rad);

	/// <summary>
	// ・・・・ｻ｢・｡・・・・・・ｮ・ｽ・・・・(Y)
	/// <summary>
	static Matrix4x4 MakeRoatateYMatrix(float rad);
	
	/// <summary>
	/// ・・・・ｻ｢・｡・・・・・・ｮ・ｽ・・・・(Z)
	/// <summary>
	static Matrix4x4 MakeRoatateZMatrix(float rad);

	/// <summary>
	/// ・ｺｧ・ｨ・・､・・・・
	/// <summary>
	static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

	/// <summary>
	// ・・｢・・・・・｣・・ｳ・｡・・・・・・ｮ・ｽ・・・・
	/// <summary>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	/// ・・・ｦ・・・・・ｽｱ・｡・・・・・・ｮ・ｽ・・・・
	/// <summary>
	static Matrix4x4 MakePerspectiveMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// <summary>
	/// ・ｭ｣・ｰ・・ｽｱ・｡・・・・・・ｮ・ｽ・・・・
	/// <summary>
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	/// <summary>
	/// ・・・・・･・・ｼ・・・・・ｼ・・・・､・・・・・｡・・・・・・ｮ・ｽ・・・・
	/// <summary>
	static Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);


	/// ・・・・・ｻ・・｢・・ｰ ///


	///// <summary>
	///// 4x4・｡・・・・・・ｮ・・ｰ・､・｡ｨ・､ｺ
	///// </summary>
	//static void MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* label);

	///// <summary>
	///// 3・ｬ｡・・・・・・・・ｯ・・・・・ｫ・・ｮ・・ｰ・､・｡ｨ・､ｺ
	///// <summary>
	//static void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label);

};



