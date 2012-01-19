/*
 * MathFunctionsWrapper.h
 *
 *  Created on: Oct 26, 2011
 *      Author: pavel
 */

#ifndef MATHFUNCTIONSWRAPPER_H_
#define MATHFUNCTIONSWRAPPER_H_

#include <math.h>
#include "ExprTypes.h"

namespace math {

double const eps = 0.1;
double const pi = 3.14159265;

double abs (double value) {
    return value < 0 ? -value : value;
}
double tg (double value){
    double temp;
    temp = abs(value/pi);
    if (abs(temp - floor(temp) -0.5) < eps){
        throw OUTOFTYPE;
    }
    return tan(value);
}
double ctg (double value){
    return - tg(value+pi/2);
}
double sqrt2 (double value){
    if (value < 0){
        throw OUTOFTYPE;
    }
    return (double)(sqrt(value));
}
double ln(double value){
    if (value <= 0){
        throw OUTOFTYPE;
    }
    return (double)(log(value));
}

double lg(double value){
    if (value <= 0){
        throw OUTOFTYPE;
    }
    return (double)(log10(value));
}
double arcsin(double value){
    if ( abs(value) > 1){
        throw OUTOFTYPE;
    }
    return (double)(asin(value));
}
double arccos(double value){
    if ( abs(value) > 1){
        throw OUTOFTYPE;
    }
    return (double)(acos(value));
}
double arcctg(double value){
    return (double)(pi/2 - atan(value));
}
}
#endif /* MATHFUNCTIONSWRAPPER_H_ */
