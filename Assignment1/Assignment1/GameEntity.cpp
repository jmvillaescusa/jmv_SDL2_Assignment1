#include "GameEntity.h"

namespace SDLFramework {
	GameEntity::GameEntity(float x, float y) : mPosition(x, y), mRotation(0.0f), mScale(Vec2_One), mActive(true), mParent(nullptr) {}
	SDLFramework::GameEntity::GameEntity(const Vector2& position) : mPosition(position), mRotation(0.0f), mScale(Vec2_One), mActive(true), mParent(nullptr) {}
	GameEntity::~GameEntity() { mParent = nullptr; }

	void GameEntity::Translate(Vector2 vec, Space space) {
		if (space == WORLD) {
			mPosition += vec;
		}
		else {
			mPosition += RotateVector(vec, Rotation());
		}
	}
	
	void GameEntity::Rotate(float amount) {
		mRotation += amount;
	}

	void GameEntity::Position(float x, float y) {
		mPosition = Vector2(x, y);
	}
	void GameEntity::Position(const Vector2& pos) {
		mPosition = pos;
	}
	Vector2 GameEntity::Position(Space space) {
		if (space == LOCAL || mParent == nullptr) {
			return mPosition;
		}
		Vector2 parentScale = mParent->Scale(WORLD);
		Vector2 rotPosition = RotateVector(mPosition, mParent->Rotation(LOCAL));

		return mParent->Position(WORLD) + Vector2(rotPosition.x * parentScale.x, rotPosition.y * parentScale.y);
	}

	void GameEntity::Rotation(float rot) {
		mRotation = rot;

		while (mRotation > 360.0f) {
			mRotation -= 360.0f;
		}

		while (mRotation < 360.0f) {
			mRotation += 360.0f;
		}
	}
	float GameEntity::Rotation(Space space) {
		if (space == LOCAL || mParent == nullptr) {
			return mRotation;
		}

		return mParent->Rotation(WORLD) + mRotation;
	}

	void GameEntity::Scale(Vector2 scale) {
		mScale = scale;
	}
	Vector2 GameEntity::Scale(Space space) {
		if (space == LOCAL || mParent == nullptr) {
			return mScale;
		}

		Vector2 scale = mParent->Scale(WORLD);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return scale;
	}

	void GameEntity::Active(bool active) {
		mActive = active;
	}
	bool GameEntity::Active() {
		return mActive;
	}

	void GameEntity::Parent(GameEntity* parent) {
		if (parent == nullptr) {
			mPosition = Position(WORLD);
			mRotation = Rotation(WORLD);
			mScale = Scale(WORLD);
		}
		else {
			if (mParent != nullptr) {
				Parent(nullptr);
			}
			Vector2 parentScale = parent->Scale(WORLD);

			mPosition = RotateVector(Position(WORLD) - parent->Position(WORLD), -parent->Rotation(WORLD));
			mPosition.x /= parentScale.x;
			mPosition.y /= parentScale.y;

			mRotation -= parent->Rotation(WORLD);
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale
				.y);
		}

		mParent = parent;
	}
	GameEntity* GameEntity::Parent() {
		return mParent;
	}
}