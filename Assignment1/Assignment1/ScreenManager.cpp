#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;
ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}
	return sInstance;
}
void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = START;
}
ScreenManager::~ScreenManager()  {
	mInput = nullptr;
	delete mStartScreen;
	mStartScreen = nullptr;

}

void ScreenManager::Update() {

	switch (mCurrentScreen)
	{
	case START:
		mStartScreen->Update();
		

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = PLAY;
			mStartScreen->ResetAnimation();
			mPlayScreen->StartNewGame();
		}
		break;

	case PLAY:
		mPlayScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = START;
			mStartScreen->PlayTheme();
		}
		break;
	}
}

void ScreenManager::Render() {

	switch (mCurrentScreen) {
	case START:
		mStartScreen->Render();
		break;

	case PLAY:
		mPlayScreen->Render();
		break;
	}
}