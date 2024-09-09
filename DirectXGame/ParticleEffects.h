#pragma once
#include <Utility/Mymath.h>
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class ParticleEffects {
public: /*コンストラクタ*/
	ParticleEffects() = default;
	~ParticleEffects();

public: /*パブリック関数*/

	//Player.hに書いてあったことをとりあえずそのまま書いた奴{
	void Init();//初期化
	void Update();//更新
	void DrawModel(ViewProjection* view);//モデル描画
	// Player.hに書いてあったことをとりあえずそのまま書いた奴}


	//頑張って自分で書いた奴{

	void CreateParticle();//パーティクルを生成

	void UpdateParticle();//生成したパーティクルを動かす

	// 頑張って自分で書いた奴}

private: /*メンバ変数*/
	//入力管理
	Input* input_ = nullptr;

	//3Dモデル
	Model* model_ = nullptr;

	//ワールド座標
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	uint32_t textureHandle_ = 0;
};
