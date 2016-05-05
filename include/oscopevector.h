#ifndef COSCOPEVECTOR_H
#define COSCOPEVECTOR_H

#include "../mathplot/mathplot.h"
#include <vector>

class cOscopeVector : public mpFXYVector
{
    private:
        static unsigned int m_NextID;
        unsigned int        m_ID;

        std::vector<double> m_VectorX;
        std::vector<double> m_VectorY;
        int                 m_MaxHistory; //-1: No limit, everything else is limit

    public:
        cOscopeVector();
        cOscopeVector(unsigned int p_MaxHistory);
        virtual ~cOscopeVector();

        unsigned int GetID() { return m_ID; };
        void         Clear(void);
        void         AddSample(double p_X, double p_Y);
};

#endif // COSCOPEVECTOR_H
