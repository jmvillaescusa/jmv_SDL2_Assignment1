#include "AnimatedTexture.h"

namespace SDLFramework {
	AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, AnimDir animationDir, bool managed) : Texture(filename, x, y, w, h, managed) {
		mTimer = Timer::Instance();
		mStartX = x;
		mStartY = y;

		mFrameCount = frameCount;
		mAnimationSpeed = animationSpeed;
		mTimePerFrame = mAnimationSpeed / mFrameCount;
		mAnimationTimer = 0.0f;

		mWrapMode = LOOP;
		mAnimationDirection = animationDir;

		mAnimationDone = false;
	}
	AnimatedTexture::~AnimatedTexture() { }

	void AnimatedTexture::SetWrapMode(WrapMode wrapMode) {
		mWrapMode = mWrapMode;
	}

	void AnimatedTexture::ResetAnimation() {
		mAnimationTimer = 0.0f;
		mAnimationDone = false;
	}

	bool AnimatedTexture::isAnimating() {
		return !mAnimationDone;
	}

	void AnimatedTexture::Update() {
		if (!mAnimationDone) {
			mAnimationTimer += mTimer->DeltaTime();

			if (mAnimationTimer >= mAnimationSpeed) {
				if (mWrapMode == LOOP) {
					// Reset timer, accounting for extra time
					mAnimationTimer -= mAnimationSpeed;
				}
				else {
					mAnimationDone = true;
					// Back up the timer to the last frame
					mAnimationTimer = mAnimationSpeed - mTimePerFrame;
				}
			}

			if (mAnimationDirection == HORIZONTAL) {
				mSourceRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
			}
			else {
				mSourceRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
			}
		}
	}
}