#include "DemoApp.h"

int main()
{
    try
    {
        DemoApp app;
        app.go();
    }
    catch (const Ogre::Exception& ex)
    {
        std::cerr << "An exception has occured: " << ex.getFullDescription().c_str() << std::endl;
    }

    std::cout << "Press any key to continue . . ." << std::endl;
    std::cin.get();

    return 0;
}
