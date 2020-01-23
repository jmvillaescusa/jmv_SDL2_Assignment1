#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "StartScreen.h"

//using namespace SDLFramework;

class ScreenManager {
private:
	static ScreenManager* sInstance;

	enum Screens{START, PLAY};
	Screens mCurrentScreen;

	InputManager* mInput;
	StartScreen* mStartScreen;

public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};

#endif // !1