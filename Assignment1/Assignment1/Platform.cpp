#include "Platform.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Platform::IgnoreCollisions() {
	return !Active();
}

Platform::Platform() {
	mPlatform = new Texture("platform.png");
	mPlatform->Parent(this);
	mPlatform->Position(Vec2_Zero);

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}
Platform::~Platform() {
	delete mPlatform;
	mPlatform = nullptr;
}

void Platform::Render() {
	mPlatform->Render();

	PhysEntity::Render();
}