#include "Level.h"

void Level::HandleStartLevels() {
	mLevelTimer += mTimer->DeltaTime();
	if (mLevelTimer >= 1.0f) {
		if (mLevel > 1) {
			StartLevel();
		}
		else {
			if (mLevelTimer >= 2.0f) {
				StartLevel();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
}

void Level::HandlePlayerDeath() {
	if (!mPlayer->IsAnimating()) {
		if (mPlayer->Lives() > 0) {
			if (mRespawnTimer == 0.0f) {
				mPlayer->Visible(false);
			}

			mRespawnTimer += mTimer->DeltaTime();
			if (mRespawnTimer >= mRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				
			}
		}
		else {
			if (mGameOverTimer == 0.0f) {
				mPlayer->Visible(false);
			}
			
			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = GAMEOVER;
			}
		}
	}
}

// Enemy Behavior
void Level::HandleEnemySpawning(){}
void Level::HandleEnemyDiving(){}

void Level::StartLevel() {
	mLevelStarted = true;
}

Level::Level(int level, Player* player) {
	mTimer = Timer::Instance();
	mUI = UserInterface::Instance();

	mLevel = level;
	mLevelStarted = false;

	mLevelTimer = 0.0f;

	mPlayer = player;
	mPlayerHit = false;
	mRespawnDelay = 3.0f;
	mRespawnTimer = 0.0f;
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = RUNNING;

	// Enemy
}
Level::~Level() {
	mTimer = nullptr;
	mPlayer = nullptr;
	mUI = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;
}

Level::LevelStates Level::State() {
	return mCurrentState;
}

void Level::Update() {
	if (!mLevelStarted) {
		HandleStartLevels();
	}
	else {
		/*if () {

		}*/

		/*for (auto e : mEnemies) {
			e->Update();
		}*/

		if (mPlayerHit) {
			HandlePlayerDeath();
		}
	}
}
void Level::Render() {
	if (!mLevelStarted) {

	}
	else {
		// Render Enemies


		if (mPlayerHit) {
			if (mRespawnTimer >= mRespawnLabelOnScreen) {
				
			}

			if (mGameOverTimer >= mGameOverLabelOnScreen) {
				mGameOverLabel->Render();
			}
		}
	}
}