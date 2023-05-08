#include "GameModel.h"

GameModel::GameModel(QObject *parent) : QObject(parent)
{
    cout << "GameModel::GameModel()" << endl;
}

void GameModel::updateGameState(Action action, std::unordered_map<std::string, std::string> params)
{
    switch (action)
    {

    case Action::StartGame:
        m_gameState.createCharacter(params["player_name"], "who do you think you are?");
        m_gameState.addReaction("Welcome to the game, " + params["player_name"] + "!");
        break;
    }

    // update view
    emit gameModelChanged(this);
}

string GameModel::getTerminalOutput()
{
    // build a string
    string output = "";
    output += "You are in room " + m_gameState.getCurentRoom()->shortDescription() + "\n";
    output += m_gameState.getReaction() + "\n";
    return output;
}

void GameModel::updatedView()
{
    // reset the reaction string
    m_gameState.resetReaction();
}

const GameState &GameModel::gameState()
{
    std::cout << "GameModel::gameState()" << std::endl;
    return m_gameState;
}
