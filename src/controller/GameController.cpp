#include "../view/cli/GameCLI.h"
#include "../view/gui/GameGUI.h"

#include "../model/Game.h"
#include <thread>

int main(int argc, char const *argv[])
{
    // game itself
    GameModel *game = new GameModel();

    // CLI Application View
    // GameCLI gameCLI = GameCLI();

    // std::thread cliThread(&GameCLI::start, &gameCLI);

    // gameCLI.update(game);

    // GUI Application View

    // Somehow need to start these at the same time on different threads while
    // passing the gameModel???

    // gameCLI.start();
    gameGUI.start();

    // the gui runs in its own loop
    // we need a loop here to watch
    bool finished = false;
    while (!finished)
    {
        // wait for game to end
    }

    /* code */
    // Game game;
    // game.play();
    // Game game;
    // game.play();

    return 0;
}
