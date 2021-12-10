// CDrawVideoClass.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "CDrawVideoClass.h"


// CDrawVideoClass

IMPLEMENT_DYNAMIC(CDrawVideoClass, CWnd)

CDrawVideoClass::CDrawVideoClass()
{

}

CDrawVideoClass::~CDrawVideoClass()
{
}


BEGIN_MESSAGE_MAP(CDrawVideoClass, CWnd)
END_MESSAGE_MAP()


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

// CDrawVideoClass 메시지 처리기


