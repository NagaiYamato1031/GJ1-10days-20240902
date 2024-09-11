#pragma once

#include <map>
#include <list>
#include <memory>
#include <Collider/MaskCollision.h>
#include "ShapeCollider.h"

namespace ACJPN::Collider {

	class CollisionManager {
	public: //** コンストラクタ **//

		/// <summary>
		/// コンストラクタ
		/// </summary>
		CollisionManager() = default;
		/// <summary>
		/// デストラクタ
		/// </summary>
		~CollisionManager() = default;

	public: //** パブリック関数 **//

		/// <summary>
		/// インスタンス取得
		/// </summary>
		static CollisionManager* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		void Init();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// コライダーを追加する
		/// <param>※マスクは設定しておく事</param>
		/// </summary>
		/// <param name="collider">アドレス</param>
		template <typename T>
		void RegistCollider(std::shared_ptr<ShapeCollider<T>>& collider);

		/// <summary>
		/// 当たり判定を検知する
		/// 何と何が当たるかは指定する
		/// </summary>
		void CheckCollision();

	private:

		// 各マスクごとにリストを持つ
		std::map<int, std::list<std::weak_ptr<ShapeColliderBase>>> colliderMap_;

	private: //** プライベート関数 **//

		/// <summary>
		/// プレイヤーの当たり判定
		/// </summary>
		void CheckPlayer();
		void CheckBoss();

	};
	template<typename T>
	inline void CollisionManager::RegistCollider(std::shared_ptr<ShapeCollider<T>>& collider) {
		colliderMap_[collider->mask].emplace_back(collider);
	}
}