// asagao/source/main.cpp


#include "engine.hpp"

#include <iostream>


int
main()
{
    try
    {
        const auto asagao = Engine("Asagao", 1600, 900);
        asagao.start();
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
