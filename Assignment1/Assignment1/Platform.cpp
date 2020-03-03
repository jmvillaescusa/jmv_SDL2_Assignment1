#include "Platform.h"

Platform::Platform(int i) {
	if (i == 3) {
		mPlatform[i] = new Texture("platform3.png");
		mPlatform[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.929f - 192));
	}
	else if (i == 2) {
		mPlatform[i] = new Texture("platform2.png");
		mPlatform[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.929f - 128));
	}
	else if (i == 1) {
		mPlatform[i] = new Texture("platform1.png");
		mPlatform[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.929f - 64));
	}
	else if (i == 0) {
		mPlatform[i] = new Texture("platformBase.png");
		mPlatform[i]->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.929f + 16));
	}
	CreateCollision(i);
	mPlatform[i]->Parent(this);
}
Platform::~Platform() {
	for (int i = 0; i < 4; i++) {
		delete mPlatform[i];
		mPlatform[i] = nullptr;
	}
}

void Platform::CreateCollision(int i) {
	mCollision.x = mPlatform[i]->Position().x;
	mCollision.y = mPlatform[i]->Position().y - (mPlatform[i]->GetHeight() / 2) + 5;
	mCollision.w = mPlatform[i]->GetWidth();
	mCollision.h = 10;
}

void Platform::Render(int i) {
		mPlatform[i]->Render();
}