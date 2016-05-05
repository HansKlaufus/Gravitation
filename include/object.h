#ifndef CBODY_H
#define CBODY_H

#include <string>

#define PI 3.14159

class cObject
{
    public:
        cObject(std::string name, double mass, double radius, double x, double y, double z);
        cObject(std::string name, double mass, double radius, double x, double y, double z, double vx, double vy, double vz);
        virtual ~cObject();

        unsigned int GetID() { return m_ID; };

        std::string GetName() { return m_Name; }
        void        SetName(std::string val) {m_Name = val; }

        double GetMass() { return m_Mass; }
        void   SetMass(double val) { m_Mass = val; }

        double GetRadius() {return m_Radius; }
        void   SetRadius(double val) { m_Radius = val; }

        double GetX() { return m_X; }
        void   SetX(double val) { m_X = val; }
        double GetY() { return m_Y; }
        void   SetY(double val) { m_Y = val; }
        double GetZ() { return m_Z; }
        void   SetZ(double val) { m_Z = val; }

        double GetVx() { return m_Vx; }
        void   SetVx(double val) { m_Vx = val; }
        double GetVy() { return m_Vy; }
        void   SetVy(double val) { m_Vy = val; }
        double GetVz() { return m_Vz; }
        void   SetVz(double val) { m_Vz = val; }

        double GetAx() { return m_Ax; }
        void   SetAx(double val) { m_Ax = val; }
        double GetAy() { return m_Ay; }
        void   SetAy(double val) { m_Ay = val; }
        double GetAz() { return m_Az; }
        void   SetAz(double val) { m_Az = val; }

        double GetFx() { return m_Fx; }
        void   SetFx(double val) { m_Fx = val; }
        double GetFy() { return m_Fy; }
        void   SetFy(double val) { m_Fy = val; }
        double GetFz() { return m_Fz; }
        void   SetFz(double val) { m_Fz = val; }

        double GetDisplacement()  { return m_Displacement; }
        double GetReferenceArea() { return PI*m_Radius*m_Radius; }

        void  PrintObject(void);
        void  UpdateMotion(double seconds);

    protected:

    private:
        static unsigned int m_NextID;
        unsigned int        m_ID;

        std::string m_Name;

        double m_Mass;
        double m_Radius;
        double m_Displacement;

        double m_X;
        double m_Y;
        double m_Z;

        double m_Vx;
        double m_Vy;
        double m_Vz;

        double m_Ax;
        double m_Ay;
        double m_Az;

        double m_Fx;
        double m_Fy;
        double m_Fz;
};

#endif // CBODY_H
