//#if !defined(AFX_DRAWVIDEOCLASS_H__E08EB891_AB3F_4BB9_8C24_47067B070D09__INCLUDED_)
//#define AFX_DRAWVIDEOCLASS_H__E08EB891_AB3F_4BB9_8C24_47067B070D09__INCLUDED_
//#endif

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

#include <ddraw.h>

#define MAX_CHANNEL		64

class CDrawVideoClass : public CWnd
{
	//DECLARE_DYNAMIC(CDrawVideoClass)
private:

	int						m_chNum;
	CRect					m_chArea[MAX_CHANNEL];
	COLORREF				m_rgbBackground;


public:
	CDrawVideoClass();
	virtual ~CDrawVideoClass();
	void					DrawRectangle(HDC hDC, int ch, BOOL bCurrent);


	void EmptyCanvas();
	void					DrawOSD(HDC hDC, int ch, LPSTR pInfoTxt);


	BOOL					DrawImage(int ch, LPVOID pImg, int w, int h, int img_type, LPSTR pInfoTxt, BOOL cur_ch);
	LPDIRECTDRAWSURFACE7	m_lpDDS7Secondary[MAX_CHANNEL];
	LPDIRECTDRAWSURFACE7	m_lpDDSBackBuffer;
	LPDIRECTDRAWSURFACE7	m_lpDDS7Primary;
	DDPIXELFORMAT			m_ddpfOverlayFormat;
	LPDIRECTDRAW7			m_lpDD7;
	DDSURFACEDESC2			m_DDSd2;

	void					SetZoom(int ch, BOOL bZoom, LPRECT rcZoom = NULL);
	CPoint					m_iView[MAX_CHANNEL];

	BOOL					m_bZoom[MAX_CHANNEL];			// Zoom
	CRect					m_rcZoom[MAX_CHANNEL];
	//HWND m_hWnd;


	HRESULT					SetImageSize(int ch, int w, int h);


	COLORREF				m_rgbRectCurrent;
	COLORREF				m_rgbRectNormal;
	UINT					m_uiFontSize;
	COLORREF				m_rgbOSD;
	UINT					m_uiDTFormatChannel;
	UINT					m_uiDTFormatTime;
	UINT					m_uiDTFormatSpeed;

protected:
	//DECLARE_MESSAGE_MAP()
};


