#include <Oasis/Game.h>
#include <iostream>

int main()
{
    Oasis::Game g("Zombiez!!", 1280, 720);
    g.Init();
    g.Run();
    return 0;
}