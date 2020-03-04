#ifndef _FLOWERS_H
#define _FLOWERS_H
#include "Texture.h"

using namespace SDLFramework;

class Flower : public GameEntity {
private:
	Texture* mFlower[5]; 

public:
	Flower(int);
	~Flower();

	void CreateCollision(int);

	void Render(int);
};

#endif // !_FLOWERS_H
