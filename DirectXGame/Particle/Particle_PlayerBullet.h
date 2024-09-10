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

	void Init(float time,Model *model,const Vector3& position,const Vector3& velocity);   // 初期化
	void Update();                        // 更新
	void Draw( const ViewProjection* viewProjection);//描画

	bool IsBreak();//フラグ管理

private: /*メンバ変数*/
	// 入力管理
	Input* input_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;

	// ワールド座標
	WorldTransform worldTransform_;

	//速度
	Vector3 velocity_;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//破壊フラグ
	bool isBreak_;
	
	//生存時間受け取り用
	float time_;
};
