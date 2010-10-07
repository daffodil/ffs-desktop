#include "xstatusbar.h"

XStatusBar::XStatusBar(QWidget *parent) :
    QStatusBar(parent)
{
}

void XStatusBar::show_error(QString mesage, int timeout){
    setStyleSheet("color: red;");
    showMessage(mesage, timeout);
}
void XStatusBar::show_error(QString mesage){
    setStyleSheet("color: red;");
    showMessage(mesage);
}



void XStatusBar::show_message(QString mesage, int timeout){
    setStyleSheet("color: black;");
    showMessage(mesage, timeout);
}
void XStatusBar::show_message(QString mesage){
    setStyleSheet("color: black;");
    showMessage(mesage);
}
