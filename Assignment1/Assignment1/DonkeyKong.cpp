#include "DonkeyKong.h"

DonkeyKong* DonkeyKong::sInstance = nullptr;
DonkeyKong* DonkeyKong::Instance() {
	if (sInstance == nullptr) {
		sInstance = new DonkeyKong();
	}
	return sInstance;
}
void DonkeyKong::Release() {
	delete sInstance;
	sInstance = nullptr;
}

DonkeyKong::DonkeyKong() {
	mTimer = Timer::Instance();

	mDK = new AnimatedTexture("dk_climbing.png", 0, 0, 160, 128, 2, 0.75f, AnimatedTexture::HORIZONTAL);
	mDK->Position(Vector2(mStartingPosition));
	mDK->Parent(this);
	CreateCollision(mDK);
	
	mDK_Hit = new AnimatedTexture("dk_hit.png", 0, 0, 160, 128, 2, 0.75f, AnimatedTexture::HORIZONTAL);
	mDK_Hit->Position(Vector2(mStartingPosition));
	mDK_Hit->Parent(mDK);
	CreateCollision(mDK_Hit);

	mDK_Stand = new AnimatedTexture("donkeykong.png", 0, 0, 128, 152, 2, 0.75f, AnimatedTexture::HORIZONTAL);
	mDK_Stand->Position(Vector2(mStartingPosition));
	mDK_Stand->Parent(mDK);

	mState = DOWN;
}
DonkeyKong::~DonkeyKong() {
	mTimer = nullptr;
	delete mDK;
	mDK = nullptr;

	delete mDK_Hit;
	mDK_Hit = nullptr;

	delete mDK_Stand;
	mDK_Stand = nullptr;
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
		Translate(Vec2_Up * (mSpeed * 10.75) * mTimer->DeltaTime(), WORLD);
		break;
	case HIT:
		Translate(-Vec2_Up * (10 * 2.5) * mTimer->DeltaTime(), WORLD);
		mHitStunTimer += mTimer->DeltaTime();

		if (mHitStunTimer > mHitStunDelay) {
			mState = DOWN;
		}
		break;
	case STAND:
		mDK_Stand->Update();
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
	case STAND:
		mDK_Stand->Render();
		break;
	}
}