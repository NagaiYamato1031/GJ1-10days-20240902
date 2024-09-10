#include "CollisionManager.h"

using namespace ACJPN;
using namespace ACJPN::Collider;

CollisionManager* ACJPN::Collider::CollisionManager::GetInstance() {
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::Init() {
	// すべて解放
	colliderMap_.clear();
}

void CollisionManager::Update() {
	// すべて走査する
	for (auto itr = colliderMap_.begin(); itr != colliderMap_.end(); ++itr) {
		// マスクごとに処理
		for (std::weak_ptr<ShapeColliderBase>& collider : itr->second) {
			// 一時的に参照する
			if (std::shared_ptr<ShapeColliderBase> r = collider.lock()) {
				r->Update();
			}
		}
	}
}

template<typename T>
inline void CollisionManager::RegistCollider(int mask, std::shared_ptr<ShapeCollider<T>> collider) {
	colliderMap_[mask].emplace_back(collider);
}

void CollisionManager::CheckCollision() {
	// 完全に手動でマスク処理を分ける


}
