#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <QObject>
#include <unordered_map>
#include "../model/GameState.h"
#include "../model/Action.h"

class GameModel : public QObject
{
    Q_OBJECT

public:
    GameModel(QObject *parent = nullptr);
    const GameState &gameState();
    void createCharacter(std::string name);
signals:
    void gameModelChanged(GameState *gameState);
public slots:
    void updateGameState(Action action, std::unordered_map<std::string, std::string> params);

private:
    GameState m_gameState;
};

#endif // GAME_MODEL_H