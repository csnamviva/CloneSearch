#pragma once


// CDrawVideoClass

#define MAX_CHANNEL		64

class CDrawVideoClass : public CWnd
{
	DECLARE_DYNAMIC(CDrawVideoClass)
private:

	int						m_chNum;
	CRect					m_chArea[MAX_CHANNEL];
	COLORREF				m_rgbBackground;


public:
	CDrawVideoClass();
	virtual ~CDrawVideoClass();

	void EmptyCanvas();

	//HWND m_hWnd;


protected:
	DECLARE_MESSAGE_MAP()
};


