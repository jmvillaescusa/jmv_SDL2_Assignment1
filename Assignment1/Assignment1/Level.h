#ifndef _LEVEL_H
#define _LEVEL_H
#include "UserInterface.h"
#include "Player.h"

#include "Platform.h"

class Level : public GameEntity {
public:
	enum LevelStates {RUNNING, FINISHED, GAMEOVER};

private:
	Timer* mTimer;
	UserInterface* mUI;

	int mLevel;
	bool mLevelStarted;

	float mLevelTimer;

	Player* mPlayer;
	bool mPlayerHit;
	float mRespawnDelay;
	float mRespawnTimer;
	float mRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LevelStates mCurrentState;

	// Enemy codes

	void StartLevel();
	void HandleStartLevels();
	void HandleCollisions();
	void HandlePlayerDeath();

	//bool EnemyFlyingIn();

	void HandleEnemySpawning();
	void HandleEnemyDiving();

public:
	Level(int stage, UserInterface * UI, Player* player);
	~Level();

	LevelStates State();

	void Update();
	void Render();
};
#endif // !_LEVEL_H