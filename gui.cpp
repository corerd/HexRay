///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menuBar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* menuFileOpen;
	menuFileOpen = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("O&pen...") ) , wxT("Open file"), wxITEM_NORMAL );
	m_menuFile->Append( menuFileOpen );

	wxMenuItem* menuFileExit;
	menuFileExit = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("E&xit") ) + wxT('\t') + wxT("Alt+X"), wxT("Quit this app"), wxITEM_NORMAL );
	m_menuFile->Append( menuFileExit );

	m_menuBar->Append( m_menuFile, wxT("&File") );

	m_menuHelp = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( m_menuHelp, wxID_ANY, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show about dialog"), wxITEM_NORMAL );
	m_menuHelp->Append( menuHelpAbout );

	m_menuBar->Append( m_menuHelp, wxT("&Help") );

	this->SetMenuBar( m_menuBar );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	m_staticText1 = new wxStaticText( m_toolBar1, wxID_ANY, wxT("  Word Size  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_toolBar1->AddControl( m_staticText1 );
	wordSizeCombo = new wxComboBox( m_toolBar1, wxID_ANY, wxT(" 8-bit"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	wordSizeCombo->Append( wxT(" 8-bit") );
	wordSizeCombo->Append( wxT("16-bit") );
	wordSizeCombo->Append( wxT("32-bit") );
	wordSizeCombo->SetSelection( 0 );
	m_toolBar1->AddControl( wordSizeCombo );
	m_toolBar1->Realize();

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	dumpHeadLineCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	dumpHeadLineCtrl->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New") ) );
	dumpHeadLineCtrl->Hide();

	mainSizer->Add( dumpHeadLineCtrl, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );

	dumpTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	dumpTextCtrl->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New") ) );
	dumpTextCtrl->Hide();

	mainSizer->Add( dumpTextCtrl, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );


	this->SetSizer( mainSizer );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnOpenClick ), this, menuFileOpen->GetId());
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ), this, menuFileExit->GetId());
	m_menuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnAboutClick ), this, menuHelpAbout->GetId());
	wordSizeCombo->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::OnWordSizeSelection ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	wordSizeCombo->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::OnWordSizeSelection ), NULL, this );

}
