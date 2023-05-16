#include "GameModel.h"

GameModel::GameModel(QObject *parent) : QObject(parent)
{
    cout << "GameModel::GameModel()" << endl;
}

void GameModel::updateGameModel(Action action, std::unordered_map<std::string, std::string> params)
{
    switch (action)
    {

    case Action::StartGame:
        m_gameState.createCharacter(params["player_name"], "who do you think you are?");
        m_gameState.addReaction("Welcome to the game, " + params["player_name"] + "!");
        break;

    case Action::Go:
        Direction direction;

        if (params["direction"] == "north")
        {
            direction = Direction::NORTH;
        }
        else if (params["direction"] == "south")
        {
            direction = Direction::SOUTH;
        }
        else if (params["direction"] == "east")
        {
            direction = Direction::EAST;
        }
        else if (params["direction"] == "west")
        {
            direction = Direction::WEST;
        }
        else
        {
            m_gameState.addReaction("Invalid direction: " + params["direction"]);
            break;
        }

        m_gameState.go(direction);
        break;

    case Action::PickupItem:
        m_gameState.pickupItem(params["item_name"]);
        break;

    case Action::Look:
        // m_gameState.addReaction("You are in room " + m_gameState.getCurentRoom()->shortDescription());
        m_gameState.addReaction(m_gameState.getCurentRoom()->longDescription());
        break;
    }

    // update view
    emit gameModelChanged(this);
}

void GameModel::updatedView()
{
    // reset the reaction string
    m_gameState.resetReaction();
}

string GameModel::getReaction()
{
    return m_gameState.getReaction();
}

const GameState &GameModel::gameState()
{
    std::cout << "GameModel::gameState()" << std::endl;
    return m_gameState;
}
