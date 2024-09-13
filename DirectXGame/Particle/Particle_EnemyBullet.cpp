#include "Particle_EnemyBullet.h"

#include <ImGuiManager.h>
#include <TextureManager.h>
#include <time.h>
#include <random>

using namespace ACJPN;
using namespace ACJPN::Math;

//通常弾
void Particle_EnemyBullet::Init_Standard(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Particle/standard_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	float distance = 0;
	if (randomRange != 0) {
		int rand_ = (rand() % (randomRange * 2)) - randomRange;
		distance = rand_ * randomFar;
	}


	// 速さ速度変換
	velocity_ = Vector3(scalar * sinf(rotate), -scalar * cosf(rotate), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate);
}
void Particle_EnemyBullet::Update_Standard(const Vector3& shrinkScale) {
	// 速度加算
	worldTransform_.translation_ += velocity_;
	// サイズ減算
	if (worldTransform_.scale_.x > 0) {
		worldTransform_.scale_ -= shrinkScale;
		if (worldTransform_.scale_.x < 0) {
			worldTransform_.scale_ = Vector3(0.0f, 0.0f, 0.0f);
		}
	}
	// 壊れるまでの時間計算
	time_--;
	if (time_ <= 0) {
		isBreak_ = true;
	}

	// ワールドマトリックス更新
	worldTransform_.UpdateMatrix();
}
void Particle_EnemyBullet::Draw_Standard(const ViewProjection* viewProjection) { 
	model_->Draw(worldTransform_, *viewProjection, textureHandle_); 
}

//追跡弾
void Particle_EnemyBullet::Init_Chaser(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Particle/chaser_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	float distance = 0;
	if (randomRange != 0) {
		int rand_ = (rand() % (randomRange * 2)) - randomRange;
		distance = rand_ * randomFar;
	}


	// 速さ速度変換
	velocity_ = Vector3(scalar * sinf(rotate), -scalar * cosf(rotate), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate);
}
void Particle_EnemyBullet::Update_Chaser(const Vector3& shrinkScale) {
	// 速度加算
	worldTransform_.translation_ += velocity_;
	// サイズ減算
	if (worldTransform_.scale_.x > 0) {
		worldTransform_.scale_ -= shrinkScale;
		if (worldTransform_.scale_.x < 0) {
			worldTransform_.scale_ = Vector3(0.0f, 0.0f, 0.0f);
		}
	}
	// 壊れるまでの時間計算
	time_--;
	if (time_ <= 0) {
		isBreak_ = true;
	}

	// ワールドマトリックス更新
	worldTransform_.UpdateMatrix();
}
void Particle_EnemyBullet::Draw_Chaser(const ViewProjection* viewProjection) {
	model_->Draw(worldTransform_, *viewProjection, textureHandle_); 
}

//持続弾
void Particle_EnemyBullet::Init_Footpace(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Particle/footpace_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	float distance = 0;
	if (randomRange != 0) {
		int rand_ = (rand() % (randomRange * 2)) - randomRange;
		distance = rand_ * randomFar;
	}


	// 速さ速度変換
	velocity_ = Vector3(scalar * sinf(rotate), -scalar * cosf(rotate), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate);
}
void Particle_EnemyBullet::Update_Footpace(const Vector3& shrinkScale) {
	// 速度加算
	worldTransform_.translation_ += velocity_;
	// サイズ減算
	if (worldTransform_.scale_.x > 0) {
		worldTransform_.scale_ -= shrinkScale;
		if (worldTransform_.scale_.x < 0) {
			worldTransform_.scale_ = Vector3(0.0f, 0.0f, 0.0f);
		}
	}
	// 壊れるまでの時間計算
	time_--;
	if (time_ <= 0) {
		isBreak_ = true;
	}

	// ワールドマトリックス更新
	worldTransform_.UpdateMatrix();
}
void Particle_EnemyBullet::Draw_Footpace(const ViewProjection* viewProjection) {
	model_->Draw(worldTransform_, *viewProjection, textureHandle_); 
}

//バウンド弾
void Particle_EnemyBullet::Init_Bound(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Particle/Bound_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	float distance = 0;
	if (randomRange != 0) {
		int rand_ = (rand() % (randomRange * 2)) - randomRange;
		distance = rand_ * randomFar;
	}


	// 速さ速度変換
	velocity_ = Vector3(scalar * sinf(rotate), -scalar * cosf(rotate), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate);
}
void Particle_EnemyBullet::Update_Bound(const Vector3& shrinkScale) {
	// 速度加算
	worldTransform_.translation_ += velocity_;
		//サイズ減算
	if (worldTransform_.scale_.x > 0){
		worldTransform_.scale_ -= shrinkScale;
		if (worldTransform_.scale_.x < 0) {
			worldTransform_.scale_ = Vector3(0.0f, 0.0f, 0.0f);
		}
	}
	// 壊れるまでの時間計算
	time_--;
	if (time_ <= 0) {
		isBreak_ = true;
	}

	// ワールドマトリックス更新
	worldTransform_.UpdateMatrix();
}
void Particle_EnemyBullet::Draw_Bound(const ViewProjection* viewProjection) {
	model_->Draw(worldTransform_, *viewProjection, textureHandle_); 
}

//大玉
void Particle_EnemyBullet::Init_BB(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Particle/bb_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	float distance = 0;
	if (randomRange != 0) {
		int rand_ = (rand() % (randomRange * 2)) - randomRange;
		distance = rand_ * randomFar;
	}


	// 速さ速度変換
	velocity_ = Vector3(scalar * sinf(rotate), -scalar * cosf(rotate), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate);
}
void Particle_EnemyBullet::Update_BB(const Vector3& shrinkScale) {
	// 速度加算
	worldTransform_.translation_ += velocity_;
	// サイズ減算
	if (worldTransform_.scale_.x > 0) {
		worldTransform_.scale_ -= shrinkScale;
		if (worldTransform_.scale_.x < 0) {
			worldTransform_.scale_ = Vector3(0.0f, 0.0f, 0.0f);
		}
	}
	// 壊れるまでの時間計算
	time_--;
	if (time_ <= 0) {
		isBreak_ = true;
	}

	// ワールドマトリックス更新
	worldTransform_.UpdateMatrix();
}
void Particle_EnemyBullet::Draw_BB(const ViewProjection* viewProjection) { 
	model_->Draw(worldTransform_, *viewProjection, textureHandle_); 
}



bool Particle_EnemyBullet::IsBreak() { 
	if (isBreak_) {
		return true;
	} 
	else {
		return false;
	}
}

float Particle_EnemyBullet::ToRadian(float angle) {
	return angle * 3.14159265359f / 180.0f;
}
