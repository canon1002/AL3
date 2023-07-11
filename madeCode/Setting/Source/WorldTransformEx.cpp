﻿#include "WorldTransform.h"
#include "madeCode/Math/Heder/Matrix4x4Funk.h"

/// 行列を計算・転送する
void WorldTransform::UpdateMatrix() {

	// スケール・回転・平行移動を合成して行列を計算する
	matWorld_ = Matrix4x4Funk::MakeAffineMatrix(scale_, rotation_, translation_);

	// 親があれば親のワールド行列を掛ける
	if (parent_) {
		matWorld_ = Matrix4x4Funk::Multiply(matWorld_, parent_->matWorld_);
	}

	// 定数バッファに転送
	TransferMatrix();

}