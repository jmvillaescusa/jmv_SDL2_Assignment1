#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Spray.h"

using namespace SDLFramework;

class Player : public GameEntity {
public:
	// states
private:
	static Player* sInstance;

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;
	bool mIsMoving;
	bool mMovingRight;
	bool mAirborne;

	int mScore;
	int mLives;

	Texture* mPlayer;
	AnimatedTexture* mPlayerWalkLeft;
	AnimatedTexture* mPlayerWalkRight;
	AnimatedTexture* mDeathAnimation;
	
	float mMoveSpeed;
	Vector2 mMoveBounds;

	static const int MAX_SPRAYS = 3;

	void HandleMovement();
	void HandleFiring();

public:
	Spray* mSprays[MAX_SPRAYS];

public:
	Player();
	~Player();

	static Player* Instance();
	static void Release();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();

	int Lives();
	void DecreaseLife() { mLives--; }

	bool GetAirborne() { return mAirborne; }
	void SetAirborne(bool a) { mAirborne = a; }

	Spray* GetSpray() { return mSprays[0]; }

	void AddScore(int change);

	bool WasHit();

	void Update();
	void Render();

};
#endif // !_PLAYER_H
