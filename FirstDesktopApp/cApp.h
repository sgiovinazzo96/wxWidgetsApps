#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();
public:
	virtual bool OnInit();

private:
	cMain* m_frame1 = nullptr;
};

