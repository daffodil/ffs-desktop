#include <QtGui/QApplication>

#include "mainobject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainObject m;

    return a.exec();
}
