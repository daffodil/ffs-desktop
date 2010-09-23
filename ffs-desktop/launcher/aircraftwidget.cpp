
/**
  This widget displays a list of aircraft,
    does a background call to a process that executes FG
  */

#include "launcher/aircraftwidget.h"

#include <QtCore/QProcess>
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QStringList>


// layouts
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QSplitter>

#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QAbstractButton>
#include <QtGui/QButtonGroup>

#include <QtGui/QAction>
#include <QtGui/QLabel>

#include <QtGui/QStandardItemModel>
#include <QtGui/QItemSelection>
#include <QtGui/QItemSelectionModel>
#include <QtGui/QAbstractItemView>
#include <QtGui/QPixmap>

//* tree
//#include <QtGui/QHeaderView>
//#include <QtGui/QTreeWidgetItem>
//#include <QtGui/QAction>
/*


*/

AircraftWidget::AircraftWidget(QWidget *parent) :
    QWidget(parent)
{

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    QSplitter *splitter = new QSplitter(this);
    mainLayout->addWidget(splitter);

    //***************************************************
    //** Left
    QWidget *leftWidget = new QWidget();
    splitter->addWidget(leftWidget);
    QVBoxLayout *treeLayout = new QVBoxLayout();
    leftWidget->setLayout(treeLayout);
    treeLayout->setContentsMargins(0,0,0,0);
    treeLayout->setSpacing(0);


    //** Toolbar
    QToolBar *treeToolbar = new QToolBar();
    treeLayout->addWidget(treeToolbar);
    treeToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    
    QAction *actionRefreshTree = new QAction(this);
    treeToolbar->addAction(actionRefreshTree);
    actionRefreshTree->setText("Refresh");
    actionRefreshTree->setIcon(QIcon(":/icons/refresh"));
    connect(actionRefreshTree, SIGNAL(triggered()), this, SLOT(load_aircraft()) );

    treeToolbar->addSeparator();

    //******************************************************
    //** Filter Buttons
    QButtonGroup *buttViewGroup = new QButtonGroup(this);
    buttViewGroup->setExclusive(true);
    connect(buttViewGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(on_view_button_clicked(QAbstractButton*))
    );

    QToolButton *buttAll = new QToolButton();
    treeToolbar->addWidget(buttAll);
    buttViewGroup->addButton(buttAll);
    buttAll->setText("All");
    buttAll->setCheckable(true);
    buttAll->setIcon(QIcon(":/icons/pink"));
    buttAll->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QToolButton *buttInstalled = new QToolButton();
    treeToolbar->addWidget(buttInstalled);
    buttViewGroup->addButton(buttInstalled);
    buttInstalled->setText("Installed");
    buttInstalled->setCheckable(true);
    buttInstalled->setIcon(QIcon(":/icons/purple"));
    buttInstalled->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QToolButton *buttAvailable = new QToolButton();
    treeToolbar->addWidget(buttAvailable);
    buttViewGroup->addButton(buttAvailable);
    buttAvailable->setText("Available");
    buttAvailable->setCheckable(true);
    buttAvailable->setIcon(QIcon(":/icons/purple"));
    buttAvailable->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    buttAll->setChecked(true);


    //******************************************************
    //** Models
    model = new QStandardItemModel(this);
    model->setColumnCount(2);
    QStringList headerLabelsList;
    headerLabelsList << "Model" << "Description";
    model->setHorizontalHeaderLabels(headerLabelsList);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);

    //** Aircraft Tree
    treeView = new QTreeView(this);
    treeLayout->addWidget(treeView);
    treeView->setModel(proxyModel);
    treeView->setAlternatingRowColors(true);
    treeView->setRootIsDecorated(false);
    treeView->setSortingEnabled(true);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    /*
    connect( treeView->selectionModel(),
             SIGNAL( selectionChanged (const QItemSelection&, const QItemSelection&) ),
             SLOT( set_aircraft(const QItemSelection&, const QItemSelection&) )
    );
    */
    connect(treeView,
            SIGNAL(clicked(QModelIndex)),
            this, SLOT(on_tree_clicked(QModelIndex))
    );

    statusBarTree = new QStatusBar();
    treeLayout->addWidget(statusBarTree);
    statusBarTree->showMessage("Idle");

    /*


    QItemSelectionModel *selModel = treeView->selectionModel();
    connect( selModel,
             SIGNAL(currentRowChanged ( QModelIndex current, QModelIndex previous )),
             SLOT(show_aircraft_details ( const QModelIndex &current, const QModelIndex &previous ))
    );
    */
    //** RightPanel
    //QPixMap()
    //* /usr/share/games/FlightGear/

    //*************************************************************************************************
    //** Right
    //*************************************************************************************************
//    QWidget *rightWidget = new QWidget();
//    splitter->addWidget(rightWidget);
    QGroupBox *grpAero = new QGroupBox();
    splitter->addWidget(grpAero);
    QString style = QString("QGroupBox{border:2px solid gray;border-radius:5px;  margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");
    grpAero->setStyleSheet(style);
    grpAero->setDisabled(false);
    grpAero->setTitle(tr("Aircraft Details"));


    QVBoxLayout *aeroLayout = new QVBoxLayout();
    grpAero->setLayout(aeroLayout);
    int aM = 10;
    aeroLayout->setContentsMargins(aM,aM,aM,aM);
    aeroLayout->setSpacing(0);

    //**********************************************8
    //** Toolbar
    QGroupBox *grpAeroPanel = new QGroupBox();
    aeroLayout->addWidget(grpAeroPanel);

    QString styleX = QString("QGroupBox{ background-color: black; border:2px solid gray;border-radius:5px;  margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");
    grpAeroPanel->setStyleSheet(styleX);
    //QWidget *aeroPanelWidget = new QWidget();
    //aeroLayout->addWidget(aeroPanelWidget);
    //aeroPanelWidget->setStyleSheet("border: 1px solid red; background-color: black;");

    QVBoxLayout *aeroPanelLayout = new QVBoxLayout();
    grpAeroPanel->setLayout(aeroPanelLayout);



    lblAircraftModel = new QLabel("B747-400ER");
    aeroPanelLayout->addWidget(lblAircraftModel);
    lblAircraftModel->setStyleSheet("padding: 5px 5px 5px 5px;   color: #eeeeee; font-fmaily: monospace; font-size: 20pt;");

    lblAircraftDescription = new QLabel("Boeing 757 ER");
    aeroPanelLayout->addWidget(lblAircraftDescription);
    lblAircraftDescription->setStyleSheet("padding: 0px 5px 5px 15px;  color: #eeeeee; font-fmaily: monospace; font-size: 10pt;");

    QLabel *aeroImageLabel =  new QLabel(this);
    aeroPanelLayout->addWidget(aeroImageLabel);

    QPixmap aeroImage("/home/ffs/ffs-desktop/ffs-desktop/icons/_test_.png");
    if(aeroImage.isNull()){
        qDebug("NULL");

    }
    aeroImageLabel->setPixmap(aeroImage);

    ;

    aeroLayout->addStretch(10);

    QToolBar *aeroToolbar = new QToolBar();
    aeroLayout->addWidget(aeroToolbar);
    aeroToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QAction *actionReloadAero = new QAction(this);
    aeroToolbar->addAction(actionReloadAero);
    actionReloadAero->setText("Reload");
    actionReloadAero->setIcon(QIcon(":/icons/refresh"));
    //connect(actionReloadAero, SIGNAL(triggered()), this, SLOT(load_aircraft()) );

    //***********************************
    //** Setup
    load_aircraft();
}

//** Load
void AircraftWidget::load_aircraft(){

    qDebug("AircraftWidget > on_load() --------------------------------");

    QString program = "fgfs";
    QStringList arguments;
    arguments << "--show-aircraft";

    QProcess *process = new QProcess(this);
    process->start(program, arguments);

    QStringList::Iterator it;
    QString line;
    int row_count=0;

    if(process->waitForStarted()){
            process->waitForFinished();
            QByteArray result =  process->readAllStandardOutput();
            QByteArray errorResult = process->readAllStandardError();
            //** The fgfs --show_mistake returns the "man" and not an error ;-(
            //* so only way to detect is to get "-available aircraft" as text

           // qDebug("OK");
            QStringList lines = QString(result).split("\n");

            for ( it = lines.begin() ; it != lines.end() ; it++ ){

                line = it->simplified();

                //* Unless first item == Available aircraft: then its an error (messy)
                if(it == lines.begin()){
                    if(line  != "Available aircraft:"){
                       // qDebug("ERROR");
                        //TODO emit("error")
                        return;
                    }else{
                        // qDebug("FIRSTLINE");

                    }
                }else{
                    //qDebug( s );

                    QStandardItem *modelItem = new QStandardItem();
                    modelItem->setText( line.section( ' ', 0, 0 )); //* first chars to space
                    model->setItem(row_count, 0, modelItem);
                    QStandardItem *descriptionItem = new QStandardItem();
                    descriptionItem->setText( line.section( ' ', 1 )); //* after first space
                    model->setItem(row_count, 1, descriptionItem);

                   // qDebug( "line");
                    row_count++;
                }
            }
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


//****************************

void AircraftWidget::on_tree_clicked(QModelIndex mIdx){
    qDebug("on_tree_clicked");
    //QString
    QStandardItem *item = model->itemFromIndex ( mIdx );

    //qDebug()  << item->text();
}


void AircraftWidget::show_aircraft_details(const QModelIndex &current, const QModelIndex &previous){
    qDebug("set_aircraft()");
    //QString
}
void AircraftWidget::on_view_button_clicked(QAbstractButton *button){
    qDebug("on_view_button_clicked()");
    //qDebug() << button->text();
    // TODO
    statusBarTree->showMessage(button->text());
    //QString
}

