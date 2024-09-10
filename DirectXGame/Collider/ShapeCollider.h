#pragma once

#include <variant>
#include <functional>
#include <Utility/Mymath.h>

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

	class ShapeColliderBase {
	public: //** デストラクタ **//
		virtual ~ShapeColliderBase() = default;
	public: //** パブリック関数 **//
		virtual void Update() = 0;
		virtual void CheckCollision(ShapeColliderBase* other) = 0;
	public: //** パブリック変数 **//
		int mask;
	};

	/// <summary>
	/// 当たり判定を便利に使うためのクラス
	/// </summary>
	template <typename T>
	class ShapeCollider : public ShapeColliderBase {
	public: //** サブクラス **//

		// 球または AABB の形状を入れられる型
		typedef std::variant<Math::Sphere*, Math::AABB*/*, Math::Capsule*/> ShapeData;

	public: //** コンストラクタ **//

		/// <summary>
		/// コンストラクタ
		/// </summary>
		ShapeCollider(T* data);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~ShapeCollider() = default;

		//** ヒット時のリアクション用の関数 **//

		// ヒット時の関数ポインタの型
		typedef std::function<void(const int& hitMask)> OnHitFunction;

		// ヒットした瞬間のとき
		OnHitFunction enterLambda = [](const int& hitMask) { hitMask; };
		// ヒットし続けているとき
		OnHitFunction stayLambda = [](const int& hitMask) { hitMask; };
		// ヒットが離れたとき
		OnHitFunction exitLambda = [](const int& hitMask) { hitMask; };

	public: //** パブリック関数 **//

		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 対応した形状までのポインタを返す
		/// </summary>
		/// <typeparam name="U">?</typeparam>
		/// <param name="c">取得するコライダー</param>
		/// <returns>形状までのポインタ</returns>
		template<class U>
		U* GetShape(ShapeCollider* c);

		/// <summary>
		/// 衝突関数
		/// </summary>
		void CheckCollision(ShapeColliderBase* other) override;


	public: //** パブリック変数 **//

		// 稼働状態か
		bool isActive = true;

		// 判定を使うか
		bool isEnable = true;

		// 形状 (球 or AABB)
		// 参照する
		ShapeData data;
	};

	template<typename T>
	ShapeCollider<T>::ShapeCollider(T* data) : data(data) {
		//// 型によってタイプを変更
		//if constexpr (std::is_same_v<T, Math::Sphere>) {
		//	type = ShapeType::tSphere;
		//}
		//else if constexpr (std::is_same_v<T, Math::AABB>) {
		//	type = ShapeType::tAABB;
		//}
	}
	template<typename T>
	void ShapeCollider<T>::Update() {
	}

	template<typename T>
	template<class U>
	U* ShapeCollider<T>::GetShape(ShapeCollider* c) {
		return *std::get_if<U*>(&c->data);
	}

	template<typename T>
	void ShapeCollider<T>::CheckCollision(ShapeColliderBase* c) {
		/*if (Math::IsCollision(*GetShape<T>(this), *GetShape<T>(c))) {
			stayLambda(c->mask);
		}*/
		c;
	}
}