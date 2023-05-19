#include "../view/gui/MainWindow.h"
#include "../model/GameState.h"
#include "Command.h"
#include <QApplication>

#include <QStyleFactory>
#include <QTimer>
#include <tuple>
#include "GameController.h"

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
}

void GameController::guiUpdateGameModel(UI_INPUT ui_input, std::unordered_map<std::string, std::string> params)
{

    Action action;
    switch (ui_input)
    {
    case UI_INPUT::CommandEntered:
        cliUpdateGameModel(params["input"]);
        return;
        break;

    case UI_INPUT::Go:
        action = Action::Go;
        break;
    case UI_INPUT::Look:
        action = Action::Look;
        break;
    case UI_INPUT::StartGame:
        if (params["difficulty"] == "Normal (Recommended)")
        {
            params["difficulty"] = "Normal";
        }

        action = Action::StartGame;
        break;

    default:
        perror("Invalid UI_INPUT");
        break;
    }

    m_gameModel.updateGameModel(action, params);
}

void GameController::cliUpdateGameModel(string commandString)
{

    Command command(commandString);
    auto [pAction, pParams] = command.parse();
    Action action = pAction;
    unordered_map<string, string> params = pParams;

    m_gameModel.updateGameModel(action, params);
}