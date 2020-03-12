#ifndef _LEVEL_H
#define _LEVEL_H
#include "UserInterface.h"
#include "Player.h"
#include "Platform.h"
#include "Flower.h"
#include "DonkeyKong.h"

class Level : public GameEntity {
public:
	enum LevelStates {RUNNING, FINISHED, GAMEOVER};

protected:
	UserInterface* mUI;
	LevelStates mState;

private:
	Timer* mTimer;

	int mLevel;
	bool mLevelStarted = false;

	float mLevelTimer;

	Player* mPlayer;
	bool mPlayerHit;
	float mRespawnDelay;
	float mRespawnTimer;
	float mRespawnLabelOnScreen;

	DonkeyKong* mDK;

	Texture* mGameOverLabel;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LevelStates mCurrentState;

	// Enemy codes

	void StartLevel();
	void HandleStartLevels();
	void HandlePlayerDeath();

	//bool EnemyFlyingIn();

	void HandleEnemySpawning();
	void HandleEnemyDiving();

public:
	Level(int stage, Player* player);
	~Level();

	bool CollisionCheck(GameEntity*, GameEntity*);

	LevelStates State();

	void LevelFinished() { mCurrentState = FINISHED; }
	void LevelStart() { mCurrentState = RUNNING; }

	bool GetLevelStarted() { return mLevelStarted; }
	void SetLevelStarted(bool l) { mLevelStarted = l; }

	void SetPlayerHit(bool h) { mPlayerHit = h; }
	bool GetPlayerHit() { return mPlayerHit; }

	void Update();
	void Render();
};
#endif // !_LEVEL_H