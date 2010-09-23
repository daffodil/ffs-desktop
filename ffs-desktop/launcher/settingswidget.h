#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QPushButton>



class SettingsWidget : public QWidget
{
Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = 0);

private:
    QLineEdit *txtExecutable;
    QLineEdit *txtFgRoot;
    QTreeWidget *treeFgScenery;
    QStatusBar *statusBar;

    QPushButton *buttSceneryUp;
    QPushButton *buttSceneryDown;
    QPushButton *buttSceneryRemove;

    void disable_scenery_actions(bool);
signals:

public slots:
    void on_exe_path();
    void on_exe_autodetect();
};

#endif // SETTINGSWIDGET_H
