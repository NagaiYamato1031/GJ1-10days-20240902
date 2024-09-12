#pragma once

#include <Utility/Mymath.h>
#include <Model.h>
#include <WorldTransform.h>
#include "CreateHpbar.h"
class DisplayHp {
public: /*コンストラクタ*/
	DisplayHp() = default;
	~DisplayHp() = default;

public: /*パブリック関数*/
	void Init();
	void Create(const Vector3&position,const int &hp);
	void Update();
	void DrawModel(const ViewProjection* viewProjection);
	void DamageBreak();


private: /*メンバ変数*/
	//3Dモデル
	Model* model_ = nullptr;
	//ワールド座標
	WorldTransform worldTransform_;

	//リスト
	std::list<CreateHpbar*> hpBars_;

	//中心からの距離
	float distance_;

};
