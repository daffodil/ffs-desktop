#include "settingswidget.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QByteArray>
#include <QtCore/QProcess>

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QFileDialog>
#include <QtGui/QTreeWidget>


SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent)
{

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(10);
    int m = 20;
    mainLayout->setContentsMargins(m,m,m,m);

    QString grp_style = QString("QGroupBox{border:2px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");

    //*******************************************************************************
    //*** Executable Group
    QGroupBox *grpExecutable = new QGroupBox(tr("Path to FlightGear executable"));
    mainLayout->addWidget(grpExecutable);
    //grpExecutable->setFlat(false);
    grpExecutable->setStyleSheet(grp_style);

    QHBoxLayout *layoutExe = new QHBoxLayout();
    grpExecutable->setLayout(layoutExe);

    txtExecutable = new QLineEdit("");
    layoutExe->addWidget(txtExecutable);

    QToolButton *buttExecutable = new QToolButton();
    layoutExe->addWidget(buttExecutable);
    buttExecutable->setIcon(QIcon(":/icons/refresh"));
    buttExecutable->setPopupMode(QToolButton::InstantPopup);

    QMenu *menuExecutable = new QMenu();
    buttExecutable->setMenu(menuExecutable);

    QAction *actExePath = new QAction(menuExecutable);
    menuExecutable->addAction(actExePath);
    actExePath->setText(tr("Select path.."));
    connect(actExePath, SIGNAL(triggered()), this, SLOT(on_exe_path()));

    QAction *actExeAutodetect = new QAction(menuExecutable);
    menuExecutable->addAction(actExeAutodetect);
    actExeAutodetect->setText(tr("Autodetect"));
    connect(actExeAutodetect, SIGNAL(triggered()), this, SLOT(on_exe_autodetect()));

    //*******************************************************************************
    //*** FG_ROOT Group
    QGroupBox *grpFgRoot = new QGroupBox(tr("FG_ROOT - Path to the data directory;"));
    mainLayout->addWidget(grpFgRoot);
    //grpExecutable->setFlat(false);
    grpFgRoot->setStyleSheet(grp_style);

    QHBoxLayout *layoutFgRoot = new QHBoxLayout();
    grpFgRoot->setLayout(layoutFgRoot);

    txtExecutable = new QLineEdit("");
    layoutFgRoot->addWidget(txtExecutable);

    QToolButton *buttFgRoot = new QToolButton();
    layoutFgRoot->addWidget(buttFgRoot);
    buttFgRoot->setIcon(QIcon(":/icons/refresh"));
    buttFgRoot->setPopupMode(QToolButton::InstantPopup);

    QMenu *menuFgRoot = new QMenu();
    buttFgRoot->setMenu(menuFgRoot);

    QAction *actFgRootPath = new QAction(menuFgRoot);
    menuFgRoot->addAction(actFgRootPath);
    actFgRootPath->setText(tr("Select path.."));
    //connect(actExePath, SIGNAL(triggered()), this, SLOT(on_exe_path()));

    QAction *actFgRootCheck = new QAction(menuFgRoot);
    menuFgRoot->addAction(actFgRootCheck);
    actFgRootCheck->setText(tr("Check path"));
    //connect(actFgRootCheck, SIGNAL(triggered()), this, SLOT(on_exe_autodetect()));


    //*******************************************************************************
    //*** FG_Scenery
    QGroupBox *grpFgScenery = new QGroupBox(tr("FG_Scenery - Paths to the scenery directories."));
    mainLayout->addWidget(grpFgScenery);
    //grpExecutable->setFlat(false);
    grpFgScenery->setStyleSheet(grp_style);

    QHBoxLayout *layoutFgScenery = new QHBoxLayout();
    grpFgScenery->setLayout(layoutFgScenery);

    treeFgScenery = new QTreeWidget();
    layoutFgScenery->addWidget(treeFgScenery);
    treeFgScenery->setRootIsDecorated(false);
    treeFgScenery->setAlternatingRowColors(true);
    QTreeWidgetItem *headerItem = treeFgScenery->headerItem();
    headerItem->setText(0, tr("Scenery Paths"));

    QVBoxLayout *layoutFgActionBox = new QVBoxLayout();
    layoutFgScenery->addLayout(layoutFgActionBox);


    //*** Action Scenery
    buttSceneryUp = new QPushButton();
    layoutFgActionBox->addWidget(buttSceneryUp);
    buttSceneryUp->setText(tr("Up"));
    buttSceneryUp->setIcon(QIcon(":/icons/up"));

    buttSceneryDown = new QPushButton();
    layoutFgActionBox->addWidget(buttSceneryDown);
    buttSceneryDown->setText(tr("Down"));
    buttSceneryDown->setIcon(QIcon(":/icons/down"));

//    QPushButton *buttSceneryAdd = new QPushButton();
//    layoutFgActionBox->addWidget(buttSceneryAdd);
//    buttSceneryAdd->setText(tr("Add Path"));
//    buttSceneryAdd->setIcon(QIcon(":/icons/add"));

    QToolButton *buttSceneryAdd = new QToolButton();
    layoutFgActionBox->addWidget(buttSceneryAdd);
    buttSceneryAdd->setText(tr("Add Path"));
    buttSceneryAdd->setIcon(QIcon(":/icons/add"));
    buttSceneryAdd->setPopupMode(QToolButton::InstantPopup);
    buttSceneryAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    buttSceneryAdd->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *menu = new QMenu();
    buttSceneryAdd->setMenu(menu);

    buttSceneryRemove = new QPushButton();
    layoutFgActionBox->addWidget(buttSceneryRemove);
    buttSceneryRemove->setText(tr("Remove"));
    buttSceneryRemove->setIcon(QIcon(":/icons/delete_small"));

    layoutFgActionBox->addStretch(10);
    disable_scenery_actions(true);


    mainLayout->addStretch(20);

    statusBar = new QStatusBar();
    mainLayout->addWidget(statusBar);
    statusBar->showMessage("Idle");
}

//******************
//* Disable Scenery Buttons
void SettingsWidget::disable_scenery_actions(bool state){
    buttSceneryDown->setDisabled(state);
    buttSceneryUp->setDisabled(state);
    buttSceneryRemove->setDisabled(state);
}


//******************
//* EXE Dialog
void SettingsWidget::on_exe_path(){
    qDebug("on_exe_path");

     QFileDialog dialog(this);
     dialog.setFileMode(QFileDialog::ExistingFile);
     //dialog.setLabelText(tr("Select path to fgfs"));
     if(dialog.exec()){
         qDebug("YES");
     }
     // TODO
}



//******************
//* Autodetect EXE
void SettingsWidget::on_exe_autodetect(){
    qDebug("on_exe_autodetect");

    QString program = "which fgfs";

    QProcess *process = new QProcess(this);
    process->start(program);

    QStringList::Iterator it;
    QString line;
    int row_count=0;

    if(process->waitForStarted()){
            process->waitForFinished();
            QByteArray result =  process->readAllStandardOutput();
            QByteArray errorResult = process->readAllStandardError();
            QString exe = QString(result).trimmed();

            if(exe.length() == 0){
                statusBar->showMessage( tr("fgfs not found").append(" :-(") , 5000);
            }else{
                statusBar->showMessage( tr("OK fgfs found ").append(" :-)") , 5000);
                txtExecutable->setText(exe);
            }
            QStringList lines = QString(result).split("\n");
        }else{
            qDebug("OOPS");
        }
}
