#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	

	// Screen Animation Variables
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Position(mAnimationStartPos);
}
StartScreen::~StartScreen() {
	
}

void StartScreen::Update() {
	
}

void StartScreen::ChangeSelectedMode(int change) {
	
}

void StartScreen::Render() {
	
}