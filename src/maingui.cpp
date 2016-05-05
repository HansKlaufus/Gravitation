#include "fileio.h"
#include "function.h"
#include "maingui.h"
#include "system.h"

#include <wx/wx.h>
#include <wx/filename.h>

#include <math.h>
#include <stdlib.h>
#include <vector>

BEGIN_EVENT_TABLE(cMainGui, wxFrame)
    EVT_TIMER(APP_TIMER_ID, cMainGui::OnTimer)
    EVT_AUI_PANE_CLOSE(cMainGui::OnPaneClose)
END_EVENT_TABLE()

cMainGui::cMainGui() : cBaseGui(NULL, wxID_ANY, wxT("Solar System"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE)
{
    // Reset pointers
    m_Grid     = NULL;
    m_GlPane   = NULL;
    m_MathPlot = NULL;
    m_System   = NULL;
    m_time     = 0.0f;

    // Define Mathplot
    m_MathPlot = new mpWindow(this, wxID_ANY, wxDefaultPosition, wxSize(500,500));//wxDefaultSize
	m_mgr.AddPane( m_MathPlot, wxAuiPaneInfo() .Left() .PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).Name(_T("m_MathPlot")));
//    this->InitialiseMathPlot();

    // Define Grid Control
    m_Grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500));//wxDefaultSize
    m_Grid->CreateGrid(0, 0);
    m_Grid->EnableEditing(false);
	m_mgr.AddPane( m_Grid, wxAuiPaneInfo() .Left() .PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).Name(_T("m_Grid")));

    // Define the openGL canvas
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    m_GlPane = new cGlCanvas(this, args);
	m_mgr.AddPane( m_GlPane, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).Floatable( false ).CentrePane() );

    // Align panes and centre window
	m_mgr.Update();
	this->Centre( wxBOTH );

    // Initialise first view
    double r = this->GetSystemRadius();
    m_GlPane->setRadius(2*r);
    m_GlPane->setCameraPosition(0, 1.5*r, 0, 0, 0, 1);

    // Enable / Disable menu items
    int open_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Open"));
    int saveas_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Save as"));
    int close_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Close"));
    int start_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Start"));
    int stop_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Stop"));

    m_MenuBar->Enable(open_id, true);
    m_MenuBar->Enable(saveas_id, false);
    m_MenuBar->Enable(close_id, false);
    m_MenuBar->Enable(start_id, false);
    m_MenuBar->Enable(stop_id, false);

    m_isRunning = false;

    // TEST
//    m_System = new cSystem;
//    m_System->CreateDustCloud(5, 10);
//    wxCommandEvent event;
//    this->OnMenuSaveAs(event);
}

cMainGui::~cMainGui()
{
    //dtor
    if (m_GlPane) delete m_GlPane;
    if (m_Grid) delete m_Grid;
    if (m_MathPlot) delete m_MathPlot;
    if (m_System) delete m_System;
}

void cMainGui::SetStatusText(wxString message, int field = 0)
{
    this->m_StatusBar->SetStatusText(message, field);
}

void cMainGui::Start(void)
{
    if(!m_isRunning) {
        m_isRunning = true;

        // Enable / Disable menu items
        int open_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Open"));
        int saveas_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Save as"));
        int close_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Close"));
        int start_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Start"));
        int stop_id  = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Stop"));

        m_MenuBar->Enable(open_id, false);
        m_MenuBar->Enable(saveas_id, false);
        m_MenuBar->Enable(close_id, false);
        m_MenuBar->Enable(start_id, false);
        m_MenuBar->Enable(stop_id, true);

        // Start timer
        m_Timer.SetOwner(this, APP_TIMER_ID);
        m_Timer.Start(100);

        // Send message
        this->SetStatusText(wxT("Execution started..."));
    }
}

void cMainGui::Stop(void)
{
    if(m_isRunning) {
        // Stop times
        m_Timer.Stop();

        // Enable / Disable menu items
        int open_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Open"));
        int saveas_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Save as"));
        int close_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Close"));
        int start_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Start"));
        int stop_id  = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Stop"));

        m_MenuBar->Enable(open_id, true);
        m_MenuBar->Enable(saveas_id, true);
        m_MenuBar->Enable(close_id, true);
        m_MenuBar->Enable(start_id, true);
        m_MenuBar->Enable(stop_id, false);

        m_isRunning = false;

        // Send message
        this->SetStatusText(wxT("Execution suspended..."));
    }
}

void cMainGui::CloseFile(void)
{
    // Stop execution
    this->Stop();

    // Delete system
    if(m_System)
    {
        m_Grid->DeleteCols(0, m_Grid->GetNumberCols());
        m_Grid->DeleteRows(0, m_Grid->GetNumberRows());

        m_MathPlot->DelAllLayers(true);

        delete m_System;
        m_System = NULL;
    }

    // Reset time
    this->m_time = 0.0f;

    // Enable / Disable menu items
    int open_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Open"));
    int saveas_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Save as"));
    int close_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Close"));
    int start_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Start"));
    int stop_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Stop"));

    m_MenuBar->Enable(open_id, true);
    m_MenuBar->Enable(saveas_id, false);
    m_MenuBar->Enable(close_id, false);
    m_MenuBar->Enable(start_id, false);
    m_MenuBar->Enable(stop_id, false);
}

void cMainGui::OnMenuOpen(wxCommandEvent &event)
{
	wxFileDialog* v_OpenDialog = new wxFileDialog(this, _("Open File"), wxEmptyString, wxEmptyString, _("Configuration XML Files (*.xml)|*.xml|All files (*.*)|*.*"), wxFD_OPEN, wxDefaultPosition);

	if(v_OpenDialog->ShowModal() == wxID_OK)
	{
		wxFileName v_FileName(v_OpenDialog->GetPath());

        this->CloseFile();
		if(m_System)
		{
		    delete m_System;
            m_System = NULL;
		}
        m_System = new cSystem();

        if(v_FileName.GetExt() == _("xml"))
        {
            cFileIo v_FileIO(m_System);
            v_FileIO.XmlReadFile(std::string(v_FileName.GetFullPath().mb_str()));
        }
        else
        {
            std::cout << "ERROR in cMainGUI::OnMenuOpen: file extension not recognised: " << v_FileName.GetExt() << std::endl;
        }

        // Enable / Disable menu items
        int open_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Open"));
        int saveas_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Save as"));
        int close_id = m_MenuBar->FindMenuItem(wxT("File"), wxT("Close"));
        int start_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Start"));
        int stop_id = m_MenuBar->FindMenuItem(wxT("Run"), wxT("Stop"));

        m_MenuBar->Enable(open_id, false);
        m_MenuBar->Enable(saveas_id, true);
        m_MenuBar->Enable(close_id, true);
        m_MenuBar->Enable(start_id, true);
        m_MenuBar->Enable(stop_id, true);

        // Initialise Controls
        this->InitialiseGrid();
        this->InitialiseMathPlot();
        this->InitialiseObjectLayers();

		// Send message
		this->SetTitle(v_OpenDialog->GetFilename());
		this->SetStatusText(_("Ready..."), 2);

        // Set opengl pane
        double v_Radius = this->GetSystemRadius();
        m_GlPane->setRadius(1.5*v_Radius);
        m_GlPane->setCameraPosition(0, 2*v_Radius, 0, 0, 0, 1);
        m_GlPane->redraw();

		std::cout << std::endl;
		std::cout << "------------------------ OPENED NEW FILE ------------------------" << std::endl;
	}
	v_OpenDialog->Destroy();
}

void cMainGui::OnMenuSaveAs(wxCommandEvent &event)
{
	wxFileDialog* v_SaveDialog = new wxFileDialog(this, _("Save File"), wxEmptyString, wxEmptyString, _("Configuration XML Files (*.xml)|*.xml|All files (*.*)|*.*"), wxFD_SAVE, wxDefaultPosition);

	if(v_SaveDialog->ShowModal() == wxID_OK)
	{
		wxFileName v_FileName(v_SaveDialog->GetPath());

		if(m_System)
		{
            if(v_FileName.GetExt() == _("xml"))
            {
                cFileIo v_FileIo(m_System);
                v_FileIo.XmlWriteFile(std::string(v_FileName.GetFullPath().mb_str()));
            }
            else
            {
                std::cout << "ERROR in cMainGUI::OnMenuSaveAs: file extension not recognised: " << v_FileName.GetExt() << std::endl;
            }
		}

		this->SetTitle(v_SaveDialog->GetFilename());
		this->SetStatusText(_("Ready..."), 2);
	}
	v_SaveDialog->Destroy();
}

void cMainGui::OnMenuClose(wxCommandEvent &event)
{
    this->CloseFile();
}

void cMainGui::OnMenuQuit(wxCommandEvent &event)
{
    this->CloseFile();
    this->Close(true);
}

void cMainGui::OnMenuShowBackgroundRaster(wxCommandEvent &event)
{
    int menu_id = m_MenuBar->FindMenuItem(wxT("Settings"), wxT("Show background raster"));

    bool show = !m_GlPane->hasBackgroundRaster();
    m_GlPane->showBackgroundRaster(show);
    m_MenuBar->Check(menu_id, show);

    this->Refresh(false);
}

void cMainGui::OnMenuShowAxisFrame(wxCommandEvent &event)
{
    int menu_id = m_MenuBar->FindMenuItem(wxT("Settings"), wxT("Show axis frame"));

    bool show = !m_GlPane->hasAxisFrame();
    m_GlPane->showAxisFrame(show);
    m_MenuBar->Check(menu_id, show);

    this->Refresh(false);
}

void cMainGui::OnMenuShowScope(wxCommandEvent &event)
{
    int menu_id = m_MenuBar->FindMenuItem(wxT("Settings"), wxT("Show oscilloscope"));

    wxAuiPaneInfo& v_PaneInfo = m_mgr.GetPane(m_MathPlot);
    bool show = !v_PaneInfo.IsShown();
    v_PaneInfo.Show(show);

    m_mgr.Update();
    m_MenuBar->Check(menu_id, show);
}

void cMainGui::OnMenuShowTreeView(wxCommandEvent &event)
{
    int menu_id = m_MenuBar->FindMenuItem(wxT("Settings"), wxT("Show tree view"));

    wxAuiPaneInfo& v_PaneInfo = m_mgr.GetPane(m_Grid);
    bool show = !v_PaneInfo.IsShown();
    v_PaneInfo.Show(show);

    m_mgr.Update();
    m_MenuBar->Check(menu_id, show);
}

void cMainGui::OnMenuTimeMultiplier(wxCommandEvent &event)
{
    // TODO
    cTimeDialog vTimeDialog(this);
    vTimeDialog.Show();
}

void cMainGui::OnMenuStart(wxCommandEvent &event)
{
    this->Start();
}

void cMainGui::OnMenuStop(wxCommandEvent &event)
{
    this->Stop();
}

void cMainGui::OnMenuX(wxCommandEvent &p_Event)
{
    m_GlPane->setCameraPosition(2*this->GetSystemRadius(), 0, 0, 0, 0, 1);
    m_GlPane->setCameraAngle(0, 0, 0);
    m_GlPane->redraw();
}

void cMainGui::OnMenuY(wxCommandEvent &p_Event)
{
    m_GlPane->setCameraPosition(0, 2*this->GetSystemRadius(), 0, 0, 0, 1);
    m_GlPane->setCameraAngle(0, 0, 0);
    m_GlPane->redraw();
}

void cMainGui::OnMenuZ(wxCommandEvent &p_Event)
{
    m_GlPane->setCameraPosition(0, 0, 2*this->GetSystemRadius(), 0, 1, 0);
    m_GlPane->setCameraAngle(0, 0, 0);
    m_GlPane->redraw();
}

void cMainGui::OnPaneClose(wxAuiManagerEvent &p_Event)
{
    int menu_id = -1;
    if(p_Event.pane->name == _T("m_Grid")) {
        menu_id = m_MenuBar->FindMenuItem(wxT("Settings"), wxT("Show tree view"));
    } else if (p_Event.pane->name == _T("m_MathPlot")) {
        menu_id = m_MenuBar->FindMenuItem(wxT("Settings"), wxT("Show oscilloscope"));
    }
    m_MenuBar->Check(menu_id, false);
}

void cMainGui::OnTimer(wxTimerEvent &event)
{
    m_System->CalculateField();
//    m_System->PrintProgress();

    double x, y, z;
    m_System->GetSystemCentre(&x, &y, &z);
    m_GlPane->setCentre(x, y, z);

    int v_NumberObjects = this->GetNumberObjects();
    wxString message = wxString::Format(wxT("Number objects: %d"), v_NumberObjects);
    this->SetStatusText(message,  2);

    // Calclulate new simulated time
    m_time += m_System->GetTimeStep();

    // Display simulated time in status bar
    int v_temp  = m_time;

    int v_yrs = v_temp / (60*60*24*365.25);
    v_temp    -= v_yrs*(60*60*24*365.25);

    int v_days  = v_temp / (60*60*24);
    v_temp      -= v_days*(60*60*24);

    int v_hrs   = v_temp / (60*60);
    v_temp      -= v_hrs*(60*60);

    int v_min   = v_temp / 60;
    v_temp      -= v_min*60;

    int v_sec   = v_temp;

    message = wxString::Format(wxT("Time: %d yrs; %d days; %d hrs; %d min; %d sec"), v_yrs, v_days, v_hrs, v_min, v_sec);
    this->SetStatusText(message);

    this->UpdateGrid();
    this->UpdateMathPlot();
    m_GlPane->redraw();
}

double cMainGui::GetSystemRadius(void)
{
    double radius = 0.0f;

    if(m_System) radius = m_System->GetSystemRadius();

    return radius;
}

int cMainGui::GetNumberObjects(void)
{
    int number_objects = 0;

    if(m_System ) number_objects = m_System->GetNumberObjects();

    return number_objects;
}

void cMainGui::InitialiseGrid(void)
{
    if(m_System)
    {
        m_Grid->InsertRows(0, this->GetNumberObjects());
        m_Grid->InsertCols(0, 8);

        m_Grid->SetColLabelValue(0, wxT("Name"));
        m_Grid->SetColLabelValue(1, wxT("Mass / kg"));
        m_Grid->SetColLabelValue(2, wxT("X / m"));
        m_Grid->SetColLabelValue(3, wxT("Y / m"));
        m_Grid->SetColLabelValue(4, wxT("Z / m"));
        m_Grid->SetColLabelValue(5, wxT("Vx / ms^-1"));
        m_Grid->SetColLabelValue(6, wxT("Vy / ms^-1"));
        m_Grid->SetColLabelValue(7, wxT("Vz / ms^-1"));

        this->UpdateGrid();
        m_Grid->AutoSizeColumns();
        m_Grid->ForceRefresh();
    }
}

void cMainGui::InitialiseMathPlot(void)
{
    // Define axes layers
    mpScaleX *v_ScaleX = new mpScaleX( wxT("time /s"), mpALIGN_BORDER_LEFT);
    mpScaleY *v_ScaleY = new mpScaleY( wxT("V /ms^-1"), mpALIGN_BOTTOM);
    v_ScaleX->SetDrawOutsideMargins(false);
    v_ScaleY->SetDrawOutsideMargins(false);

    // Add layers to plot
    m_MathPlot->AddLayer(v_ScaleX);
    m_MathPlot->AddLayer(v_ScaleY);

    // Define legend layer
    int v_Width = 0;
    int v_Height = 0;
    m_MathPlot->GetClientSize(&v_Width, &v_Height);

    mpInfoLegend *v_Legend = new mpInfoLegend(wxRect(v_Width-20-40,20,40,40), wxTRANSPARENT_BRUSH);
    m_MathPlot->AddLayer(v_Legend);
    v_Legend->SetVisible(true);

    // General properties
    m_MathPlot->SetMargins(10, 10, 20, 60);
    m_MathPlot->EnableDoubleBuffer(true); // Prevents flickering?
}

void cMainGui::UpdateGrid(void)
{
    int v_RowIdx = 0;

    std::vector<cObject>           v_Objects = m_System->GetObjects();
    std::vector<cObject>::iterator v_ObjectIterator;
    for(v_ObjectIterator = v_Objects.begin(); v_ObjectIterator != v_Objects.end(); v_ObjectIterator++)
    {
        wxString    v_ID   = wxString::Format(wxT("%d"), v_ObjectIterator->GetID());
        std::string v_Name = v_ObjectIterator->GetName();
        wxString    v_Mass = wxString::Format(wxT("%+3.2E"), v_ObjectIterator->GetMass());
        wxString    v_X    = wxString::Format(wxT("%+3.2E"), v_ObjectIterator->GetX());
        wxString    v_Y    = wxString::Format(wxT("%+3.2E"), v_ObjectIterator->GetY());
        wxString    v_Z    = wxString::Format(wxT("%+3.2E"), v_ObjectIterator->GetZ());
        wxString    v_Vx   = wxString::Format(wxT("%+3.2E"), v_ObjectIterator->GetVx());
        wxString    v_Vy   = wxString::Format(wxT("%+3.2E"), v_ObjectIterator->GetVy());
        wxString    v_Vz   = wxString::Format(wxT("%+3.2E"), v_ObjectIterator->GetVz());

        m_Grid->SetRowLabelValue(v_RowIdx, v_ID);
        m_Grid->SetCellValue(v_RowIdx, 0, wxString(v_Name.c_str(), wxConvUTF8));
        m_Grid->SetCellValue(v_RowIdx, 1, v_Mass);
        m_Grid->SetCellValue(v_RowIdx, 2, v_X);
        m_Grid->SetCellValue(v_RowIdx, 3, v_Y);
        m_Grid->SetCellValue(v_RowIdx, 4, v_Z);
        m_Grid->SetCellValue(v_RowIdx, 5, v_Vx);
        m_Grid->SetCellValue(v_RowIdx, 6, v_Vy);
        m_Grid->SetCellValue(v_RowIdx, 7, v_Vz);

        v_RowIdx++;
    }

    int v_NumberRows = m_Grid->GetNumberRows();
    if (v_NumberRows > v_RowIdx) m_Grid->DeleteRows(v_RowIdx, v_NumberRows - v_RowIdx);
}

void cMainGui::UpdateMathPlot(void)
{
    static double v_Time;
    v_Time += m_Timer.GetInterval();

    // Update layers
    std::vector<cObject> v_Objects = this->GetObjects();
    std::vector<cObject>::iterator v_ObjectIterator;
    for(v_ObjectIterator = v_Objects.begin(); v_ObjectIterator != v_Objects.end(); v_ObjectIterator++)
    {
        double v_Vx = v_ObjectIterator->GetVx();
        double v_Vy = v_ObjectIterator->GetVy();
        double v_Vz = v_ObjectIterator->GetVz();
        double v_V  = sqrt(v_Vx*v_Vx + v_Vy*v_Vy + v_Vz*v_Vz);

        std::string    v_Name = v_ObjectIterator->GetName();
        cOscopeVector *v_ObjectLayer = (cOscopeVector*) m_MathPlot->GetLayerByName(wxString(v_Name.c_str(), wxConvUTF8));
        if(v_ObjectLayer) v_ObjectLayer->AddSample(v_Time, v_V);
    }

    // Delete layers of objects that are deleteded
    v_Objects = this->GetDeletedObjects();
    for(v_ObjectIterator = v_Objects.begin(); v_ObjectIterator != v_Objects.end(); v_ObjectIterator++)
    {
        std::string    v_Name = v_ObjectIterator->GetName();
        cOscopeVector *v_ObjectLayer = (cOscopeVector*) m_MathPlot->GetLayerByName(wxString(v_Name.c_str(), wxConvUTF8));
//        if(v_ObjectLayer) m_MathPlot->DelLayer(v_ObjectLayer,true, true);
        if(v_ObjectLayer) v_ObjectLayer->SetVisible(false);

    }

//    m_MathPlot->UpdateAll();
    m_MathPlot->Fit();
}

void cMainGui::InitialiseObjectLayers(void)
{
    long int v_ColourIdx = 0;
    long int v_ColourDelta = 255*255*255 / this->GetNumberObjects();

    std::vector<cObject> v_Objects = this->GetObjects();
    std::vector<cObject>::iterator v_ObjectIterator;
    for(v_ObjectIterator = v_Objects.begin(); v_ObjectIterator != v_Objects.end(); v_ObjectIterator++)
    {
        std::string    v_Name = v_ObjectIterator->GetName();
        cOscopeVector *v_ObjectLayer = new cOscopeVector(1000);

        v_ObjectLayer->SetName(wxString(v_Name.c_str(), wxConvUTF8));
        v_ObjectLayer->SetDrawOutsideMargins(false);
        v_ObjectLayer->SetContinuity(true);
        v_ObjectLayer->SetPen( wxPen(wxColour(v_ColourIdx), 1, wxSOLID));

        m_MathPlot->AddLayer(v_ObjectLayer);
        v_ColourIdx += v_ColourDelta;
    }
}
