#ifndef XCALC_H
#define XCALC_H

#include <QObject>
#include "latlng.h"

class XCalc : public QObject
{
Q_OBJECT
public:
    explicit XCalc(QObject *parent = 0);

    LatLng latlng_dist_heading(LatLng latlng, int dist, float heading);

   static  float deg_to_rad(float deg);
    static float deg_to_quad(float deg);

    static float rad_to_deg(float rad);


    static int rev_deg(int deg);

signals:

public slots:

};

#endif // XCALC_H
