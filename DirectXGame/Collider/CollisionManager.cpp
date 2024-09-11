#include "CollisionManager.h"

#include "MaskCollision.h"

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
		itr->second.remove_if([](std::weak_ptr<ShapeColliderBase>& ptr) {
			// 参照が消えているなら
			if (ptr.expired()) {
				return true;
			}
			return false;
			});
	}
}

void CollisionManager::CheckCollision() {

	//** 完全に手動でマスク処理を分ける **//

	// プレイヤーと敵の弾

	// ボスとプレイヤーの弾
	CheckCollisionBoss();
}

void ACJPN::Collider::CollisionManager::CheckCollisionBoss() {
	// ボスの当たり判定
	std::weak_ptr<ShapeColliderBase>& boss = colliderMap_[MBoss()].front();
	// 中身が無かったら処理しない
	if (boss.expired()) {
		return;
	}
	// プレイヤーの弾の当たり判定
	if (std::shared_ptr<ShapeColliderBase> ptr = boss.lock()) {
		for (auto listItr = colliderMap_[MPlayerBullet()].begin(); listItr != colliderMap_[MPlayerBullet()].end(); ++listItr) {
			ptr->CheckCollision(listItr->lock().get());
		}
	}

}
