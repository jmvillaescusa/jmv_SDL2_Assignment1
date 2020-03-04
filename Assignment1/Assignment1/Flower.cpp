#include "Flower.h"

Flower::Flower(int i) {
	if (i == 4) {
		mFlower[i] = new Texture("flower.png");
		mFlower[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.25f, Graphics::SCREEN_HEIGHT * 0.91f));
	}
	else if (i == 3) {
		mFlower[i] = new Texture("flower.png");
		mFlower[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.375f, Graphics::SCREEN_HEIGHT * 0.91f));
	}
	else if (i == 2) {
		mFlower[i] = new Texture("flower.png");
		mFlower[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.91f));
	}
	else if (i == 1) {
		mFlower[i] = new Texture("flower.png");
		mFlower[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.625f, Graphics::SCREEN_HEIGHT * 0.91f));
	}
	else if (i == 0) {
		mFlower[i] = new Texture("flower.png");
		mFlower[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.75f, Graphics::SCREEN_HEIGHT * 0.91f));
	}
	CreateCollision(i);
	mFlower[i]->Parent(this);
}
Flower::~Flower() {
	for (int i = 0; i < 5; i++) {
		delete mFlower[i];
		mFlower[i] = nullptr;
	}
}

void Flower::CreateCollision(int i) {
	mCollision.x = mFlower[i]->Position().x;
	mCollision.y = mFlower[i]->Position().y;
	mCollision.w = (float)mFlower[i]->GetWidth();
	mCollision.h = (float)mFlower[i]->GetHeight();
}

void Flower::Render(int i) {
	mFlower[i]->Render();
}