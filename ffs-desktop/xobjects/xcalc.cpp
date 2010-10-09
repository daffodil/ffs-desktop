#include "xcalc.h"
#include "math.h"



LatLng XCalc::latlng_dist_heading(LatLng latlng, int distance, float heading) {

    // The simpliest lat/lon to distance formula
    // thanks pigeon http://pigeond.net/git/?p=flightgear/fgmap.git;a=blob;f=fgmap.js;
    // var r = 365239.5;
    //float PI = 3.14159265;
    float r = 365239.5;

    //var rad = deg_to_rad(parseFloat(heading));
    int rad = XCalc::deg_to_rad(heading);

    //var a = Math.cos(rad) * dist;
    float a = cos(rad) * distance;

    //var o = Math.sin(rad) * dist;
    float o = sin(rad) * distance;

    //var dlat = a / r;
    //LatLng rLatLng;
    float dLat = a / r;
    //rLatLng.setLat( a / r );

    //var dlng = o / Math.cos(deg_to_rad(latlng.lat() + dlat)) / r;
    float dLng = o / (cos( XCalc::deg_to_rad(latlng.lat() + dLat) )) / r;
    //rLatLng.setLng(dLng);
    return  LatLng(dLat, dLng);
    //return new GLatLng(latlng.lat() + dlat, latlng.lng() + dlng);
    //*/
}


float XCalc::deg_to_rad(float deg) {
    //return (deg * Math.PI / 180);
    return (deg * 3.14159265 / 180);
}

float XCalc::deg_to_quad(float deg) {
    //return parseInt(deg / 90);
    return deg / 90;
}

float XCalc::rad_to_deg(float rad) {
    //return (rad * 180 / Math.PI);
    return (rad * 180 / 3.14159265);
}

int XCalc::rev_deg(int deg) {
    return deg > 180 ? deg - 180 : deg + 180;
}
