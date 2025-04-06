///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CalculatorFrame.h"

///////////////////////////////////////////////////////////////////////////

CalculatorFrame::CalculatorFrame(wxWindow* parent, wxWindowID id,
    const wxString& title, const wxPoint& pos, const wxSize& size, long style) :
    wxFrame(parent, id, title, pos, size, style) {
  this->SetSizeHints(wxDefaultSize, wxDefaultSize);
  this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

  wxBoxSizer* topLevelSizer;
  topLevelSizer = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* textControlSizer;
  textControlSizer = new wxBoxSizer(wxVERTICAL);

  textInput = new wxTextCtrl(
      this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 40), 0);
  textControlSizer->Add(textInput, 0, wxALL | wxEXPAND, 5);

  topLevelSizer->Add(textControlSizer, 0, wxEXPAND, 5);

  wxGridSizer* GridButtonSizer;
  GridButtonSizer = new wxGridSizer(5, 4, 0, 0);

  m_button1 = new wxButton(
      this, wxID_ANY, wxT("7"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button1, 0, wxLEFT | wxEXPAND, 5);

  m_button2 = new wxButton(
      this, wxID_ANY, wxT("8"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button2, 0, wxLEFT | wxEXPAND, 5);

  m_button3 = new wxButton(
      this, wxID_ANY, wxT("9"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button3, 0, wxLEFT | wxEXPAND, 5);

  m_button4 = new wxButton(
      this, wxID_ANY, wxT("x"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button4, 0, wxLEFT | wxEXPAND, 5);

  m_button5 = new wxButton(
      this, wxID_ANY, wxT("4"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button5, 0, wxLEFT | wxEXPAND, 5);

  m_button6 = new wxButton(
      this, wxID_ANY, wxT("5"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button6, 0, wxLEFT | wxEXPAND, 5);

  m_button7 = new wxButton(
      this, wxID_ANY, wxT("6"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button7, 0, wxLEFT | wxEXPAND, 5);

  m_button8 = new wxButton(
      this, wxID_ANY, wxT("+"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button8, 0, wxLEFT | wxEXPAND, 5);

  m_button9 = new wxButton(
      this, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button9, 0, wxLEFT | wxEXPAND, 5);

  m_button10 = new wxButton(
      this, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button10, 0, wxLEFT | wxEXPAND, 5);

  m_button11 = new wxButton(
      this, wxID_ANY, wxT("3"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button11, 0, wxLEFT | wxEXPAND, 5);

  m_button12 = new wxButton(
      this, wxID_ANY, wxT("/"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button12, 0, wxLEFT | wxEXPAND, 5);

  m_button13 = new wxButton(
      this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button13, 0, wxLEFT | wxEXPAND, 5);

  m_button14 = new wxButton(
      this, wxID_ANY, wxT("."), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button14, 0, wxLEFT | wxEXPAND, 5);

  m_button15 = new wxButton(
      this, wxID_ANY, wxT("EXP"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button15, 0, wxLEFT | wxEXPAND, 5);

  m_button16 = new wxButton(
      this, wxID_ANY, wxT("-"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button16, 0, wxLEFT | wxEXPAND, 5);

  m_button17 = new wxButton(
      this, wxID_ANY, wxT("DEL"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button17, 0, wxLEFT | wxEXPAND, 5);

  m_button18 = new wxButton(
      this, wxID_ANY, wxT("AC"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button18, 0, wxLEFT | wxEXPAND, 5);

  m_button19 = new wxButton(
      this, wxID_ANY, wxT("ANS"), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button19, 0, wxLEFT | wxEXPAND, 5);

  m_button20 = new wxButton(
      this, wxID_ANY, wxT("="), wxDefaultPosition, wxSize(65, 35), 0);
  GridButtonSizer->Add(m_button20, 0, wxLEFT | wxEXPAND, 5);

  topLevelSizer->Add(GridButtonSizer, 1, wxEXPAND, 5);

  this->SetSizer(topLevelSizer);
  this->Layout();

  this->Centre(wxBOTH);
}

CalculatorFrame::~CalculatorFrame() { }