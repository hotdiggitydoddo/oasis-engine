#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace Oasis
{
    class Game
    {
    public:
        Game(const std::string& name, int screenWidth, int screenHeight);
        ~Game();

        virtual int Init();
        virtual void Run();

    private:
        GLFWwindow* _glWindow;
        bool _isRunning;
        int _screenWidth, _screenHeight;
        std::string _title;
    };
}