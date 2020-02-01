#ifndef _COLLIDER_H
#define _COLLIDER_H
#include "Texture.h"

using namespace SDLFramework;

class Collider : public GameEntity {
public:
	enum class ColliderType {BOX, CIRCLE}; // Type Safety

protected:
	ColliderType mType;

	static const bool DEBUG_COLLIDERS = true;
	Texture* mDebugTexture;

	void SetDebugTexture(Texture* tex);

public:
	Collider(ColliderType type);
	virtual ~Collider();

	virtual Vector2 GetFurthestPoint() = 0;

	ColliderType GetType();

	virtual void Render() override;
};
#endif // !_COLLIDER_H
