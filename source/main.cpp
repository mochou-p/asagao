// asagao/source/main.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "log.hpp"


int
main
(int argc, char* argv[])
{
    try
    {
        argc == 2
            ? Asagao::Application.run(argv[1])
            : Asagao::Application.run();
    }
    catch (const std::exception& error)
    {
        LOG_ERROR(error.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
