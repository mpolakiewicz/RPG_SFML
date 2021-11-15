#include "Game.h"
#include "Hero.h"

int main()
{

    std::srand((int)time(0));
    Game game;

    while(game.get_window().isOpen())
    {
        game.update();
        game.render();
    }

    return 0;
}
