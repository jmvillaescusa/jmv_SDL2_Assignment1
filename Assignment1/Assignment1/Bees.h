#ifndef _BEES_H
#define _BEES_H
#include "AnimatedTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Bee : public GameEntity {
public:
	enum states{IDLE, DIVE, DIES, GRAB};
	states mState;

private:
	Timer* mTimer;
	AnimatedTexture* mBee;

	float mSpeed;

	int mScoreValue;
	bool mGrabbedFlower;

public:
	Bee();
	~Bee();

	void CreateCollision();
	void ClearCollision();

	float GetSpeed() { return mSpeed; }
	void SetSpeed(float s) { mSpeed = s; }

	void Update();
	void Render();
};

#endif // !_BEES_H