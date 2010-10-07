#ifndef XSTATUSBAR_H
#define XSTATUSBAR_H

#include <QStatusBar>

class XStatusBar : public QStatusBar
{
Q_OBJECT
public:
    explicit XStatusBar(QWidget *parent = 0);

    void show_message(QString message, int timeout);
    void show_message(QString message);

    void show_error(QString message, int timeout);
    void show_error(QString message);


signals:

public slots:

};

#endif // XSTATUSBAR_H
