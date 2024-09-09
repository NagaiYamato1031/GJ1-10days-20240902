#include "BulletManager.h"

using namespace ACJPN;
using namespace ACJPN::Math;

void BulletManager::Init() {
	bullets_.clear();
}

void BulletManager::Update() {
	// 死んだデータは消す
	bullets_.remove_if([](IBullet* b) {
		if (!b->isActive) {
			delete b;
			return true;
		}
		return false;
		});
	for (IBullet* b : bullets_) {
		// 更新する
		b->Update();
	}
}

void BulletManager::DrawModel(ViewProjection* view) {
	for (IBullet* b : bullets_) {
		b->DrawModel(view);
	}
}

void BulletManager::Regist(IBullet* b) {
	bullets_.push_back(b);
}
