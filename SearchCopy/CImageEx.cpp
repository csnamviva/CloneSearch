#include "pch.h"
#include "CImageEx.h"
#include "SearchCopy.h"


stPICTURE_FILE CImageEx::GetPictureInfo(CString strPath, CString strPrefix, BOOL span)
{
	int i = 0, j = 0, istrsize = 0;
	istrsize = strPrefix.GetLength();
	int sp = 0, ep = 0;
	CString prefix[7] = { _T(""),_T(""),_T(""),_T(""),_T(""),_T(""),_T("") };
	char t;
	for (i = 0; i < 6; i++)
	{
		for (j = sp; j < istrsize; j++)
		{
			t = strPrefix.GetAt(j);
			if (t == ',')
			{
				ep = j;
				prefix[i] = strPrefix.Mid(sp, ep - sp);
				sp = ep + 1;
				break;
			}
		}
	}
	prefix[6] = strPrefix.Mid(sp, istrsize + 1 - sp);

	stPICTURE_FILE stPicture;
	stPicture.strFileName.Format("%s\\%s", strPath, prefix[0]);    //요기 해결해야함

	stPicture.iLeft = atoi(prefix[1]);
	stPicture.iTop = atoi(prefix[2]);
	stPicture.iWidth = atoi(prefix[3]);
	stPicture.iHeight = atoi(prefix[4]);

	prefix[0].Empty();
	prefix[1].Empty();
	prefix[2].Empty();
	prefix[3].Empty();
	prefix[4].Empty();
	prefix[5].Empty();
	prefix[6].Empty();
	strPrefix.Empty();
	strPath.Empty();
	return stPicture;
}

CBitmap* CImageEx::GetBitmap(CDC* pdc, LPCTSTR lpszFileName)
{
    HBITMAP hbm;
    PBITMAPFILEHEADER pbmfh;
    PBITMAPINFOHEADER pbmih;
    PBYTE             pBits;
    int fh;
    int bfOffBits;
    int nbytes;

    fh = _lopen(lpszFileName, OF_READ);
    if (fh == -1) return NULL;
    nbytes = GetFileSize((HANDLE)fh, NULL);

    if (!(pbmfh = (PBITMAPFILEHEADER)LocalAlloc(LPTR, sizeof(BITMAPFILEHEADER))))
        return NULL;
    _lread(fh, (LPSTR)pbmfh, sizeof(BITMAPFILEHEADER));
    bfOffBits = pbmfh->bfOffBits;

    if (!(pbmih = (PBITMAPINFOHEADER)LocalAlloc(LPTR, bfOffBits - sizeof(BITMAPFILEHEADER))))
        return NULL;
    _lread(fh, (LPSTR)pbmih, bfOffBits - sizeof(BITMAPFILEHEADER));

    if (!(pBits = (PBYTE)LocalAlloc(LPTR, (nbytes - bfOffBits)))) return NULL;
    _lread(fh, (LPSTR)pBits, (nbytes - bfOffBits));

    hbm = CreateDIBitmap(pdc->m_hDC, pbmih, CBM_INIT,
        pBits, (PBITMAPINFO)pbmih, DIB_RGB_COLORS);


    LocalFree(LocalHandle((LPSTR)pBits));
    LocalFree(LocalHandle((LPSTR)pbmih));
    LocalFree(LocalHandle((LPSTR)pbmfh));
    _lclose(fh);

    return CBitmap::FromHandle(hbm);
}

void CImageEx::MoveSkinButton(CDC* pdc, CBitmap* pBitmap, LPRECT lpRect)
{
    BITMAP bm;
    CDC dcImage;

    if (!pBitmap || !dcImage.CreateCompatibleDC(pdc))
        return;

    pBitmap->GetBitmap(&bm);

    // Paint the image.
    CBitmap* pOldBitmap = dcImage.SelectObject(pBitmap);
    if (lpRect)
    {
        if (lpRect->right < 0 && lpRect->bottom < 0)
        {
            ::StretchBlt(pdc->m_hDC,
                lpRect->left, lpRect->top, bm.bmWidth, bm.bmHeight,
                dcImage.m_hDC,
                0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }
        else
        {
            ::StretchBlt(pdc->m_hDC,
                lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
                dcImage.m_hDC,
                0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }
    }
    else
    {
        ::StretchBlt(pdc->m_hDC,
            0, 0, bm.bmWidth, bm.bmHeight,
            dcImage.m_hDC,
            0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    }

    dcImage.SelectObject(pOldBitmap);

    dcImage.DeleteDC();
}

CRect CImageEx::AnalyzeRect2(CString str, BOOL span)
{
	int irect[4];
	int i, j, istrsize;
	CRect re;
	istrsize = str.GetLength();
	int sp = 0, ep = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = sp; j < istrsize; j++)
		{
			char t = str.GetAt(j);
			if (t == ',')
			{
				ep = j;
				irect[i] = atoi(str.Mid(sp, ep - sp));
				sp = ep + 1;
				break;
			}
		}
	}
	irect[3] = atoi(str.Mid(sp, istrsize + 1 - sp));
	//20100702 GUI 늘이기
	if (span) {
		re.SetRect((int)(irect[0] * theApp.w_ratio), (int)(irect[1] * theApp.h_ratio),
			(int)((irect[0] + irect[2]) * theApp.w_ratio), (int)((irect[1] + irect[3]) * theApp.h_ratio));
	}
	else {
		re.SetRect(irect[0], irect[1], irect[0] + irect[2], irect[1] + irect[3]);
	}
	return re;
}


COLORREF CImageEx::AnalyzeRGB(CString str)
{
	COLORREF rgb;
	int iColorInfo[3];
	int istrsize = str.GetLength();
	int sp = 0, ep = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = sp; j < istrsize; j++)
		{
			char t = str.GetAt(j);
			if (t == ',')
			{
				ep = j;
				iColorInfo[i] = atoi(str.Mid(sp, ep - sp));
				sp = ep + 1;
				break;
			}
		}
	}
	iColorInfo[2] = atoi(str.Mid(sp, istrsize + 1 - sp));

	rgb = RGB(iColorInfo[0], iColorInfo[1], iColorInfo[2]);
	return rgb;
}