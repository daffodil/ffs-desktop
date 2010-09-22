#ifndef MPMAPWIDGET_H
#define MPMAPWIDGET_H

#include <QWidget>
#include <QWebView>
#include <QtGui/QProgressBar>

class MpMapWidget : public QWidget
{
Q_OBJECT
public:
    explicit MpMapWidget(QWidget *parent = 0);

private:
    QWebView *browser;
    QProgressBar *progressBar;
signals:

public slots:
    void start_progress();
    void update_progress(int progress);
    void end_progress(bool Ok);

    void on_combo_server(QString);
};

#endif // MPMAPWIDGET_H
