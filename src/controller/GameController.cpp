#include "../view/cli/GameCLI.h"
#include "../view/gui/GameGUI.h"
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
    // GUI Elements
    // m_gameModel = new GameModel();
    cout << "GameController::GameController()" << endl;
}

void GameController::updateGameState(Action action, std::unordered_map<std::string, std::string> params)
{
    if (action == Action::ParseCommand)
    {
        std::cout << "GameModel::updateGameState() - ParseCommand" << std::endl;
        // m_gameState = GameState(params);
        Command command(params["input"]);
        auto [pAction, pParams] = command.parse();
        action = pAction;
        params = pParams;
        // if (!command.validate())
        // {
        //     // formulate error as a string
        //     std::string error = "Invalid command: " + params["input"];
        //     error += command.getErrorMessage();
        //     params = {{"error", error}};
        // }
    }

    // put the action and params into the game model
    cout << "Action: " << action << endl;
    cout << "Params: " << endl;
    for (auto &param : params)
    {
        cout << param.first << ": " << param.second << ",";
        cout << endl;
    }

    m_gameModel.updateGameModel(action, params);
}
