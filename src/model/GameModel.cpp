#include "GameModel.h"

GameModel::GameModel(QObject *parent) : QObject(parent) {}

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
        std::cout << param.first << ": " << param.second << std::endl;
    }
    // update game state

    // update view
    emit gameStateChanged(&m_gameState);
}

const GameState &GameModel::gameState() { return m_gameState; }