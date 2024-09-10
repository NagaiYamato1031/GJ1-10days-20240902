#pragma once
#include <Utility/Mymath.h>
#include <Input.h>
#include <Model.h>
#include <Sprite.h>
#include "WorldTransform.h"
#include "Particle_PlayerBullet.h"
#include "list"

class ParticleEffects {
public: /*コンストラクタ*/
	ParticleEffects() = default;
	~ParticleEffects();

public: /*パブリック関数*/

	void Init();//初期化

	//頑張って自分で書いた奴{

	void CreateParticle_PlayerBullet(const Vector3& position,const float& rotationDeg);//パーティクルを生成

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

	//速さ
	float scalar_PlayerBullet_;
	//サイズ
	Vector3 scale_PlayerBullet_;
	//回転
	float rotate_PlayerBullet_;
	// 生存時間
	float lifeTime_PlayerBullet_;

	//生成間隔
	float interval_PlayerBullet_;
	float intervalBuff_PlayerBullet_;

	//生成ランダム範囲（正方向のみのサイズ
	int randomRenge_PlayerBullet_;

	//ランダムでずらす距離
	float randomFar_PlayerBullet_;

	//パーティクルのリスト
	std::list<Particle_PlayerBullet*> particle_PlayerBullets_;


};
