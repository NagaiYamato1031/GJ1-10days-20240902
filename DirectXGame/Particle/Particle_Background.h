#pragma once

#include <Utility/Mymath.h>
#include <Model.h>
#include <WorldTransform.h>
class Particle_Background {
public: /*コンストラクタ*/
	Particle_Background() = default;
	~Particle_Background() = default;

public:
	void Init();
	void Update();
	void DrawModel();
};
