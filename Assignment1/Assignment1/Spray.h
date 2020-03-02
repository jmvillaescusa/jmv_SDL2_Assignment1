#ifndef _SPRAY_H
#define _SPRAY_H
#include "AnimatedTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Spray : public GameEntity {
private:
	static const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;
	AnimatedTexture* mTexture;

	float mSpeed;

public:
	Spray();
	~Spray();

	void Fire(Vector2 pos);
	void Reload();

	void Update();
	void Render();
};
#endif // !_BULLET_H
