/**
*	@file Label.h
*	@brief file contains the definaion of the class Label
*	@author Mikayel Egibyan
*/

#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include <string>
#include <QString>

using namespace std;

class Label
{
public:
    Label();
    Label(string);
    void setValue(string);
    string getValue();

private:
    string label;
};

#endif // LABEL_H
