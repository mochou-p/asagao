// asagao/source/main.cpp


#include "hello.hpp"

#include <GLFW/glfw3.h>

#include <stdexcept>


auto app() -> void
{
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    const auto window = glfwCreateWindow(256, 256, "hi", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow failed");
    }

    glfwMakeContextCurrent(window);

    std::printf
    (
        "OpenGL\n\t%s\n\t%s\n\t%s\n\t%s\n",
        glGetString(GL_VENDOR),
        glGetString(GL_RENDERER),
        glGetString(GL_VERSION),
        glGetString(GL_SHADING_LANGUAGE_VERSION)
    );

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main()
{
    try
    {
        app();
        hi();
    }
    catch (const std::exception& error)
    {
        std::printf("\033[31m%s\033[0m\n", error.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

