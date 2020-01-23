#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include <SDL.h>
#include "Timer.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ScreenManager.h"

namespace SDLFramework {
	class GameManager {
	private:
		static GameManager* sInstance;
		bool mQuit;
		Graphics* mGraphics;

		SDL_Event mEvent;

		const int FRAME_RATE = 60;
		Timer* mTimer;

		GameEntity* mParent;
		GameEntity* mChild;

		AssetManager* mAssetManager;
		InputManager* mInputManager;

		AudioManager* mAudioManager;
		
		ScreenManager* mScreenManager;

	public: 
		static GameManager* Instance();
		static void Release();

		void Run();

		void Update();
		void LateUpdate();

		void Render();

		GameManager();
		~GameManager();
	};
}

#endif // !_GAMEMANAGER_H