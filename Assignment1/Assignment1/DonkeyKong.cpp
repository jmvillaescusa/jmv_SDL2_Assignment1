#include "DonkeyKong.h"

DonkeyKong::DonkeyKong() {
	mTimer = Timer::Instance();

	mDK = new AnimatedTexture("dk_climbing.png", 0, 0, 160, 128, 2, 0.75f, AnimatedTexture::HORIZONTAL);
	mDK->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.25f));
	mDK->Parent(this);
	CreateCollision(mDK);
	
	mDK_Hit = new AnimatedTexture("dk_hit.png", 0, 0, 160, 128, 2, 0.75f, AnimatedTexture::HORIZONTAL);
	mDK_Hit->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.25f));
	mDK_Hit->Parent(mDK);
	CreateCollision(mDK_Hit);

	mState = DOWN;
}
DonkeyKong::~DonkeyKong() {
	mTimer = nullptr;
	delete mDK;
	mDK = nullptr;
}

void DonkeyKong::CreateCollision(AnimatedTexture* object) {
	mCollision.x = object->Position().x;
	mCollision.y = object->Position().y;
	mCollision.w = (float)object->GetWidth();
	mCollision.h = (float)object->GetHeight();
}

void DonkeyKong::Update() {
	mDK->Update();
	switch (mState) {
	case DOWN:
		mHitStunTimer = 0;
		Translate(Vec2_Up * (mSpeed * 1.75) * mTimer->DeltaTime(), WORLD);
		break;
	case HIT:
		Translate(-Vec2_Up * (mSpeed * 2.75) * mTimer->DeltaTime(), WORLD);
		mHitStunTimer += mTimer->DeltaTime();

		if (mHitStunTimer > mHitStunDelay) {
			mState = DOWN;
		}
		break;
	}

	mCollision.x = mDK->Position().x;
	mCollision.y = mDK->Position().y;
}

void DonkeyKong::Render() {
	switch (mState) {
	case DOWN:
		mDK->Render();
		break;
	case HIT:
		mDK_Hit->Render();
		break;
	}
}