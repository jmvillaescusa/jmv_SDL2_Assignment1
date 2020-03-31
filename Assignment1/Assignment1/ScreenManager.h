#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"

class ScreenManager {
private:
	static ScreenManager* sInstance;

	InputManager* mInput;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

public:
	enum Screens { START, PLAY };
	Screens mCurrentScreen;

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};

#endif // !1