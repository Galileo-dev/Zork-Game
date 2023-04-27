#include "../view/cli/GameCLI.h"
#include "../view/gui/GameGUI.h"
#include "../view/gui/MainWindow.h"
#include "../model/GameState.h"

#include <QApplication>

#include <QStyleFactory>
#include <QTimer>
#include "GameController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("macos"));

    GameController gameController;
    // QApplication::setProperty("GameState", QVariant::fromValue(game));
    MainWindow w;
    w.show();
    return a.exec();
    return 0;
}

GameController::GameController(QObject *parent) : QObject(parent)
{
}

void GameController::updateGameState()
{
    m_gameModel.updateGameState();
}
