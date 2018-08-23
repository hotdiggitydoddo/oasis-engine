#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace Oasis
{
	enum class GameState
	{
		ACTIVE,
		MENU
	};

    class Game
    {
    public:
        Game(const std::string& name, int screenWidth, int screenHeight);
        ~Game();

        virtual int Init();
		void Run();

		virtual void Update(float dt) = 0;
		virtual void Render() = 0;

		GameState State;

    private:
		


        GLFWwindow* _glWindow;
        bool _isRunning;
        int _screenWidth, _screenHeight;
        std::string _title;
    };

	
}