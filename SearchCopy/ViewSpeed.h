#pragma once


// ViewSpeed

class ViewSpeed : public CWnd
{
	DECLARE_DYNAMIC(ViewSpeed)

public:
	ViewSpeed();
	virtual ~ViewSpeed();

	void	InitCtrl(COLORREF rgbBack, COLORREF rgbText, CString strFont);

	COLORREF	m_rgbBack;
	COLORREF	m_rgbText;
	CFont		m_textFont;

protected:
	DECLARE_MESSAGE_MAP()
};


