// asagao/source/main.cpp


#include <iostream>
#include "application.hpp"
#include "log.hpp"

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
        LOG_ERROR(error.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
