#include "Game.h"
#include <glad/glad.h>

namespace Oasis
{
    Game::Game(const std::string& name, int screenWidth, int screenHeight) :
        _screenWidth(screenWidth),
        _screenHeight(screenHeight),
        _title(name),
        _glWindow(nullptr)
    {

    }

    Game::~Game()
    {
        glfwDestroyWindow(_glWindow);
        _glWindow = nullptr;
    }

    int Game::Init()
    {
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

    void Game::Run()
    {
        _isRunning = true;
		State = GameState::ACTIVE;

		double t = 0.0;
		const double dt = 0.01;
		double currentTime = 0.0;
		double accumulator = 0.0;

        while (glfwWindowShouldClose(_glWindow) == false) {
            if (glfwGetKey(_glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(_glWindow, true);

			double newTime = glfwGetTime();
			double frameTime = newTime - currentTime;
			currentTime = newTime;

			accumulator += frameTime;

			while (accumulator >= dt)
			{
				Update(dt);
				accumulator -= dt;
				t += dt;
			}

			// Background Fill Color
			glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			Render();

			// Flip Buffers and Draw
			glfwSwapBuffers(_glWindow);
			glfwPollEvents();
        }   
		glfwTerminate();
    }
}