#pragma once


// CWndObj

class CWndObj : public CStatic
{
	DECLARE_DYNAMIC(CWndObj)

public:
	CWndObj();
	virtual ~CWndObj();

	BOOL m_bPressed;
	CRect   m_rcPosition;
	CRect   m_rcRealPosition;
	CWnd* m_pWnd;
	UINT	m_ID;

	virtual void SetPosition(stPICTURE_FILE* stpicinfo);

	virtual void SetID(CWnd* pWnd, stPICTURE_FILE* stpicinfo);
	void   Refresh(BOOL bErase = TRUE);

	BOOL PtInRect(POINT point);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


