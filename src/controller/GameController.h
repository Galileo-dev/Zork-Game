#include <QObject>
#include "../model/GameModel.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QObject *parent = nullptr);

private slots:
    void updateGameState();

private:
    GameModel m_gameModel;
};