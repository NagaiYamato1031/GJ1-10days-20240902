#pragma once

#include "ShapeCollider.h"

namespace ACJPN::Collider {

	//** マスクフラグを設定している **//

	constexpr int MPlayer() { return MaskCollision0; }
	constexpr int MPlayerBullet() { return MaskCollision1; }
	constexpr int MBoss() { return MaskCollision2; }
	constexpr int MBossBullet() { return MaskCollision3; }
	constexpr int MWave() { return MaskCollision4; }
	constexpr int MStage() { return MaskCollision5; }

}