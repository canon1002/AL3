#pragma once

// 自作コードのインクルード
#include"madeCode/Math/Heder/MathTool.h"

// エンジンコードなどのインクルード
#define _USE_MATH_DEFINES
#include<cmath>
#include"madeCode/Novice/Novice.h"


#pragma region 共通

/// <summary>
/// 
/// </summary>
/// <param name="num"></param>
/// <param name="max"></param>
/// <param name="min"></param>
/// <returns></returns>
float clamp(float num, float max, float min)
{
	if (num > max)
	{
		return max;
	}
	else if (num < min)
	{
		return max;
	}
	else
	{
		return num;
	}
}

#pragma endregion


#pragma region 二次元ベクトル

/// <summary>
/// ベクトルの長さを求める
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Length(const Vector2& v) {
	float result;
	result = sqrt(v.x * v.x + v.y * v.y);
	return result;
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vector2 Nomalize(const Vector2& v)
{
	Vector2 result;
	result.x = v.x / Length(v);
	result.y = v.y / Length(v);

	return result;
}

#pragma endregion

#pragma region 三次元ベクトル


Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}


Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}


Vector3 Scalar(float scalar, const Vector3& v)
{
	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

/// <summary>
/// ベクトルの長さを求める
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Length(const Vector3& v) {
	float result;
	result = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vector3 Nomalize(const Vector3& v)
{
	Vector3 result;
	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;
}

/// <summary>
/// クロス積・外積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = {
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	};

	return result;
};

/// <summary>
/// ドット積・内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vector3& v1, const Vector3& v2)
{
	return float{ v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
};

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = Scalar(Dot(v1, Nomalize(v2)), Nomalize(v2));

	return result;
}

/// <summary>
/// 最近接点
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
/// <returns></returns>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	float t = Dot(Subtract(point, segment.origin), segment.diff) / pow(Length(segment.diff), 2.0f);
	t = clamp(t, 1.0f, 0.0f);

	Vector3 result = Add(segment.origin, Scalar(t, segment.diff));
	return result; 
}

Vector3 Perpendicular(const Vector3& v) {
	if (v.x != 0 || v.y != 0) {
		return { -v.y,v.x,0.0f };
	}

	return{ 0.0f,-v.z,v.y };
}

#pragma region 衝突判定関数

bool isCollision(const Sphere& s1, const Sphere& s2) {

	// 2つの球体の中心点間の距離を求める
	float distance = Length(Subtract(s2.center, s1.center));

	// 半径の合計よりも短ければ衝突
	if (distance <= (s1.radius + s2.radius)) 
	{
		return true;
	}

	return false;

}

#pragma endregion


#pragma region 描画関数


/// グリッド線を表示する関数
void DrawGrid(const Matrix4x4& viewProjection, const Matrix4x4& viewport) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	Vector3 localWidthVer[2]{};  // 横線の頂点	[0]が始点[1]が終点
	Vector3 localHeightVer[2]{}; // 縦線の頂点

	Vector3 screenWidthVer[2]{};  // 横線の頂点
	Vector3 screenHeightVer[2]{}; // 縦線の頂点

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		/// ローカル座標系をセット

		// 横線
		localWidthVer[0] = { -kGridHalfWidth, 0.0f, kGridEvery * (float(xIndex) - 5) };
		localWidthVer[1] = { kGridHalfWidth, 0.0f, kGridEvery * (float(xIndex) - 5) };
		// 縦線
		localHeightVer[0] = { kGridEvery * (float(xIndex) - 5), 0.0f, -kGridHalfWidth };
		localHeightVer[1] = { kGridEvery * (float(xIndex) - 5), 0.0f, kGridHalfWidth };

		// ndcに変換
		Vector3 ndcWidthStart = Matrix4x4Funk::Transform(localWidthVer[0], viewProjection);
		Vector3 ndcWidthEnd = Matrix4x4Funk::Transform(localWidthVer[1], viewProjection);
		Vector3 ndcHeightStart = Matrix4x4Funk::Transform(localHeightVer[0], viewProjection);
		Vector3 ndcHeightEnd = Matrix4x4Funk::Transform(localHeightVer[1], viewProjection);

		// スクリーン座標系へ変換
		screenWidthVer[0] = Matrix4x4Funk::Transform(ndcWidthStart, viewport);
		screenWidthVer[1] = Matrix4x4Funk::Transform(ndcWidthEnd, viewport);
		screenHeightVer[0] = Matrix4x4Funk::Transform(ndcHeightStart, viewport);
		screenHeightVer[1] = Matrix4x4Funk::Transform(ndcHeightEnd, viewport);

		// 上の情報を使ってワールド座標系上の始点と終点を求める
		// スクリーン座標系まで返還をかける
		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)原点は黒ぐらいが良い

		Novice::DrawLine(
			int(screenWidthVer[0].x), int(screenWidthVer[0].y), int(screenWidthVer[1].x),
			int(screenWidthVer[1].y), 0xAAAAAAFF);
		Novice::DrawLine(
			int(screenHeightVer[0].x), int(screenHeightVer[0].y), int(screenHeightVer[1].x),
			int(screenHeightVer[1].y), 0xAAAAAAFF);

		//
		if (localWidthVer[0].z == 0) {
			Novice::DrawLine(
				int(screenWidthVer[0].x), int(screenWidthVer[0].y), int(screenWidthVer[1].x),
				int(screenWidthVer[1].y), 0x000000FF);
			Novice::DrawLine(
				int(screenHeightVer[0].x), int(screenHeightVer[0].y), int(screenHeightVer[1].x),
				int(screenHeightVer[1].y), 0x000000FF);
		}
	}
}

/// 球体を描画する
void DrawSphere(const Sphere& sphere, 
	const Matrix4x4& viewProjection,const Matrix4x4& viewport,uint32_t color) {
	float pi = 3.14f;
	const uint32_t kSubdivision = 24;
	const float kLonEvery = (2 * pi) / kSubdivision;
	const float kLatEvery = pi / kSubdivision;

	// 緯度の方向に分割　-π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex; //	現在の緯度を求める

		// 経度の方向に分割　0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; //	現在の経度を求める

			Vector3 a = {
				cos(lat) * cos(lon) * sphere.radius, sin(lat) * sphere.radius,
				cos(lat) * sin(lon) * sphere.radius };
			Vector3 b = {
				cos(lat + (pi / kSubdivision)) * cos(lon) * sphere.radius,
				sin(lat + (pi / kSubdivision)) * sphere.radius,
				cos(lat + (pi / kSubdivision)) * sin(lon) * sphere.radius };
			Vector3 c = {
				cos(lat) * cos(lon + ((pi * 2) / kSubdivision)) * sphere.radius,
				sin(lat) * sphere.radius,
				cos(lat) * sin(lon + ((pi * 2) / kSubdivision)) * sphere.radius };

			// 球体の座標分移動させる
			a.x += sphere.center.x;
			a.y += sphere.center.y;
			a.z += sphere.center.z;
			b.x += sphere.center.x;
			b.y += sphere.center.y;
			b.z += sphere.center.z;
			c.x += sphere.center.x;
			c.y += sphere.center.y;
			c.z += sphere.center.z;

			// スクリーン座標系へ変換する
			a = Matrix4x4Funk::Transform(a, viewProjection);
			a = Matrix4x4Funk::Transform(a, viewport);
			b = Matrix4x4Funk::Transform(b, viewProjection);
			b = Matrix4x4Funk::Transform(b, viewport);
			c = Matrix4x4Funk::Transform(c, viewProjection);
			c = Matrix4x4Funk::Transform(c, viewport);

			// ab,bcで線を引く
			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);
		}
	}
}

void DrawPlane(const Plane& plane,
	const Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t color) {

	// <4頂点は以下の通りに求める>
	
	// 1.中心点を決める
	// 2.法線と垂直なベクトルを1つ求める
	// 3.2の逆ベクトルを求める
	// 4.2の法線とのクロス積を求める
	// 5.4の逆ベクトルを求める
	// 6.2~5のベクトルを中心点にそれぞれ定数倍してたスト4頂点が出来上がる

	Vector3 center = Scalar(plane.distance, plane.normal);		// 1
	Vector3 perpendiculars[4];
	perpendiculars[0] = Nomalize(Perpendicular(plane.normal));	// 2
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };	// 3
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);	// 4
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };	// 5
	// 6
	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++) {
		Vector3 extend = Scalar(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Matrix4x4Funk::Transform(Matrix4x4Funk::Transform(point, viewProjection), viewport);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);

	Novice::DrawEllipse((int)points[0].x, (int)points[0].y, 8, 8, 0.0f, 0xFF0000FF, kFillModeSolid);
	Novice::DrawEllipse((int)points[1].x, (int)points[1].y, 8, 8, 0.0f, 0x00FF00FF, kFillModeSolid);
	Novice::DrawEllipse((int)points[2].x, (int)points[2].y, 8, 8, 0.0f, 0x0000FFFF, kFillModeSolid);
	Novice::DrawEllipse((int)points[3].x, (int)points[3].y, 8, 8, 0.0f, 0xFF00FFFF, kFillModeSolid);

}

#pragma endregion

#pragma endregion