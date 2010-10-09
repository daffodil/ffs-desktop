#include "xcalc.h"
#include "math.h"
#include <QtDebug>

//** Calculate position from
//*** Current position
//*** Distance metres
//*** Heading

LatLng XCalc::latlng_dist_heading(LatLng latlng, int distance, float heading) {

    //float PI = 3.14159265;
    float r = 365239.5;
    float rad = XCalc::deg_to_rad(heading);
    qDebug() << "Heading radians=" << rad;

    float a = cos(rad) * distance;

    float o = sin(rad) * distance;

    float dLat = a / r;

    float dLng = o / (cos( XCalc::deg_to_rad(latlng.lat() + dLat) )) / r;

    return  LatLng(latlng.lat() + dLat, latlng.lng() + dLng);

}

//** Degrees To Radians
float XCalc::deg_to_rad(float deg) {
    return (deg * XCalc::PI / 180);
}

float XCalc::deg_to_quad(float deg) {
    //return parseInt(deg / 90);
    return deg / 90;
}

float XCalc::rad_to_deg(float rad) {
    //return (rad * 180 / Math.PI);
    return (rad * 180 / XCalc::PI);
}

int XCalc::rev_deg(int deg) {
    return deg > 180 ? deg - 180 : deg + 180;
}
