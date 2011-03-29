
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

#include "settingswidget.h"

/* Presents the settings "dialog" for the fgfs paths

*/

SettingsWidget::SettingsWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{

    mainObject = mOb;

    //* Main Layout
    QVBoxLayout *mainContainer = new QVBoxLayout();
    setLayout(mainContainer);
    mainContainer->setSpacing(0);
    //int m = 0;
    mainContainer->setContentsMargins(0,0,0,0);

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainContainer->addLayout(mainLayout);
    mainLayout->setSpacing(20);
    int m = 20;
    mainLayout->setContentsMargins(m,m,m,m);


    //*******************************************************************************
    //*** Executable Group
    grpExecutable = new QGroupBox(tr("Path to FlightGear executable"));
    mainLayout->addWidget(grpExecutable);
    //grpExecutable->setFlat(false);
    grpExecutable->setStyleSheet(set_frame_style(""));

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
    grpFgRoot = new QGroupBox(tr("FG_ROOT - Path to the data directory;"));
    mainLayout->addWidget(grpFgRoot);
    //grpExecutable->setFlat(false);
    grpFgRoot->setStyleSheet(set_frame_style(""));

    QHBoxLayout *layoutFgRoot = new QHBoxLayout();
    grpFgRoot->setLayout(layoutFgRoot);

    txtFgRoot = new QLineEdit("");
    layoutFgRoot->addWidget(txtFgRoot);

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
    grpFgScenery = new QGroupBox(tr("FG_Scenery - Paths to the scenery directories."));
    mainLayout->addWidget(grpFgScenery);
    //grpExecutable->setFlat(false);
    grpFgScenery->setStyleSheet(set_frame_style(""));

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


    //*** Bottom Button Box
    QHBoxLayout *buttonBox = new QHBoxLayout();
    mainLayout->addLayout(buttonBox);
    buttonBox->addStretch(10);

    QPushButton *buttSave = new QPushButton();
    buttonBox->addWidget(buttSave);
    buttSave->setText("Save");
    buttSave->setIcon(QIcon(":/icons/save"));



    mainContainer->addStretch(20);


    statusBar = new QStatusBar();
    mainContainer->addWidget(statusBar);
    statusBar->showMessage("Idle");
}



//******************
//* Disable Scenery Buttons
void SettingsWidget::disable_scenery_actions(bool state){
    buttSceneryDown->setDisabled(state);
    buttSceneryUp->setDisabled(state);
    buttSceneryRemove->setDisabled(state);
}
QString SettingsWidget::set_frame_style(QString color){
    if(color == ""){
        color = "gray";
    }
    return QString("QGroupBox{border:2px solid %1;border-radius:5px;  margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}").arg(color);

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
                grpExecutable->setStyleSheet(set_frame_style("pink"));
            }else{
                statusBar->showMessage( tr("OK fgfs found ").append(" :-)") , 5000);
                txtExecutable->setText(exe);
                grpExecutable->setStyleSheet(set_frame_style("#77FF77"));
            }
            QStringList lines = QString(result).split("\n");
        }else{
            qDebug("OOPS");
        }
}
