// asagao/source/main.cpp


#include "engine.hpp"

#include <iostream>


int main()
{
    try
    {
        Engine asagao("Asagao", 1600, 900);
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
