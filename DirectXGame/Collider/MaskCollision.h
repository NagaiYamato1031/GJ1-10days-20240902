#pragma once

#include "ICollider.h"

namespace ACJPN::Collider {

	//** マスクフラグを設定している **//

	constexpr int MPlayer() { return MaskCollision0; }
	constexpr int MPlayerBullet() { return MaskCollision1; }
	constexpr int MBoss() { return MaskCollision2; }
	constexpr int MBossBulet() { return MaskCollision3; }
	constexpr int MWave() { return MaskCollision4; }

}