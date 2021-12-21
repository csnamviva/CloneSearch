// CSkinVerticleScrollbar.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "SearchCopyDlg.h"
#include "CSkinVerticleScrollbar.h"


// CSkinVerticleScrollbar

IMPLEMENT_DYNAMIC(CSkinVerticleScrollbar, CWnd)

CSkinVerticleScrollbar::CSkinVerticleScrollbar()
{
}

CSkinVerticleScrollbar::~CSkinVerticleScrollbar()
{
}

void CSkinVerticleScrollbar::Init(void)
{
	stPICTURE_FILE	pic;
	//CSearchCopyDlg m_ParentWnd;

	pic = theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Timebar VScroll", "ScrollBarUp", "VScrollUp.bmp,0,0,0,0,ID_BT_NONE,255"), FALSE);
	m_rectVScrollUp.SetRect(pic.iLeft, pic.iTop, pic.iWidth, pic.iHeight);
	m_bmVScrollUp.Attach(LoadImage(NULL, pic.strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	pic = theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Timebar VScroll", "ScrollBarDown", "VScrollDown.bmp,0,0,0,0,ID_BT_NONE,255"), FALSE);
	m_rectVScrollDown.SetRect(pic.iLeft, pic.iTop, pic.iWidth, pic.iTop + pic.iHeight);
	m_bmVScrollDown.Attach(LoadImage(NULL, pic.strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	pic = theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Timebar VScroll", "ScrollBarThumb", "VScrollThumb.bmp,0,0,0,0,ID_BT_NONE,255"), FALSE);
	m_rectVScrollThumb.SetRect(pic.iLeft, pic.iTop, pic.iWidth, pic.iHeight);
	m_bmVScrollThumb.Attach(LoadImage(NULL, pic.strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	pic = theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Timebar VScroll", "ScrollBarSpan", "VScrollSpan.bmp,0,0,0,0,ID_BT_NONE,255"), FALSE);
	m_rectVScrollSpan.SetRect(pic.iLeft, pic.iTop, pic.iWidth, pic.iHeight);
	m_bmVScrollSpan.Attach(LoadImage(NULL, pic.strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	m_nThumbTop = m_rectVScrollUp.Height();
}


void CSkinVerticleScrollbar::UpdateThumbPosition()
{
	CSearchCopyDlg* pMainWnd = (CSearchCopyDlg*)AfxGetApp()->m_pMainWnd;

	CRect clientRect;
	GetClientRect(&clientRect);

	double nPos = pMainWnd->m_CamGroup - 1;
	double nMax = pMainWnd->m_lMaxGroup - 1;
	double nHeight = clientRect.Height() - m_rectVScrollUp.Height() - m_rectVScrollThumb.Height() - m_rectVScrollDown.Height();
	double nVar = nMax;

	m_dbThumbInterval = nHeight / nVar;

	double nNewdbValue = (m_dbThumbInterval * nPos);
	int nNewValue = (int)nNewdbValue;

	m_nThumbTop = m_rectVScrollUp.Height() + nNewValue;

	LimitThumbPosition();

	Draw();
}

void CSkinVerticleScrollbar::LimitThumbPosition()
{
	CRect	clientRect;
	GetClientRect(&clientRect);

	if (m_nThumbTop + m_rectVScrollThumb.Height() > (clientRect.Height() - m_rectVScrollDown.Height()))
	{
		m_nThumbTop = clientRect.Height() - m_rectVScrollThumb.Height() - m_rectVScrollDown.Height();
	}

	if (m_nThumbTop < (clientRect.top + m_rectVScrollUp.Height()))
	{
		m_nThumbTop = clientRect.top + m_rectVScrollUp.Height();
	}
}


void CSkinVerticleScrollbar::Draw()
{
	//CClientDC	dc(this);
	//CRect		clientRect;
	//GetClientRect(&clientRect);
	//CMemDC		memDC(&dc, &clientRect);
	//memDC.FillSolidRect(&clientRect, RGB(74, 82, 107));
	//CDC			bitmapDC;
	//bitmapDC.CreateCompatibleDC(&dc);
	//
	//CBitmap* pOldBitmap;
	//
	//pOldBitmap = bitmapDC.SelectObject(&m_bmVScrollUp);
	//memDC.StretchBlt(clientRect.left, clientRect.top, clientRect.Width(), m_rectVScrollUp.Height(), &bitmapDC, 0, 0, m_rectVScrollUp.Width(), m_rectVScrollUp.Height(), SRCCOPY);
	//bitmapDC.SelectObject(pOldBitmap);
	//pOldBitmap = NULL;
	//
	////draw the background (span)
	//pOldBitmap = bitmapDC.SelectObject(&m_bmVScrollSpan);
	//memDC.StretchBlt(clientRect.left, clientRect.top + m_rectVScrollUp.Height(), clientRect.Width(), clientRect.Height() - m_rectVScrollUp.Height() - m_rectVScrollDown.Height(), &bitmapDC, 0, 0, m_rectVScrollSpan.Width(), m_rectVScrollSpan.Height(), SRCCOPY);
	//bitmapDC.SelectObject(pOldBitmap);
	//pOldBitmap = NULL;
	//
	////draw the down arrow of the scrollbar
	//pOldBitmap = bitmapDC.SelectObject(&m_bmVScrollDown);
	//memDC.StretchBlt(clientRect.left, clientRect.Height() - m_rectVScrollDown.Height(), clientRect.Width(), m_rectVScrollDown.Height(), &bitmapDC, 0, 0, m_rectVScrollDown.Width(), m_rectVScrollDown.Height(), SRCCOPY);
	//bitmapDC.SelectObject(pOldBitmap);
	//pOldBitmap = NULL;
	//
	////If there is nothing to scroll then don't
	////show the thumb control otherwise show it
	//if (1)
	//{
	//	//draw the thumb control
	//	pOldBitmap = bitmapDC.SelectObject(&m_bmVScrollThumb);
	//	memDC.StretchBlt(clientRect.left, clientRect.top + m_nThumbTop, clientRect.Width(), m_rectVScrollThumb.Height(), &bitmapDC, 0, 0, m_rectVScrollThumb.Width(), m_rectVScrollThumb.Height(), SRCCOPY);
	//	bitmapDC.SelectObject(pOldBitmap);
	//	pOldBitmap = NULL;
	//}
}

BEGIN_MESSAGE_MAP(CSkinVerticleScrollbar, CWnd)
END_MESSAGE_MAP()



// CSkinVerticleScrollbar 메시지 처리기


