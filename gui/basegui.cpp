///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "basegui.h"

///////////////////////////////////////////////////////////////////////////

cBaseGui::cBaseGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_MenuBar = new wxMenuBar( 0 );
	m_MenuFile = new wxMenu();
	wxMenuItem* m_MenuOpen;
	m_MenuOpen = new wxMenuItem( m_MenuFile, wxID_ANY, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuFile->Append( m_MenuOpen );
	
	wxMenuItem* m_MenuSaveAs;
	m_MenuSaveAs = new wxMenuItem( m_MenuFile, wxID_ANY, wxString( wxT("Save as") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuFile->Append( m_MenuSaveAs );
	
	wxMenuItem* m_MenuClose;
	m_MenuClose = new wxMenuItem( m_MenuFile, wxID_ANY, wxString( wxT("Close") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuFile->Append( m_MenuClose );
	
	m_MenuFile->AppendSeparator();
	
	wxMenuItem* m_MenuQuit;
	m_MenuQuit = new wxMenuItem( m_MenuFile, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuFile->Append( m_MenuQuit );
	
	m_MenuBar->Append( m_MenuFile, wxT("File") ); 
	
	m_MenuSettings = new wxMenu();
	wxMenuItem* m_MenuShowBackgroundRaster;
	m_MenuShowBackgroundRaster = new wxMenuItem( m_MenuSettings, wxID_ANY, wxString( wxT("Show background raster") ) , wxEmptyString, wxITEM_CHECK );
	m_MenuSettings->Append( m_MenuShowBackgroundRaster );
	m_MenuShowBackgroundRaster->Check( true );
	
	wxMenuItem* m_MenuShowAxisFrame;
	m_MenuShowAxisFrame = new wxMenuItem( m_MenuSettings, wxID_ANY, wxString( wxT("Show axis frame") ) , wxEmptyString, wxITEM_CHECK );
	m_MenuSettings->Append( m_MenuShowAxisFrame );
	m_MenuShowAxisFrame->Check( true );
	
	m_MenuSettings->AppendSeparator();
	
	wxMenuItem* m_MenuShowTreeView;
	m_MenuShowTreeView = new wxMenuItem( m_MenuSettings, wxID_ANY, wxString( wxT("Show tree view") ) , wxEmptyString, wxITEM_CHECK );
	m_MenuSettings->Append( m_MenuShowTreeView );
	m_MenuShowTreeView->Check( true );
	
	wxMenuItem* m_MenuShowScope;
	m_MenuShowScope = new wxMenuItem( m_MenuSettings, wxID_ANY, wxString( wxT("Show oscilloscope") ) , wxEmptyString, wxITEM_CHECK );
	m_MenuSettings->Append( m_MenuShowScope );
	m_MenuShowScope->Check( true );
	
	m_MenuSettings->AppendSeparator();
	
	wxMenuItem* m_MenuTimeMultiplier;
	m_MenuTimeMultiplier = new wxMenuItem( m_MenuSettings, wxID_ANY, wxString( wxT("Set time multiplier") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuSettings->Append( m_MenuTimeMultiplier );
	
	m_MenuBar->Append( m_MenuSettings, wxT("Settings") ); 
	
	m_MenuCamera = new wxMenu();
	wxMenuItem* m_MenuX;
	m_MenuX = new wxMenuItem( m_MenuCamera, wxID_ANY, wxString( wxT("Set Camera on X") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuCamera->Append( m_MenuX );
	
	wxMenuItem* m_MenuY;
	m_MenuY = new wxMenuItem( m_MenuCamera, wxID_ANY, wxString( wxT("Set Camera on Y") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuCamera->Append( m_MenuY );
	
	wxMenuItem* m_MenuZ;
	m_MenuZ = new wxMenuItem( m_MenuCamera, wxID_ANY, wxString( wxT("Set Camera on Z") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuCamera->Append( m_MenuZ );
	
	m_MenuBar->Append( m_MenuCamera, wxT("Camera") ); 
	
	m_MenuRun = new wxMenu();
	wxMenuItem* m_MenuStart;
	m_MenuStart = new wxMenuItem( m_MenuRun, wxID_ANY, wxString( wxT("Start") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuRun->Append( m_MenuStart );
	
	wxMenuItem* m_MenuStop;
	m_MenuStop = new wxMenuItem( m_MenuRun, wxID_ANY, wxString( wxT("Stop") ) , wxEmptyString, wxITEM_NORMAL );
	m_MenuRun->Append( m_MenuStop );
	
	m_MenuBar->Append( m_MenuRun, wxT("Run") ); 
	
	this->SetMenuBar( m_MenuBar );
	
	m_StatusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	
	m_mgr.Update();
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_MenuOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuOpen ) );
	this->Connect( m_MenuSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuSaveAs ) );
	this->Connect( m_MenuClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuClose ) );
	this->Connect( m_MenuQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuQuit ) );
	this->Connect( m_MenuShowBackgroundRaster->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowBackgroundRaster ) );
	this->Connect( m_MenuShowAxisFrame->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowAxisFrame ) );
	this->Connect( m_MenuShowTreeView->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowTreeView ) );
	this->Connect( m_MenuShowScope->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowScope ) );
	this->Connect( m_MenuTimeMultiplier->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuTimeMultiplier ) );
	this->Connect( m_MenuX->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuX ) );
	this->Connect( m_MenuY->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuY ) );
	this->Connect( m_MenuZ->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuZ ) );
	this->Connect( m_MenuStart->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuStart ) );
	this->Connect( m_MenuStop->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuStop ) );
}

cBaseGui::~cBaseGui()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuOpen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuSaveAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowBackgroundRaster ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowAxisFrame ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowTreeView ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuShowScope ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuTimeMultiplier ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuX ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuY ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuZ ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuStart ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( cBaseGui::OnMenuStop ) );
	
	m_mgr.UnInit();
	
}

cTimeDialog::cTimeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxStaticBoxSizer* m_Sizer;
	m_Sizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Set time multiplier") ), wxVERTICAL );
	
	m_TimeSlider = new wxSlider( m_Sizer->GetStaticBox(), wxID_ANY, 100, 50, 200, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_SELRANGE|wxSL_VERTICAL );
	m_Sizer->Add( m_TimeSlider, 0, wxALL, 5 );
	
	m_ButtonSizer = new wxStdDialogButtonSizer();
	m_ButtonSizerOK = new wxButton( m_Sizer->GetStaticBox(), wxID_OK );
	m_ButtonSizer->AddButton( m_ButtonSizerOK );
	m_ButtonSizer->Realize();
	
	m_Sizer->Add( m_ButtonSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( m_Sizer );
	this->Layout();
	m_Sizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_ButtonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( cTimeDialog::OnOkButtonClick ), NULL, this );
}

cTimeDialog::~cTimeDialog()
{
	// Disconnect Events
	m_ButtonSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( cTimeDialog::OnOkButtonClick ), NULL, this );
	
}
