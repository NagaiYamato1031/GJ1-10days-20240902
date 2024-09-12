#pragma once
#include <Utility/Mymath.h>
#include <Model.h>
#include <WorldTransform.h>
class CreateHpbar {
public: /*コンストラクト*/
	CreateHpbar()=default;
	~CreateHpbar()=default;

public: /*パブリック関数*/
	void Init(const Vector3& pos, Model* model_);
	void Update();
	void Draw(const ViewProjection *viewProjection);

private: /*メンバ変数*/
	//3Dモデル
	Model* model_;
	//ワールド座標
	WorldTransform worldTransform_;
	//破壊フラグ
	bool isBreak;
	//テクスチャハンドル
	TextureManager textureHandle_;
};
