#include "calcwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcWindow w;
    w.show();
    return a.exec();
}
