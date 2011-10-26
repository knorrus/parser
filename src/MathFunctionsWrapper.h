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

	double const eps = 0.0001;
	double const pi = 3.14159265;

	double abs (double value) {
		return value < 0 ? -value : value;
	}

	double wSin(double value){
		double temp = sin(value);
		temp = abs(temp - round(temp));
		return temp < eps ? int(sin(value)) : sin(value);
	}

	double wCos(double value){
		double temp = cos(value);
		temp = abs(temp - round(temp));
		return temp < eps ? int(cos(value)) : cos(value);
	}

	double tg (double value){
		double temp;
		temp = (value/(pi/2));
		if (abs(round(temp)-temp) < eps){
			throw OUTOFTYPE;
		}
		temp = tan(value);
		temp = abs(temp - round(temp));
		return temp < eps ? int(tan(value)) : tan(value);
	}

	double ctg (double value){
		double temp;
		temp = (value/pi);
		if (abs(round(temp)-temp) < eps){
			throw OUTOFTYPE;
		}
		temp = wCos(value)/wSin(value);
		temp = abs(temp - round(temp));
		return temp < eps ? int(tan(value)) : tan(value);
	}

	double sqrt2 (double value){
		if (value < 0){
			throw OUTOFTYPE;
		}
		return (double)(sqrt(value));
	}

}
#endif /* MATHFUNCTIONSWRAPPER_H_ */
