#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

namespace ACJPN {
	namespace Math {

		/// <summary>
		/// 3x3 行列
		/// </summary>
		struct Matrix3x3 {
			float m[3][3];
		};

		/// <summary>
		/// 球体
		/// </summary>
		struct Sphere {
			Vector3 center;	// 中心
			float radius;	// 半径
		};

		/// <summary>
		/// 直線
		/// </summary>
		struct Line {
			Vector3 origin;	// 始点
			Vector3 diff;	// 終点への差分ベクトル
		};

		/// <summary>
		/// 半直線
		/// </summary>
		struct Ray {
			Vector3 origin;	// 始点
			Vector3 diff;	// 終点への差分ベクトル
		};

		/// <summary>
		/// 線分
		/// </summary>
		struct Segment {
			Vector3 origin;	// 始点
			Vector3 diff;	// 終点への差分ベクトル
		};

		struct Plane {
			Vector3 normal;	// 法線
			float distance;	// 距離
		};

	}
}