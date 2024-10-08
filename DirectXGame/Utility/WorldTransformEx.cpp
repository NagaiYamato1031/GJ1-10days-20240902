#include "WorldTransform.h"

#include "Mymath.h"

using namespace ACJPN::Math;

void WorldTransform::UpdateMatrix() {

	// スケール、回転、平行移動
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	// 親があれば親のワールド行列をかける
	if (parent_) {
		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}

	// 定数バッファに転送する
	TransferMatrix();
}