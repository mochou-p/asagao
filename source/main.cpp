// asagao/source/main.cpp


#include "app.hpp"
#include <iostream>

#define APP_NAME "Asagao"

int main()
{
    App app(APP_NAME);

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
