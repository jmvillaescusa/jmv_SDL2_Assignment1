#include "PlayScreen.h"

void PlayScreen::StartNextLevel() {
	mLevelStartTimer = 0.0f;

	UpdateLevelLabel();
	
	delete mLevel;
	mLevel = new Level(mCurrentLevel, mPlayer);
	mLevel->SetLevelStarted(true);
	mLevel->SetPlayerHit(false);

	mBees->Active(true);

	std::cout << "Speed: " << mDK->GetSpeed() << std::endl;
	std::cout << "Stun:  " << mDK->GetStunDelay() << std::endl;
	std::cout << "Stage: " << mCurrentLevel << std::endl;
	std::cout << "Lives: " << mPlayer->GetLives() << std::endl << std::endl;
}

void PlayScreen::UpdateLevelLabel() {
	if (mLevelLabel != nullptr) {
		delete mLevelLabel;
		if (!mLevel->GetPlayerHit()) {
			mCurrentLevel++;
			if (mCurrentLevel <= 7) {
				mDKSpeed++;
				if (mCurrentLevel <= 5) {
					mDKStun -= 0.05;
				}
				else {
					mDKStun = 0.25;
				}
			}
			else {
				mDKSpeed = 17;
				mDKStun = 0.25;
			}
			mDK->SetSpeed(mDKSpeed);
			mDK->SetStunDelay(mDKStun);
		}
	}

	if (mCurrentLevel == 0) {
		mLevelLabel = new Texture("Stage " + std::to_string(mCurrentLevel + 1), "emulogic.ttf", 32, { 220, 220, 220 });
		mLevelLabel->Parent(this);
		mLevelLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.475f);
	}

	else {
		mLevelLabel = new Texture("Stage " + std::to_string(mCurrentLevel), "emulogic.ttf", 32, { 220, 220, 220 });
		mLevelLabel->Parent(this);
		mLevelLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.475f);
	}
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

	mBeehiveA = new AnimatedTexture("beehive.png", 0, 0, 64, 64, 2, 0.25, AnimatedTexture::HORIZONTAL);
	mBeehiveB = new AnimatedTexture("beehive.png", 0, 0, 64, 64, 2, 0.25, AnimatedTexture::HORIZONTAL);
	mBeehiveA->Parent(this);
	mBeehiveB->Parent(this);
	mBeehiveA->Position(Graphics::SCREEN_WIDTH * 0.29f, Graphics::SCREEN_HEIGHT * 0.184f);
	mBeehiveB->Position(Graphics::SCREEN_WIDTH * 0.71f, Graphics::SCREEN_HEIGHT * 0.184f);

	mBees = new Bee();
	mBees->Parent(this);

	mReadyLabel = new Texture("Ready?", "emulogic.ttf", 32, { 220, 220, 220 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.525f);

	mCurrentLevel = 0;
	mLevelStartTimer = 0;
	mGameStarted = false;

	mLevelStartDelay = 2.0f;
	mLevel = new Level(mCurrentLevel, mPlayer);
	mLevel->SetLevelStarted(false);
	UpdateLevelLabel();

	mPlayer = nullptr;

	mDK = DonkeyKong::Instance();
	mDK->Parent(this);
	mDKSpeed = mDK->GetSpeed();
	mDKStun = mDK->GetStunDelay();
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

	delete mBeehiveA;
	mBeehiveA = nullptr;
	delete mBeehiveB;
	mBeehiveB = nullptr;

	delete mBees;
	mBees = nullptr;

	mPlayer = nullptr;
	mDK = nullptr;
}

void PlayScreen::StartNewGame() {
	delete mPlayer;
	mPlayer = Player::Instance();
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.75f);
	mPlayer->Active(true);

	mUI->SetLives(mPlayer->GetLives());
	mUI->SetPlayerScore(mPlayer->Score());

	mGameStarted = true;
	mLevel->SetLevelStarted(false);
	mLevelStartTimer = 0.0f;
	mCurrentLevel = 0;
	// Play theme
} 

bool PlayScreen::GameOver() {
	return !mLevel->GetLevelStarted() ? false : (mLevel->State() == Level::GAMEOVER);
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

		if (mLevel->CollisionCheck(mPlayer->mSprays[i], mBees) && !mPlayer->mSprays[i]->GetContact()) {
			mPlayer->mSprays[i]->SetContact(true);

			std::cout << "Contact!\n";
		}
	}
}

void PlayScreen::Update() {
	if (mGameStarted) {
		if (!mLevel->GetLevelStarted()) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
				mLevel->LevelStart();
			}

			mBeehiveA->Update();
			mBeehiveB->Update();

			mBees->Active(false);
		}
		else {

			PlatformCollisions();
			SprayCollision();
			mLevel->Update();
			if (mLevel->State() == Level::FINISHED) {
				mDK->Translate(-Vec2_Up * 45 * 2 * mTimer->DeltaTime(), WORLD);

				if (mDK->Position().y <= -300) {
					mLevel->SetLevelStarted(false);
				}
			}

			mPlayer->Update();
			mDK->Update();
			mBees->Update();

			mUI->SetPlayerScore(mPlayer->Score());

			PlatformCollisions();
			SprayCollision();

			// Level Complete
			if (mDK->Position().y <= -125) {
				mLevel->LevelFinished();
			}
			
			// Player loses a life
			if (mDK->Position().y >= 225) {
				if (mDK->Position().y <= 314.0f) {
					mDK->Translate(Vec2_Up * 50 * 3 * mTimer->DeltaTime(), WORLD);
				}
				else {
					mDK->mState = DonkeyKong::STAND;
					mLevel->SetPlayerHit(true);
				}
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
	if (!mLevel->GetLevelStarted()) {
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
		if (mLevel->GetLevelStarted()) {
			mLevel->Render();

			mBees->Render();
		}

		mPlayer->Render();
		mDK->Render();

		mBeehiveA->Render();
		mBeehiveB->Render();
	}

	mUI->Render();
}