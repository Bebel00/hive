#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Partie;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    

    void setPartie(class Partie* const partie);

private:
    Ui::MainWindow *ui;

    class Partie* partie=nullptr;

    class QGridLayout* layout=nullptr;
     void setupConnections();
    void afficherMenu();
    void fermerMenu();
    void recommencerPartie();
    void confirmerQuitterApplication();
    


signals:
    void menuFerme();
    void nouvellePartieDemandee();  

};
#endif // MAINWINDOW_H
