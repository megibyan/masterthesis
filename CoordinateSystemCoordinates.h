/**
*	@file CoordinateSystemCoordinates.h
*	@brief file contains the definaion of the class CoordinateSystemCoordinates.
*	@author Mikayel Egibyan
*/

#ifndef COORDINATESYSTEMCOORDINATES_H
#define COORDINATESYSTEMCOORDINATES_H

#include <iostream>
#include <string>

using namespace std;

class CoordinateSystemCoordinates
{
public:
    CoordinateSystemCoordinates();
    CoordinateSystemCoordinates(float);
    void setValue(float);
    float getValue();

private:
    float coordinateSystemCoordinates;
};

#endif // COORDINATESYSTEMCOORDINATES_H
