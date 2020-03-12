#ifndef _ANIMATEDTEXTURE_H
#define _ANIMATEDTEXTURE_H
#include "Texture.h"
#include "Timer.h"

namespace SDLFramework {
	class AnimatedTexture : public Texture {
	public :
		enum WrapMode { ONCE = 0, LOOP = 1};
		enum AnimDir { HORIZONTAL = 0, VERTICAL = 1 };

	private:
		Timer* mTimer;
		int mStartX;
		int mStartY;

		int mFrameCount; // Total frames

		float mAnimationSpeed; // in seconds
		float mTimePerFrame;   // time to display
		float mAnimationTimer; // time displayed

		WrapMode mWrapMode;
		AnimDir mAnimationDirection;

		bool mAnimationDone;

	public:
		AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, AnimDir animationDir, bool managed = false);
		~AnimatedTexture();

		void SetWrapMode(WrapMode mode);

		void ResetAnimation();
		bool isAnimating();

		void Update();
	};
}

#endif // !_ANIMATEDTEXTURE_H

