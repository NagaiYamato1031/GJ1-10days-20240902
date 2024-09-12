#include "CollisionManager.h"

#include "MaskCollision.h"

using namespace ACJPN;
using namespace ACJPN::Collider;

CollisionManager* CollisionManager::GetInstance() {
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

	// プレイヤーとボスの弾
	CheckPlayer();
	// ボスとプレイヤーの弾
	CheckBoss();
	// 弾同士の判定
	CheckBullets();
}

void CollisionManager::CheckPlayer() {
	// プレイヤーの当たり判定
	std::weak_ptr<ShapeColliderBase>& player = colliderMap_[MPlayer()].front();
	// 中身が無かったら処理しない
	if (player.expired()) {
		return;
	}
	// スコープで制限する
	if (std::shared_ptr<ShapeColliderBase> ptr = player.lock(); ptr->isEnable) {
		// ボスの弾の当たり判定
		for (auto listItr = colliderMap_[MBossBullet()].begin(); listItr != colliderMap_[MBossBullet()].end(); ++listItr) {
			if (std::shared_ptr<ShapeColliderBase> col = listItr->lock(); col->isEnable) {
				ptr->CheckCollision(listItr->lock().get());
				listItr->lock().get()->CheckCollision(ptr.get());
			}
		}

		// 波との判定
		for (auto listItr = colliderMap_[MWave()].begin(); listItr != colliderMap_[MWave()].end(); ++listItr) {
			if (std::shared_ptr<ShapeColliderBase> col = listItr->lock(); col->isEnable) {
				ptr->CheckCollision(listItr->lock().get());
				listItr->lock().get()->CheckCollision(ptr.get());
			}
		}

	}
}

void CollisionManager::CheckBoss() {
	// ボスの当たり判定
	std::weak_ptr<ShapeColliderBase>& boss = colliderMap_[MBoss()].front();
	// 中身が無かったら処理しない
	if (boss.expired()) {
		return;
	}
	// プレイヤーの弾の当たり判定
	if (std::shared_ptr<ShapeColliderBase> ptr = boss.lock(); ptr->isEnable) {
		for (auto listItr = colliderMap_[MPlayerBullet()].begin(); listItr != colliderMap_[MPlayerBullet()].end(); ++listItr) {
			if (std::shared_ptr<ShapeColliderBase> col = listItr->lock(); col->isEnable) {
				ptr->CheckCollision(listItr->lock().get());
				listItr->lock().get()->CheckCollision(ptr.get());
			}
		}
	}

}

void CollisionManager::CheckBullets() {
	// プレイヤーの弾
	for (auto listItrA = colliderMap_[MPlayerBullet()].begin(); listItrA != colliderMap_[MPlayerBullet()].end(); ++listItrA) {
		// スコープで制限する
		if (std::shared_ptr<ShapeColliderBase> colA = listItrA->lock(); colA->isEnable) {
			// ボスの弾の当たり判定
			for (auto listItrB = colliderMap_[MBossBullet()].begin(); listItrB != colliderMap_[MBossBullet()].end(); ++listItrB) {
				// スコープで制限する
				if (std::shared_ptr<ShapeColliderBase> colB = listItrB->lock(); colB->isEnable) {
					colB->CheckCollision(colA.get());
					colA->CheckCollision(colB.get());
				}
			}
		}

	}
}
