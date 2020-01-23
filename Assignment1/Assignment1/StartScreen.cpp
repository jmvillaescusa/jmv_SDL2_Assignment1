#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	// Logo Animation Variables
	mAnimationStartPos = Vector2(Graphics::SCREEN_WIDTH, 0.0f);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	// Logo Entities
	mLogo = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
	mDonkeyKong = new AnimatedTexture("donkeykong.png", 0, 0, 128, 152, 2, 0.75f, AnimatedTexture::HORIZONTAL);
	mTitle = new Texture("title.png", 0, 0, 828, 352);

	mLogo->Parent(this);
	mDonkeyKong->Parent(mLogo);
	mTitle->Parent(mLogo);

	mDonkeyKong->Position(-325.0f, 100.0f);
	mTitle->Position(mAnimationStartPos);
}
StartScreen::~StartScreen() {
	mTimer = nullptr;
	mInputManager = nullptr;

	// Logo Entities
	delete mLogo;
	mLogo = nullptr;
	delete mDonkeyKong;
	mDonkeyKong = nullptr;
	delete mTitle;
	mTitle = nullptr;
}

void StartScreen::Update() {
	mDonkeyKong->Update();

	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		mTitle->Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));
		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
		}
	}
	else {
		if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
			ChangeSelectedMode(1);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelectedMode(-1);
		}
	}

	if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN) || mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
		mAnimationTimer = mAnimationTotalTime;
	}
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(Graphics::SCREEN_WIDTH, 0.0f);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	mTitle->Position(mAnimationStartPos);
}

int StartScreen::SelectedMode() {
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0) {
		mSelectedMode = 1;
	}
	else if (mSelectedMode > 1) {
		mSelectedMode = 0;
	}
}

void StartScreen::Render() {
	mDonkeyKong->Render();
	mTitle->Render();
}