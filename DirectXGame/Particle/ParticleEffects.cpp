#include "ParticleEffects.h"

#include <ImGuiManager.h>
#include <TextureManager.h>


using namespace ACJPN;
using namespace ACJPN::Math;

ParticleEffects::~ParticleEffects() { 
	
}

void ParticleEffects::Init() { 
	#pragma region 弾の構造体
	//プレイヤーの弾
	playerBullet_={
	    0.3f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f,// 回転角
		30,//生存時間
		3.0f,//生成間隔(フレーム)
		0.0f,//生成間隔バッファ
		4,//ランダム範囲（正方向のみ
		0.5f,//ランダムでずらす距離
	    1, //  一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0,0,0}, //  小さくするときにいじるやつ
	};
	//通常弾
	standardBullet_ = {
	    0.3f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f, // 回転角
	    30, //  生存時間
	    3.0f, //  生成間隔(フレーム)
	    0.0f, //  生成間隔バッファ
	    4, //  ランダム範囲（正方向のみ
	    0.5f,  //  ランダムでずらす距離
	    1, //  一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0,0,0}, //  小さくするときにいじるやつ
	};
	//追跡弾
	chaserBullet_ = {
	    0.3f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f, // 回転角
	    30, //  生存時間
	    3.0f, //  生成間隔(フレーム)
	    0.0f, //  生成間隔バッファ
	    4, //  ランダム範囲（正方向のみ
	    0.5f,  //  ランダムでずらす距離
	    1, //  一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0,0,0 }, //  小さくするときにいじるやつ
	};
	//持続弾
	footpaceBullet_ = {
	    0.3f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f, // 回転角
	    30, //  生存時間
	    3.0f, //  生成間隔(フレーム)
	    0.0f, //  生成間隔バッファ
	    4, //  ランダム範囲（正方向のみ
	    0.5f,  //  ランダムでずらす距離
	    1, //  一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0,    0,    0   }, //  小さくするときにいじるやつ
	};
	//バウンド弾
	boundBullet_ = {
	    0.3f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f, // 回転角
	    30, //  生存時間
	    3.0f, //  生成間隔(フレーム)
	    0.0f, //  生成間隔バッファ
	    4, //  ランダム範囲（正方向のみ
	    0.5f,  //  ランダムでずらす距離
	    1, //  一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0,    0,    0   }, //  小さくするときにいじるやつ
	};
	//大玉
	bbBullet_ = {
	    0.3f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f, // 回転角
	    30, //  生存時間
	    3.0f, //  生成間隔(フレーム)
	    0.0f, //  生成間隔バッファ
	    4, //  ランダム範囲（正方向のみ
	    0.5f,  //  ランダムでずらす距離
	    1, //  一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0,    0,    0   }, //  小さくするときにいじるやつ
	};

#pragma endregion

	wave_ = {
	    0.3f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f, // 回転角
	    30, //  生存時間
	    3.0f, //  生成間隔(フレーム)
	    0.0f, //  生成間隔バッファ
	    0, //  ランダム範囲（正方向のみ
	    0.0f,  //  ランダムでずらす距離
		3,//一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0,    0,    0   }, //  小さくするときにいじるやつ
	};

	conflict_ = {
	    0.6f, // 速さ
	    {1.0f, 1.0f, 1.0f}, // サイズ
	    0.0f, // 回転角
	    30, //  生存時間
	    3.0f, //  生成間隔(フレーム)
	    0.0f, //  生成間隔バッファ
	    0, //  ランダム範囲（正方向のみ
	    0.0f, //  ランダムでずらす距離
	    20, //  一度に生成する数(波とぶつかった時のエフェクトで使用するよ～
	    {0.08f,    0.08f,    0.08f   }, //  小さくするときにいじるやつ
	};


	model_ = Model::Create();

}



void ParticleEffects::CreateParticle_PlayerBullet(const Vector3& position,const float& rotationDeg) { 

	if (playerBullet_.intervalBuff <= 0) {
		playerBullet_.intervalBuff = playerBullet_.interval;

		for (int i = 0; i < playerBullet_.createCount; i++) {
			Particle_PlayerBullet* newParticle = new Particle_PlayerBullet();
			Vector3 createPos = Vector3(((position.x + (playerBullet_.scale.x * i * 2)) - (playerBullet_.scale.x * 2.0f * (playerBullet_.createCount - 1.0f) / 2.0f)), position.y, position.z);
			newParticle->Init(playerBullet_.lifeTime, model_, createPos, playerBullet_.scalar, playerBullet_.scale, rotationDeg, playerBullet_.randomRenge, playerBullet_.randomFar);
			particle_PlayerBullets_.push_back(newParticle);
		}
	}
	playerBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_StandardBullet(const Vector3& position, const float& rotationDeg) {

	if (standardBullet_.intervalBuff <= 0) {
		standardBullet_.intervalBuff = standardBullet_.interval;

		for (int i = 0; i < standardBullet_.createCount; i++) {
			Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
			Vector3 createPos = Vector3(((position.x + (standardBullet_.scale.x * i * 2)) - (standardBullet_.scale.x * 2.0f * (standardBullet_.createCount - 1.0f) / 2.0f)), position.y, position.z);
			newParticle->Init_Standard(standardBullet_.lifeTime, model_, createPos, standardBullet_.scalar, standardBullet_.scale, rotationDeg, standardBullet_.randomRenge, standardBullet_.randomFar);
			particle_StandardBullets_.push_back(newParticle);
		}
	}
	standardBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_ChaserBullet(const Vector3& position, const float& rotationDeg) {

	if (chaserBullet_.intervalBuff <= 0) {
		chaserBullet_.intervalBuff = chaserBullet_.interval;

		for (int i = 0; i < chaserBullet_.createCount; i++) {
			Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
			Vector3 createPos = Vector3(((position.x + (chaserBullet_.scale.x * i * 2)) - (chaserBullet_.scale.x * 2.0f * (chaserBullet_.createCount - 1.0f) / 2.0f)), position.y, position.z);
			newParticle->Init_Chaser(chaserBullet_.lifeTime, model_, createPos, chaserBullet_.scalar, chaserBullet_.scale, rotationDeg, chaserBullet_.randomRenge, chaserBullet_.randomFar);
			particle_ChaserBullets_.push_back(newParticle);
		}
	}
	chaserBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_FootpaceBullet(const Vector3& position, const float& rotationDeg) {
	if (footpaceBullet_.intervalBuff <= 0) {
		footpaceBullet_.intervalBuff = footpaceBullet_.interval;

		for (int i = 0; i < footpaceBullet_.createCount; i++) {
			Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
			Vector3 createPos = Vector3(((position.x + (footpaceBullet_.scale.x * i * 2)) - (footpaceBullet_.scale.x * 2.0f * (footpaceBullet_.createCount - 1.0f) / 2.0f)), position.y, position.z);
			newParticle->Init_Footpace(footpaceBullet_.lifeTime, model_, createPos, footpaceBullet_.scalar, footpaceBullet_.scale, rotationDeg, footpaceBullet_.randomRenge, footpaceBullet_.randomFar);
			particle_FootpaceBullets_.push_back(newParticle);
		}
	}
	footpaceBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_BoundBullet(const Vector3& position, const float& rotationDeg) {
	if (boundBullet_.intervalBuff <= 0) {
		boundBullet_.intervalBuff = boundBullet_.interval;

		for (int i = 0; i < boundBullet_.createCount; i++) {
			Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
			Vector3 createPos = Vector3(((position.x + (boundBullet_.scale.x * i * 2)) - (boundBullet_.scale.x * 2.0f * (boundBullet_.createCount - 1.0f) / 2.0f)), position.y, position.z);
			newParticle->Init_Bound(boundBullet_.lifeTime, model_, createPos, boundBullet_.scalar, boundBullet_.scale, rotationDeg, boundBullet_.randomRenge, boundBullet_.randomFar);
			particle_BoundBullets_.push_back(newParticle);
		}
	}
	boundBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_BBBullet(const Vector3& position, const float& rotationDeg) {
	if (bbBullet_.intervalBuff <= 0) {
		boundBullet_.intervalBuff = bbBullet_.interval;

		for (int i = 0; i < bbBullet_.createCount; i++) {
			Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
			Vector3 createPos = Vector3(((position.x + (bbBullet_.scale.x * i * 2)) - (bbBullet_.scale.x * 2.0f * (bbBullet_.createCount - 1.0f) / 2.0f)), position.y, position.z);
			newParticle->Init_BB(bbBullet_.lifeTime, model_, createPos, bbBullet_.scalar, bbBullet_.scale, rotationDeg, bbBullet_.randomRenge, bbBullet_.randomFar);
			particle_BBBullets_.push_back(newParticle);
		}
	}
	bbBullet_.intervalBuff--;
}

void ParticleEffects::CreateParticle_Wave(const Vector3& position, const float& rotationDeg) {
	if (wave_.intervalBuff <= 0) {
		wave_.intervalBuff = wave_.interval;

		for (int i = 0; i < wave_.createCount; i++) {
			Particle_Wave* newParticle = new Particle_Wave();
			Vector3 createPos = Vector3(((position.x + (wave_.scale.x * i * 2)) - (wave_.scale.x * 2.0f * (wave_.createCount - 1.0f) / 2.0f)), position.y, position.z);
			newParticle->Init(wave_.lifeTime, model_, createPos, wave_.scalar, wave_.scale, rotationDeg, wave_.randomRenge, wave_.randomFar);
			particle_Waves_.push_back(newParticle);
		}
	}
	bbBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_Conflict(const Vector3& position, const float& rotationDeg) {
	for (int i = 0; i < conflict_.createCount; i++) {
		Particle_Conflict* newParticle = new Particle_Conflict();
		float createDeg = 0;
		createDeg = (float)(rand() % 360);
		
		newParticle->Init(conflict_.lifeTime, model_, position, conflict_.scalar, conflict_.scale, rotationDeg+createDeg, conflict_.randomRenge, conflict_.randomFar);
		particle_Conflicts_.push_back(newParticle);
	}
}

void ParticleEffects::UpdateParticle() {

#ifdef _DEBUG
	ImGui::Begin("ParticleWindow");
	#pragma region 弾
	// プレイヤー
	ImGui::Text("PlayerBullet");
	ImGui::DragFloat("Scalar_PlayerBullet", &playerBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_PlayerBullet", &playerBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_PlayerBullet", &playerBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_PlayerBullet", &playerBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_PlayerBullet", &playerBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_PlayerBullet", &playerBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_PlayerBullet", &playerBullet_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_PlayerBullet", &playerBullet_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_PlayerBullet", &playerBullet_.shrinkScale.x, 0.01f);

	//通常弾
	ImGui::Text("StandardBullet");
	ImGui::DragFloat("Scalar_StandardBullet", &standardBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_StandardBullet", &standardBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_StandardBullet", &standardBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_StandardBullet", &standardBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_StandardBullet", &standardBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_StandardBullet", &standardBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_StandardBullet", &standardBullet_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_StandardBullet", &standardBullet_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_StandardBullet", &standardBullet_.shrinkScale.x, 0.01f);

	// 追跡弾
	ImGui::Text("ChaserBullet");
	ImGui::DragFloat("Scalar_ChaserBullet", &chaserBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_ChaserBullet", &chaserBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_ChaserBullet", &chaserBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_ChaserBullet", &chaserBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_ChaserBullet", &chaserBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_ChaserBullet", &chaserBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_ChaserBullet", &chaserBullet_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_ChaserBullet", &chaserBullet_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_ChaserBullet", &chaserBullet_.shrinkScale.x, 0.01f);

	//持続弾 
	ImGui::Text("FootpaceBullet");
	ImGui::DragFloat("Scalar_FootpaceBullet", &footpaceBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_FootpaceBullet", &footpaceBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_FootpaceBullet", &footpaceBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_FootpaceBullet", &footpaceBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_FootpaceBullet", &footpaceBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_FootpaceBullet", &footpaceBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_FootpaceBullet", &footpaceBullet_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_FootpaceBullet", &footpaceBullet_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_FootpaceBullet", &footpaceBullet_.shrinkScale.x, 0.01f);

	// バウンド弾
	ImGui::Text("BoundBullet");
	ImGui::DragFloat("Scalar_BoundBullet", &boundBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_BoundBullet", &boundBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_BoundBullet", &boundBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_BoundBullet", &boundBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_BoundBullet", &boundBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_BoundBullet", &boundBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_BoundBullet", &boundBullet_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_BoundBullet", &boundBullet_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_BoundBullet", &boundBullet_.shrinkScale.x, 0.01f);

	// 大玉
	ImGui::Text("BBBullet");
	ImGui::DragFloat("Scalar_BBBullet", &bbBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_BBBullet", &bbBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_BBBullet", &bbBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_BBBullet", &bbBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_BBBullet", &bbBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_BBBullet", &bbBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_BBBullet", &bbBullet_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_BBBullet", &bbBullet_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_BBBullet", &bbBullet_.shrinkScale.x, 0.01f);

#pragma endregion

	// 波
	ImGui::Text("Wave");
	ImGui::DragFloat("Scalar_Wave", &wave_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_Wave", &wave_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_Wave", &wave_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_Wave", &wave_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_Wave", &wave_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_Wave", &wave_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_Wave", &wave_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_Wave", &wave_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_Wave", &wave_.shrinkScale.x, 0.01f);

	//衝突
	ImGui::Text("Conflict_");
	ImGui::DragFloat("Scalar_Conflict", &conflict_.scalar, 0.1f);
	ImGui::DragFloat("Rotate_Conflict", &conflict_.rotation, 0.1f);
	ImGui::DragFloat3("Scale_Conflict", &conflict_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall_Conflict", &conflict_.interval, 0.1f);
	ImGui::DragFloat("LifeTime_Conflict", &conflict_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge_Conflict", &conflict_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar_Conflict", &conflict_.randomFar, 0.1f);
	ImGui::DragInt("CreateCount_Conflict", &conflict_.createCount, 1);
	ImGui::DragFloat3("ShrinkScale_Conflict", &conflict_.shrinkScale.x, 0.01f);



	ImGui::End();

#endif // _DEBUG


	for (auto it = particle_PlayerBullets_.begin(); it != particle_PlayerBullets_.end();) {
		Particle_PlayerBullet* particle_PlayerBullet = *it;
		particle_PlayerBullet->Update(playerBullet_.shrinkScale);

		if (particle_PlayerBullet->IsBreak()) {
			delete particle_PlayerBullet;
			it = particle_PlayerBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_StandardBullets_.begin(); it != particle_StandardBullets_.end();) {
		Particle_EnemyBullet* particle_StandardBullet = *it;
		particle_StandardBullet->Update_Standard(standardBullet_.shrinkScale);

		if (particle_StandardBullet->IsBreak()) {
			delete particle_StandardBullet;
			it = particle_StandardBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_ChaserBullets_.begin(); it != particle_ChaserBullets_.end();) {
		Particle_EnemyBullet* particle_ChaserBullet = *it;
		particle_ChaserBullet->Update_Chaser(chaserBullet_.shrinkScale);

		if (particle_ChaserBullet->IsBreak()) {
			delete particle_ChaserBullet;
			it = particle_ChaserBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_FootpaceBullets_.begin(); it != particle_FootpaceBullets_.end();) {
		Particle_EnemyBullet* particle_FootpaceBullet = *it;
		particle_FootpaceBullet->Update_Footpace(footpaceBullet_.shrinkScale);

		if (particle_FootpaceBullet->IsBreak()) {
			delete particle_FootpaceBullet;
			it = particle_FootpaceBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_BoundBullets_.begin(); it != particle_BoundBullets_.end();) {
		Particle_EnemyBullet* particle_BoundBullet = *it;
		particle_BoundBullet->Update_Bound(boundBullet_.shrinkScale);

		if (particle_BoundBullet->IsBreak()) {
			delete particle_BoundBullet;
			it = particle_BoundBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_BBBullets_.begin(); it != particle_BBBullets_.end();) {
		Particle_EnemyBullet* particle_BBBullet = *it;
		particle_BBBullet->Update_Bound(bbBullet_.shrinkScale);

		if (particle_BBBullet->IsBreak()) {
			delete particle_BBBullet;
			it = particle_BBBullets_.erase(it);

		} else {
			++it;
		}
	}

	for (auto it = particle_Waves_.begin(); it != particle_Waves_.end();) {
		Particle_Wave* particle_Wave = *it;
		particle_Wave->Update(wave_.shrinkScale);

		if (particle_Wave->IsBreak()) {
			delete particle_Wave;
			it = particle_Waves_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_Conflicts_.begin(); it != particle_Conflicts_.end();) {
		Particle_Conflict* particle_Conflict = *it;
		particle_Conflict->Update(conflict_.shrinkScale);

		if (particle_Conflict->IsBreak()) {
			delete particle_Conflict;
			it = particle_Conflicts_.erase(it);

		} else {
			++it;
		}
	}
}

void ParticleEffects::DrawParticle(const ViewProjection* viewProjection) { 
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		particle_PlayerBullet->Draw(viewProjection);
	}
	for (Particle_EnemyBullet* particle_StandardBullet : particle_StandardBullets_) {
		particle_StandardBullet->Draw_Standard(viewProjection);
	}
	for (Particle_EnemyBullet* particle_ChaserBullet : particle_ChaserBullets_) {
		particle_ChaserBullet->Draw_Chaser(viewProjection);
	}
	for (Particle_EnemyBullet* particle_FootpaceBullet : particle_FootpaceBullets_) {
		particle_FootpaceBullet->Draw_Footpace(viewProjection);
	}
	for (Particle_EnemyBullet* particle_BoundBullet : particle_BoundBullets_) {
		particle_BoundBullet->Draw_Bound(viewProjection);
	}
	for (Particle_EnemyBullet* particle_BBBullet : particle_BBBullets_) {
		particle_BBBullet->Draw_BB(viewProjection);
	}

	for (Particle_Wave* particle_Wave : particle_Waves_) {
		particle_Wave->Draw(viewProjection);
	}
	for (Particle_Conflict* particle_Conflict : particle_Conflicts_) {
		particle_Conflict->Draw(viewProjection);
	}
}

void ParticleEffects::TestDelete() {
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		delete particle_PlayerBullet;
	}
	particle_PlayerBullets_.clear();
	for (Particle_EnemyBullet* particle_StandardBullet : particle_StandardBullets_) {
		delete particle_StandardBullet;
	}
	particle_StandardBullets_.clear();
	for (Particle_EnemyBullet* particle_ChaserBullet : particle_ChaserBullets_) {
		delete particle_ChaserBullet;
	}
	particle_ChaserBullets_.clear();
	for (Particle_EnemyBullet* particle_FootpaceBullet : particle_FootpaceBullets_) {
		delete particle_FootpaceBullet;
	}
	particle_ChaserBullets_.clear();
	for (Particle_EnemyBullet* particle_BoundBullet : particle_BoundBullets_) {
		delete particle_BoundBullet;
	}
	particle_BoundBullets_.clear();
	for (Particle_EnemyBullet* particle_BoundBullet : particle_BoundBullets_) {
		delete particle_BoundBullet;
	}
	particle_BBBullets_.clear();

	for (Particle_Wave* particle_Wave : particle_Waves_) {
		delete particle_Wave;
	}
	particle_Waves_.clear();
	for (Particle_Conflict* particle_Conflict : particle_Conflicts_) {
		delete particle_Conflict;
	}
	particle_Waves_.clear();
}
