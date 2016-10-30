#include "DemoApp.h"
#include <irrKlang.h>

using namespace irrklang;

int main()
{
    DemoApp app;
    ISoundEngine* engine = nullptr;

    try
    {
        engine = createIrrKlangDevice();
        if (!engine)
        {
            std::cerr << "Unable to create irrKlang device" << std::endl;
            return 0;
        }
        app.go(engine);
    }
    catch (const Ogre::Exception& ex)
    {
        std::cerr << "An exception has occured: " << ex.getFullDescription().c_str() << std::endl;
    }

    if (engine)
        engine->drop();

    return 0;
}
