#include "UserInterface.h"

UserInterface* UserInterface::sInstance = nullptr;
UserInterface* UserInterface::Instance() {
	if (sInstance == nullptr) {
		sInstance = new UserInterface();
	}
	return sInstance;
}
void UserInterface::Release() {
	delete sInstance;
	sInstance = nullptr;
}

UserInterface::UserInterface() {
	mTimer = Timer::Instance();
	mPlayer = Player::Instance();

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 32.5);
	mTopBar->Parent(this);

	mHighLabel = new Texture("TOP", "emulogic.ttf", 32, { 200, 0, 0 });
	mHighLabel->Parent(mTopBar);
	mHighLabel->Position(-Graphics::SCREEN_WIDTH * 0.10f, 0.0f);

	mHighScoreboard = new Scoreboard();
	mHighScoreboard->Parent(mTopBar);
	mHighScoreboard->Position(Graphics::SCREEN_WIDTH * 0.12f, 0);

	mPlayerOneLabel = new Texture("1UP", "emulogic.ttf", 32, { 0, 0, 195 });
	mPlayerOneLabel->Parent(mTopBar);
	mPlayerOneLabel->Position(-Graphics::SCREEN_WIDTH * 0.42f, 0.0f);

	mPlayerOneScore = new Scoreboard();
	mPlayerOneScore->Parent(mTopBar);
	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.2f, 0);

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mPlayerOneLabelVisible = true;

	mLives = new Texture(std::to_string(mPlayer->GetLives()), "emulogic.ttf", 32, { 220, 220, 220 });
	mLives->Parent(mTopBar);
	mLives->Position(Graphics::SCREEN_WIDTH * 0.45f, 0);

	mLivesLabel = new Texture("LIFE", "emulogic.ttf", 32, {0, 0, 195});
	mLivesLabel->Parent(mTopBar);
	mLivesLabel->Position(Graphics::SCREEN_WIDTH * 0.35f, 0);
}
UserInterface::~UserInterface() {
	mTimer = nullptr;
	mPlayer = nullptr;

	delete mTopBar;
	mTopBar = nullptr;

	delete mHighLabel;
	mHighLabel = nullptr;
	delete mHighScoreboard;
	mHighScoreboard = nullptr;

	delete mPlayerOneLabel;
	mPlayerOneLabel = nullptr;
	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;
	delete mLives;
	mLives = nullptr;
	delete mLivesLabel;
	mLivesLabel = nullptr;
}

void UserInterface::SetHighScore(int score) {
	mHighScoreboard->Score(score);
}

void UserInterface::SetPlayerScore(int score) {
	mPlayerOneScore->Score(score);
}

void UserInterface::SetLives(int lives) {
	mCurrentLife = lives;
}

void UserInterface::Update() {
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval) {
		mPlayerOneLabelVisible = !mPlayerOneLabelVisible;
		mBlinkTimer = 0.0f;
	}

	if (mLives != nullptr && mPlayer->WasHit()) {
		mPlayer->DecreaseLife();
		mPlayer->SetHit(false);

		delete mLives;
		mLives = new Texture(std::to_string(mPlayer->GetLives()), "emulogic.ttf", 32, { 220, 220, 220 });
		mLives->Parent(mTopBar);
		mLives->Position(Graphics::SCREEN_WIDTH * 0.45f, 0);
	}
}

void UserInterface::Render() {
	mHighLabel->Render();
	mHighScoreboard->Render();

	if (mPlayerOneLabelVisible) {
		mPlayerOneLabel->Render();
	}

	mLives->Render();
	mLivesLabel->Render();
	mPlayerOneScore->Render();
}