#include "DemoApp.h"

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
