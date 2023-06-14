#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Rozwiązywanie układu równań liniowych o współczynnikach zespolonych");
    return a.exec();
}
