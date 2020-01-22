#include "GameManager.h"

namespace SDLFramework {
	GameManager* GameManager::sInstance = nullptr;
	GameManager* GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		// Main game loop
		while (!mQuit) {
			mTimer->Update();

			// Event processing loop
			while (SDL_PollEvent(&mEvent)) {
				switch (mEvent.type) {
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}
			if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
				Update();
				LateUpdate();
				Render();
				mTimer->Reset();
			}
		}
	}

	void GameManager::Update() {
		mInputManager->Update();
	}

	void GameManager::LateUpdate() {
		mInputManager->UpdatePrevInput();
	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		mGraphics = Graphics::Instance();
		if (!Graphics::Initialized()) {
			mQuit = true;
		}

		mAssetManager = AssetManager::Instance();

		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();

		mTimer = Timer::Instance();
	}

	GameManager::~GameManager() {
		Timer::Release();
		mTimer = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;
		
		InputManager::Release();
		mInputManager = nullptr;

		Graphics::Release();
		mGraphics = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		SDL_Quit();
	}
}