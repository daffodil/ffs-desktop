#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <mainobject.h>

#include <QtCore/QString>

#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QPushButton>
#include <QtGui/QGroupBox>


class SettingsWidget : public QWidget
{
Q_OBJECT
public:
    explicit SettingsWidget(MainObject *mOb, QWidget *parent = 0);

private:
    MainObject *mainObject;
    QGroupBox *grpExecutable;
    QGroupBox *grpFgRoot;
    QGroupBox *grpFgScenery;

    QLineEdit *txtExecutable;
    QLineEdit *txtFgRoot;
    QTreeWidget *treeFgScenery;
    QStatusBar *statusBar;

    QPushButton *buttSceneryUp;
    QPushButton *buttSceneryDown;
    QPushButton *buttSceneryRemove;


    QString set_frame_style(QString color);
    void disable_scenery_actions(bool);
signals:

public slots:
    void on_exe_path();
    void on_exe_autodetect();
};

#endif // SETTINGSWIDGET_H
