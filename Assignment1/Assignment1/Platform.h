#ifndef _PLATFORM_H
#define _PLATFORM_H
#include "Texture.h"

using namespace SDLFramework;

class Platform : public GameEntity {
private: 
	Texture* mPlatformBase;
	Texture* mPlatformOne;
	Texture* mPlatformTwo;
	Texture* mPlatformThree;

public:
	Platform();
	~Platform();

	void Render();
};
#endif // !_PLATFORM_H