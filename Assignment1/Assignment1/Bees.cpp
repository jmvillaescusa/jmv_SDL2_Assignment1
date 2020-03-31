#include "Bees.h"

Bee::Bee() {
	mTimer = Timer::Instance();

	mBee = new AnimatedTexture("bees.png", 0, 0, 70, 70, 3, 0.15, AnimatedTexture::HORIZONTAL);
	mBee->Parent(this);
	mBee->Position(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.5);

	mState = IDLE;

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
void Bee::ClearCollision() {
	mCollision.w = NULL;
	mCollision.h = NULL;
	mCollision.y = NULL;
	mCollision.x = NULL;
}

void Bee::Update() {
	switch (mState)
	{
	case Bee::IDLE:
		mBee->Update();

		Active(false);
		break;

	case Bee::DIVE:
		Active(true);
		mBee->Update();

		mCollision.x = mBee->Position().x;
		mCollision.y = mBee->Position().y;
		break;

	case Bee::DIES:
		delete mBee;
		mBee = nullptr;

		ClearCollision();
		break;

	case Bee::GRAB:
		break;
	}
}
void Bee::Render() {
	if (mState != DIES) {
		mBee->Render();
	}
}