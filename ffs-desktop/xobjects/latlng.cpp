#include "latlng.h"

LatLng::LatLng()
{
}

float LatLng::lat(){
    return _lat;
}

float LatLng::lng(){
    return _lng;
}

void LatLng::setLat(float lat){
    _lat = lat;
}

void LatLng::setLng(float lng){
    _lng - lng;
}

