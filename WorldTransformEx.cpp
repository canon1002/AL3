﻿#include "WorldTransform.h"
#include "./class/Matrix4.h"

/// 行列を計算・転送する
void WorldTransform::UpdateMatrix() {

	// スケール・回転・平行移動を合成して行列を計算する
	matWorld_ = Matrix4::MakeAffineMatrix(scale_, rotation_, translation_);
	// 定数バッファに転送
	TransferMatrix();

}