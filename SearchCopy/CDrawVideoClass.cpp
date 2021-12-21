// CDrawVideoClass.cpp: 구현 파일
//

#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include "SearchCopy.h"
#include "CDrawVideoClass.h"


// CDrawVideoClass

//IMPLEMENT_DYNAMIC(CDrawVideoClass, CWnd)

CDrawVideoClass::CDrawVideoClass()
{

}

CDrawVideoClass::~CDrawVideoClass()
{
}


//BEGIN_MESSAGE_MAP(CDrawVideoClass, CWnd)
//END_MESSAGE_MAP()


void CDrawVideoClass::EmptyCanvas()
{
	//if (!m_hWnd) return;

	for (int i = 0; i < m_chNum; i++) {
		m_chArea[i].SetRectEmpty();
	}

	CDC* pdc = GetDC();
	RECT rt;
	GetClientRect(&rt);
	pdc->FillSolidRect(&rt, m_rgbBackground);
	ReleaseDC(pdc);
}


void CDrawVideoClass::SetZoom(int ch, BOOL bZoom, LPRECT rcZoom)
{
	m_bZoom[ch] = bZoom;
	if (rcZoom)
		m_rcZoom[ch].SetRect(rcZoom->left, rcZoom->top, rcZoom->right, rcZoom->bottom);
}

// CDrawVideoClass 메시지 처리기


BOOL CDrawVideoClass::DrawImage(int ch, LPVOID pImg, int w, int h, int img_type, LPSTR pInfoTxt, BOOL bCurrent)
{
	if (m_chArea[ch].left == 0 && m_chArea[ch].right == 0)
		return FALSE;

	// source area
	CRect rt;
	if (m_bZoom[ch]) rt = m_rcZoom[ch];
	else rt.SetRect(0, 0, w, h);

	// use ddraw
	if (img_type == 0) // YUV422
	{
		if (m_lpDDS7Secondary[ch] == NULL) {
			return FALSE;
		}

		/*if (m_lpDDS7Secondary[ch]->Lock(NULL, &m_DDSd2, DDLOCK_WAIT, NULL) == DDERR_SURFACELOST)
		{
			if (m_lpDDS7Secondary[ch]->Restore() != DD_OK) {
				return FALSE;
			}
			if (m_lpDDS7Secondary[ch]->Lock(NULL, &m_DDSd2, DDLOCK_WAIT, NULL) != DD_OK) {
				return FALSE;
			}
		}*/

		//LPBYTE pSurface = (LPBYTE)m_DDSd2.lpSurface;

		//LPBYTE p = (LPBYTE)pImg;
		//for (int i = 0; i < h; i++)
		//{
		//	memcpy(pSurface, p, (w << 1)); // *2
		//	pSurface += m_DDSd2.lPitch;
		//	p += (w << 1); // *2
		//}

		m_lpDDS7Secondary[ch]->Unlock(NULL);

		HRESULT hr = m_lpDDSBackBuffer->Blt(&m_chArea[ch], m_lpDDS7Secondary[ch], &rt, DDBLT_ASYNC | DDBLT_WAIT, NULL);
	}
	// use dib
	else if (img_type == 1) // RGB24
	{
		BITMAPINFO bmi = { 0, };
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = -h;
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biCompression = 0;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biSizeImage = w * h * 3;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biClrImportant = 0;
		bmi.bmiHeader.biClrUsed = 0;

		if (m_bZoom[ch])
		{
			rt.bottom = h - m_rcZoom[ch].top;
			rt.top = rt.bottom - m_rcZoom[ch].Height();
		}

		// dc
		HDC hDC;
		m_lpDDSBackBuffer->GetDC(&hDC);
		::SetStretchBltMode(hDC, HALFTONE);
		::StretchDIBits(hDC, m_chArea[ch].left, m_chArea[ch].top, m_chArea[ch].Width(), m_chArea[ch].Height(),
			rt.left, rt.bottom - rt.Height(), rt.Width(), rt.Height(),
			(LPBYTE)pImg, &bmi, DIB_RGB_COLORS, SRCCOPY);
		m_lpDDSBackBuffer->ReleaseDC(hDC);
	}
	else if (img_type == 10) // CBitmap*
	{
		// dc
		HDC hDC;
		m_lpDDSBackBuffer->GetDC(&hDC);
		::SetStretchBltMode(hDC, HALFTONE);

		CDC		dcImage;
		dcImage.CreateCompatibleDC(CDC::FromHandle(hDC));
		CBitmap* pOldBitmap = dcImage.SelectObject((CBitmap*)pImg);

		::StretchBlt(hDC, m_chArea[ch].left, m_chArea[ch].top, m_chArea[ch].Width(), m_chArea[ch].Height(),
			dcImage.m_hDC, rt.left, rt.top, rt.Width(), rt.Height(), SRCCOPY);

		dcImage.SelectObject(pOldBitmap);
		dcImage.DeleteDC();

		m_lpDDSBackBuffer->ReleaseDC(hDC);

		CString tmpInfo = pInfoTxt;
		int idx = tmpInfo.Find(0x1f, 0);
		if (idx >= 0)															// 20130215
			sprintf(pInfoTxt, "%s\x1f%s", tmpInfo.Left(idx), "00:00:00");
	}
	// error
	else {
		return FALSE;
	}

	// description and rectangle
	HDC hDC;
	m_lpDDSBackBuffer->GetDC(&hDC);

	DrawOSD(hDC, ch, pInfoTxt);
	DrawRectangle(hDC, ch, bCurrent);

	m_lpDDSBackBuffer->ReleaseDC(hDC);

	// draw onto primary screen
	CRect rtw = m_chArea[ch];
	GetParent()->ClientToScreen(rtw);
	if (m_lpDDS7Primary->Blt(&rtw, m_lpDDSBackBuffer, &m_chArea[ch], DDBLT_ASYNC | DDBLT_WAIT, NULL) == DDERR_SURFACELOST)
	{
		if (m_lpDDS7Primary->Restore() != DD_OK)
			return FALSE;

		if (m_lpDDS7Primary->Blt(&rtw, m_lpDDSBackBuffer, &m_chArea[ch], DDBLT_ASYNC | DDBLT_DONOTWAIT, NULL) != DD_OK)
			return FALSE;
	}

	return TRUE;
}


void CDrawVideoClass::DrawOSD(HDC hDC, int ch, LPSTR pInfoTxt)
{
	// 20100331 pInfoTxt 가 두개의 정보를 가지도록 변경
	// cam_desc|date_time
	if (pInfoTxt)
	{
		//inserted--------------------------------------------------
		CString		strInfoTxt = pInfoTxt;
		CString		cam_desc;
		CString		date_time;
		CString		play_speed;
		int			sp;

		sp = strInfoTxt.Find("\x1f", 0);
		if (sp < 0)
		{
			cam_desc = strInfoTxt;
			date_time = _T("");
			play_speed = _T("");
		}
		else
		{
			cam_desc = strInfoTxt.Left(sp);

			strInfoTxt = strInfoTxt.Right(strInfoTxt.GetLength() - (sp + 1));
			sp = strInfoTxt.Find("\x1f", 0);
			if (sp < 0)
			{
				date_time = strInfoTxt;
				play_speed = _T("");
			}
			else
			{
				date_time = strInfoTxt.Left(sp);
				play_speed = strInfoTxt.Right(strInfoTxt.GetLength() - sp - 1);
			}
		}
		//--------------------------------------------------

			////////////////////////////////////
			// 20130215
		HFONT	oldFont;
		CFont	font;
		font.CreateFont(m_uiFontSize, //font height
			0, //fon weight
			0, // 이전 글자와 다음 글자간 폰트 출력 각도 
			0, // font 회전 900 -> 90 2700 -> 270
			FW_BOLD, // 글자 굵기 FW_NORMAL,FW_BOLD
			FALSE, // italic
			FALSE, // underline
			FALSE, // 글자 중단에 줄이 감
			DEFAULT_CHARSET, // font 글자 setting : ANSI_CHARSET,SYMBOL_CHARSET
			OUT_DEFAULT_PRECIS, // 글자 출력 정밀도 
			CLIP_DEFAULT_PRECIS, // 글자 출력 정밀도 
			DEFAULT_QUALITY,// clip 출력 정밀도 
			DEFAULT_PITCH,
			"Microsoft Sans Serif"); // image kind 

		oldFont = (HFONT)SelectObject(hDC, HFONT(font));
		////////////////////////////////////

		::SetBkMode(hDC, TRANSPARENT);
		::SetTextColor(hDC, m_rgbOSD);

		CRect	rt;
		if (cam_desc.GetLength() > 0)
		{
			//			rt.left = m_chArea[ch].left + 5;
			//			rt.top = m_chArea[ch].top + 5;
			//			rt.right = m_chArea[ch].right - 5;		// rt.right = rt.left + 20; // 20 pixel이 아니라 전체라인으로 변경 20100331
			//			rt.bottom = rt.top + 20;
			rt.left = m_chArea[ch].left + 5;
			rt.top = m_chArea[ch].top + 5;
			rt.right = m_chArea[ch].right - 5;
			rt.bottom = m_chArea[ch].bottom - 5;

			DrawTextEx(hDC, cam_desc.GetBuffer(0), cam_desc.GetLength(), rt, m_uiDTFormatChannel, NULL);
		}

		if (date_time.GetLength() > 0)
		{
			//			rt.left = m_chArea[ch].left + 50;		// 5
			//			rt.top = m_chArea[ch].bottom - 23;
			//			rt.right = m_chArea[ch].right - 50;		// 5
			//			rt.bottom = m_chArea[ch].bottom - 3;
			rt.left = m_chArea[ch].left + 5;
			rt.top = m_chArea[ch].top + 5;
			rt.right = m_chArea[ch].right - 5;
			rt.bottom = m_chArea[ch].bottom - 5;

			DrawTextEx(hDC, date_time.GetBuffer(0), date_time.GetLength(), rt, m_uiDTFormatTime, NULL);
		}

		if (play_speed.GetLength() > 0)
		{
			//			rt.left = m_chArea[ch].right - 40;		// 5
			//			rt.top = m_chArea[ch].bottom - 23;
			//			rt.right = m_chArea[ch].right - 5;
			//			rt.bottom = m_chArea[ch].bottom - 3;
			rt.left = m_chArea[ch].left + 5;
			rt.top = m_chArea[ch].top + 5;
			rt.right = m_chArea[ch].right - 5;
			rt.bottom = m_chArea[ch].bottom - 5;

			DrawTextEx(hDC, play_speed.GetBuffer(0), play_speed.GetLength(), rt, m_uiDTFormatSpeed, NULL);
		}

		////////////////////////////////////
		// 20130215
		SelectObject(hDC, oldFont);
		font.DeleteObject();
		////////////////////////////////////
	}
}


void CDrawVideoClass::DrawRectangle(HDC hDC, int ch, BOOL bCurrent)
{
	CPen RedPen;
	if (bCurrent) {
		RedPen.CreatePen(PS_SOLID, 1, m_rgbRectCurrent);
	}
	else {
		RedPen.CreatePen(PS_SOLID, 1, m_rgbRectNormal);
	}
	CDC* pdc = CDC::FromHandle(hDC);
	CBrush* pOldBr = (CBrush*)pdc->SelectStockObject(NULL_BRUSH);
	CPen* pOldPen = (CPen*)pdc->SelectObject(&RedPen);

	pdc->Rectangle(&m_chArea[ch]);

	pdc->SelectObject(pOldPen);
	pdc->SelectObject(pOldBr);

	RedPen.DeleteObject();
}


HRESULT CDrawVideoClass::SetImageSize(int ch, int w, int h)
{
	if (w == m_iView[ch].x && h == m_iView[ch].y)
		return DD_OK;

	if (m_lpDDS7Secondary[ch] != NULL)
	{
		if (m_lpDDS7Secondary[ch]->Release() == DD_OK)
			m_lpDDS7Secondary[ch] = NULL;
	}

	m_iView[ch].x = w;
	m_iView[ch].y = h;

	memset(&m_DDSd2, 0, sizeof(m_DDSd2));
	m_DDSd2.dwSize = sizeof(m_DDSd2);
	m_DDSd2.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
	m_DDSd2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
	memcpy(&m_DDSd2.ddpfPixelFormat, &m_ddpfOverlayFormat, sizeof(m_ddpfOverlayFormat));

	m_DDSd2.dwWidth = w;
	m_DDSd2.dwHeight = h;

	return m_lpDD7->CreateSurface(&m_DDSd2, &m_lpDDS7Secondary[ch], NULL);
}
