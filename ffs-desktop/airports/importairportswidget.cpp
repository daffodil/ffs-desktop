#include "importairportswidget.h"
#include "aptdatparser.h"
#include "airportsdb.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QIcon>
#include <QtGui/QLabel>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QProgressDialog>
//#include <QtGui/>

ImportAirportsWidget::ImportAirportsWidget(MainObject *mainOb, QDialog *parent) :
    QDialog(parent)
{

    mainObject = mainOb;
 //   airportsDb = new AirportsDb(this);

    setWindowTitle("Import Airports");
    setWindowIcon(QIcon(":/icons/import"));
    //setWindowFlags(  Qt::WindowStaysOnTopHint);

    //* MainWidget and MainLayout
    //QWidget *mainWidget = new QWidget(this);
    //setCentralWidget(mainWidget);
    setFixedWidth(400);

    QVBoxLayout *mainVBox = new QVBoxLayout();
    this->setLayout(mainVBox);
    int m = 20;
    mainVBox->setContentsMargins(m,m,m,m);
    mainVBox->setSpacing(10);


//    QLabel *headerLabel = new QLabel(this);
//    headerLabel->setText("Import Airports");
//    headerLabel->setStyleSheet("font-size: 20pt; font-weight: bold; background-color: white;");
//    mainVBox->addWidget(headerLabel, 1);

    //QGroupBox *grpOpts = new QGroupBox();
    //mainVBox->addWidget(grpOpts);
    //grpOpts->setTitle(tr("Aiport Import Options"));
   // mainVBox->addWidget(headerLabel, 1);
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


}

void ImportAirportsWidget::on_import_button_clicked(){
    qDebug() << "on_import_button_clicked()";


    AptDatParser *aptDatParser = new AptDatParser(this);

    progress = new QProgressDialog("Importing Airports...", "Cancel", 0, aptDatParser->estimated_lines, this);
    progress->setWindowModality(Qt::WindowModal);
    connect(progress, SIGNAL(canceled()),
            aptDatParser, SLOT(cancel_import())
    );

    AirportsDb *airportsDb = new AirportsDb();
    connect(aptDatParser,   SIGNAL(airport_data(QString, QString, QString, QString)),
            airportsDb,      SLOT(insert_airport(QString, QString, QString, QString))
    );
    connect(aptDatParser,   SIGNAL(line_count(int)),
            progress,      SLOT(setValue(int))
    );
    airportsDb->create_tables();
    aptDatParser->import_aptdat();
    //QProgressBar progress = new QProgressBar
}
