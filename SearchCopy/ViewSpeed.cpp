// ViewSpeed.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "ViewSpeed.h"


// ViewSpeed

IMPLEMENT_DYNAMIC(ViewSpeed, CWnd)

ViewSpeed::ViewSpeed()
{

}

ViewSpeed::~ViewSpeed()
{
}


void ViewSpeed::InitCtrl(COLORREF rgbBack, COLORREF rgbText, CString strFont)
{
	m_rgbBack = rgbBack;
	m_rgbText = rgbText;


	int			nIndexStart, nIndexOffset;
	int			nWidth, nHeight, nCharSet;
	CString		strTemp;

	// Height
	nIndexStart = 0;
	nIndexOffset = strFont.Find(',', nIndexStart);
	strTemp = strFont.Mid(nIndexStart, nIndexOffset - nIndexStart);
	nHeight = atoi((LPCTSTR)strTemp);

	// Width
	nIndexStart = nIndexOffset + 1;
	nIndexOffset = strFont.Find(',', nIndexStart);
	strTemp = strFont.Mid(nIndexStart, nIndexOffset - nIndexStart);
	nWidth = atoi((LPCTSTR)strTemp);

	// CharSet
	nIndexStart = nIndexOffset + 1;
	nIndexOffset = strFont.Find(',', nIndexStart);
	strTemp = strFont.Mid(nIndexStart, nIndexOffset - nIndexStart);
	nCharSet = atoi((LPCTSTR)strTemp);

	// reserved
	nIndexStart = nIndexOffset + 1;
	nIndexOffset = strFont.Find(',', nIndexStart);
	strTemp = strFont.Mid(nIndexStart, nIndexOffset - nIndexStart);

	// reserved
	nIndexStart = nIndexOffset + 1;
	nIndexOffset = strFont.Find(',', nIndexStart);
	strTemp = strFont.Mid(nIndexStart, nIndexOffset - nIndexStart);

	// Font Name
	nIndexStart = nIndexOffset + 1;
	CString		strFontName = strFont.Right(strFont.GetLength() - nIndexStart);

	m_textFont.CreateFont(
		nHeight,				// 12 //font height
		nWidth,					// 6, //fon weight
		0,						// 이전 글자와 다음 글자간 폰트 출력 각도 
		0,						// font 회전 900 -> 90 2700 -> 270
		FW_BOLD,				// 글자 굵기 FW_NORMAL,FW_BOLD
		FALSE,					// italic
		FALSE,					// underline
		FALSE,					// 글자 중단에 줄이 감
		nCharSet,				// EFAULT_CHARSET, // font 글자 setting : ANSI_CHARSET,SYMBOL_CHARSET
		OUT_DEFAULT_PRECIS,		// 글자 출력 정밀도 
		CLIP_DEFAULT_PRECIS,	// 글자 출력 정밀도 
		DEFAULT_QUALITY,		// clip 출력 정밀도 
		DEFAULT_PITCH,
		(LPCTSTR)strFontName);	// Arial, MS Sans Serif
}


BEGIN_MESSAGE_MAP(ViewSpeed, CWnd)
END_MESSAGE_MAP()



// ViewSpeed 메시지 처리기


