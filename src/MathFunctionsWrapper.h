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

        double const eps = 0.05;
	double const pi = 3.14159265;

	double abs (double value) {
		return value < 0 ? -value : value;
	}

	double tg (double value){
		double temp;
                temp = (value/pi);
                if (abs(temp - floor(temp) -0.5) < eps){
                        throw OUTOFTYPE;
                }
                return tan(value);
	}

        double ctg (double value){
                double temp;
                temp = (value/pi);
                if (abs(temp - floor(temp)) < eps){
                        throw OUTOFTYPE;
                }
                temp = cos(value)/sin(value);
                return temp;
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

}
#endif /* MATHFUNCTIONSWRAPPER_H_ */
