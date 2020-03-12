#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H
#include "MathHelper.h"
#include "Collision.h"

namespace SDLFramework {
	class GameEntity {
	public: 
		enum Space { LOCAL = 0, WORLD = 1 };

	private:
		Vector2 mPosition;
		float mRotation;
		Vector2 mScale;

		bool mActive;
		GameEntity* mParent;

	protected:
		Collision mCollision;
		

	public:
		GameEntity(float x = 0.0f, float y = 0.0f);
		GameEntity(const Vector2& position);
		~GameEntity();

		void Position(float x, float y);
		void Position(const Vector2& pos);
		Vector2 Position(Space space = WORLD);

		void Rotation(float rot);
		float Rotation(Space space = WORLD);

		void Scale(Vector2 scale);
		Vector2 Scale(Space space = WORLD);

		void Active(bool active);
		bool Active() const;

		void Parent(GameEntity* parent);
		GameEntity* Parent() const;

		void Translate(Vector2 vec, Space space = LOCAL);
		void Rotate(float amount);

		Collision GetCollision() { return mCollision; }

		virtual void Update() {};
		virtual void Render() {};
	};
}
#endif // !_GAMEENTITY_H