#ifndef _BEES_H
#define _BEES_H
<<<<<<< HEAD
<<<<<<< HEAD
#include "AnimatedTexture.h"
#include "Timer.h"
#include "BezierPath.h"

using namespace SDLFramework;

class Bee : public GameEntity {
protected:
	static std::vector<std::vector<Vector2>> sPaths;

	enum states{IDLE, DIVE, DEAD, GRAB};
	states mState;

	Timer* mTimer;
	AnimatedTexture* mBee;

	unsigned mCurrentPath;
	unsigned mCurrentWaypoint;

private:
	const float EPSILON = 5.0f;

	float mSpeed;
	int mHealth;

	const int mSCORE_VALUE = 300;
	bool mGrabbedFlower;

protected:
	void HandleIdleState();
	void HandleDiveState();
	void HandleDeadState();
	void HandleGrabState();

	void HandleState();

	void RenderIdleState();
	void RenderDiveState();
	void RenderDeadState();
	void RenderGrabState();

	void RenderState();

public:
	static void CreatePaths();

	Bee(int);
	~Bee();

	states CurrentState();

	void CreateCollision();

	float GetSpeed() { return mSpeed; }
	void SetSpeed(float s) { mSpeed = s; }

	int GetHealth() { return mHealth; }
	void SetHealth(float h) { mHealth = h; }

	int GetScore();

	void Update();
	void Render();
};
=======

>>>>>>> parent of 43d63b3... Added Lives to UI
=======

>>>>>>> parent of 43d63b3... Added Lives to UI

#endif // !_BEES_H