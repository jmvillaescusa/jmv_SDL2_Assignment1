#include "Spray.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Spray::IgnoreCollisions() {
	return !Active();
}

Spray::Spray(bool friendly) {
	mTimer = Timer::Instance();

	mTexture = new AnimatedTexture("spray.png", 0, 0, 56, 64, 7, 1.5f, AnimatedTexture::HORIZONTAL);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mSpeed = 500;

	Reload();

	// Collider
	//AddCollider(new BoxCollider()));

	if (friendly) {
		PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
	}
	else {
		PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
	}
}
Spray::~Spray() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Spray::Fire(Vector2 pos) {
	Position(pos);
	Active(true);
}

void Spray::Reload() {
	mTexture->ResetAnimation();
	Active(false);
}

void Spray::Hit(PhysEntity* other) {
	Reload();
}

void Spray::Update() {
	if (Active()) {

		Translate(-Vec2_Up * mSpeed * mTimer->DeltaTime());

		Vector2 pos = Position();
		if (pos.y < -OFFSCREEN_BUFFER) {
			Reload();
		}
		mTexture->Update();
	}
}

void Spray::Render() {
	if (Active()) {
		mTexture->Render();
		PhysEntity::Render();
	}
}