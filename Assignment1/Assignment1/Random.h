#ifndef _RANDOM_H
#define _RANDOM_H
#include <random>
#include <chrono>

namespace SDLFramework {
	class Random {
	private:
		static Random* sInstance;

		std::mt19937 mGenerator;

	public:
		static Random* Instance();
		static void Release();

		unsigned RandomInt();                  // [0, usigned max]
		float RandomFloat();                   // [0.0f, 1.0f)
		int RandomRange(int lo, int hi);       // [lo, hi]
		float RandomRange(float lo, float hi); // [lo, hi)

	private:
		Random();
		~Random();
	};
}
#endif // !_RANDOM_H
