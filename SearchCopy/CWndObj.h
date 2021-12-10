#pragma once


// CWndObj

class CWndObj : public CStatic
{
	DECLARE_DYNAMIC(CWndObj)

public:
	CWndObj();
	virtual ~CWndObj();
	CRect   m_rcPosition;
	CWnd* m_pWnd;

	void   Refresh(BOOL bErase = TRUE);

protected:
	DECLARE_MESSAGE_MAP()
};


