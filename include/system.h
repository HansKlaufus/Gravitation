#ifndef CSYSTEM_H
#define CSYSTEM_H

#include <fstream>
#include <vector>

#include "object.h"

#define PRECISION 1E-4

#define GRAV_CONST 6.673E-11 //Nm^2kg^-2
#define RHO_AIR 0.0 //1.293  // Kg/m^3 at 0degC and 1 atm
#define CD_SPHERE 0.47 // Sphere

#define EARTH_DISTANCE 1.496E11 // Astronomical Unit, m
#define EARTH_MASS     5.972E24  // Kg

#define SOLARSYSTEM_RADIUS 7.5E15

#define DATAFILE "system.dat"

class cSystem
{
    public:
        cSystem(void);
        cSystem(bool dumpData);
        virtual ~cSystem();

        int                  GetNumberObjects(void) {return m_objects.size(); };
        std::vector<cObject> GetObjects(void) {return m_objects;};
        void                 AddObject(cObject object) {m_objects.push_back(object);};
        cObject              GetObject(int p_Idx) {return m_objects.at(p_Idx);}

        std::vector<cObject> GetDeletedObjects(void) {return m_deletedobjects;};
        int                  GetNumberDeletedObjects(void) {return m_deletedobjects.size(); };

        double               GetSystemRadius(void);
        void                 GetSystemCentre(double*, double*, double*);

        double               GetTimeStep(void) {return m_timeStep;};
        void                 SetTimeStep(double timeStep) {m_timeStep = timeStep;};

        int                  CalculateField(void);
        int                  CalculateField(double timeStep);

        void                 PrintSystem(void);
        void                 PrintProgress(void);

        void                 CreateSolarSystem(double timeStep);
        void                 CreateDustCloud(double size, double timeStep);

    protected:

    private:
        std::vector<cObject> m_objects;
        std::vector<cObject> m_deletedobjects;
        std::fstream         m_file;
        double               m_timeStep;
        double               m_timeMultiplier;
        double               m_largestDisplacement;
        double               m_smallestDistance;

        void Initialise(int numberPlanets, double radius, double timeStep);

        void ResetForces(void);
        void CalculateGravitationalForces(void);
        void CalculateDragForces(void);
        void UpdateMotions(double timeStep);
        void DetectCollisions(void);
        void MergeObjects(std::vector<cObject>::iterator &objectIterator1, std::vector<cObject>::iterator &objectIterator2);
        void ElasticCollision(std::vector<cObject>::iterator objectIterator1, std::vector<cObject>::iterator objectIterator2);

        void ExportObjectMotion(void);
};

#endif // CSYSTEM_H
