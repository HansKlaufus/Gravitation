#include "oscopevector.h"

unsigned int cOscopeVector::m_NextID = 0;

cOscopeVector::cOscopeVector() : mpFXYVector()
{
    //ctor
    m_ID         = cOscopeVector::m_NextID++;
    m_MaxHistory = 500;

    if(m_MaxHistory > -1)
    {
        m_VectorX.reserve(m_MaxHistory);
        m_VectorY.reserve(m_MaxHistory);
    }
}

cOscopeVector::cOscopeVector(unsigned int p_MaxHistory = 500) : mpFXYVector()
{
    //ctor
    m_ID         = cOscopeVector::m_NextID++;
    m_MaxHistory = p_MaxHistory;

    if(m_MaxHistory > -1)
    {
        m_VectorX.reserve(m_MaxHistory);
        m_VectorY.reserve(m_MaxHistory);
    }
}

cOscopeVector::~cOscopeVector()
{
    //dtor
}

void cOscopeVector::Clear()
{
    mpFXYVector::Clear();

    m_VectorX.clear();
    m_VectorY.clear();
}

void cOscopeVector::AddSample(double p_X = 0, double p_Y = 0)
{
    m_VectorX.push_back(p_X);
    m_VectorY.push_back(p_Y);

    if(m_MaxHistory > 0)
    {
        while(m_VectorX.size() > m_MaxHistory)
        {
            m_VectorX.erase(m_VectorX.begin());
            m_VectorY.erase(m_VectorY.begin());
        }
    }

    this->SetData(m_VectorX, m_VectorY);
}
