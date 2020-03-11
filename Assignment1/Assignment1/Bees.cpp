#include "Bees.h"

Bee::Bee() {
	mTimer = Timer::Instance();

	mBee = new AnimatedTexture("bees.png", 0, 0, 70, 70, 3, 0.15, AnimatedTexture::HORIZONTAL);
	mBee->Parent(this);
	mBee->Position(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.5);

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


void Bee::Update() {
	mBee->Update();
}
void Bee::Render() {
	mBee->Render();
}