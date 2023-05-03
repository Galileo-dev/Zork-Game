#include "../view/cli/GameCLI.h"
#include "../view/gui/GameGUI.h"
#include "../view/gui/MainWindow.h"
#include "../model/GameState.h"

#include <QApplication>

#include <QStyleFactory>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("macos"));
    GameController gameController = new GameController();
    MainWindow w(&gameController);

    w.show();
    return a.exec();
}

GameController::GameController(QObject *parent) : QObject(parent)
{
    // GUI Elements
    // m_gameModel = new GameModel();
}

void GameController::updateGameState(Action action, std::unordered_map<std::string, std::string> params)
{
    m_gameModel.updateGameState(action, params);
}
