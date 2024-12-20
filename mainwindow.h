#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "graphicsPartie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPartie(class GraphicsPartie* const graphicpartie);

private:
    Ui::MainWindow *ui;

    class GraphicsPartie* partie;

    class QGridLayout* layout;

};
#endif // MAINWINDOW_H
