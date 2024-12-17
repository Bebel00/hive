#ifndef SETTINGS_H
#define SETTINGS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include <QString>
#include <QSet>

class Settings : public QGraphicsView {
    Q_OBJECT
public:
    explicit Settings(QWidget* parent = nullptr);

signals:
/**
     * Signal pour sauvegarder les paramètres de la partie.
     * @param joueur1 Le nom du Joueur 1.
     * @param joueur2 Le nom du Joueur 2 ou "IA" si contre l'IA.
     * @param contreIA Booléen pour savoir si l'adversaire est l'IA.
     * @param extensions Un ensemble des extensions sélectionnées.
     * @param nbUndo Le nombre de tours annulables.
     */
    void saveSettings(QString joueur1, QString joueur2, bool contreIA,QSet<QString> extensions, int nbUndo);
    void backToMainMenu(); // Signal pour retourner au menu principal

private:
    QGraphicsScene* settingsScene=nullptr;

    void setupSettingsScene(); // Configure la scène des paramètres

    void setupPlayerInputs();      // entrées pour les joueurs
    void setupExtensionOptions();  //cases à cocher pour les extensions
    void setupUndoOption();        //le champ pour les tours annulables
    void setupButtons();           //les boutons Retour et Sauvegarde
};

#endif // SETTINGS_H

