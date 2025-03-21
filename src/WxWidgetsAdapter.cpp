// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include <WxWidgetsAdapter/WxWidgetsAdapter.hpp>
#include <WxWidgetsAdapter/version.h>
#include <Logger/Logger.hpp>
#include <Utils/Utils.hpp>

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

// wmFormBuilder generated code
#include <Calculator/CalculatorFrame.h>
#include <Dialog/MyProjectBase.h>

// Define a new application type, each program should derive a class from
// wxApp
class MyApp : public wxApp
{
public:
  // override base class virtuals
  // ----------------------------

  // this one is called on application startup and is a good place for the
  // app initialization (doing it here and not in the ctor allows to have an
  // error
  virtual bool OnInit () wxOVERRIDE;
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
// wxBEGIN_EVENT_TABLE(MyFrame, wxFrame) EVT_MENU(Minimal_Quit,
// MyFrame::OnQuit)
//     EVT_MENU(Minimal_About, MyFrame::OnAbout) wxEND_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp
// and not wxApp)
wxIMPLEMENT_APP (MyApp);

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit ()
{
  // call the base class initialization method, currently it only parses a
  // few common command-line options but it could be do more in the future
  if (!wxApp::OnInit ())
    return false;

  // create the main application window
  CalculatorFrame *frame = new CalculatorFrame (nullptr);
  frame->Show (true);

  MyDialogMW *dialog = new MyDialogMW (nullptr);
  dialog->Show (true);

  // success: wxApp::OnRun() will be called which will enter the main message
  // loop and the application will run. If we returned false here, the
  // application would exit immediately.
  return true;
}

namespace library
{

  WxWidgetsAdapter::WxWidgetsAdapter (const std::string &assetsPath)
    : m_assetsPath (assetsPath)
  {
    LOG_INFO ("WxWidgetsAdapter v." + std::string (WXWIDGETSADAPTER_VERSION)
              + " constructed.");
    LOG_DEBUG ("Assets Path: " + this->m_assetsPath);
  }

  WxWidgetsAdapter::~WxWidgetsAdapter ()
  {
    LOG_DEBUG ("WxWidgetsAdapter deconstructed.");
  }

} // namespace library