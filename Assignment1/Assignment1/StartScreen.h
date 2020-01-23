#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInputManager;

	// Logo Entities
	GameEntity* mLogo;
	AnimatedTexture* mDonkeyKong;
	Texture* mTitle;

	// Play Mode Entities
	int mSelectedMode;

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

	int SelectedMode();
	void ChangeSelectedMode(int change);

	void Update() override;
	void Render() override;
};
#endif // !_STARTSCREEN_H