#include "aircraftwidget.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QToolBar>
#include <QtGui/QAction>

#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidgetItem>

#include <QtCore/QProcess>
#include <QtCore/QByteArray>
#include <QtCore/QString>

AircraftWidget::AircraftWidget(QWidget *parent) :
    QWidget(parent)
{
    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    //** Toolbar
    QToolBar *toolbar = new QToolBar();
    mainLayout->addWidget(toolbar);
    
    QAction *refreshButton = new QAction(this);
    toolbar->addAction(refreshButton);
    refreshButton->setText("Refresh");
    connect(refreshButton, SIGNAL(triggered()), this, SLOT(on_load()) );

    //** Middle HBox
    QHBoxLayout *hBox = new QHBoxLayout();
    mainLayout->addLayout(hBox);
    
    //** Aircraft Tree
    treeWidget = new QTreeWidget(this);
    hBox->addWidget(treeWidget);

    QHeaderView *treeHeader = treeWidget->header();
    treeHeader->setStretchLastSection(true);

    QTreeWidgetItem *headerItem = treeWidget->headerItem();
    headerItem->setText(0, tr("Model"));
    headerItem->setText(1, tr("Description"));



}

//** Load
void AircraftWidget::on_load(){
    qDebug("AircraftWidget > on_load() --------------------------------");

    QString program = "fgfs";
    QStringList arguments;
    arguments << "--show-aircraft";

    QProcess *process = new QProcess(this);

    process->start(program, arguments);

    if(process->waitForStarted()){
            process->waitForFinished();
            QByteArray result =  process->readAllStandardOutput();
            QByteArray errorResult = process->readAllStandardError();
            //** The fgfs --show_mistake returns the "man" and not an error ;-(
            //* so only way to detect is to get "-available aircraft" as text

            qDebug("OK");
            QStringList lines = QString(result).split("\n");
            //qDebug(lines);
            //#print type(result), result

            //#print type(error), error
            //qDebug(errorResult);
            //if(errorResult){
             //   qDebug("Error");

            //}
            //if error:
              //      self.emit(QtCore.SIGNAL("compile_log"), "error", QtCore.QString(error))
            //else:
               //     self.emit(QtCore.SIGNAL("compile_log"), "result", QtCore.QString(result))
            //    }
    }
}
