#include "DemoApp.h"
#include <irrKlang.h>

using namespace irrklang;

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
AudioEngine *AudioEngine::sInstance = 0;

int main()
{
    DemoApp app;

    try
    {
       
        app.go();
    }
    catch (const Ogre::Exception& ex)
    {
        std::cerr << "An exception has occured: " << ex.getFullDescription().c_str() << std::endl;
    }



    return 0;
}
