#ifndef _PLATFORM_H
#define _PLATFORM_H
#include "PhysEntity.h"

using namespace SDLFramework;

class Platform : public PhysEntity {
private: 
	Texture* mPlatform;

	bool IgnoreCollisions() override;

public:
	Platform();
	~Platform();

	void Render();


};
#endif // !_PLATFORM_H

