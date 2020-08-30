#include "MainWindow.h"

#include <QApplication>
#include <gsl/gsl_errno.h>

int main(int argc, char *argv[])
{
    gsl_set_error_handler_off();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
