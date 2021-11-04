#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
//EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "My first Desktop Application", wxPoint(30, 30), wxSize(800, 600))
{
	//m_btn1 = new wxButton(this, 10001, "Click me", wxPoint(10, 10), wxSize(150, 50));
	//m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	//m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
	nField = new int[nFieldWidth * nFieldHeight];
	m_btn = new wxButton * [nFieldHeight * nFieldWidth];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	for (int y = 0; y < nFieldHeight; y++)
	{
		for (int x = 0; x < nFieldWidth; x++)
		{
			m_btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			grid->Add(m_btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			m_btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * nFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	delete[]m_btn;
}
//
void cMain::OnButtonClicked(wxCommandEvent& evt)
{

	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldHeight;

	if (bFirstClick)
	{
		int mines = 30;

		while (mines)
		{
			int rx = rand() % nFieldHeight;
			int ry = rand() % nFieldWidth;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldHeight + rx] = -1;
				mines--;
			}

		}
		bFirstClick = false;
	}

	m_btn[y * nFieldWidth + x]->Enable(false);

	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox("BOOOOMMM - Game Over =)");

		bFirstClick = true;
		for (int y = 0; y < nFieldHeight; y++)
		{
			for (int x = 0; x < nFieldWidth; x++)
			{
				nField[y * nFieldWidth + x] = 0;
				m_btn[y * nFieldWidth + x]->SetLabel("");
				m_btn[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
					{
						mine_count++;
					}
				}
			}
		}
		if (mine_count > 0)
		{
			m_btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}

	evt.Skip();
}
