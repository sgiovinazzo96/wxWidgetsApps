#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
public:
	//wxButton* m_btn1 = nullptr;
	//wxTextCtrl* m_txt1 = nullptr;
	//wxListBox* m_list1 = nullptr;
	wxButton** m_btn;
	int* nField = nullptr;
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	bool bFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

