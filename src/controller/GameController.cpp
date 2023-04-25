#include "../view/cli/GameCLI.h"
#include "../view/gui/GameGUI.h"
#include "../view/gui/MainWindow.h"

#include "../model/Game.h"
#include <thread>

#include <QApplication>

#include <chrono>
#include <thread>
#include "../view/gui/GameGUI.h"

int main(int argc, char *argv[])
{
    // game itself
    GameModel *game = new GameModel();

    // Somehow need to start these at the same time on different threads while
    // passing the gameModel???
    GameGUI *gameGUI = new GameGUI();
    // gameGUI->setup();

    GameCLI *gameCLI = new GameCLI();
    // gameCLI->start();

    InputArgs args = {argc, argv};

    // gameGUI->start(args);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    return 0;

    // start a new thread
    // std::thread t1(&GameGUI::start, gameGUI);
    // t1.join();
    // gameCLI.start();

    // return a.exec();
}
