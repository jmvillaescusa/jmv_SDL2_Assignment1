#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include "Graphics.h"
#include <map>
#include <sstream>
#include <SDL_mixer.h>

namespace SDLFramework {
	class AssetManager {
	private:
		static AssetManager* sInstance;

		std::map<std::string, TTF_Font*> mFonts;
		std::map<std::string, SDL_Texture*> mText;

		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;

		std::map<Mix_Music*, unsigned> mMusicRefCount;
		std::map<Mix_Chunk*, unsigned*> mSFXRefCount;

	public:
		static AssetManager* Instance();
		static void Release();
		SDL_Texture* GetTexture(std::string filename, bool managed = false);
		SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed = false);
		void DestroyTexture(SDL_Texture* texture);

		Mix_Music* GetMusic(std::string filename, bool managed = false);
		Mix_Chunk* GetSFX(std::string filename, bool managed = false);
		void DestroyMusic(Mix_Music* music);
		void DestroySFX(Mix_Chunk* sfx);

	private:
		std::map<std::string, SDL_Texture*> mTextures;
		std::map<SDL_Texture*, unsigned> mTexturesRefCount;

		TTF_Font* GetFont(std::string filename, int size);

		AssetManager();
		~AssetManager();
	};
}

#endif // !_ASSETMANAGER_H