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
	bool mContact;

public:
	Spray();
	~Spray();

	void Fire(Vector2 pos);
	void Reload();

	void CreateCollisions();

	bool GetContact() { return mContact; }
	void SetContact(bool c) { mContact = c; }

	AnimatedTexture* GetTexture() { return mTexture; }

	void Update();
	void Render();
};
#endif // !_BULLET_H
