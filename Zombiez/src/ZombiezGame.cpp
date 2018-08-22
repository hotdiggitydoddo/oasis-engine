#include "ZombiezGame.h"
#include <Oasis/Game.h>
#include <Oasis/ResourceManager.h>
#include <Oasis/Texture2D.h>

ZombiezGame::ZombiezGame(int screenWidth, int screenHeight) : Oasis::Game("Zombiez!!", screenWidth, screenHeight)
{
	auto t = Oasis::ResourceManager::LoadTexture("resources/textures/circle.png", true, "circle");
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
