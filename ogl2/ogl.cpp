#include "Engine.h"

#ifdef DEBUG
const bool debug_pause = true;
#else
const bool debug_pause = false;
#endif

int main(int argc, char* argv[])
{
    Engine engine;
    try
    {
        engine.run();
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        if (debug_pause)
        {
            system("pause");
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (debug_pause)
    {
        system("pause");
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
