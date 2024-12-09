#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <qdialog.h>
#include "plateau.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPartie(class Partie* const p);

private slots:
    void onButtonAnnulerClicked();

private:
    Ui::MainWindow *ui;

    class Partie* partie;

    class QGridLayout* layout;
    QPushButton *button;
    QLabel *annuler;

};
#endif // MAINWINDOW_H
