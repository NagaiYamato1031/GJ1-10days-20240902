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
		virtual void CheckCollision(ShapeColliderBase* other) = 0;
		virtual void Hit(ShapeColliderBase* c) = 0;
	public: //** パブリック変数 **//
		int mask = MaskCollision0;
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
		/// mask は必ず設定すること
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
		/// 対応した形状までのポインタを返す
		/// </summary>
		/// <typeparam name="U">?</typeparam>
		/// <returns>形状までのポインタ</returns>
		T* GetShape();

		/// <summary>
		/// 衝突関数
		/// </summary>
		void CheckCollision(ShapeColliderBase* other) override;

		/// <summary>
		/// ヒットしているポインタ
		/// </summary>
		/// <param name="c"></param>
		void Hit(ShapeColliderBase* c) override;

		/// <summary>
		/// ヒットしていない時
		/// </summary>
		void NoHit();

	public: //** パブリック変数 **//

		// 稼働状態か
		bool isActive = true;

		// 判定を使うか
		bool isEnable = true;

		// 形状 (球 or AABB)
		// 参照する
		ShapeData data;

		// ヒット対象
		// Enter と Exit の判別
		ShapeColliderBase* hit_ = nullptr;
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
	T* ShapeCollider<T>::GetShape() {
		return *std::get_if<T*>(&data);
	}

	template<typename T>
	void ShapeCollider<T>::CheckCollision(ShapeColliderBase* c) {
		if (auto sphere = dynamic_cast<ShapeCollider<Math::Sphere>*>(c)) {
			if (Math::IsCollision(*GetShape(), *sphere->GetShape())) {
				Hit(c);
				return;
			}
		}
		else if (auto aabb = dynamic_cast<ShapeCollider<Math::AABB>*>(c)) {
			if (Math::IsCollision(*GetShape(), *aabb->GetShape())) {
				Hit(c);
				return;
			}
		}
		// 当たっていないとき
		// 前フレームに当たっていたら
		NoHit();
	}

	template<typename T>
	void ShapeCollider<T>::Hit(ShapeColliderBase* c) {
		// nullptr なら処理しない
		if (!c) {
			return;
		}
		// 当たっていなかったとき
		if (hit_ == nullptr) {
			enterLambda(c->mask);
			hit_ = c;
		}
		// 同じものに当たっている時
		else if (hit_ == c) {
			stayLambda(c->mask);
		}
		// 違うものに当たっている時
		else {
			hit_ = c;
		}
	}
	template<typename T>
	inline void ShapeCollider<T>::NoHit() {
		if (hit_) {
			exitLambda(hit_->mask);
			hit_ = nullptr;
		}
	}
}