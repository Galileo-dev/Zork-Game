#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <QObject>
#include <unordered_map>
#include "../model/GameState.h"
#include "../model/Enum.h"

class GameModel : public QObject
{
    Q_OBJECT

public:
    GameModel(QObject *parent = nullptr);
    const GameState *gameState();
    string getReaction();
    Character *getCharacter();
    GameState *getGameState();
    IRoom *getCurentRoom();
    void startGame(Character *character, Difficulty difficulty);
signals:
    void gameModelChanged(GameModel *gameModel);
public slots:
    void updateGameModel(Action action, std::unordered_map<std::string, std::string> params);

private:
    GameState *m_gameState;
};

#endif // GAME_MODEL_H