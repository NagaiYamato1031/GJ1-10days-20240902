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
		0.5f//ランダムでずらす距離
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
	    0.5f  //  ランダムでずらす距離
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
	    0.5f  //  ランダムでずらす距離
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
	    0.5f  //  ランダムでずらす距離
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
	    0.5f  //  ランダムでずらす距離
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
	    0.5f  //  ランダムでずらす距離
	};

#pragma endregion

	model_ = Model::Create();

}



void ParticleEffects::CreateParticle_PlayerBullet(const Vector3& position,const float& rotationDeg) { 

	if (playerBullet_.intervalBuff <= 0) {
		playerBullet_.intervalBuff = playerBullet_.interval;

		Particle_PlayerBullet* newParticle = new Particle_PlayerBullet();
		newParticle->Init(playerBullet_.lifeTime, model_, position, playerBullet_.scalar, playerBullet_.scale, rotationDeg,playerBullet_.randomRenge,playerBullet_.randomFar);

		particle_PlayerBullets_.push_back(newParticle);
	}
	playerBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_StandardBullet(const Vector3& position, const float& rotationDeg) {

	if (standardBullet_.intervalBuff <= 0) {
		standardBullet_.intervalBuff = standardBullet_.interval;

		Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
		newParticle->Init_Standard(standardBullet_.lifeTime, model_, position, standardBullet_.scalar, standardBullet_.scale, rotationDeg, standardBullet_.randomRenge, standardBullet_.randomFar);

		particle_StandardBullets_.push_back(newParticle);
	}
	standardBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_ChaserBullet(const Vector3& position, const float& rotationDeg) {

	if (chaserBullet_.intervalBuff <= 0) {
		chaserBullet_.intervalBuff = chaserBullet_.interval;

		Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
		newParticle->Init_Chaser(chaserBullet_.lifeTime, model_, position, chaserBullet_.scalar, chaserBullet_.scale, rotationDeg, chaserBullet_.randomRenge, chaserBullet_.randomFar);

		particle_ChaserBullets_.push_back(newParticle);
	}
	chaserBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_FootpaceBullet(const Vector3& position, const float& rotationDeg) {
	if (footpaceBullet_.intervalBuff <= 0) {
		footpaceBullet_.intervalBuff = footpaceBullet_.interval;

		Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
		newParticle->Init_Footpace(footpaceBullet_.lifeTime, model_, position, footpaceBullet_.scalar, footpaceBullet_.scale, rotationDeg, footpaceBullet_.randomRenge, footpaceBullet_.randomFar);

		particle_FootpaceBullets_.push_back(newParticle);
	}
	footpaceBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_BoundBullet(const Vector3& position, const float& rotationDeg) {
	if (boundBullet_.intervalBuff <= 0) {
		boundBullet_.intervalBuff = boundBullet_.interval;

		Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
		newParticle->Init_Bound(boundBullet_.lifeTime, model_, position, boundBullet_.scalar, boundBullet_.scale, rotationDeg, boundBullet_.randomRenge, boundBullet_.randomFar);

		particle_BoundBullets_.push_back(newParticle);
	}
	boundBullet_.intervalBuff--;
}
void ParticleEffects::CreateParticle_BBBullet(const Vector3& position, const float& rotationDeg) {
	if (bbBullet_.intervalBuff <= 0) {
		boundBullet_.intervalBuff = bbBullet_.interval;

		Particle_EnemyBullet* newParticle = new Particle_EnemyBullet();
		newParticle->Init_BB(bbBullet_.lifeTime, model_, position, bbBullet_.scalar, bbBullet_.scale, rotationDeg, bbBullet_.randomRenge, bbBullet_.randomFar);

		particle_BBBullets_.push_back(newParticle);
	}
	bbBullet_.intervalBuff--;
}


void ParticleEffects::UpdateParticle() {

#ifdef _DEBUG
	ImGui::Begin("ParticleWindow");

	// プレイヤー
	ImGui::Text("PlayerBullet");
	ImGui::DragFloat("Scalar", &playerBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate", &playerBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale", &playerBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall", &playerBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime", &playerBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge", &playerBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar", &playerBullet_.randomFar, 0.1f);

	//通常弾
	ImGui::Text("StandardBullet");
	ImGui::DragFloat("Scalar", &standardBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate", &standardBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale", &standardBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall", &standardBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime", &standardBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge", &standardBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar", &standardBullet_.randomFar, 0.1f);

	// 追跡弾
	ImGui::Text("ChaserBullet");
	ImGui::DragFloat("Scalar", &chaserBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate", &chaserBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale", &chaserBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall", &chaserBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime", &chaserBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge", &chaserBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar", &chaserBullet_.randomFar, 0.1f);

	//持続弾 
	ImGui::Text("FootpaceBullet");
	ImGui::DragFloat("Scalar", &footpaceBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate", &footpaceBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale", &footpaceBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall", &footpaceBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime", &footpaceBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge", &footpaceBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar", &footpaceBullet_.randomFar, 0.1f);

	// バウンド弾
	ImGui::Text("BoundBullet");
	ImGui::DragFloat("Scalar", &boundBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate", &boundBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale", &boundBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall", &boundBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime", &boundBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge", &boundBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar", &boundBullet_.randomFar, 0.1f);

	// 大玉
	ImGui::Text("BBBullet");
	ImGui::DragFloat("Scalar", &bbBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate", &bbBullet_.rotation, 0.1f);
	ImGui::DragFloat3("Scale", &bbBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall", &bbBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime", &bbBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge", &bbBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar", &bbBullet_.randomFar, 0.1f);

	ImGui::End();
#endif // _DEBUG


	for (auto it = particle_PlayerBullets_.begin(); it != particle_PlayerBullets_.end();) {
		Particle_PlayerBullet* particle_PlayerBullet = *it;
		particle_PlayerBullet->Update();

		if (particle_PlayerBullet->IsBreak()) {
			delete particle_PlayerBullet;
			it = particle_PlayerBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_StandardBullets_.begin(); it != particle_StandardBullets_.end();) {
		Particle_EnemyBullet* particle_StandardBullet = *it;
		particle_StandardBullet->Update_Standard();

		if (particle_StandardBullet->IsBreak()) {
			delete particle_StandardBullet;
			it = particle_StandardBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_ChaserBullets_.begin(); it != particle_ChaserBullets_.end();) {
		Particle_EnemyBullet* particle_ChaserBullet = *it;
		particle_ChaserBullet->Update_Chaser();

		if (particle_ChaserBullet->IsBreak()) {
			delete particle_ChaserBullet;
			it = particle_ChaserBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_FootpaceBullets_.begin(); it != particle_FootpaceBullets_.end();) {
		Particle_EnemyBullet* particle_FootpaceBullet = *it;
		particle_FootpaceBullet->Update_Footpace();

		if (particle_FootpaceBullet->IsBreak()) {
			delete particle_FootpaceBullet;
			it = particle_FootpaceBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_BoundBullets_.begin(); it != particle_BoundBullets_.end();) {
		Particle_EnemyBullet* particle_BoundBullet = *it;
		particle_BoundBullet->Update_Bound();

		if (particle_BoundBullet->IsBreak()) {
			delete particle_BoundBullet;
			it = particle_BoundBullets_.erase(it);

		} else {
			++it;
		}
	}
	for (auto it = particle_BBBullets_.begin(); it != particle_BBBullets_.end();) {
		Particle_EnemyBullet* particle_BBBullet = *it;
		particle_BBBullet->Update_Bound();

		if (particle_BBBullet->IsBreak()) {
			delete particle_BBBullet;
			it = particle_BBBullets_.erase(it);

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
}
