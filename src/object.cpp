#include <math.h>
#include <stdio.h>

#include "object.h"

unsigned int cObject::m_NextID = 0;

cObject::cObject(std::string name, double mass, double radius, double x, double y, double z)
{
    //ctor
    m_ID = cObject::m_NextID++;

    m_Name         = name;
    m_Mass         = mass;
    m_Radius       = radius;
    m_Displacement = 0.0;

    m_X = x;
    m_Y = y;
    m_Z = z;

    m_Vx = 0.0;
    m_Vy = 0.0;
    m_Vz = 0.0;

    m_Ax = 0.0;
    m_Ay = 0.0;
    m_Az = 0.0;

    m_Fx = 0.0;
    m_Fy = 0.0;
    m_Fz = 0.0;
}

cObject::cObject(std::string name, double mass, double radius, double x, double y, double z, double vx, double vy, double vz)
{
    //ctor
    m_ID = cObject::m_NextID++;

    m_Name         = name;
    m_Mass         = mass;
    m_Radius       = radius;
    m_Displacement = 0.0;

    m_X = x;
    m_Y = y;
    m_Z = z;

    m_Vx = vx;
    m_Vy = vy;
    m_Vz = vz;

    m_Ax = 0.0;
    m_Ay = 0.0;
    m_Az = 0.0;

    m_Fx = 0.0;
    m_Fy = 0.0;
    m_Fz = 0.0;
}

cObject::~cObject()
{
    //dtor
}

void cObject::PrintObject(void)
{
    printf("Name = %s, Mass = %6.2E, Radius = %6.2E, (X, Y, Z) = (%6.2E, %6.2E, %6.2E), (Vx, Vy, Vz) = (%6.2E, %6.2E, %6.2E), (Ax, Ay, Az) = (%6.2E, %6.2E, %6.2E)\n", m_Name.c_str(), m_Mass, m_Radius, m_X, m_Y, m_Z, m_Vx, m_Vy, m_Vz, m_Ax, m_Ay, m_Az);
}

void cObject::UpdateMotion(double timeStep)
{
    // TODO: Gravitational Forces are not constant, hence acceleration is not constant
    // Too large timesteps will cause errors

    m_Ax = m_Fx / m_Mass;
    m_Ay = m_Fy / m_Mass;
    m_Az = m_Fz / m_Mass;

    double dx = m_Vx*timeStep + 0.5*m_Ax*timeStep*timeStep;
    double dy = m_Vy*timeStep + 0.5*m_Ay*timeStep*timeStep;
    double dz = m_Vz*timeStep + 0.5*m_Az*timeStep*timeStep;

    m_Displacement = sqrt(dx*dx + dy*dy + dz*dz);

    m_X  = m_X + dx;
    m_Y  = m_Y + dy;
    m_Z  = m_Z + dz;

    m_Vx = m_Vx + m_Ax * timeStep;
    m_Vy = m_Vy + m_Ay * timeStep;
    m_Vz = m_Vz + m_Az * timeStep;
}
