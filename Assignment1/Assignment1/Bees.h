#ifndef _BEES_H
#define _BEES_H
#include "AnimatedTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Bee : public GameEntity {
public:
	enum states{IDLE, DIVE, DIES, GRAB};
	states state;

private:
	Timer* mTimer;
	AnimatedTexture* mBee;

	float mSpeed;
	int mHealth;

	int mScoreValue;
	bool mGrabbedFlower;

public:
	Bee();
	~Bee();

	void CreateCollision();

	float GetSpeed() { return mSpeed; }
	void SetSpeed(float s) { mSpeed = s; }

	int GetHealth() { return mHealth; }
	void SetHealth(float h) { mHealth = h; }

	void Update();
	void Render();
};

#endif // !_BEES_H