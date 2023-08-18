// asagao/source/main.cpp


#include <iostream>
#include "app.hpp"

#define APP_NAME "Asagao"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main()
{
    App app(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

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
