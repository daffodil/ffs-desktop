#include <QtGui/QApplication>

#include "mainobject.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.setQuitOnLastWindowClosed(false);
    app.setApplicationName("FFS-Desktop");



	/* The application starts as a QObject in the status bar. Ie NOT a widget.
	   The reasoning for this is that all the windows could be destoyed ie little memory..
	   and then pulled up/dismissed as required
	 */
    MainObject m;

    return app.exec();
}
