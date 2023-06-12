#pragma once
#include<Matrix4x4.h>
#include<Vector3.h>

class Matrix4x4Funk {

public:


	/// <summary>
	/// 行列の和を返す関数
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns>"行列1"と"行列2"の積を返す</returns>
	static Matrix4x4 Add(Matrix4x4 matrix1, Matrix4x4 matrix2);

	/// <summary>
	/// 行列の差を返す関数
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns>"行列1"と"行列2"の積を返す</returns>
	static Matrix4x4 Subtract(Matrix4x4 matrix1, Matrix4x4 matrix2);

	/// <summary>
	/// 行列の積を返す関数
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns>"行列1"と"行列2"の積を返す</returns>
	static Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2);

	/// <summary>
	/// 逆行列を作成する
	/// </summary>
	/// <param name="matrix">4x4の正方行列</param>
	/// <returns>引数の逆行列を返す</returns>
	static Matrix4x4 Inverse(Matrix4x4 m);

	/// <summary>
	/// 転置行列の計算
	/// </summary>
	/// <param name="matrix">4x4の行列</param>
	/// <returns>引数の行列の"列"と"行"を入れ替えた転置行列を返す</returns>
	static Matrix4x4 Transpose(Matrix4x4 m);

	/// <summary>
	/// 単位行列の作成
	/// </summary>
	/// <returns>作成した4x4の単位行列を返す</returns>
	static Matrix4x4 MakeIdentity();

	/// <summary>
	// 平行移動行列の作成
	/// <summary>
	static Matrix4x4 MakeTranslateMatrix(const Vector3 translate);

	/// <summary>
	// 拡大縮小行列の作成
	/// <summary>
	static Matrix4x4 MakeScaleMatrix(const Vector3 scale);

	/// <summary>
	// 回転行列の作成(X)
	/// <summary>
	static Matrix4x4 MakeRoatateXMatrix(float rad);

	/// <summary>
	// 回転行列の作成(Y)
	/// <summary>
	static Matrix4x4 MakeRoatateYMatrix(float rad);

	/// <summary>
	// 回転行列の作成(Z)
	/// <summary>
	static Matrix4x4 MakeRoatateZMatrix(float rad);

	/// <summary>
	// 座標変換
	/// <summary>
	static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

	/// <summary>
	// アフィン行列の作成
	/// <summary>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	// 透視投影行列の作成
	/// <summary>
	static Matrix4x4 MakePerspectiveMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// <summary>
	// 正射影行列の作成
	/// <summary>
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	/// <summary>
	// ビューポート変換行列の作成
	/// <summary>
	static Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);


	/// 描画関数 ///

	/// <summary>
	/// 4x4行列の数値表示
	/// </summary>
	static void MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* label);

	/// <summary>
	/// 3次元ベクトルの数値表示
	/// <summary>
	static void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label);

};

