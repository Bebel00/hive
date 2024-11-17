#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QObject>

class MainMenu : public QGraphicsView {
    Q_OBJECT
public:
    MainMenu(QWidget* parent = nullptr);

private:
    QGraphicsScene* mainMenuScene;
    QGraphicsScene* newGameScene;

    void setupMainMenu();
    void setupNewGameScene();

private slots:
    void goToNewGame();
    void quitApplication();
};

#endif 
