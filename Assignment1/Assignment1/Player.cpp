#include "Player.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		mMovingRight = true;
		mIsMoving = true;
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), WORLD);
		mPlayerWalkRight->Update();
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		mMovingRight = false;
		mIsMoving = true;
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), WORLD);
		mPlayerWalkLeft->Update();
	}

	if (mInput->KeyDown(SDL_SCANCODE_UP)) {
		// Intended for jump
		mIsMoving = true;
		Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), WORLD);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
		// Intended for jump
		mIsMoving = true;
		Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), WORLD);
	}

	if (mInput->KeyRelease(SDL_SCANCODE_RIGHT) || mInput->KeyRelease(SDL_SCANCODE_LEFT)) {
		mIsMoving = false;
	}
	if (mInput->KeyRelease(SDL_SCANCODE_UP) || mInput->KeyRelease(SDL_SCANCODE_DOWN)) {
		mIsMoving = false;
	}

	Vector2 pos = Position(LOCAL);
	mCollision.x = Position().x;
	mCollision.y = Position().y;
	/*if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}*/

	Position(pos);
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		for (int i = 0; i < MAX_SPRAYS; ++i) {
			if (!mSprays[i]->Active()) {
				mSprays[i]->Fire(Position());
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

	mScore = 0;
	mLives = 3;

	mPlayer = new Texture("stanley_walkleft.png", 0, 0, 77, 90);
	mPlayer->Parent(this);
	mPlayer->Position(Vec2_Zero);

	mCollision.x = Position().x;
	mCollision.y = Position().y;
	mCollision.w = mPlayer->GetSrcRect().w;
	mCollision.h = mPlayer->GetSrcRect().h;

	mPlayerWalkLeft = new AnimatedTexture("stanley_walkleft.png", 0, 0, 77, 90, 4, 0.5f, AnimatedTexture::HORIZONTAL);
	mPlayerWalkLeft->Parent(this);
	mPlayerWalkRight = new AnimatedTexture("stanley_walkright.png", 0, 0, 77, 90, 4, 0.5f, AnimatedTexture::HORIZONTAL);
	mPlayerWalkRight->Parent(this);

	mMoveSpeed = 300.0f;
	//mMoveBounds = Vector2(190.0f, 835.0f);

	mDeathAnimation = new AnimatedTexture("stanley_death.png", 0, 0, 96, 96, 4, 2.5f, AnimatedTexture::HORIZONTAL);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::ONCE);

	// Bullet
	for (int i = 0; i < MAX_SPRAYS; ++i) {
		mSprays[i] = new Spray();
	}

	// Collider
	

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