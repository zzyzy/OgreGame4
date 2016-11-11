#pragma once
#include <irrKlang.h>

using namespace irrklang;



class AudioEngine
{
	 ISoundEngine* engine;
	 static AudioEngine *sInstance;
	 AudioEngine() {
		 engine = createIrrKlangDevice();
	 }

public:

	~AudioEngine(void) {
	 if (engine)
        engine->drop();
	}

	static ISoundEngine* sharedInstance() {
		if(!sInstance) {
			sInstance = new AudioEngine();
		}

		return sInstance->engine;
	}
};


