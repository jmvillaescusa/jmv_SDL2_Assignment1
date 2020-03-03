#ifndef _PLATFORM_H
#define _PLATFORM_H
#include "Texture.h"

using namespace SDLFramework;

class Platform : public GameEntity {
private: 
	Texture* mPlatform[4];

public:
	Platform(int);
	~Platform();

	void CreateCollision(int);

	void Render(int);
};
#endif // !_PLATFORM_H