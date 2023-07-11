#pragma once
#include<Vector3.h>

/// <summary>
/// 球
/// </summary>
struct Sphere {
	Vector3 center;
	float radius;
};

/// <summary>
/// 平面
/// </summary>
struct Plane {
	Vector3 normal;// 法線
	float distance;// 距離
};

/// <summary>
/// 直線
/// </summary>
struct Line
{
	Vector3 origin;
	Vector3 diff;
};

/// <summary>
/// 半直線
/// </summary>
struct Ray
{
	Vector3 origin;
	Vector3 diff;
};

/// <summary>
/// 線分
/// </summary>
/// 
struct Segment
{
	Vector3 origin;
	Vector3 diff;
};

