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
	//mUI = UserInterface::Instance();

	for (int i = 0; i < 4; i++) {
		mPlatform[i] = new Platform(i);
		mPlatform[i]->Parent(this);
		mPlatform[i]->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.929f);
	}

	mTree = new Texture("tree.png", 0, 0, 1024, 448);
	mTree->Parent(this);
	mTree->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mVines = new Texture("vines.png", 0, 0, 496, 320);
	mVines->Parent(this);
	mVines->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.26f);

	mLevel = nullptr;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = nullptr;

	mCurrentLevel = 0;
	mLevelStartTimer = 0;
	mGameStarted = false;

	// Enemy::CreatePaths();
}
PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;
	//mUI = nullptr;

	delete mLevel;
	mLevel = nullptr;

	for (int i = 0; i < 4; i++) {
		delete mPlatform[i];
		mPlatform[i] = nullptr;
	}
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
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);

	//mUI->SetHighScore(30000);
	//mUI->SetLives(mPlayer->Lives());
	//mUI->SetPlayerScore(mPlayer->Score());

	mGameStarted = true;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentLevel = 0;
	// Play theme
} 

bool PlayScreen::GameOver() {
	return !mLevelStarted ? false : (mLevel->State() == Level::GAMEOVER);
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
			mLevel->Update();
			if (mLevel->State() == Level::FINISHED) {
				mLevelStarted = false;
			}
		}
		if (mCurrentLevel > 0) {
			//mUI->Update();
		}

		mPlayer->Update();
		//mUI->SetPlayerScore(mPlayer->Score());
		std::cout << mPlatform[0]->GetCollision().y << std::endl;

		if (mLevel->CollisionCheck(mPlayer, mPlatform[1])) {
			//std::cout << "test";
			std::cout << "Test" << std::endl;
		}
	}
	else {
		mGameStarted = true;
	}
}
void PlayScreen::Render() {
	if (!mGameStarted) {
		
	}
	
	for (int i = 0; i < 4; i++) {
		mPlatform[i]->Render(i);
	}
	mTree->Render();
	mVines->Render();

	if (mGameStarted) {
		if (mLevelStarted) {
			mLevel->Render();
		}

		mPlayer->Render();
	}

	//mUI->Render();
}