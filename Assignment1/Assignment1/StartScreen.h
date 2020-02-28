#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"
#include "AudioManager.h"
#include "UserInterface.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;
	

	// Top Bar Entities
	/*GameEntity* mTopBar;
	Texture* mPlayerTwo;
	Texture* mPlayerOne;
	Texture* mHiScore;

	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;*/
	UserInterface* mUI;

	// Logo Entities
	GameEntity* mLogo;
	AnimatedTexture* mDonkeyKong;
	Texture* mTitle;

	// Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mOnePlayerModeA;
	Texture* mOnePlayerModeB;
	Texture* mTwoPlayerModeA;
	Texture* mTwoPlayerModeB;

	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedMode;

	// Bottom Bar Entities
	Texture* mCopyrights;

	// Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

public:
	StartScreen();
	~StartScreen();

	void ResetAnimation();

	void PlayTheme();

	int SelectedMode();
	void ChangeSelectedMode(int change);

	void Update() override;
	void Render() override;
};
#endif // !_STARTSCREEN_H