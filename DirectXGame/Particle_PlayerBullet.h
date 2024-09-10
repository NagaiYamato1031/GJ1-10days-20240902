#pragma once
#include <Utility/Mymath.h>
#include <Input.h>
#include <Model.h>
#include <WorldTransform.h>
class Particle_PlayerBullet {
public: /*コンストラクタ*/
	Particle_PlayerBullet() = default;
	~Particle_PlayerBullet();

public: /*パブリック関数*/

	void Init(Model *model,const Vector3& position);   // 初期化
	void Update();                        // 更新
	void Draw( const ViewProjection* viewProjection);//描画

private: /*メンバ変数*/
	// 入力管理
	Input* input_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;

	// ワールド座標
	WorldTransform worldTransform_;


	uint32_t textureHandle_ = 0;
};
