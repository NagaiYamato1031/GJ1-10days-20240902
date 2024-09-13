#pragma once
#include <Utility/Mymath.h>
#include <Model.h>
#include <WorldTransform.h>
class CreateHpbar {
public: /*コンストラクト*/
	CreateHpbar()=default;
	~CreateHpbar()=default;

public: /*パブリック関数*/
	void Init(const Vector3& pos, Model* model_,const float &deg ,const float &far_);
	void Update();
	void Draw(const ViewProjection *viewProjection);
	void NeedReturn();
	float ToRadian(float angle);

public:  /*パブリック変数*/
	bool isActive = true;

private: /*メンバ変数*/
	//3Dモデル
	Model* model_;
	//ワールド座標
	WorldTransform worldTransform_;
	//破壊フラグ
	bool isBreak;
	//ベクトル
	Vector3 velocity_;
	//中心からの距離
	float distance_;
	//中心
	Vector3 pos_;

	//テクスチャハンドル
	uint32_t textureHandle_;
};
