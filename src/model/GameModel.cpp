#include "GameModel.h"

GameModel::GameModel(QObject *parent) : QObject(parent) {}

void GameModel::updateGameState()
{
    // debug print
    std::cout << "GameModel::updateGameState()" << std::endl;
}

const GameState &GameModel::gameState() { return m_gameState; }