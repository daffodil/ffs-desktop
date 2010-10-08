#include "importairportswidget.h"
#include "aptdatparser.h"

#include <QtCore/QFileInfo>
#include <QtCore/QProcess>


#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QIcon>
#include <QtGui/QLabel>
#include <QtGui/QCheckBox>
#include <QtGui/QProgressDialog>


ImportAirportsWidget::ImportAirportsWidget(MainObject *mainOb, QDialog *parent) :
    QDialog(parent)
{

    mainObject = mainOb;

    setWindowTitle("Import Airports");
    setWindowIcon(QIcon(":/icons/import"));
    //setWindowFlags(  Qt::WindowStaysOnTopHint);

    setFixedWidth(400);

    QVBoxLayout *outerContainer = new QVBoxLayout();
    this->setLayout(outerContainer);
    outerContainer->setContentsMargins(0,0,0,0);
    outerContainer->setSpacing(10);

    QVBoxLayout *mainVBox = new QVBoxLayout();
    outerContainer->addLayout(mainVBox);
    int m = 20;
    mainVBox->setContentsMargins(m,m,m,m);
    mainVBox->setSpacing(10);


    QLabel *lblHelp = new QLabel("<ul><li>Select the airports to import</li><li>You can run this more than once</li></ul>");
    mainVBox->addWidget(lblHelp, 1);
    lblHelp->setStyleSheet("background-color: #efefef; padding: 5px; border: 1px solid #000099;");

    //** IACO Only
    buttIcaoOnly = new QRadioButton();
    mainVBox->addWidget(buttIcaoOnly, 1);
    buttIcaoOnly->setText("Import ICAO airports only");
    buttIcaoOnly->setChecked(true);

    //** All Airports
    buttAllAiports = new QRadioButton();
    mainVBox->addWidget(buttAllAiports, 1);
    buttAllAiports->setText("Import all airports.");
    buttAllAiports->setDisabled(true);

    //** Seaports
    chkImportSeaports = new QCheckBox();
    chkImportSeaports->setText(tr("Import Seaports"));
    mainVBox->addWidget(chkImportSeaports, 1);
    chkImportSeaports->setDisabled(true);

    //** Heliports
    chkImportHeliports = new QCheckBox();
    chkImportHeliports->setText(tr("Import Heliports"));
    mainVBox->addWidget(chkImportHeliports, 1);
    chkImportHeliports->setDisabled(true);

    //*****************************************************************
    //** Bottom Button Box
    QHBoxLayout *buttonBox = new QHBoxLayout();
    mainVBox->addLayout(buttonBox);
    buttonBox->addStretch(10);


    //* Cancel Import button
    buttCancelImport = new QPushButton();
    buttonBox->addWidget(buttCancelImport);
    buttCancelImport->setText(tr("Close"));
    buttCancelImport->setIcon(QIcon(":/icons/black"));
    connect(buttCancelImport, SIGNAL(clicked()), this, SLOT(reject()));
    //buttCancelImport->setDisabled(true);

    //* Import button
    buttImport = new QPushButton();
    buttonBox->addWidget(buttImport);
    buttImport->setText(tr("Import"));
    buttImport->setIcon(QIcon(":/icons/save"));
    connect(buttImport, SIGNAL(clicked()),
            this, SLOT(on_import_button_clicked())
            );

    statusBar = new XStatusBar();
    outerContainer->addWidget(statusBar);

}



void ImportAirportsWidget::update_progress(int value){
    progress->setValue(value);
    progress->setLabelText(QString::number(value));
}

//*********************************************************************
//** Import Clicked
void ImportAirportsWidget::on_import_button_clicked(){

    QString tarball_path = mainObject->settings->fg_root("Airports/apt.dat.gz");
    qDebug() << tarball_path;
    QFileInfo fileInfo = QFileInfo(tarball_path);
    if(!fileInfo.exists()){
        statusBar->showError(QString("Cannot open '%1'").arg(tarball_path));
        return;
    }
    QString temp_file = mainObject->settings->temp("apt.dat");

    statusBar->showMessage(QString("Unpacking tarball"));
    //** Unzip to temp file
    //TODO but does it work on WindoZE ??
    QString command = QString("zcat %1")
                      .arg(tarball_path);

    QProcess unzipProcess;
    unzipProcess.setStandardOutputFile(temp_file);
    unzipProcess.start(command);
    if (!unzipProcess.waitForStarted())
        return; // false;
    if (!unzipProcess.waitForFinished())
        return; // false;
    QByteArray result = unzipProcess.readAll();

    //qDebug() <<  result;
    //return;
    statusBar->showMessage( QString("Importing '%1'").arg(temp_file) );

    AptDatParser *aptDatParser = new AptDatParser(this);
    aptDatParser->import_aptdat(temp_file);

    //this->accept();
}

