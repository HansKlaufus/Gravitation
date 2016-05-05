#include "fileio.h"

#include <cstddef>
#include <iostream>
#include <typeinfo>

unsigned int cFileIo::m_NextID = 0;

cFileIo::cFileIo()
{
    m_ID = cFileIo::m_NextID++;

    m_System = NULL;
}

cFileIo::cFileIo(cSystem *p_System)
{
    m_ID = cFileIo::m_NextID++;

    m_System = p_System;
}

cFileIo::~cFileIo()
{
    //dtor
}

void cFileIo::XmlWriteFile(std::string p_FileName)
{
    if(m_System)
    {
        wxXmlDocument *v_XmlDocument = new wxXmlDocument;

        wxXmlNode *v_Root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("SYSTEM"));
        v_XmlDocument->SetRoot(v_Root);

        wxXmlNode *v_Item = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("PROPERTIES"));
        v_Root->AddChild(v_Item);
        v_Item->AddAttribute(wxT("TimeStep"), wxString::Format(wxT("%.3f"), m_System->GetTimeStep()));

        this->XmlWriteObjects(v_Root);

        v_XmlDocument->Save(wxString(p_FileName.c_str(), wxConvUTF8));

        delete v_XmlDocument;
    }
    else
    {
        std::cout << "ERROR in cFileIo::XmlWriteFile: No file loaded." << std::endl;
    }
}

void cFileIo::XmlWriteObjects(wxXmlNode *p_Parent)
{
    unsigned int v_NumberObjects = m_System->GetNumberObjects();
    if(v_NumberObjects>0)
    {
        wxXmlNode *v_Chapter = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("OBJECTS"));
        p_Parent->AddChild(v_Chapter);

        std::vector<cObject> m_Objects = m_System->GetObjects();
        std::vector<cObject>::iterator objectIterator;
        for(objectIterator = m_Objects.begin(); objectIterator != m_Objects.end(); objectIterator++)
        {
            wxXmlNode *v_Item = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("OBJECT"));

            v_Item->AddAttribute(wxT("ID"), wxString::Format(wxT("%d"), objectIterator->GetID()));
            v_Item->AddAttribute(wxT("Name"), wxString(objectIterator->GetName().c_str(), wxConvUTF8));

            v_Item->AddAttribute(wxT("Mass"), wxString::Format(wxT("%.3f"), objectIterator->GetMass()));
            v_Item->AddAttribute(wxT("Radius"), wxString::Format(wxT("%.3f"), objectIterator->GetRadius()));

            v_Item->AddAttribute(wxT("X"), wxString::Format(wxT("%.3f"), objectIterator->GetX()));
            v_Item->AddAttribute(wxT("Y"), wxString::Format(wxT("%.3f"), objectIterator->GetY()));
            v_Item->AddAttribute(wxT("Z"), wxString::Format(wxT("%.3f"), objectIterator->GetZ()));

            v_Item->AddAttribute(wxT("Vx"), wxString::Format(wxT("%.3f"), objectIterator->GetVx()));
            v_Item->AddAttribute(wxT("Vy"), wxString::Format(wxT("%.3f"), objectIterator->GetVy()));
            v_Item->AddAttribute(wxT("Vz"), wxString::Format(wxT("%.3f"), objectIterator->GetVz()));

            v_Chapter->AddChild(v_Item);
        }
    }
}

void cFileIo::XmlReadFile(std::string p_FileName)
{
    if(m_System)
    {
        /*
        ** Read XML file
        */
        wxXmlDocument *v_XmlDocument = new wxXmlDocument;
        v_XmlDocument->Load(wxString(p_FileName.c_str(), wxConvUTF8));

        wxXmlNode *v_Root  = v_XmlDocument->GetRoot();
        wxXmlNode *v_Child = v_Root->GetChildren();

        while(v_Child)
        {
            wxString v_ChildName = v_Child->GetName();
            if(v_ChildName == wxT("PROPERTIES"))
            {
                double v_TimeStep = wxAtof(v_Child->GetAttribute(wxT("TimeStep"), wxT("0")));
                m_System->SetTimeStep(v_TimeStep);
            }
            else if(v_ChildName == wxT("OBJECTS"))
            {
                this->XmlReadObjects(v_Child);
            }
            else
            {
                std::cout << "ERROR in cFileIo::XmlReadFile: unknown child name: " << v_ChildName << std::endl;
            }

            v_Child = v_Child->GetNext();
        }

        delete v_XmlDocument;
    }
    else
    {
        std::cout << "ERROR in cFileIo::XmlReadFile: Object not defined." << std::endl;
    }
}

void cFileIo::XmlReadObjects(wxXmlNode *p_Parent)
{
    wxXmlNode *v_Child = p_Parent->GetChildren();
    while(v_Child)
    {
        if(v_Child->GetName() == wxT("OBJECT"))
        {
            unsigned int v_Idx  = wxAtoi(v_Child->GetAttribute(wxT("ID"), wxT("0")));
            wxString     v_Name = v_Child->GetAttribute(wxT("Name"), wxT("NameLess"));

            double v_Mass      = wxAtof(v_Child->GetAttribute(wxT("Mass"), wxT("0")));
            double v_Radius    = wxAtof(v_Child->GetAttribute(wxT("Radius"), wxT("0")));

            double v_X         = wxAtof(v_Child->GetAttribute(wxT("X"), wxT("0")));
            double v_Y         = wxAtof(v_Child->GetAttribute(wxT("Y"), wxT("0")));
            double v_Z         = wxAtof(v_Child->GetAttribute(wxT("Z"), wxT("0")));

            double v_Vx        = wxAtof(v_Child->GetAttribute(wxT("Vx"), wxT("0")));
            double v_Vy        = wxAtof(v_Child->GetAttribute(wxT("Vy"), wxT("0")));
            double v_Vz        = wxAtof(v_Child->GetAttribute(wxT("Vz"), wxT("0")));

            cObject v_Object = cObject(std::string(v_Name.mb_str()), v_Mass, v_Radius, v_X, v_Y, v_Z, v_Vx, v_Vy, v_Vz);
            m_System->AddObject(v_Object);
        }
        else
        {
            std::cout << "ERROR in cFileIo::XmlReadObjects: unknown child name: " << v_Child->GetName() << std::endl;
        }

        v_Child = v_Child->GetNext();
    }
}
