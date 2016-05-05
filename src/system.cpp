#include <iostream>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "system.h"

cSystem::cSystem(void)
{
    m_timeStep            = 1.0;
    m_timeMultiplier      = 1.0;
    m_largestDisplacement = -1.0;
    m_smallestDistance    = -1.0;
}

cSystem::cSystem(bool dumpData)
{
    m_timeStep            = 1.0;
    m_timeMultiplier      = 1.0;
    m_largestDisplacement = -1.0;
    m_smallestDistance    = -1.0;

    if(dumpData) m_file.open(DATAFILE, std::fstream::out);
}

cSystem::~cSystem()
{
    //dtor
    if(m_file.is_open()) m_file.close();
}

void cSystem::CreateSolarSystem(double timeStep)
{
    m_timeStep = timeStep;

    /*
    **  Format: Name, Mass, Radius, X, Y, Z, VX, VY, VZ
    */

    // Create Sun
    cObject sun = cObject( "Sun", 1.988E30, 696E6, 0.0, 0.0, 0.0);
    this->AddObject(sun);

    // Create Mercury
    cObject mercury = cObject("Mercury", 0.0553*EARTH_MASS, 2439.9E3, 0.3871*EARTH_DISTANCE, 0, 0, 0, 47.872E3, 0);
    this->AddObject(mercury);

    // Create Venus
    cObject venus = cObject("Venus", 0.8150*EARTH_MASS, 1000*6051.8E3, 0.7233*EARTH_DISTANCE, 0, 0, 0, 35.021E3, 0);
    this->AddObject(venus);

    // Create Earth
    cObject earth = cObject("Earth", 1.0000*EARTH_MASS, 1000*6378.1E3, 1.0000*EARTH_DISTANCE, 0, 0, 0, 29.784E3, 0);
    this->AddObject(earth);

    // Create Moon
    cObject moon = cObject("Moon", 0.0123*EARTH_MASS, 1000*1737.5E3, 1.0000*EARTH_DISTANCE, 384.404E6, 0, -1.02317E3, 0, 0);
    this->AddObject(moon);

    // Create Mars
    cObject mars = cObject("Mars", 0.1074*EARTH_MASS, 1000*3396.2E3, 1.5237*EARTH_DISTANCE, 0, 0, 0, 24.129E3, 0);
    this->AddObject(mars);

    // Create Jupiter
    cObject jupiter = cObject("Jupiter", 317.8284*EARTH_MASS, 1000*71492E3, 5.2027*EARTH_DISTANCE, 0, 0, 0, 13.064E3, 0);
    this->AddObject(jupiter);

    // Create Saturn
    cObject saturn = cObject("Saturn", 95.1910*EARTH_MASS, 1000*60268E3, 9.5233*EARTH_DISTANCE, 0, 0, 0, 9.661E3, 0);
    this->AddObject(saturn);

    // Create Uranus
    cObject uranus = cObject("Uranus", 14.5358*EARTH_MASS, 1000*25559E3, 19.2470*EARTH_DISTANCE, 0, 0, 0, 6.813E3, 0);
    this->AddObject(uranus);

    // Create Neptune
    cObject neptune = cObject("Neptune", 17.1478*EARTH_MASS, 1000*24764E3, 30.1166*EARTH_DISTANCE, 0, 0, 0, 5.443E3, 0);
    this->AddObject(neptune);
}

void cSystem::Initialise(int numberPlanets, double size, double timeStep)
{
    m_timeStep            = timeStep;
    m_timeMultiplier      = 1.0;
    m_largestDisplacement = -1.0;
    m_smallestDistance    = -1.0;

    srand(time(NULL));
    for(int i=0; i<numberPlanets; i++)
    {
        std::ostringstream ss;
        ss << i;
        std::string name = ss.str();

        // Use randomised initiating values for new planet
        double mass   = 1.0; //1.0 + rand() * (size - 1.0) / RAND_MAX;
        double radius = 10.0; //1.0 + rand() * (size - 1.0) / RAND_MAX;

        double x  = -1*size + rand() * (2*size) / RAND_MAX;
        double y  = -1*size + rand() * (2*size) / RAND_MAX;
        double z  = -1*size + rand() * (2*size) / RAND_MAX;

        // Create planet and add to solarsystem
        cObject aPlanet = cObject(name, mass, radius, x, y, z);
        this->AddObject(aPlanet);
    }
}

void cSystem::CreateDustCloud(double size, double timeStep)
{
    m_timeStep = timeStep;

    int numberPlanets = size*size*size;

    srand(time(NULL));
    for(int i=0; i<numberPlanets; i++)
    {
        std::ostringstream ss;
        ss << "Particle " << i;
        std::string name = ss.str();

        // Set mas and radius
        double mass   = size*10; //10*size/numberPlanets;
        double radius = size/100; //size/numberPlanets;

        // Use randomised initiating values for new particle
        double x = -1*size + rand() * (2*size) / RAND_MAX;
        double y = -1*size + rand() * (2*size) / RAND_MAX;
        double z = -1*size + rand() * (2*size) / RAND_MAX;

        // Determine distance to z-axis
        double dist = sqrt(x*x+y*y);

        // Calculate initial velocities
        double vx = 0.0; //-y/dist*0.001;
        double vy = 0.0; //+x/dist*0.001;
        double vz = 0.0;

        // Create planet and add to solarsystem
        cObject aPlanet= cObject(name, mass, radius, x, y, z, vx, vy, vz);
        this->AddObject(aPlanet);
    }
}

void cSystem::PrintSystem(void)
{
    std::cout << "------------------------------------------------------" << std::endl;

    std::vector<cObject>::iterator objectIterator;

    for(objectIterator = m_objects.begin(); objectIterator != m_objects.end(); objectIterator++)
    {
        objectIterator->PrintObject();
    }

    std::cout << "------------------------------------------------------" << std::endl;
}

void cSystem::PrintProgress(void)
{
    if(m_objects.size()>1)
    {

        std::vector<cObject>::iterator objectIterator1 = m_objects.begin();
        std::vector<cObject>::iterator objectIterator2 = m_objects.end();

        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "Smallest Distance:    " << m_smallestDistance << std::endl;
        std::cout << "Largest Displacement: " << m_largestDisplacement << std::endl << std::endl;

        for(objectIterator1 = m_objects.begin(); objectIterator1 < m_objects.end(); objectIterator1++)
        {
            // Compare with second planet
            if(objectIterator1 == m_objects.begin())
            {
                objectIterator2 = m_objects.end()-1;
            }
            else
            {
                objectIterator2 = m_objects.begin();
            }
            double dx = objectIterator1->GetX() - objectIterator2->GetX();
            double dy = objectIterator1->GetY() - objectIterator2->GetY();
            double dz = objectIterator1->GetZ() - objectIterator2->GetZ();
            double d  = sqrt(dx*dx + dy*dy + dz*dz);

            std::vector<cObject>::iterator closestObject = objectIterator2;
            double sd = d;

            // Compare with remaining planets
            for(objectIterator2 = m_objects.begin(); objectIterator2 < m_objects.end(); objectIterator2++)
            {
                if(objectIterator2 != objectIterator1)
                {
                    dx = objectIterator1->GetX() - objectIterator2->GetX();
                    dy = objectIterator1->GetY() - objectIterator2->GetY();
                    dz = objectIterator1->GetZ() - objectIterator2->GetZ();
                    d  = sqrt(dx*dx + dy*dy + dz*dz);

                    if(d < sd)
                    {
                        sd=d;
                        closestObject = objectIterator2;
                    }
                }
            }

            std::cout << "Object " << objectIterator1->GetName() << " closest to object " << closestObject->GetName() << " (Distance = " << sd << ")" << std::endl;
        }

        std::cout << "------------------------------------------------------" << std::endl;
    }
}

int cSystem::CalculateField(void)
{
    this->ResetForces();
    this->CalculateGravitationalForces();
//    this->CalculateDragForces();
    this->UpdateMotions(m_timeMultiplier*m_timeStep);
    this->DetectCollisions();
    this->ExportObjectMotion();

    return m_objects.size();
}

int cSystem::CalculateField(double timeStep)
{
    this->ResetForces();
    this->CalculateGravitationalForces();
//    this->CalculateDragForces();
    this->UpdateMotions(timeStep);
    this->DetectCollisions();
    this->ExportObjectMotion();

    return m_objects.size();
}

void cSystem::ResetForces(void)
{
    std::vector<cObject>::iterator objectIterator1;

    // Initialise all Gravitational forces to zero
    for(objectIterator1 = m_objects.begin(); objectIterator1 != m_objects.end(); objectIterator1++)
    {
        objectIterator1->SetFx(0);
        objectIterator1->SetFy(0);
        objectIterator1->SetFz(0);
    }
}

void cSystem::CalculateGravitationalForces(void)
{
    std::vector<cObject>::iterator objectIterator1;
    std::vector<cObject>::iterator objectIterator2;

    // Calculate Gravitational Forces
    for(objectIterator1 = m_objects.begin(); objectIterator1 != m_objects.end(); objectIterator1++)
    {
        for(objectIterator2 = m_objects.begin(); objectIterator2 != objectIterator1; objectIterator2++)
        {
            // Calculate distances
            double dx = objectIterator1->GetX() - objectIterator2->GetX();
            double dy = objectIterator1->GetY() - objectIterator2->GetY();
            double dz = objectIterator1->GetZ() - objectIterator2->GetZ();
            double d  = sqrt(dx*dx + dy*dy + dz*dz);

            // Calculate Gravitational Forces
            double F  = GRAV_CONST * (objectIterator1->GetMass() * objectIterator2->GetMass()) / (d*d);
            double Fx = F*dx/d;
            double Fy = F*dy/d;
            double Fz = F*dz/d;

            objectIterator1->SetFx(objectIterator1->GetFx() - Fx);
            objectIterator1->SetFy(objectIterator1->GetFy() - Fy);
            objectIterator1->SetFz(objectIterator1->GetFz() - Fz);
        }

        for(objectIterator2 = objectIterator1+1; objectIterator2 != m_objects.end(); objectIterator2++)
        {
            // Calculate distances
            double dx = objectIterator1->GetX() - objectIterator2->GetX();
            double dy = objectIterator1->GetY() - objectIterator2->GetY();
            double dz = objectIterator1->GetZ() - objectIterator2->GetZ();
            double d  = sqrt(dx*dx + dy*dy + dz*dz);

            // Calculate Gravitational Forces
            double F  = GRAV_CONST * (objectIterator1->GetMass() * objectIterator2->GetMass()) / (d*d);
            double Fx = F*dx/d;
            double Fy = F*dy/d;
            double Fz = F*dz/d;

            objectIterator1->SetFx(objectIterator1->GetFx() - Fx);
            objectIterator1->SetFy(objectIterator1->GetFy() - Fy);
            objectIterator1->SetFz(objectIterator1->GetFz() - Fz);
        }

//        std::cout << "(Name, Fx, Fy, Fz) = (" << objectIterator1->GetName() << ", " << objectIterator1->GetFx() << ", " << objectIterator1->GetFy() << ", " << objectIterator1->GetFz() << ")" << std::endl;
    }
}

void cSystem::CalculateDragForces(void)
{
    std::vector<cObject>::iterator objectIterator1;

    // Calculate Gravitational Forces
    for(objectIterator1 = m_objects.begin(); objectIterator1 != m_objects.end(); objectIterator1++)
    {
        // Fd = 0.5*rho*v^2*Cd*A
        double vx = objectIterator1->GetVx();
        double vy = objectIterator1->GetVy();
        double vz = objectIterator1->GetVz();

        double Fdx = 0.5 * RHO_AIR * vx*vx * CD_SPHERE * objectIterator1->GetReferenceArea() * vx/fabs(vx);
        double Fdy = 0.5 * RHO_AIR * vy*vy * CD_SPHERE * objectIterator1->GetReferenceArea() * vy/fabs(vy);
        double Fdz = 0.5 * RHO_AIR * vz*vz * CD_SPHERE * objectIterator1->GetReferenceArea() * vz/fabs(vz);

        double Fx = objectIterator1->GetFx();
        double Fy = objectIterator1->GetFy();
        double Fz = objectIterator1->GetFz();

        objectIterator1->SetFx(Fx - Fdx);
        objectIterator1->SetFy(Fy - Fdy);
        objectIterator1->SetFz(Fz - Fdz);
    }
}

void cSystem::UpdateMotions(double timeStep)
{
    std::vector<cObject>::iterator objectIterator;

    for(objectIterator = m_objects.begin(); objectIterator != m_objects.end(); objectIterator++)
    {
        objectIterator->UpdateMotion(timeStep);
    }
}

void cSystem::DetectCollisions(void)
{
    double sd = -1.0; // Smallest Distance
    double ld = -1.0; // Largest Displacement

    std::vector<cObject>::iterator objectIterator1;
    std::vector<cObject>::iterator objectIterator2;

    // Calculate distances between planets
    for(objectIterator1 = m_objects.begin(); objectIterator1 < m_objects.end()-1; objectIterator1++)
    {
        // Store planet with largest displacement
        if(objectIterator1->GetDisplacement()>ld) ld=objectIterator1->GetDisplacement();

        if(m_objects.size()>1)
        {
            // Calculate distance between current planet with other planets in the solar system
            for(objectIterator2 = objectIterator1+1; objectIterator2 < m_objects.end(); objectIterator2++)
            {
                // Calculate distance
                double dx = objectIterator1->GetX() - objectIterator2->GetX();
                double dy = objectIterator1->GetY() - objectIterator2->GetY();
                double dz = objectIterator1->GetZ() - objectIterator2->GetZ();
                double d  = sqrt(dx*dx + dy*dy + dz*dz);

                // Store smallest distance
                if(sd<0 || d<sd) sd=d;

                // Detect any collissions
                if(d<(objectIterator1->GetRadius()+objectIterator2->GetRadius()))
                {
                    std::cout << "*** COLLOSION BETWEEN OBJECT " << objectIterator1->GetName() << " AND OBJECT " << objectIterator2->GetName() << " DETECTED ***" << std::endl;

//                    MergeObjects(objectIterator1, objectIterator2);
                    ElasticCollision(objectIterator1, objectIterator2);

                }
            }
        }
    }

//    if(sd<10*ld)
//    {
//        // Planets close to collission; slow down time
//        m_timeMultiplier = m_timeMultiplier*0.1;
//        std::cout << "*** Decreasing time step. TS = " << m_timeMultiplier*m_timeStep << " seconds." << std::endl;
//    }
//
//    if(sd>20*ld && m_timeMultiplier<1)
//    {
//        // Planet distances large; speed up time
//        m_timeMultiplier = m_timeMultiplier*1.1;
//        std::cout << "*** Increasing time step. TS = " << m_timeMultiplier*m_timeStep << " seconds." << std::endl;
//    }

    m_smallestDistance    = sd;
    m_largestDisplacement = ld;
}

void cSystem::MergeObjects(std::vector<cObject>::iterator &objectIterator1, std::vector<cObject>::iterator &objectIterator2)
{
    // Collision, merge masses, assume non-elastic collision
    double newMass    = objectIterator1->GetMass() + objectIterator2->GetMass();
    double newVx      = (objectIterator1->GetMass() * objectIterator1->GetVx() + objectIterator2->GetMass() * objectIterator2->GetVx())/newMass;
    double newVy      = (objectIterator1->GetMass() * objectIterator1->GetVy() + objectIterator2->GetMass() * objectIterator2->GetVy())/newMass;
    double newVz      = (objectIterator1->GetMass() * objectIterator1->GetVz() + objectIterator2->GetMass() * objectIterator2->GetVz())/newMass;
    double newDensity = (objectIterator1->GetMass()/objectIterator1->GetRadius() + objectIterator2->GetMass()/objectIterator2->GetRadius())/2.0;
    double newRadius  = newMass / newDensity;

    // Planet with smallest weight will be absorbed by planet with largest weight
    if(objectIterator1->GetMass() > objectIterator2->GetMass())
    {
        // Redefine planet 1
        objectIterator1->SetMass(newMass);
        objectIterator1->SetRadius(newRadius);
        objectIterator1->SetVx(newVx);
        objectIterator1->SetVy(newVy);
        objectIterator1->SetVz(newVz);

        // Delete planet 2
        unsigned int v_idx = objectIterator2 - m_objects.begin();
        m_deletedobjects.push_back(m_objects.at(v_idx));
        m_objects.erase(objectIterator2);
    }
    else
    {
        // Redefine planet 2
        objectIterator2->SetMass(newMass);
        objectIterator2->SetRadius(newRadius);
        objectIterator2->SetVx(newVx);
        objectIterator2->SetVy(newVy);
        objectIterator2->SetVz(newVz);

        // Delete planet 1
        unsigned int v_idx = objectIterator1 - m_objects.begin();
        m_deletedobjects.push_back(m_objects.at(v_idx));
        m_objects.erase(objectIterator1);
    }

    // Restart from beginning
    objectIterator1 = m_objects.begin();
    objectIterator2 = m_objects.begin();
}

void cSystem::ElasticCollision(std::vector<cObject>::iterator objectIterator1, std::vector<cObject>::iterator objectIterator2)
{
    // Object 1
    double mass1 = objectIterator1->GetMass();
    double vx1   = objectIterator1->GetVx();
    double vy1   = objectIterator1->GetVy();
    double vz1   = objectIterator1->GetVz();

    // Object 2
    double mass2 = objectIterator2->GetMass();
    double vx2   = objectIterator2->GetVx();
    double vy2   = objectIterator2->GetVy();
    double vz2   = objectIterator2->GetVz();

    // Object 1
    objectIterator1->SetVx((vx1*(mass1-mass2) + 2.0*mass2*vx2)/(mass1+mass2));
    objectIterator1->SetVy((vy1*(mass1-mass2) + 2.0*mass2*vy2)/(mass1+mass2));
    objectIterator1->SetVz((vz1*(mass1-mass2) + 2.0*mass2*vz2)/(mass1+mass2));

    // Object 2
    objectIterator2->SetVx((vx2*(mass2-mass1) + 2.0*mass1*vx1)/(mass1+mass2));
    objectIterator2->SetVy((vy2*(mass2-mass1) + 2.0*mass1*vy1)/(mass1+mass2));
    objectIterator2->SetVz((vz2*(mass2-mass1) + 2.0*mass1*vz1)/(mass1+mass2));
}

void cSystem::ExportObjectMotion(void)
{
    if(m_file.is_open())
    {
        static int it = 0;
        it++;

        if(it%100000==0)
        {
            std::vector<cObject>::iterator objectIterator;

            for(objectIterator = m_objects.begin(); objectIterator != m_objects.end(); objectIterator++)
            {
//                m_file << objectIterator->GetName() << "; ";
                m_file << objectIterator->GetX() << "; ";
                m_file << objectIterator->GetY() << "; ";
                m_file << objectIterator->GetZ() << "; ";
                m_file << objectIterator->GetRadius() << "; ";
            }
            m_file << std::endl;
        }
    }
}

double cSystem::GetSystemRadius(void)
{
    std::vector<cObject>::iterator objectIterator;

    double systemRadius = 0.0;

    for(objectIterator = m_objects.begin(); objectIterator != m_objects.end(); objectIterator++)
    {
        double x = objectIterator->GetX();
        double y = objectIterator->GetY();
        double z = objectIterator->GetZ();

        double r = sqrt(x*x + y*y + z*z);
        if(r>systemRadius) systemRadius=r;
    }

    return systemRadius;
}

void cSystem::GetSystemCentre(double *centreX, double *centreY, double *centreZ)
{
    std::vector<cObject>::iterator objectIterator;

    int    numberObjects = 0;
    for(objectIterator = m_objects.begin(); objectIterator != m_objects.end(); objectIterator++)
    {
        numberObjects++;

        *centreX += objectIterator->GetX();
        *centreY += objectIterator->GetY();
        *centreZ += objectIterator->GetZ();
    }

    *centreX /= numberObjects;
    *centreY /= numberObjects;
    *centreZ /= numberObjects;
}
