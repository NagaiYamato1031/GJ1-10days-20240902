#pragma once
#include <Mymath/Mymath.h>

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

	bool GetSousaMozi() { return SousaMozi; }

	bool GetJumMozi() { return JumMozi; }

	bool GetHipMozi() { return HipMozi; }

private:

	bool SousaMozi = false;

	bool JumMozi = false;

	bool HipMozi = false;



};
