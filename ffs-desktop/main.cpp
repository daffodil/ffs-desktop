#include <QtGui/QApplication>

#include "mainobject.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.setQuitOnLastWindowClosed(false);
    app.setApplicationName("FFS-Desktop");




    MainObject m;

    return app.exec();
}
