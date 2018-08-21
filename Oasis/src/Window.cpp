
#include <glad/glad.h>
#include <Window.h>

#include "Window.h"

namespace Oasis
{
    void Window::SwapBuffer()
    {
        glfwSwapBuffers(_glWindow);
    }

    Window::Window() : _glWindow(nullptr)
    {
    }

    Window::~Window()
    {
        glfwDestroyWindow(_glWindow);
        _glWindow = nullptr;
    }

    int Window::Create(const std::string& windowName, int screenWidth, int screenHeight)
    {
        _title = windowName;
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        _glWindow = glfwCreateWindow(_screenWidth, _screenHeight, _title.c_str(), nullptr, nullptr);

        // Check for Valid Context
        if (_glWindow == nullptr) {
            fprintf(stderr, "Failed to Create OpenGL Context");
            return EXIT_FAILURE;
        }

        // Create Context and Load OpenGL Functions
        glfwMakeContextCurrent(_glWindow);
        gladLoadGL();
        fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

        return 0;
    }
}