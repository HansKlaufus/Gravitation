///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __BASEGUI_H__
#define __BASEGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/slider.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class cBaseGui
///////////////////////////////////////////////////////////////////////////////
class cBaseGui : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_MenuBar;
		wxMenu* m_MenuFile;
		wxMenu* m_MenuSettings;
		wxMenu* m_MenuCamera;
		wxMenu* m_MenuRun;
		wxStatusBar* m_StatusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnMenuOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuShowBackgroundRaster( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuShowAxisFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuShowTreeView( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuShowScope( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuTimeMultiplier( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuY( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuStop( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		cBaseGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("cBaseGui"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 612,398 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~cBaseGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class cTimeDialog
///////////////////////////////////////////////////////////////////////////////
class cTimeDialog : public wxDialog 
{
	private:
	
	protected:
		wxSlider* m_TimeSlider;
		wxStdDialogButtonSizer* m_ButtonSizer;
		wxButton* m_ButtonSizerOK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOkButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		cTimeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Time multiplier"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~cTimeDialog();
	
};

#endif //__BASEGUI_H__
