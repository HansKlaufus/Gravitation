#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "../mathplot/mathplot.h"

#include <math.h>

class cFunction: public mpFX
{
public:
    cFunction() : mpFX( wxT("Function")) {}

    virtual double GetY( double x ) {return sin(x);};
};

#endif //__FUNCTION_H__
