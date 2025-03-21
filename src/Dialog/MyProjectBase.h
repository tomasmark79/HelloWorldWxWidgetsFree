///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialogMW
///////////////////////////////////////////////////////////////////////////////
class MyDialogMW : public wxDialog
{
private:
protected:
  wxButton *m_button1;
  wxButton *m_button2;
  wxButton *m_button3;
  wxButton *m_buttonExit;

  // Virtual event handlers, override them in your derived class
  virtual void m_button1OnButtonClick (wxCommandEvent &event)
  {
    event.Skip ();
  }
  virtual void m_buttonExitOnButtonClick (wxCommandEvent &event)
  {
    event.Skip ();
  }

public:
  MyDialogMW (wxWindow *parent, wxWindowID id = wxID_ANY,
              const wxString &title = _ ("MyDialogMW"),
              const wxPoint &pos = wxDefaultPosition,
              const wxSize &size = wxDefaultSize,
              long style = wxCAPTION | wxDEFAULT_DIALOG_STYLE);

  ~MyDialogMW ();
};
