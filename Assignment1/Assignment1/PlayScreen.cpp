#include "PlayScreen.h"

void PlayScreen::StartNextLevel() {
	mCurrentLevel += 1;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentLevel, mPlayer);
}

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mPlatform = new Texture("platform.png", 0, 0, 1024, 288);
	mPlatform->Parent(this);
	mPlatform->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT - 144.0f);

	mTree = new Texture("tree.png", 0, 0, 1024, 448);
	mTree->Parent(this);
	mTree->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mVines = new Texture("vines.png", 0, 0, 496, 320);
	mVines->Parent(this);
	mVines->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.25f);

	mLevel = nullptr;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = nullptr;

	// Enemy::CreatePaths();
}
PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlatform;
	mPlatform = nullptr;
	delete mTree;
	mTree = nullptr;
	delete mVines;
	mVines = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::StartNewGame() {
	delete mPlayer;
	mPlayer = new Player();
	//mPlayer->Parent(this);
	//mPlayer->Position(Graphics::SCREEN_WIDTH 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	//mPlayer->Active(false);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentLevel = 0;
	// Play theme
}

bool PlayScreen::GameOver() {
	//return !mLevelStarted ? false : (mLevel->State() == Level::GAMEOVER);
	return false;
}

void PlayScreen::Update() {
	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}
		else {
			//mLevel->Update();
			/*if () {
				mLevelStarted = false;
			}*/
		}
		if (mCurrentLevel > 0) {

		}

		mPlayer->Update();
	}
}
void PlayScreen::Render() {
	if (!mGameStarted) {

	}

	if (mGameStarted) {
		if (mLevelStarted) {
			mLevel->Render();
		}

		//mPlayer->Render();
		
	}

	mPlatform->Render();
	mTree->Render();
	mVines->Render();
}