#pragma once
#include <Utility/Mymath.h>
#include <Input.h>
#include <Model.h>
#include <Sprite.h>
#include "WorldTransform.h"
#include "Particle_PlayerBullet.h"
#include "Particle_EnemyBullet.h"
#include "Particle_Wave.h"
#include "Particle_Conflict.h"
#include "Particle_Background.h"
#include "list"

struct Particle {
	float scalar;// 速さ
	Vector3 scale;// サイズ
	float rotation;// 回転
	float lifeTime;// 生存時間
	float interval;// 生成間隔
	float intervalBuff; // 生成間隔のバッファ
	int randomRenge;// 生成ランダム範囲
	float randomFar;// ランダムでずらす距離
	int createCount;//一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	Vector3 shrinkScale;//小さくするやつ

	
	Vector3 createPos;        // 背景用発生位置
	float breakPos;         // 背景用消滅位置
	Model *model_tetrahedron; // 背景用モデル正四面体
	Model *model_hexahedron;//背景用モデル正六面体
	Model *model_dodecahedron;//背景用モデル正十二面体
};




class ParticleEffects {
public: /*コンストラクタ*/
	ParticleEffects() = default;
	~ParticleEffects();



public: /*パブリック関数*/

	void Init();//初期化

	//頑張って自分で書いた奴{


	void CreateParticle_PlayerBullet(const Vector3& position,const float& rotationDeg);//パーティクルを生成
	void CreateParticle_StandardBullet(const Vector3& position, const float& rotationDeg);
	void CreateParticle_ChaserBullet(const Vector3& position, const float& rotationDeg);
	void CreateParticle_FootpaceBullet(const Vector3& position, const float& rotationDeg);
	void CreateParticle_BoundBullet(const Vector3& position, const float& rotationDeg);
	void CreateParticle_BBBullet(const Vector3& position, const float& rotationDeg);

	void CreateParticle_Wave(const Vector3& position, const float& rotationDeg);
	void CreateParticle_Conflict(const Vector3& position, const float& rotationDeg);
	void CreatParticle_Background();


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
	Particle playerBullet_;//プレイヤーの弾
	Particle standardBullet_;//通常弾
	Particle chaserBullet_;//追跡弾
	Particle footpaceBullet_;//持続弾
	Particle boundBullet_;//バウンド弾
	Particle bbBullet_; //大玉
	Particle wave_;//波攻撃
	Particle conflict_;//弾と弾がぶつかった時のやつ
	Particle background_;



	//パーティクルのリスト
	std::list<Particle_PlayerBullet*> particle_PlayerBullets_;//プレイヤーの弾
	std::list<Particle_EnemyBullet*> particle_StandardBullets_;//通常弾
	std::list<Particle_EnemyBullet*> particle_ChaserBullets_;//追跡弾
	std::list<Particle_EnemyBullet*> particle_FootpaceBullets_;//持続弾
	std::list<Particle_EnemyBullet*> particle_BoundBullets_;//バウンド弾
	std::list<Particle_EnemyBullet*> particle_BBBullets_;//大玉


	std::list<Particle_Wave*> particle_Waves_; // 波
	std::list<Particle_Conflict*> particle_Conflicts_;//衝突
	std::list<Particle_Background*> particle_Backgrounds_;

};
