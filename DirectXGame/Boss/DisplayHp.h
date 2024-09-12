#pragma once

#include <Utility/Mymath.h>
#include <Model.h>
#include <WorldTransform.h>
class DisplayHp {
public: /*コンストラクタ*/
	DisplayHp() = default;
	~DisplayHp() = default;

public: /*パブリック関数*/
	void Init();
	void Update();
	void DrawModel();

private: /*メンバ変数*/
	//3Dモデル
	Model* model_ = nullptr;
	//ワールド座標
	WorldTransform worldTransform_;

};
