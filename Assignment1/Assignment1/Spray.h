#ifndef _SPRAY_H
#define _SPRAY_H
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Spray : public PhysEntity {
private:
	static const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;
	AnimatedTexture* mTexture;

	float mSpeed;

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:
	Spray(bool friendly);
	~Spray();

	void Fire(Vector2 pos);
	void Reload();

	// Inherited from PhysEntity
	void Hit(PhysEntity* other) override;

	void Update();
	void Render();
};
#endif // !_BULLET_H
