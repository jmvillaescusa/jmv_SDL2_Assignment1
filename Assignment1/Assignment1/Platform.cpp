#include "Platform.h"

Platform::Platform() {
	mPlatformBase = new Texture("platformBase.png");
	mPlatformBase->Parent(this);
	mPlatformBase->Position(Vector2(Vec2_Zero.x, Vec2_Zero.y + 16));

	mPlatformOne = new Texture("platform1.png");
	mPlatformOne->Parent(this);
	mPlatformOne->Position(Vector2(Vec2_Zero.x, -64));

	mPlatformTwo = new Texture("platform2.png");
	mPlatformTwo->Parent(mPlatformOne);
	mPlatformTwo->Position(Vector2(Vec2_Zero.x, -64));

	mPlatformThree = new Texture("platform3.png");
	mPlatformThree->Parent(mPlatformTwo);
	mPlatformThree->Position(Vector2(Vec2_Zero.x, -64));
}
Platform::~Platform() {
	delete mPlatformBase;
	mPlatformBase = nullptr;

	delete mPlatformOne;
	mPlatformOne = nullptr;

	delete mPlatformTwo;
	mPlatformTwo = nullptr;

	delete mPlatformThree;
	mPlatformThree = nullptr;
}

void Platform::Render() {
	mPlatformBase->Render();
	mPlatformOne->Render();
	mPlatformTwo->Render();
	mPlatformThree->Render();
}