#include <QtGui/QApplication>

#include "mainobject.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.setQuitOnLastWindowClosed(false);

    MainObject m;

    return app.exec();
}
