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

signals:
    void nouvellePartieDemandee(QString joueur1, QString joueur2, bool contreIA);
    void quitApplication();

private:
    QGraphicsScene* mainMenuScene;
    QGraphicsScene* newGameScene;
    QGraphicsScene* settingsScene;

    void setupMainMenu();
    void setupNewGameScene();
    void setupSettingsScene();

private slots:
    void goToNewGame();
    void goToSettings();
    void quitApplication();
};

#endif 

