#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();
	//mUI = UserInterface::Instance();

	// Top Bar Entities
	/*mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 50);
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 0, 0, 195 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 0, 0, 255 });
	mHiScore = new Texture("TOP", "emulogic.ttf", 32, { 200, 0, 0 });

	mTopBar->Parent(this);
	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);

	mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.42f, 0.0f);
	mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.22f, 0.0f);
	mHiScore->Position(-Graphics::SCREEN_WIDTH * 0.10f, 0.0f);

	mPlayerOneScore = new Scoreboard();
	mPlayerTwoScore = new Scoreboard();
	mTopScore = new Scoreboard();

	mPlayerOneScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.2f, 0);
	mPlayerTwoScore->Position(Graphics::SCREEN_WIDTH * 0.44f, 0);
	mTopScore->Position(Graphics::SCREEN_WIDTH * 0.12f, 0);

	mTopScore->Score(10000);*/


	// Logo Animation Variables
	mAnimationStartPos = Vector2(Graphics::SCREEN_WIDTH, 0.0f);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 4.45f;
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

	// Play Mode Entities
	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
	mOnePlayerModeA = new Texture("1 Player Game A", "emulogic.ttf", 32, { 0, 230, 0 });
	mOnePlayerModeB = new Texture("1 Player Game B", "emulogic.ttf", 32, { 0, 230, 0 });
	mTwoPlayerModeA = new Texture("2 Player Game A", "emulogic.ttf", 32, { 0, 230, 0 });
	mTwoPlayerModeB = new Texture("2 Player Game B", "emulogic.ttf", 32, { 0, 230, 0 });

	mPlayModes->Parent(this);
	mOnePlayerModeA->Parent(mPlayModes);
	mOnePlayerModeB->Parent(mPlayModes);
	mTwoPlayerModeA->Parent(mPlayModes);
	mTwoPlayerModeB->Parent(mPlayModes);

	mOnePlayerModeA->Position(0.0f, 45.0f);
	mOnePlayerModeB->Position(0.0f, 110.0f);
	mTwoPlayerModeA->Position(0.0f, 175.0f);
	mTwoPlayerModeB->Position(0.0f, 240.0f);

	mCursor = new Texture("cursor.png");
	mCursor->Parent(mPlayModes);
	mCursor->Position(-280.f, 47.5f);
	
	mCursorStartPos = mCursor->Position(LOCAL);
	mCursorOffset = Vector2(0.0f, 65.0f);
	mSelectedMode = 0;

	// Bottom Bar Entities
	mCopyrights = new Texture("©1984 Nintendo Co.,LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
	mCopyrights->Parent(this);
	mCopyrights->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.925f);
	mCopyrights->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.925f);

	PlayTheme();
}
StartScreen::~StartScreen() {
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;
	//mUI = nullptr;

	// Logo Entities
	delete mLogo;
	mLogo = nullptr;
	delete mDonkeyKong;
	mDonkeyKong = nullptr;
	delete mTitle;
	mTitle = nullptr;

	// Play Modes Entites
	delete mPlayModes;
	mPlayModes = nullptr;
	delete mOnePlayerModeA;
	mOnePlayerModeA = nullptr;
	delete mOnePlayerModeB;
	mOnePlayerModeB = nullptr;
	delete mTwoPlayerModeA;
	mOnePlayerModeA = nullptr;
	delete mTwoPlayerModeB;
	mOnePlayerModeB = nullptr;
	delete mCursor;
	mCursor = nullptr;

	// Bottom Bar Entities
	delete mCopyrights;
	mCopyrights = nullptr;
}

void StartScreen::PlayTheme() {
	mAudioManager->PlayMusic("MUS/DK3Theme.wav", 0);
}

void StartScreen::Update() {
	mDonkeyKong->Update();
	if (!mAnimationDone) {
		//mUI->SetLabelVisible(true);
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
	mAnimationTotalTime = 4.45f;
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
		mSelectedMode = 3;
	}
	else if (mSelectedMode > 3) {
		mSelectedMode = 0;
	}

	mCursor->Position(mCursorStartPos + mCursorOffset * (float)mSelectedMode);
}

void StartScreen::Render() {
	if (mAnimationDone) {
		//mUI->Render();

		mOnePlayerModeA->Render();
		mOnePlayerModeB->Render();
		mTwoPlayerModeA->Render();
		mTwoPlayerModeB->Render();
		mCursor->Render();

		mCopyrights->Render();
	}

	mDonkeyKong->Render();
	mTitle->Render();
}