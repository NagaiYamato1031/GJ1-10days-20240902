#pragma once
#include <Utility/Mymath.h>
#include <Input.h>
#include <Model.h>
#include <Sprite.h>
#include "WorldTransform.h"
#include "Particle_PlayerBullet.h"
#include "Particle_EnemyBullet.h"
#include "list"

struct BulletParticle {
float scalar;       // 速さ
Vector3 scale;      // サイズ
float rotation;     // 回転
float lifeTime;     // 生存時間
float interval;     // 生成間隔
float intervalBuff; // 生成間隔のバッファ
int randomRenge;    // 生成ランダム範囲
float randomFar;    // ランダムでずらす距離
};


class ParticleEffects {
public: /*コンストラクタ*/
	ParticleEffects() = default;
	~ParticleEffects();



public: /*パブリック関数*/

	void Init();//初期化

	//頑張って自分で書いた奴{

	void CreateParticle_StandardBullet(const Vector3& position, const float& rotationDeg);
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

	//パーティクルに必要な変数類
	BulletParticle playerBullet_;//プレイヤーの弾
	BulletParticle standardBullet_;//通常弾
	BulletParticle chaserBullet_;//追跡弾
	BulletParticle footpaceBullet_;//持続弾
	BulletParticle boundBullet_;//バウンド弾


	//パーティクルのリスト
	std::list<Particle_PlayerBullet*> particle_PlayerBullets_;//プレイヤーの弾
	std::list<Particle_EnemyBullet*> particle_StandardBullets_;//通常弾
	std::list<Particle_EnemyBullet*> particle_ChaserBullets_;//追跡弾
	std::list<Particle_EnemyBullet*> particle_FootpaceBullets_;//持続弾
	std::list<Particle_EnemyBullet*> particle_BoundBullets_;//バウンド弾


};
