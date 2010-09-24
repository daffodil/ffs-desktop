#include "googlemapwidget.h"


#include <QtCore/QByteArray>
#include <QtCore/QFile>
#include <QtCore/QStringList>

#include <QtGui/QVBoxLayout>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>
#include <QtGui/QToolButton>
#include <QtGui/QMenu>
#include <QtGui/QLabel>

#include <QtWebKit/QWebFrame>


GoogleMapWidget::GoogleMapWidget(QWidget *parent) :
    QWidget(parent)
{

    setWindowTitle(tr("Google Map"));
    setWindowIcon(QIcon(":/icons/mpmap"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);


    QToolBar *toolbar = new QToolBar();
    mainLayout->addWidget(toolbar, 0);


    //* Map Type
    QActionGroup *groupMapType = new QActionGroup(this);
    groupMapType->setExclusive(true);
    //connect(groupMapType, QtCore.SIGNAL("triggered(QAction *)"), this, self.on_map_type)

    QToolButton *buttMapType = new QToolButton();
    toolbar->addWidget(buttMapType);
    buttMapType->setText("XXXX");
    buttMapType->setPopupMode(QToolButton::InstantPopup);
    buttMapType->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QMenu *popTypeMenu = new QMenu(buttMapType);
    buttMapType->setMenu(popTypeMenu);

//    for b in ['RoadMap', 'Satellite','Hybrid','Terrain']:
//            act = QtGui.QAction(popTypeMenu)
//            act->setText(b)
//            act->setCheckable(True)
//            if b == "Hybrid": #self.main.settings.value("map_mode", "Hybrid"):
//                    act.setChecked(True)
//                    self.buttMapType.setText(b)
//
//            popTypeMenu.addAction(act)
//            self.groupMapType.addAction(act)

    toolbar->addSeparator();

    //style = "" #background-color: #efefef;"




    //** WebView
    webView = new QWebView();
    mainLayout->addWidget(webView);

    webView->page()->mainFrame()->addToJavaScriptWindowObject("QtWidget", this);

    //*********************************
    //** Status Bar
    statusBar = new QStatusBar();
    mainLayout->addWidget(statusBar);

    statusBar->addPermanentWidget(new QLabel("Zoom:"));
    //lblZoom = new QLabel("-");
   //statusBar->addPermanentWidget(lblZoom);

    buttZoom = new QToolButton();
    statusBar->addPermanentWidget(buttZoom);
    buttZoom->setText("Zoom");
    //buttZoom->setIcon(QIcon(":/icons/refresh"));
    buttZoom->setPopupMode(QToolButton::InstantPopup);
    buttZoom->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QMenu *menuZoom = new QMenu();
    buttZoom->setMenu(menuZoom);

    groupZoom = new QActionGroup(this);
    groupZoom->setExclusive(true);
    connect(groupZoom, SIGNAL(triggered(QAction *)),
            this, SLOT(on_zoom_action(QAction *))
    );
    //QAction *act;
    for(int z=1; z < 8; z++){
        QAction *act = new QAction(this);
        act->setText(QString(" %1 ").arg(z));
        act->setProperty("zoom", QVariant("z"));
        act->setCheckable(true);
        //act.setChecked(b[0] == 'Uk');
        menuZoom->addAction(act);
        groupZoom->addAction(act);
    }
//    for b in self.Zoom.levels():
//            act = QtGui.QAction(toolbar)
//            act.setText(b[0])
//            act.setProperty("zoom", QtCore.QVariant(b[1]))
//            act.setCheckable(True)
//            act.setChecked(b[0] == 'Uk')
//            toolbar.addAction(act)
//            self.groupZoom.addAction(act)
    //#toolbar->addSeparator()


    statusBar->addPermanentWidget(new QLabel("Lat:"));
    lblLat = new QLabel();
    //lblLat.setStyleSheet(style)
    lblLat->setFixedWidth(140);
    lblLat->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar->addPermanentWidget(lblLat);

    //QLabel *lblLng = QLabel();
    //toolbar.addAction("Lng:")
    statusBar->addPermanentWidget(new QLabel("Lng:"));
    lblLng = new QLabel();
    //lblLng->setStyleSheet(style);
    lblLng->setFixedWidth(140);
    statusBar->addPermanentWidget(lblLng);

    //toolbar->addSeparator();



    resize(800, 400);
    move(10,10);

    //qDebug() << QResource(":/map/gmap.html");
    QFile *file = new QFile("/home/mash/ffs-desktop/ffs-desktop/map/html/gmap.html");
    //QFile *file = new QFile(":/gmap/gmap.html");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug("not open file");
            return;
       }
    QByteArray contents = file->readAll();
    webView->setHtml(contents);
//        qDebug("OKKK");
}



void GoogleMapWidget::map_mouse_move(QVariant dLat, QVariant dLng){
    //qDebug("YES");
    //qDebug() << lat.toString();
    lblLat->setText(dLat.toString());
    lblLng->setText(dLng.toString());
}


void GoogleMapWidget::map_error(QVariant err){
    qDebug("map_error()");
}

void GoogleMapWidget::marker_clicked(QVariant marker, QVariant mId){
    qDebug("marker_clicked()");
}

void GoogleMapWidget::marker_unselected(QVariant curr_idx, QVariant mLocationId){
    qDebug("marker_unselected()");
}

//** JS
void GoogleMapWidget::map_right_click(QVariant lat, QVariant lng){

    qDebug("map_right_click()");
}

//** JS
void GoogleMapWidget::map_zoom_changed(QVariant zoom){
    buttZoom->setText(zoom.toString());
    int zoomInt = zoom.toInt();
    QList<QAction *> actions = groupZoom->actions();
    for (int i = 0; i < actions.size(); ++i) {
        if (actions.at(i)->property("zoom").toInt() == zoomInt){
             actions.at(i)->setChecked(true);
             return;
        }
     }
//    for a in self.groupZoom.actions():
//            checked = a.property("zoom").toString() == new_zoom_level
//            a.setChecked(checked)
      qDebug("map_zoom_changed()");
}

void GoogleMapWidget::on_zoom_action(QAction *act){
    qDebug("on_zoom_action()");
}

/*
The whole units of degrees will remain the same (i.e. in 121.135° longitude, start with 121°).
Multiply the decimal by 60 (i.e. .135 * 60 = 8.1).
The whole number becomes the minutes (8').
Take the remaining decimal and multiply by 60. (i.e. .1 * 60 = 6).
The resulting number becomes the seconds (6"). Seconds can remain as a decimal.
Take your three sets of numbers and put them together, using the symbols for degrees (°), minutes (‘), and seconds (") (i.e. 121°8'6" longitude)
*/
QString GoogleMapWidget::to_lat(QVariant lat){
    QStringList latParts = lat.toString().split(".");
    int deci = latParts[1].toInt();
    //qDebug() << deci;
    float f = deci * 60;
    //qDebug() << deci << f;
    return latParts[1];
}


/*
  /home/mash/ffs-desktop/ffs-desktop/map/googlemapwidget.cpp:128: error: invalid use of incomplete type ‘struct QDebug’
  */
