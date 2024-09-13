#pragma once

#include <Utility/Mymath.h>
#include <Model.h>
#include <WorldTransform.h>
class Particle_Background {
public: /*コンストラクタ*/
	Particle_Background() = default;
	~Particle_Background() = default;


public: /*メンバ関数*/
	void Init(Model* model, const Vector3& position, const float& scalar, const float& breakPos, const Vector3& scale);
	void Update();
	void DrawModel(const ViewProjection* viewProjection);

	bool IsBreak();
	// ３Dモデル
	Model* model_ = nullptr;
	// ワールド座標
	WorldTransform worldTransform_;
	// 速度
	Vector3 velocity_;
	//壊れる座標
	float breakPos_;

	// 破壊フラグ
	bool isBreak_;
};
