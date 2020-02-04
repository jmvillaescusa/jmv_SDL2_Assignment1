#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class UserInterface : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	GameEntity* mTopBar;

	Texture* mHighLabel;
	Scoreboard* mHighScoreboard;

	Texture* mPlayerOneLabel;
	Scoreboard* mPlayerOneScore;

	float mBlinkTimer;
	float mBlinkInterval;
	bool mPlayerOneLabelVisible;

	GameEntity* mLives;
	Texture* mLivesLabel;
	int mTotalLives;

public:
	UserInterface();
	~UserInterface();

	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetLives(int ships);

	void Update();
	void Render();
};
#endif // !_USERINTERFACE_H
