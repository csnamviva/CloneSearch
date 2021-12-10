#pragma once

struct stPICTURE_FILE
{
	CString	strFileName;
	int		iLeft;
	int		iTop;
	int		iWidth;
	int		iHeight;
	CString strImageIdName;
	UINT	iIdNumber;
};



class CImageEx
{
public:

	stPICTURE_FILE GetPictureInfo(CString strPath, CString strPrefix, BOOL span = TRUE);

	CBitmap* GetBitmap(CDC* pdc, LPCTSTR lpszFileName);

	void		MoveSkinButton(CDC* pDC, CBitmap* btn, LPRECT lpRect);
	CRect		AnalyzeRect2(CString str, BOOL span = TRUE);
	COLORREF	AnalyzeRGB(CString str);

};

