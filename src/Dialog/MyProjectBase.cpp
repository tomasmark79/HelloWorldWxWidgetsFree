///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyProjectBase.h"

///////////////////////////////////////////////////////////////////////////

MyDialogMW::MyDialogMW (wxWindow *parent, wxWindowID id, const wxString &title,
                        const wxPoint &pos, const wxSize &size, long style)
  : wxDialog (parent, id, title, pos, size, style)
{
  this->SetSizeHints (wxDefaultSize, wxDefaultSize);

  wxGridSizer *gSizer1;
  gSizer1 = new wxGridSizer (0, 2, 0, 0);

  m_button1 = new wxButton (this, wxID_ANY, _ ("Basic"), wxDefaultPosition,
                            wxDefaultSize, 0);
  gSizer1->Add (m_button1, 0, wxALL, 5);

  m_button2 = new wxButton (this, wxID_ANY, _ ("DotName"), wxDefaultPosition,
                            wxDefaultSize, 0);
  gSizer1->Add (m_button2, 0, wxALL, 5);

  m_button3 = new wxButton (this, wxID_ANY, _ ("Template"), wxDefaultPosition,
                            wxDefaultSize, 0);
  gSizer1->Add (m_button3, 0, wxALL, 5);

  m_buttonExit = new wxButton (this, wxID_ANY, _ ("SeeYou"),
                               wxDefaultPosition, wxDefaultSize, 0);
  gSizer1->Add (m_buttonExit, 0, wxALL, 5);

  this->SetSizer (gSizer1);
  this->Layout ();
  gSizer1->Fit (this);

  this->Centre (wxBOTH);

  // Connect Events
  m_button1->Connect (
    wxEVT_COMMAND_BUTTON_CLICKED,
    wxCommandEventHandler (MyDialogMW::m_button1OnButtonClick), NULL, this);
  m_buttonExit->Connect (
    wxEVT_COMMAND_BUTTON_CLICKED,
    wxCommandEventHandler (MyDialogMW::m_buttonExitOnButtonClick), NULL, this);
}

MyDialogMW::~MyDialogMW () {}
