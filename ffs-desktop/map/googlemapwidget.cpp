#include "googlemapwidget.h"


#include <QtCore/QByteArray>
#include <QtCore/QFile>

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


    QToolbar * toolbar = QToolBar();
    mapLayout->addWidget(toolbar, 0);


    //* Map Type
    QActionGroup * groupMapType = QActionGroup();
    groupMapType.setExclusive(True);
    //connect(groupMapType, QtCore.SIGNAL("triggered(QAction *)"), this, self.on_map_type)

    QToolButton *buttMapType = QToolButton();
    toolbar->addWidget(self.buttMapType);
    buttMapType->setText("XXXX");
    buttMapType->setPopupMode(QToolButton::InstantPopup);
    buttMapType->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QMenu *popTypeMenu = QtGui.QMenu(buttMapType);
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

    toolbar->addSeparator()

    style = "" #background-color: #efefef;"

    toolbar.addAction(new QLabel("Lat:"));
    self.lat = QtGui.QLabel()
    self.lat.setStyleSheet(style)
    self.lat.setFixedWidth(140)
    self.lat.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
    toolbar.addWidget(self.lat)

    QLabel *lblLng = QLabel();
    toolbar.addAction("Lng:")
    self.lng = QtGui.QLabel()
    self.lng.setStyleSheet(style)
    self.lng.setFixedWidth(140)
    toolbar.addWidget(self.lng)

    toolbar.addSeparator()


    browser = new QWebView();
    mainLayout->addWidget(browser);

    browser->page()->mainFrame()->addToJavaScriptWindowObject("QtWidget", this);

    resize(800, 400);
    move(10,10);

    //qDebug() << QResource(":/map/gmap.html");
    QFile *file = new QFile("/home/ffs/ffs-desktop/ffs-desktop/map/html/gmap.html");
    //QFile *file = new QFile(":/gmap/gmap.html");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug("not open file");
            return;
       }
    QByteArray contents = file->readAll();
    browser->setHtml(contents);
//        qDebug("OKKK");
}

void GoogleMapWidget::map_mouse_move(QVariant lat, QVariant lng){
    qDebug("YES");
}
