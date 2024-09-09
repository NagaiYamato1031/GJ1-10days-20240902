#pragma once
#include <Utility/Mymath.h>
#include <Input.h>
#include <Model.h>
#include <WorldTransform.h>
class Particle_PlayerBullet {
public: /*コンストラクタ*/
	Particle_PlayerBullet() = default;
	~Particle_PlayerBullet();

public: /*パブリック関数*/
	// Player.hに書いてあったことをとりあえずそのまま書いた奴{
	void Init(Model *model,const Vector3& position);   // 初期化
	void Update();                        // 更新
	// Player.hに書いてあったことをとりあえずそのまま書いた奴}

	// 頑張って自分で書いた奴{

	void Draw( const ViewProjection* viewProjection);

	// 頑張って自分で書いた奴}

private: /*メンバ変数*/
	// 入力管理
	Input* input_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;

	// ワールド座標
	WorldTransform worldTransform_;


	uint32_t textureHandle_ = 0;
};
