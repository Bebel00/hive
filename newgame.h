#ifndef NEWGAME_H
#define NEWGAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>

class NewGame : public QGraphicsView {
    Q_OBJECT
public:
    explicit NewGame(QWidget* parent = nullptr);

signals:
    void startGame();
    void backToMainMenu();

private:
    QGraphicsScene* newGameScene;

    void setupNewGameScene(); 
};

#endif 
