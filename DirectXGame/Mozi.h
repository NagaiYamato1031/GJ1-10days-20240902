#pragma once
#include <Mymath/Mymath.h>

#include "DirectXCommon.h"
#include "Sprite.h"

class Mozi {

public:

	//コンストラクタ・デストラクター

	Mozi();
	~Mozi();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	void DrawM();

	//Setter一覧
	void SetActiveSMozi(bool frag) { 
		
		SousaMozi = frag;
	};

	void SetActiveJMozi(bool frag) { 
		
		JumMozi = frag;
	};

	void SetActiveHMozi(bool frag) { 
		
		HipMozi = frag;
	};
	

private:
	DirectXCommon* dxCommon_ = nullptr;

	//フラグ一覧
	bool SousaMozi = false;

	bool JumMozi = false;

	bool HipMozi = false;

	//文字座標
	Vector3 SMoziPos = {0, 0, 0};

	Vector3 JMoziPos = {0, 0, 0};
	
	Vector3 HMoziPos = {0, 0, 0};

	//スプライト関連
	uint32_t textureHandleS_ = 0;
	uint32_t textureHandleJ_ = 0;
	uint32_t textureHandleH_ = 0;


	Sprite* spriteS_ = nullptr;
	Sprite* spriteJ_ = nullptr;
	Sprite* spriteH_ = nullptr;
};
