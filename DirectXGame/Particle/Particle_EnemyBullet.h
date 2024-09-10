#pragma once
#include <Utility/Mymath.h>
#include <Model.h>
#include <WorldTransform.h>
class Particle_EnemyBullet {
public:
	Particle_EnemyBullet()=default;
	~Particle_EnemyBullet() = default;

public:
	//通常弾
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init_Standard(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar);//初期化生成
	void Update_Standard();//更新
	void Draw_Standard(const ViewProjection* viewProjection);//描画


	//追跡弾
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init_Chaser(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar); // 初期化生成
	void Update_Chaser();// 更新
	void Draw_Chaser(const ViewProjection* viewProjection);// 描画


	// 持続弾
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init_Footpace(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar); // 初期化生成
	void Update_Footpace();// 更新
	void Draw_Footpace(const ViewProjection* viewProjection);// 描画


	// バウンド弾
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init_Bound(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar); // 初期化生成
	void Update_Bound();// 更新
	void Draw_Bound(const ViewProjection* viewProjection);// 描画
	

	//大玉
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init_BB(float time, Model* model, const Vector3& position, const float& scalar, const Vector3& scale, const float& rotate, const int& randomRange, const float& randomFar); // 初期化生成
	void Update_BB();// 更新
	void Draw_BB(const ViewProjection* viewProjection);// 描画



	bool IsBreak(); // フラグ管理
	float ToRadian(float angle);

private:
	// 3Dモデル
	Model* model_ = nullptr;

	// ワールド座標
	WorldTransform worldTransform_;

	// 速度
	Vector3 velocity_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 破壊フラグ
	bool isBreak_;

	// 生存時間受け取り用
	float time_;
};
