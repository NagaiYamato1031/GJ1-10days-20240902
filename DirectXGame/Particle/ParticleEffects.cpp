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

#pragma endregion

	model_ = Model::Create();

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

void ParticleEffects::CreateParticle_PlayerBullet(const Vector3& position,const float& rotationDeg) { 

	if (playerBullet_.intervalBuff <= 0) {
		playerBullet_.intervalBuff = playerBullet_.interval;

		Particle_PlayerBullet* newParticle = new Particle_PlayerBullet();
		newParticle->Init(playerBullet_.lifeTime, model_, position, playerBullet_.scalar, playerBullet_.scale, rotationDeg,playerBullet_.randomRenge,playerBullet_.randomFar);

		particle_PlayerBullets_.push_back(newParticle);
	}
	playerBullet_.intervalBuff--;
}


void ParticleEffects::UpdateParticle() {

	ImGui::Begin("ParticleWindow");
	ImGui::DragFloat("Scalar", &playerBullet_.scalar, 0.1f);
	ImGui::DragFloat("Rotate", &playerBullet_.rotation,0.1f);
	ImGui::DragFloat3("Scale", &playerBullet_.scale.x, 0.1f);
	ImGui::DragFloat("Intervall", &playerBullet_.interval, 0.1f);
	ImGui::DragFloat("LifeTime", &playerBullet_.lifeTime, 0.1f);
	ImGui::DragInt("RandomRenge", &playerBullet_.randomRenge, 0.1f);
	ImGui::DragFloat("RandomFar", &playerBullet_.randomFar, 0.1f);
	ImGui::End();

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
}

void ParticleEffects::DrawParticle(const ViewProjection* viewProjection) { 
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		particle_PlayerBullet->Draw(viewProjection);
	}
	for (Particle_EnemyBullet* particle_StandardBullet : particle_StandardBullets_) {
		particle_StandardBullet->Draw_Standard(viewProjection);
	}
}

void ParticleEffects::TestDelete() {
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		delete particle_PlayerBullet;
	}
	particle_PlayerBullets_.clear();
}
