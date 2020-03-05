#include "Player.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		// Move Right
		mMovingRight = true;
		mIsMoving = true;
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), WORLD);
		mPlayerWalkRight->Update();
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		// Move Left
		mMovingRight = false;
		mIsMoving = true;
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), WORLD);
		mPlayerWalkLeft->Update();
	}

	if (mInput->KeyPressed(SDL_SCANCODE_UP) && !mAirborne && mPlayer->Position().y > 571.0f) {
		// Jumping
		mIsMoving = true;
		Translate(-Vec2_Up * 3800 * mTimer->DeltaTime(), WORLD);
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_DOWN) && mPlayer->Position().y < 690.0f) {
		// Fall through platforms
		mIsMoving = true;
		mAirborne = true;
	}

	// Gravity
	if (mAirborne) {
		Translate(Vec2_Up * (mMoveSpeed + 300) * mTimer->DeltaTime(), WORLD);
	}


	Vector2 pos = Position(LOCAL);
	mCollision.x = Position().x;
	mCollision.y = Position().y + (mPlayer->GetHeight() / 2);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		for (int i = 0; i < MAX_SPRAYS; ++i) {
			if (!mSprays[i]->Active()) {
				mSprays[i]->Fire(Position());
				mSprays[i]->SetContact(false);
				break;
			}
		}
	}
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;
	mWasHit = false;

	mIsMoving = NULL;
	mMovingRight = NULL;

	mAirborne = true;

	mScore = 0;
	mLives = 3;

	// Sprays
	mSprays[0] = NULL;
	for (int i = 0; i < MAX_SPRAYS; ++i) {
		mSprays[i] = new Spray();
	}

	mPlayer = new Texture("stanley_walkleft.png", 0, 0, 77, 90);
	mPlayer->Parent(this);
	mPlayer->Position(Vec2_Zero);

	mCollision.x = Position().x;
	mCollision.y = Position().y + (mPlayer->GetHeight() / 2);
	mCollision.w = (float)mPlayer->GetWidth();
	mCollision.h = (float)mPlayer->GetHeight();

	mPlayerWalkLeft = new AnimatedTexture("stanley_walkleft.png", 0, 0, 77, 90, 4, 0.5f, AnimatedTexture::HORIZONTAL);
	mPlayerWalkLeft->Parent(mPlayer);
	mPlayerWalkRight = new AnimatedTexture("stanley_walkright.png", 0, 0, 77, 90, 4, 0.5f, AnimatedTexture::HORIZONTAL);
	mPlayerWalkRight->Parent(mPlayer);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(190.0f, 835.0f);

	mDeathAnimation = new AnimatedTexture("stanley_death.png", 0, 0, 96, 96, 4, 2.5f, AnimatedTexture::HORIZONTAL);
	mDeathAnimation->Parent(mPlayer);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::ONCE);
}
Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
	delete mPlayerWalkLeft;
	mPlayerWalkLeft = nullptr;
	delete mPlayerWalkRight;
	mPlayerWalkRight = nullptr;
	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	// Bullets
	for (auto s : mSprays) {
		delete s;
	}
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::WasHit() {
	return mWasHit;
}

void Player::Update() {
	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->isAnimating();
	}
	else {
		if (Active()) {
			HandleMovement();
			HandleFiring();
		}
	}

	// Bullets
	for (int i = 0; i < MAX_SPRAYS; ++i) {
		mSprays[i]->Update();
	}

	if (mInput->KeyPressed(SDL_SCANCODE_D)) {
		mAnimating = !mAnimating;
	}
}
void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else if (mIsMoving) {
			if (mMovingRight) {
				mPlayerWalkRight->Render();
			}
			else {
				mPlayerWalkLeft->Render();
			}
		}
		else {
			mPlayer->Render();
		}
	}

	// bullets render
	for (int i = 0; i < MAX_SPRAYS; ++i) {
		mSprays[i]->Render();
	}
}