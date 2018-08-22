#pragma once

#include <Oasis/Game.h>

class ZombiezGame : public Oasis::Game
{
public:
	ZombiezGame(int screenWidth, int screenHeight);
	~ZombiezGame();
	void Update(float dt) override;
	void Render() override;

private:
};