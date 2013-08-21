/**
*	@file Label.cpp
*	@brief file contains all necessary methods to work with Label.
*
*	@author Mikayel Egibyan
*/

#include "Label.h"

/**
 * Default constructor
 * @author Mikayel Egibyan
 */
Label::Label()
{

}

/**
 * Default constructor
 * Returns the value of the label
 * @author Mikayel Egibyan
 * @param value The value of the label
 */
Label::Label(string value)
{
    label = value;
}

/**
 * This method is used to set a value to a label
 * @author Mikayel Egibyan
 * @param value The value of the label
 */
void Label::setValue(string value)
{
    label = value;
}

/**
 * This method is used to get a value of a label
 * @author Mikayel Egibyan
 * @return The value of the label
 */
string Label::getValue()
{
    return label;
}

