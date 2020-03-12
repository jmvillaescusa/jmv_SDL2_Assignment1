<<<<<<< HEAD
#include "Bees.h"

std::vector<std::vector<Vector2>> Bee::sPaths;
void Bee::CreatePaths() {
	int screenMidPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.4f);

	int currentPath = 0;
	BezierPath* path = new BezierPath();
	path->AddCurve({Vector2(500.0f, 10.0f), Vector2(500.0f, 0.0f), Vector2(500.0f, 310.0f), Vector2(500.0f, 300.0f)}, 1);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
}

Bee::Bee(int path) : mCurrentPath(path) {
	mTimer = Timer::Instance();

	mState = IDLE;

	mCurrentWaypoint = 1;
	Position(sPaths[mCurrentPath][0]);

	mBee = new AnimatedTexture("bees.png", 0, 0, 70, 70, 3, 0.15f, AnimatedTexture::HORIZONTAL);
	mBee->Parent(this);
	mBee->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mSpeed = 100.0f;
	mGrabbedFlower = false;

	CreateCollision();
}
Bee::~Bee() {
	mTimer = nullptr;
	
	delete mBee;
	mBee = nullptr;
}

void Bee::CreateCollision() {
	mCollision.x = mBee->Position().x;
	mCollision.y = mBee->Position().y;
	mCollision.w = (float)mBee->GetWidth();
	mCollision.h = (float)mBee->GetHeight();
}

int Bee::GetScore() {
	if (mGrabbedFlower) {
		return mSCORE_VALUE + 200;
	}
	else {
		return mSCORE_VALUE;
	}
}

// Handling States //--------------------------------------------------------------
void Bee::HandleIdleState() {}
void Bee::HandleDiveState() {
	if ((sPaths[mCurrentPath][mCurrentWaypoint] - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
		mCurrentWaypoint++;
	}

	if (mCurrentWaypoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - Position();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), WORLD);
	}
	else {

	}
}
void Bee::HandleDeadState() {}
void Bee::HandleGrabState() {}
void Bee::HandleState() {
	switch (mState)
	{
	case IDLE:
		HandleIdleState();
		break;

	case DIVE:
		HandleDiveState();
		break;

	case DEAD:
		HandleDeadState();
		break;

	case GRAB:
		HandleGrabState();
		break;
	}
}

// Rendering States //-------------------------------------------------------------
void Bee::RenderIdleState() {}
void Bee::RenderDiveState() {}
void Bee::RenderDeadState() {}
void Bee::RenderGrabState() {}
void Bee::RenderState() {
	switch (mState) {
	case IDLE:
		RenderIdleState();
		break;
		
	case DIVE:
		RenderDiveState();
		break;

	case DEAD:
		RenderDeadState();
		break;

	case GRAB:
		RenderGrabState();
		break;
	}
}

void Bee::Update() {
	if (Active()) {
		HandleState();
	}
}
void Bee::Render() {
	if (Active()) {
		mBee->Render();
	}
}
=======
#include "Bees.h"
>>>>>>> parent of 43d63b3... Added Lives to UI
