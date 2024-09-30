#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPlateau(class Plateau* const plateau);

private:
    Ui::MainWindow *ui;

    class Plateau* plateau;

    class QGridLayout* layout;

};
#endif // MAINWINDOW_H
