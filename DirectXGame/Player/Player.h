#pragma once

#include <Mymath/Mymath.h>

/// <summary>
/// 操作するプレイヤー
/// </summary>
class Player {
public: //** コンストラクタ **//

	Player() = default;
	~Player() = default;

public: // パブリック関数 **//

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// モデル描画
	/// </summary>
	void DrawModel();

private: //** メンバ変数 **//

};

