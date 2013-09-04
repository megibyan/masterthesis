/**
*	@file CoordinateSystemCoordinates.cpp
*	@brief file contains all necessary methods to work with CoordinateSystemCoordinates
*	@author Mikayel Egibyan
*/

#include "CoordinateSystemCoordinates.h"

/**
 * Default constructor
 * @author Mikayel Egibyan
 */
CoordinateSystemCoordinates::CoordinateSystemCoordinates()
{

}

/**
 * Default constructor
 * Returns the value of the coordinate
 * @param value The value of the coordinate
 */
CoordinateSystemCoordinates::CoordinateSystemCoordinates(float value)
{
    coordinateSystemCoordinates = value;
}

/**
 * This method is used to set a value to the coordinate
 * @author Mikayel Egibyan
 * @param value The value of the coordinate
 */
void CoordinateSystemCoordinates::setValue(float value)
{
    coordinateSystemCoordinates = value;
}

/**
 * This method is used to get a value to a label
 * @author Mikayel Egibyan
 * @return The value of the label
 */
float CoordinateSystemCoordinates::getValue()
{
    return coordinateSystemCoordinates;
}


