#ifndef CFILEIO_H
#define CFILEIO_H

#include "object.h"
#include "system.h"

#include <wx/xml/xml.h>

class cFileIo
{
    public:
        cFileIo();
        cFileIo(cSystem *p_System);
        virtual ~cFileIo();

        void XmlWriteFile(std::string p_FileName);
        void XmlReadFile(std::string p_FileName);

    protected:

    private:
        static unsigned int m_NextID;
        unsigned int        m_ID;

        cSystem            *m_System;

        void XmlWriteObjects(wxXmlNode *p_Parent);
        void XmlReadObjects(wxXmlNode *p_Parent);
};

#endif // CFILEIO_H
