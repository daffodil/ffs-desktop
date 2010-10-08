#include "xstatusbar.h"

XStatusBar::XStatusBar(QWidget *parent) :
    QStatusBar(parent)
{
}

void XStatusBar::showError(QString mesage, int timeout){
    setStyleSheet("color: red;");
    showMessage(mesage, timeout);
}
void XStatusBar::showError(QString mesage){
    setStyleSheet("color: red;");
    showMessage(mesage);
}



void XStatusBar::showMessage(QString mesage, int timeout){
    setStyleSheet("color: black;");
    QStatusBar::showMessage(mesage, timeout);
}
void XStatusBar::showMessage(QString mesage){
    setStyleSheet("color: black;");
    QStatusBar::showMessage(mesage);
}
