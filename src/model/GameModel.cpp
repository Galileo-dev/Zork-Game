#include "GameModel.h"

GameModel::GameModel(QObject *parent) : QObject(parent)
{
    m_gameState = new GameState();

    // emit gameModelChanged(this);
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
        m_gameState->difficulty = Difficulty::NORMAL;

        string output = "Welcome to the game, " + params["player_name"] + "!\n"
                                                                          "You are " +
                        m_gameState->character->getDescription() + "\n"
                                                                   "You are playing on " +
                        params["difficulty"] + " difficulty...\n"
                                               "<Dev>: Hello there " +
                        m_gameState->character->name + " I'm the developer of this \"game\"\n";

        m_gameState->addReaction("Welcome to the game, " + params["player_name"] + "!");
        m_gameState->addReaction("You are " + m_gameState->character->getDescription());
        m_gameState->addReaction("You are playing on " + params["difficulty"] + " difficulty...");
        m_gameState->addReaction("<Dev>: Hello there " + m_gameState->character->name + " I'm the developer of this \"game\"");

        if (toLower(params["difficulty"]) == "easy")
        {
            m_gameState->setDifficulty(Difficulty::EASY);
            m_gameState->addReaction("<Dev>: Hey why are you playing on easy mode? if you are this bad at games you should just quit now. alt+f4 should do the trick");
        }
        else if (toLower(params["difficulty"]) == "normal")
        {
            m_gameState->setDifficulty(Difficulty::NORMAL);
            m_gameState->addReaction("<Dev>: Why are you're playing on Normal, normal is for people with bad tempers, you should be play on hard or cursed");
        }
        else if (toLower(params["difficulty"]) == "hard")
        {
            m_gameState->setDifficulty(Difficulty::HARD);
            m_gameState->addReaction("<Dev>: Good your playing on hard. despite what I told you in the menu this is the recommended difficulty. *wink wink*");
        }
        else if (toLower(params["difficulty"]) == "cursed")
        {
            m_gameState->setDifficulty(Difficulty::CURSED);
            m_gameState->addReaction("<Dev>: AHHHHhhh whyyy are you playing on cursed! this will allow for the optimal experience of wanting to turn your laptop into a frisbee. or for the Mac lovers out their turn your Mac into an Ipad.");
        }
        else
        {
            m_gameState->setDifficulty(Difficulty::CURSED);
            m_gameState->addReaction("<Dev>: I see you are trying to break the game. well I'm sorry to say that you have failed. I have already broken it. I have made it so that you are playing on cursed mode. have fun with that.");
        }

        m_gameState->addReaction("<Dev>: Alright, moving on...");

        StoryRoom *storyRoom = dynamic_cast<StoryRoom *>(m_gameState->currentRoom);
        if (storyRoom != nullptr)
        {
            m_gameState->addReaction(storyRoom->getStoryEvent());
        }
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

        // cast current room to exit room
        ExitRoom *exitRoom = dynamic_cast<ExitRoom *>(m_gameState->currentRoom);
        if (exitRoom != nullptr)
        {
            if (exitRoom->getRoom(direction) == NULL)
            {
                m_gameState->addReaction("You walk " + params["direction"] + " into a wall... Ouch!");
                break;
            }

            m_gameState->addReaction("You walk " + params["direction"]);
            m_gameState->go(direction);
            // add story to reaction

            StoryRoom *storyRoom = dynamic_cast<StoryRoom *>(m_gameState->currentRoom);
            if (storyRoom != nullptr)
            {
                m_gameState->addReaction(storyRoom->getStoryEvent());
            }
            RiddleRoom *riddleRoom = dynamic_cast<RiddleRoom *>(m_gameState->currentRoom);
            if (riddleRoom != nullptr)
            {

                if (!riddleRoom->isSolved)
                {
                    m_gameState->addReaction(riddleRoom->getRiddle());
                    riddleRoom->lockAllExits();
                    // lock all exits
                }
                break;
            }
            break;
        }
        break;
    }
    case Action::SolveRiddle:
    {
        m_gameState->solveRiddle(params["riddle_answer"]);
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

IRoom *GameModel::getCurentRoom()
{
    return m_gameState->currentRoom;
}

GameState *GameModel::getGameState()
{
    return m_gameState;
}
