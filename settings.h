#ifndef SETTINGS_H
#define SETTINGS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>

class Settings : public QGraphicsView {
    Q_OBJECT
public:
    explicit Settings(QWidget* parent = nullptr);

signals:
    void saveSettings(QString joueur1, QString joueur2, bool contreIA);
    void backToMainMenu(); // Signal pour retourner au menu principal

private:
    QGraphicsScene* settingsScene=nullptr;

    void setupSettingsScene(); // Configure la scène des paramètres
};

#endif // SETTINGS_H

