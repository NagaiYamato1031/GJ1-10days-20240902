#include "Particle_EnemyBullet.h"

#include <ImGuiManager.h>
#include <TextureManager.h>
#include <time.h>
#include <random>

using namespace ACJPN;
using namespace ACJPN::Math;

void Particle_EnemyBullet::Init_Standard(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("standard_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	int rand_ = (rand() % (randomRange * 2)) - randomRange;
	float distance = rand_ * randomFar;

	float rotate_ = ToRadian(rotate);
	// 速さ速度変換
	velocity_ = Vector3(scalar * sinf(rotate_), -scalar * cosf(rotate_), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate_), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate_);
}
void Particle_EnemyBullet::Update_Standard() {
	// 速度加算
	worldTransform_.translation_ += velocity_;

	// なんか書いてあった奴をまねて書いた奴ら
	ImGui::Begin("StandardEnemyBulletParticleWindow");

	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	ImGui::Checkbox(" isBreak", &isBreak_);

	ImGui::End();

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


void Particle_EnemyBullet::Init_Chaser(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Sample_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	int rand_ = (rand() % (randomRange * 2)) - randomRange;
	float distance = rand_ * randomFar;

	float rotate_ = ToRadian(rotate);
	// 速さ速度変換
	velocity_ = Vector3(-scalar * sinf(rotate_), scalar * cosf(rotate_), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate_), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate_);
}
void Particle_EnemyBullet::Update_Chaser() {
	// 速度加算
	worldTransform_.translation_ += velocity_;

	// なんか書いてあった奴をまねて書いた奴ら
	ImGui::Begin("StandardEnemyBulletParticleWindow");

	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	ImGui::Checkbox(" isBreak", &isBreak_);

	ImGui::End();

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


void Particle_EnemyBullet::Init_Footpace(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Sample_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	int rand_ = (rand() % (randomRange * 2)) - randomRange;
	float distance = rand_ * randomFar;

	float rotate_ = ToRadian(rotate);
	// 速さ速度変換
	velocity_ = Vector3(-scalar * sinf(rotate_), scalar * cosf(rotate_), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate_), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate_);
}
void Particle_EnemyBullet::Update_Footpace() {
	// 速度加算
	worldTransform_.translation_ += velocity_;

	// なんか書いてあった奴をまねて書いた奴ら
	ImGui::Begin("StandardEnemyBulletParticleWindow");

	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	ImGui::Checkbox(" isBreak", &isBreak_);

	ImGui::End();

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


void Particle_EnemyBullet::Init_Bound(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Sample_Bullet.png");

	// 生存時間受け取り
	time_ = time;

	// ランダム生成
	int rand_ = (rand() % (randomRange * 2)) - randomRange;
	float distance = rand_ * randomFar;

	float rotate_ = ToRadian(rotate);
	// 速さ速度変換
	velocity_ = Vector3(-scalar * sinf(rotate_), scalar * cosf(rotate_), 0);
	Vector3 disranceVec = Vector3(distance * cosf(rotate_), distance * sinf(rotate), 0);

	// 破壊フラグ初期化
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(position.x + disranceVec.x, position.y + disranceVec.y, position.z + disranceVec.z);
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = Vector3(0, 0, rotate_);
}
void Particle_EnemyBullet::Update_Bound() {
	// 速度加算
	worldTransform_.translation_ += velocity_;

	// なんか書いてあった奴をまねて書いた奴ら
	ImGui::Begin("StandardEnemyBulletParticleWindow");

	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	ImGui::Checkbox(" isBreak", &isBreak_);

	ImGui::End();

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
