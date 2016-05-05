#ifndef CMAINGUI_H
#define CMAINGUI_H

#include "glcanvas.h"
#include "object.h"
#include "oscopevector.h"
#include "system.h"

#include "../gui/basegui.h"
#include "../mathplot/mathplot.h"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/timer.h>
#include <wx/treectrl.h>

#include <vector>

#define APP_TIMER_ID 2000
#define APP_PANE_ID 2001

class cMainGui : public cBaseGui
{
    private:
        cGlCanvas     *m_GlPane;
        wxGrid        *m_Grid;
        mpWindow      *m_MathPlot;

        cSystem       *m_System;
        wxTimer        m_Timer;
        bool           m_isRunning;

        double         m_time;

        void Start(void);
        void Stop(void);
        void CloseFile(void);

        void InitialiseGrid(void);
        void InitialiseMathPlot(void);
        void InitialiseObjectLayers(void);

        void UpdateGrid(void);
        void UpdateMathPlot(void);

        void OnTimer( wxTimerEvent &event );
        void OnPaneClose( wxAuiManagerEvent &event );

        void OnMenuOpen(wxCommandEvent &event);
        void OnMenuSaveAs(wxCommandEvent &event);
        void OnMenuClose(wxCommandEvent &event);
        void OnMenuQuit(wxCommandEvent &event);
        void OnMenuShowBackgroundRaster(wxCommandEvent &event);
        void OnMenuShowAxisFrame(wxCommandEvent &event);
		void OnMenuShowTreeView(wxCommandEvent& event);
		void OnMenuShowScope(wxCommandEvent& event);
		void OnMenuTimeMultiplier(wxCommandEvent& event);
        void OnMenuStart(wxCommandEvent &event);
        void OnMenuStop(wxCommandEvent &event);
        void OnMenuX(wxCommandEvent &p_Event);
        void OnMenuY(wxCommandEvent &p_Event);
        void OnMenuZ(wxCommandEvent &p_Event);

    public:
        cMainGui();
        virtual ~cMainGui();

        double               GetSystemRadius(void);
        int                  GetNumberObjects(void);
        std::vector<cObject> GetObjects(void) {return m_System->GetObjects();};
        cObject              GetObject(int p_Idx) {return m_System->GetObject(p_Idx);};
        std::vector<cObject> GetDeletedObjects(void) {return m_System->GetDeletedObjects();};
        void                 SetStatusText(wxString, int);

        DECLARE_EVENT_TABLE()
};

#endif // CMAINGUI_H
