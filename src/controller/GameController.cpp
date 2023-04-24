#include <../view/cli/GameCLI.h>
#include <../view/gui/GameGUI.h>

#include <../model/Game.h>

int main(int argc, char const *argv[])
{
    // game itself
    GameModel *game = new GameModel();

    // create the cli
    GameCLI gameCLI = GameCLI();
    gameCLI.setup(game);
    gameCLI.start();

    // create the gui
    GameGUI gameGUI = GameGUI();
    gameGUI.setup();
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
