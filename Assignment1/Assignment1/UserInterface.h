#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
#include "Timer.h"
#include "Scoreboard.h"

// Need Fixing

class UserInterface : public GameEntity {
private:
	static UserInterface* sInstance;

	Timer* mTimer;

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

	static UserInterface* Instance();
	static void Release();

	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetLives(int ships);

	void SetLabelVisible(bool b) { mPlayerOneLabelVisible = b; }

	void Update();
	void Render();
};
#endif // !_USERINTERFACE_H
