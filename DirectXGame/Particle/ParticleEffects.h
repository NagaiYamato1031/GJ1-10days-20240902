#pragma once
#include <Utility/Mymath.h>
#include <Input.h>
#include <Model.h>
#include <Sprite.h>
//#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Particle_PlayerBullet.h"
#include "list"

class ParticleEffects {
public: /*コンストラクタ*/
	ParticleEffects() = default;
	~ParticleEffects();

public: /*パブリック関数*/

	//Player.hに書いてあったことをとりあえずそのまま書いた奴{
	void Init();
	//初期化
	//time：生存時間(フレーム計算)

	// Player.hに書いてあったことをとりあえずそのまま書いた奴}


	//頑張って自分で書いた奴{

	void CreateParticle_PlayerBullet(const Vector3& position);//パーティクルを生成

	void UpdateParticle();//生成したパーティクルを動かす

	void DrawParticle(const ViewProjection* viewProjection);//パーティクルを描画

	void TestDelete();//パーティクルを全削除

	// 頑張って自分で書いた奴}

private: /*メンバ変数*/
	//入力管理
	Input* input_ = nullptr;

	//3Dモデル
	Model* model_ = nullptr;

	//ワールド座標
	WorldTransform worldTransform_;

	//速度
	Vector3 velocity_;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//パーティクルのリスト
	std::list<Particle_PlayerBullet*> particle_PlayerBullets_;

	//生存時間
	float time_;
};
