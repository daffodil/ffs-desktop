#ifndef XCALC_H
#define XCALC_H

#include "latlng.h"

class XCalc
{
    //const float PI = 3.14159265;
public:

    static LatLng latlng_dist_heading(LatLng latlng, int dist, float heading);

    static  float deg_to_rad(float deg);
    static float deg_to_quad(float deg);

    static float rad_to_deg(float rad);
    static int rev_deg(int deg);



};

#endif // XCALC_H
