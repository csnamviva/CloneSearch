#pragma once
//#include "SearchCopyDlg.h"
#include "CDrawVideoClass.h"
// CWindow


class CWindow : public CButton
{
	DECLARE_DYNAMIC(CWindow)

public:
	CWindow();
	virtual ~CWindow();
	//static CDrawVideoClass* m_ddraw;
	//CSearchCopyDlg* m_pOwner;
	static CDrawVideoClass* m_pdraw;;
	
	void SetArea(CRect* rc);
	void DrawImage();
	BOOL IsColorAdjust(void);
	void DrawAdjustImage(HDC hDC, CRect rectArea, int BrightValue, int ContrastValue, int HueValue, LPSTR strText);
	void DrawImageSplit(HDC hDC, LPSTR strText);
	CRect				m_rectPlaySelectArea;

	//CSearchCopyDlg *m_pOwner;

	void OperateImageAll(BOOL bfUpdate);
	void FlushBuffer(void);
	int m_nScreenNo;
	//CSearchCopyDlg m_pOwner;
	BITMAPINFO			m_bmi;

	void GetRGBImage(BOOL bfAlways = FALSE);
	CObList				m_listOperationImage;
	BOOL				m_bPanoramaEndDisplay;
	CRect				m_rectImageArea;
	BOOL				m_bShow;
	BOOL				m_bImageReady;
	CWnd* m_pOwnerWnd;
	LPBYTE				m_pImageYUV;

protected:
	DECLARE_MESSAGE_MAP()
};


