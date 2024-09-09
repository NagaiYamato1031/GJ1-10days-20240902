#pragma once

#include "IBullet.h"

/// <summary>
/// 弾を一括で管理する
/// </summary>
class BulletManager final {
public: //** コンストラクタ **//

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BulletManager() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BulletManager() = default;

public: //** パブリック関数 **//

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
	void DrawModel(ViewProjection* view);

	/// <summary>
	/// あらかじめ生成した弾渡して登録する
	/// </summary>
	void Regist(IBullet* b);

	/// <summary>
	/// リストを取得する
	/// </summary>
	/// <returns></returns>
	std::list<IBullet*>& GetList() { return bullets_; }

private: //** プライベート変数 **//

	// 弾をまとめて管理する
	std::list<IBullet*> bullets_;
};