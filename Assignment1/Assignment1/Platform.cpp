#include "Platform.h"

Platform::Platform(int i) {
	if (i == 3) {
		mPlatform[i] = new Texture("platform3.png");
		mPlatform[i]->Parent(mPlatform[i - 1]);
		mPlatform[i]->Parent(this);
		mPlatform[i]->Position(Vector2(Vec2_Zero.x, -64));
	}
	else if (i == 2) {
		mPlatform[i] = new Texture("platform2.png");
		mPlatform[i]->Parent(mPlatform[i - 1]);
		mPlatform[i]->Parent(this);
		mPlatform[i]->Position(Vector2(Vec2_Zero.x, -64));
	}
	else if (i == 1) {
		mPlatform[i] = new Texture("platform1.png");
		mPlatform[i]->Parent(this);
		mPlatform[i]->Position(Vector2(Vec2_Zero.x, -64));
	}
	else if (i == 0) {
		mPlatform[i]->Parent(this);
		mPlatform[i]->Position(Vector2(Vec2_Zero.x, Vec2_Zero.y + 16));
	}

	mCollision[i].x = mPlatform[i]->Position().x;
	mCollision[i].y = mPlatform[i]->Position().y;
	mCollision[i].w = mPlatform[i]->GetSrcRect().w;
	mCollision[i].h = mPlatform[i]->GetSrcRect().h;
}
Platform::~Platform() {
	for (int i = 0; i < 4; i++) {
		delete mPlatform[i];
		mPlatform[i] = nullptr;
	}
}

void Platform::Render(int i) {
		mPlatform[i]->Render();
}