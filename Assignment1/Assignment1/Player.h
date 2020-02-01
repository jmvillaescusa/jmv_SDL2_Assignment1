#ifndef _PLAYER_H
#define _PLAYER_H
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	int mScore;
	int mLives;

	AnimatedTexture* mPlayer;
	AnimatedTexture* mDeathAnimation;
	
	float mMoveSpeed;
	Vector2 mMoveBounds;

	void HandleMovement();
	void HandleFiring();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;

	bool WasHit();

	void Update();
	void Render();

};
#endif // !_PLAYER_H
