#pragma once

#include <memory>
#include <ViewProjection.h>
#include <WorldTransform.h>

#include <Utility/Mymath.h>

class FollowCamera {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FollowCamera() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~FollowCamera() = default;

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
	/// カメラ取得
	/// </summary>
	ViewProjection* GetView() const { return camera_.get(); }

	/// <summary>
	/// ターゲット設定
	/// </summary>
	/// <param name="ptr"></param>
	void SetTarget(WorldTransform* const ptr) { target_ = ptr; }

	/// <summary>
	/// デバッグの表示
	/// </summary>
	void DebguWindow();

private: //** メンバ変数 **//
	
	// 基本的なターゲットからの距離
	// 北側にいるところから始まる
	Vector3 kOffset = { 0.0f,-25.0f,-100.0f };

	// オフセット
	// 毎回計算して位置に加算する
	Vector3 offset = { 0.0f,0.0f,0.0f };


	// ターゲット
	const WorldTransform* target_ = nullptr;

	// カメラ実体
	std::unique_ptr<ViewProjection> camera_;

};