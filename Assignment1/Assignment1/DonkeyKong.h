#ifndef _DONKEYKONG_H
#define _DONKEYKONG_H
#include "AnimatedTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class DonkeyKong : public GameEntity {
public:
	// states
	enum states {DOWN, HIT};
	states mState;

private:
	AnimatedTexture* mDK;
	AnimatedTexture* mDK_Hit;
	Timer* mTimer;

	Vector2 mStartingPosition = Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.25f);

	float mSpeed = 10.0f;

	float mHitStunTimer;
	float mHitStunDelay = 0.5f;

public:
	DonkeyKong();
	~DonkeyKong();

	void CreateCollision(AnimatedTexture*);

	void ResetTimer() { mHitStunTimer = 0; }

	void SetSpeed(float s) { mSpeed = s; }

	void Update();
	void Render();
};
#endif // !_DONKEYKONG_H