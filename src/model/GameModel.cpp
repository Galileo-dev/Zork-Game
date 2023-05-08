#include "GameModel.h"

GameModel::GameModel(QObject *parent) : QObject(parent)
{
    cout << "GameModel::GameModel()" << endl;
}

void GameModel::updateGameState(Action action, std::unordered_map<std::string, std::string> params)
{
    // debug print
    std::cout << "GameModel::updateGameState()" << std::endl;
    // action
    std::cout << "action: " << action << std::endl;
    // params
    std::cout << "params: " << std::endl;
    for (auto &param : params)
    {
        std::cout << param.first << ": " << param.second << ",";
    }
    // update game state

    switch (action)
    {

    case Action::StartGame:
        if (params["player_name"] == "")
        {
            GameModel
        }

        m_gameState.createCharacter(params["player_name"]);
        break;
    }

    // update view
    emit gameModelChanged(&m_gameState);
}

const GameState &GameModel::gameState()
{
    std::cout << "GameModel::gameState()" << std::endl;
    return m_gameState;
}