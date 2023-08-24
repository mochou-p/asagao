// asagao/source/main.cpp


#include <iostream>
#include "application.hpp"

int
main()
{
    Application app;

    try
    {
        app.run();
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
