// asagao/source/main.cpp


#include "asagao.hpp"

#include "log.hpp"


int
main()
{
    try
    {
        Asagao::Application.run();
    }
    catch (const std::exception& error)
    {
        LOG_ERROR(error.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
