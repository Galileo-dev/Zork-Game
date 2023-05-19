#include "GameModel.h"

GameModel::GameModel(QObject *parent) : QObject(parent)
{
    m_gameState = new GameState();
    cout << "GameModel::GameModel()" << endl;
}

std::string toLower(const std::string &str)
{
    std::string result;

    for (char c : str)
    {
        result += std::tolower(c);
    }

    return result;
}

void GameModel::updateGameModel(Action action, std::unordered_map<std::string, std::string> params)
{
#ifdef DEBUG_LOG
    // put the action and params into the game model
    cout << "GameModel::updateGameModel()" << endl;
    cout << "Input: " << static_cast<std::underlying_type<Action>::type>(action) << endl;
    cout << "Params: " << endl;
    for (auto &param : params)
    {
        cout << param.first << ": " << param.second << ",";
        cout << endl;
    }
#endif
    switch (action)
    {

    case Action::StartGame:
    {
        if (m_gameState->isGameStarted)
        {
            m_gameState->resetReaction();
            m_gameState->addReaction("Game has already started");
            break;
        }
        Character *character = new Character(params["player_name"], "a fierce zork hunter, travels on the back of camel named Steve moving from village to village slaying the helpless zorks and that is how he got his name, Zork Hunter.");
        m_gameState->setCharacter(character);

        if (toLower(params["difficulty"]) == "easy")
        {
            m_gameState->setDifficulty(Difficulty::EASY);
        }
        else if (toLower(params["difficulty"]) == "normal")
        {
            m_gameState->setDifficulty(Difficulty::MEDIUM);
        }
        else if (toLower(params["difficulty"]) == "hard")
        {
            m_gameState->setDifficulty(Difficulty::HARD);
        }
        else if (toLower(params["difficulty"]) == "Cursed")
        {
            m_gameState->setDifficulty(Difficulty::HARD);
        }
        else
        {
            m_gameState->setDifficulty(Difficulty::EASY);
        }

        m_gameState->addReaction("Welcome to the game, " + params["player_name"] + "!");
        m_gameState->addReaction("You are " + m_gameState->character->getDescription());
        m_gameState->isGameStarted = true;
        break;
    }

    case Action::Go:
    {
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
            m_gameState->addReaction("Invalid direction: " + params["direction"]);
            break;
        }

        m_gameState->addReaction("You walk " + params["direction"]);

        m_gameState->go(direction);
        break;
    }
    case Action::PickupItem:
    {
        m_gameState->pickupItem(params["item_name"]);
        break;
    }

    case Action::DropItem:
    {
        m_gameState->dropItem(params["item_name"]);
        break;
    }

    case Action::Look:
    { // m_gameState->addReaction("You are in room " + m_gameState->getCurentRoom()->shortDescription());
        m_gameState->addReaction(m_gameState->currentRoom->longDescription());
        break;
    }

    case Action::ShowInventory:
    {
        m_gameState->addReaction(m_gameState->character->getInventoryDescription());
        break;
    }

    default:
    {
        m_gameState->addReaction("Invalid action: " + static_cast<std::underlying_type<Action>::type>(action));
        break;
    }
    }

    // update view
    emit gameModelChanged(this);
    m_gameState->resetReaction();
}

string GameModel::getReaction()
{
    return m_gameState->reaction;
}

Character *GameModel::getCharacter()
{
    return m_gameState->character;
}

const GameState *GameModel::gameState()
{
    std::cout << "GameModel::gameState()" << std::endl;
    return m_gameState;
}

Room *GameModel::getCurentRoom()
{
    return m_gameState->currentRoom;
}
