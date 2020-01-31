#include "PlayScreen.h"

void PlayScreen::StartNextLevel() {
	mCurrentLevel += 1;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	//mLevel = new Level(mCurrentLevel, mPlayer);
}

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	

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
}

void PlayScreen::Update() {

}
void PlayScreen::Render() {

}