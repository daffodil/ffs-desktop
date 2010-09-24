

#include "airportswidget.h"
#include "parse/aptdatparser.h"


//#include <QtCore/QProcess>
//#include <QtCore/QByteArray>
#include <QtCore/QString>
//#include <QtCore/QStringList>


// layouts
#include <QtGui/QVBoxLayout>
//#include <QtGui/QHBoxLayout>
//#include <QtGui/QGroupBox>
#include <QtGui/QSplitter>

#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
//#include <QtGui/QAbstractButton>
#include <QtGui/QButtonGroup>

#include <QtGui/QAction>
#include <QtGui/QLabel>
//#include <QtGui/QCheckBox>
//#include <QtGui/QTabWidget>

#include <QtGui/QStandardItemModel>
#include <QtGui/QItemSelection>
#include <QtGui/QItemSelectionModel>
#include <QtGui/QAbstractItemView>
//#include <QtGui/QPixmap>

AirportsWidget::AirportsWidget(QWidget *parent) :
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
    connect(actionRefreshTree, SIGNAL(triggered()), this, SLOT(load_airports()) );

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
    headerLabelsList << "Code" << "Aiport";
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

}


void AirportsWidget::load_airports(){
    AptDatParser *aptDatParser = new AptDatParser(this);
    qDebug("load_airports()");
    aptDatParser->process_file();

}
