#include "Level.h"

void Level::HandleStartLebels() {
	mLabelTimer += mTimer->DeltaTime();
	//if(mLabelTimer >= mLevel)
}

void Level::HandleCollisions() {
	if (!mPlayerHit) {
		if (mPlayer->WasHit()) {
			

			mPlayerHit = true;
			mRespawnTimer = 0.0f;
			//mPlayer->Active(false);
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
				//mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				
			}
		}
	}
}
// Enemy Behavior
void Level::HandleEnemySpawning(){}
void Level::HandleEnemyDiving(){}

void Level::StartStage() {
	mLevelStarted = true;
}

Level::Level(int level, Player* player) {
	mTimer = Timer::Instance();

	mLevel = level;
	mLevelStarted = false;

	mLabelTimer = 0.0f;

	// UI

	mPlayer = player;
	mPlayerHit = false;
	mRespawnDelay = 3.0f;
	mRespawnTimer = 0.0f;
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = RUNNING;

	// Enemy
}
Level::~Level() {
	mTimer = nullptr;

	mPlayer = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;
}

Level::LevelStates Level::State() {
	return mCurrentState;
}

void Level::Update() {
	if (!mLevelStarted) {
		HandleStartLebels();
	}
	else {
		/*if () {

		}*/

		/*for (auto e : mEnemies) {
			e->Update();
		}*/

		HandleCollisions();

		if (mPlayerHit) {
			HandlePlayerDeath();
		}
	}
}
void Level::Render() {

}