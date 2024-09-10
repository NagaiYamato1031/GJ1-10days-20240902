#pragma once

#define MaskCollision0 0b1 
#define MaskCollision1 0b1 << 1
#define MaskCollision2 0b1 << 2
#define MaskCollision3 0b1 << 3
#define MaskCollision4 0b1 << 4
#define MaskCollision5 0b1 << 5
#define MaskCollision6 0b1 << 6
#define MaskCollision7 0b1 << 7
#define MaskCollisionAll !(0b1 << 8)

namespace ACJPN::Collider {

	/// <summary>
	/// 当たり判定を便利に使うための仮想クラス
	/// </summary>
	class ICollider {
	public: //** コンストラクタ **//

		/// <summary>
		/// コンストラクタ
		/// </summary>
		ICollider() = default;
		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~ICollider() = default;

	public: //** パブリック関数 **//

		/// <summary>
		/// 初期化
		/// </summary>
		virtual void Init();

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

	public: //** パブリック変数 **//

		// 稼働状態か
		bool isActive_ = true;

		// 判定を使うか
		bool isEnable_ = true;

	};

}