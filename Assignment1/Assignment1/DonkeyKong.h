#ifndef _DONKEYKONG_H
#define _DONKEYKONG_H
#include "AnimatedTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class DonkeyKong : public GameEntity {
public:
	// states
	enum states {DOWN, HIT, STAND};
	states mState;

private:
	static DonkeyKong* sInstance;

	Vector2 mStartingPosition = Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.25f);
	AnimatedTexture* mDK;
	AnimatedTexture* mDK_Hit;
	AnimatedTexture* mDK_Stand;
	Timer* mTimer;

	float mSpeed = 9.0f;

	float mHitStunTimer;
	float mHitStunDelay = 0.55f;

public:
	DonkeyKong();
	~DonkeyKong();

	static DonkeyKong* Instance();
	static void Release();

	void CreateCollision(AnimatedTexture*);

	void ResetTimer() { mHitStunTimer = 0; }

	float GetSpeed() { return mSpeed; }
	void SetSpeed(float s) { mSpeed = s; }

	float GetStunDelay() { return mHitStunDelay; }
	void SetStunDelay(float s) { mHitStunDelay = s; }

	void Update();
	void Render();
};
#endif // !_DONKEYKONG_H
