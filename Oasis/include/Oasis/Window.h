#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace Oasis
{
    class Window
    {
    public:
        Window();
        ~Window();
        int Create(const std::string& windowName, int screenWidth, int screenHeight);
        int GetScreenWidth() { return _screenWidth; }
        int GetScreenHeight() { return _screenHeight; }
        void SwapBuffer();
    private:
        GLFWwindow* _glWindow;
        int _screenWidth, _screenHeight;
        std::string _title;
    };
}
