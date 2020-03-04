#include "Spray.h"

Spray::Spray() {
	mTimer = Timer::Instance();

	mTexture = new AnimatedTexture("spray.png", 0, 0, 56, 64, 7, 1.5f, AnimatedTexture::HORIZONTAL);
	mTexture->Parent(this);

	mSpeed = 500;
	CreateCollisions();

	Reload();
}
Spray::~Spray() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Spray::Fire(Vector2 pos) {
	Position(pos);
	Active(true);
}

void Spray::Reload() {
	mTexture->ResetAnimation();
	Active(false);
}

void Spray::CreateCollisions() {
	mCollision.x = mTexture->Position().x;
	mCollision.y = mTexture->Position().y;
	mCollision.w = (float)mTexture->GetWidth();
	mCollision.h = (float)mTexture->GetHeight();
}

void Spray::Update() {
	if (Active()) {

		Translate(-Vec2_Up * mSpeed * mTimer->DeltaTime());
		mCollision.x = Position().x;
		mCollision.y = Position().y;

		Vector2 pos = Position();
		if (pos.y < -OFFSCREEN_BUFFER) {
			Reload();
		}
		mTexture->Update();
	}
}

void Spray::Render() {
	if (Active()) {
		mTexture->Render();
	}
}