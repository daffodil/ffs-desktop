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
	QGroupBox *grpFgfs;
    QGroupBox *grpFgRoot;
    QGroupBox *grpFgScenery;

	QLineEdit *txtFgfs;
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
	void on_select_fgfs_path();
	void on_fgfs_autodetect();
	void on_select_fg_root_path();

	void load_settings();
	void save_settings();
};

#endif // SETTINGSWIDGET_H
