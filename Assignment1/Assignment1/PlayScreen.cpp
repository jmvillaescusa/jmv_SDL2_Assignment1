#include "PlayScreen.h"

void PlayScreen::StartNextLevel() {
	mCurrentLevel += 1;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	
	delete mLevel;
	mLevel = new Level(mCurrentLevel, mPlayer);

	delete mDK;
	mDK = new DonkeyKong();

	if (mCurrentLevel <= 7) {
		mDK->SetSpeed(mDK->GetSpeed() + mCurrentLevel);
		if (mCurrentLevel <= 5) {
			mDK->SetStunDelay(mDK->GetStunDelay() - (mCurrentLevel/20.0f));
		}
		else {
			mDK->SetStunDelay(0.25);
		}
	}
	else {
		mDK->SetSpeed(17);
		mDK->SetStunDelay(0.25);
	}

	delete mReadyLabel;
	mReadyLabel = new Texture("Ready?", "emulogic.ttf", 32, { 220, 220, 220 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.525f);
	
	delete mLevelLabel;
	mLevelLabel = new Texture("Stage " + std::to_string(mCurrentLevel + 1), "emulogic.ttf", 32, { 220, 220, 220 });
	mLevelLabel->Parent(this);
	mLevelLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.475f);
}

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mUI = UserInterface::Instance();

	mPlatform[0] = NULL;
	for (int i = 0; i < 4; i++) {
		mPlatform[i] = new Platform(i);
	}

	mFlower[0] = NULL;
	for (int i = 0; i < 5; i++) {
		mFlower[i] = new Flower(i);
	}

	mTree = new Texture("tree.png", 0, 0, 1024, 448);
	mTree->Parent(this);
	mTree->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mVines = new Texture("vines.png", 0, 0, 496, 320);
	mVines->Parent(this);
	mVines->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.26f);

	mReadyLabel = new Texture("Ready?", "emulogic.ttf", 32, { 220, 220, 220 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.525f);

	mLevelLabel = new Texture("Stage " + std::to_string(mCurrentLevel + 1), "emulogic.ttf", 32, { 220, 220, 220 });
	mLevelLabel->Parent(this);
	mLevelLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.475f);

	mLevel = nullptr;
	mLevelStartDelay = 2.0f;
	mLevelStarted = false;

	mPlayer = nullptr;

	mDK = new DonkeyKong();
	mDK->Parent(this);

	mCurrentLevel = 0;
	mLevelStartTimer = 0;
	mGameStarted = false;

	// Enemy::CreatePaths();
}
PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;
	mUI = nullptr;

	delete mReadyLabel;
	mReadyLabel = nullptr;
	delete mLevelLabel;
	mLevelLabel = nullptr;

	delete mLevel;
	mLevel = nullptr;

	for (int i = 0; i < 4; i++) {
		delete mPlatform[i];
		mPlatform[i] = nullptr;
	}
	
	for (int i = 0; i < 5; i++) {
		delete mFlower[i];
		mFlower[i] = nullptr;
	}

	delete mTree;
	mTree = nullptr;
	delete mVines;
	mVines = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
	delete mDK;
	mDK = nullptr;
}

void PlayScreen::StartNewGame() {
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.75f);
	mPlayer->Active(true);

	mUI->SetLives(mPlayer->Lives());
	mUI->SetPlayerScore(mPlayer->Score());

	mGameStarted = true;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentLevel = 0;
	// Play theme
} 

bool PlayScreen::GameOver() {
	return !mLevelStarted ? false : (mLevel->State() == Level::GAMEOVER);
}

void PlayScreen::PlatformCollisions() {
	if (mLevel->CollisionCheck(mPlayer, mPlatform[1]) || mLevel->CollisionCheck(mPlayer, mPlatform[2]) || mLevel->CollisionCheck(mPlayer, mPlatform[3])) {
		mPlayer->SetAirborne(false);
	}
	else {
		mPlayer->SetAirborne(true);
	}
}

void PlayScreen::SprayCollision() {
	for (int i = 0; i < 3; i++) {
		if (mLevel->CollisionCheck(mPlayer->mSprays[i], mDK) && !mPlayer->mSprays[i]->GetContact()) {
			mPlayer->mSprays[i]->SetContact(true);
			mDK->ResetTimer();
			mDK->mState = DonkeyKong::HIT;
		}
	}
}

void PlayScreen::Update() {
	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
				mLevel->LevelStart();
			}
		}
		else {
			mLevel->Update();
			if (mLevel->State() == Level::FINISHED) {
				mDK->Translate(-Vec2_Up * 45 * 2 * mTimer->DeltaTime(), WORLD);

				if (mDK->Position().y <= -300) {
					mLevelStarted = false;
				}
			}

			mPlayer->Update();
			mDK->Update();
			mUI->SetPlayerScore(mPlayer->Score());

			PlatformCollisions();
			SprayCollision();

			// Level Complete
			if (mDK->Position().y <= -125) {
				
				mLevel->LevelFinished();
			}
			
			// Player loses a life
			if (mDK->Position().y >= 225) {
				
			}
		}
		if (mCurrentLevel > 0) {
			mUI->Update();
		}
	}
	else {
		mGameStarted = true;
	}
}
void PlayScreen::Render() {
	if (!mLevelStarted) {
		// Render Stage label and Ready label
		mReadyLabel->Render();
		mLevelLabel->Render();
	}
	
	for (int i = 0; i < 4; i++) {
		mPlatform[i]->Render(i);
	}
	for (int i = 0; i < 5; i++) {
		mFlower[i]->Render(i);
	}
	mTree->Render();
	mVines->Render();

	if (mGameStarted) {
		if (mLevelStarted) {
			mLevel->Render();
		}

		mPlayer->Render();
		mDK->Render();
	}

	mUI->Render();
}