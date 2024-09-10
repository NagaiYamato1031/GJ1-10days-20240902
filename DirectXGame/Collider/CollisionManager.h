#pragma once

#include <map>
#include <list>
#include "ICollider.h"

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
		/// 初期化
		/// </summary>
		void Init();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();

	private:

		// 各マスクごとにリストを持つ
		std::map<int, std::list<ICollider*>> colliderMap_;

	};
}