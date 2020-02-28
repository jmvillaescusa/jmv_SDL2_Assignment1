#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "Level.h"

using namespace SDLFramework;

class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	Level* mLevel;
	UserInterface* mUI;

	Platform* mPlatform;
	Texture* mTree;
	Texture* mVines;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;

	bool mLevelStarted;
	int mCurrentLevel;

	Player* mPlayer;

	void StartNextLevel();

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	bool GameOver();

	void Update();
	void Render();
};
#endif // !_PLAYSCREEN_H