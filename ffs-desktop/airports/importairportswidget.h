#ifndef IMPORTAIRPORTSWIDGET_H
#define IMPORTAIRPORTSWIDGET_H

#include <QtGui/QDialog>
#include <QtGui/QRadioButton>
#include <QtGui/QCheckBox>
#include <QtGui/QPushButton>
#include <QtGui/QProgressDialog>

#include "mainobject.h"

class ImportAirportsWidget : public QDialog
{
Q_OBJECT
public:
    explicit ImportAirportsWidget(MainObject *mainOb, QDialog *parent = 0);
    MainObject *mainObject;

    QRadioButton *buttAllAiports;
    QRadioButton *buttIcaoOnly;
    QCheckBox *chkImportSeaports;
    QCheckBox *chkImportHeliports;

    QPushButton *buttImport;
    QPushButton *buttCancelImport;

    QProgressDialog *progress;

signals:

public slots:
    void on_import_button_clicked();
    void update_progress(int);
};

#endif // IMPORTAIRPORTSWIDGET_H
