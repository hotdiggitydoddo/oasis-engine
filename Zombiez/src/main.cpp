#include "ZombiezGame.h"
#include <iostream>

int main()
{
	ZombiezGame g(1280, 720);
    g.Init();
    g.Run();
    return 0;
}