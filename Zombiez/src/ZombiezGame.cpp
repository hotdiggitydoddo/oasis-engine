#include "ZombiezGame.h"
#include <Oasis/Game.h>
#include <Oasis/ResourceManager.h>
#include <Oasis/Texture2D.h>
#include <ZombiezGame.h>


ZombiezGame::ZombiezGame(int screenWidth, int screenHeight) : Oasis::Game("Zombiez!!", screenWidth, screenHeight)
{
}

ZombiezGame::~ZombiezGame()
{
}

void ZombiezGame::Update(float dt)
{
}

void ZombiezGame::Render()
{
}

int ZombiezGame::Init()
{
	Game::Init();
	auto t = Oasis::ResourceManager::LoadTexture("resources/textures/circle.png", true, "circle");

}
