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
	~ParticleEffects() = default;

public: /*パブリック関数*/

	void Init();//初期化

	void Update();//更新

	void DrawModel(ViewProjection* view);//モデル描画

private: /*メンバ変数*/
	//入力管理
	Input* input_ = nullptr;

	//3Dモデル
	Model* model_ = nullptr;

	//ワールド座標
	WorldTransform transform_
};
