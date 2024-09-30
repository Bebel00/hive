#include "mainwindow.h"
#include "partie.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Partie partie("Bebel", "Léo", &w);
    w.setPlateau(partie.get_plateau());

    return a.exec();
}
