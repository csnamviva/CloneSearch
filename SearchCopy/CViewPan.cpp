// CViewPan.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "CViewPan.h"
#include "SearchCopyDlg.h"


// CViewPan

IMPLEMENT_DYNAMIC(CViewPan, CStatic)

CViewPan::CViewPan()
{

}

CViewPan::~CViewPan()
{
}


BEGIN_MESSAGE_MAP(CViewPan, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CViewPan 메시지 처리기




void CViewPan::OnPaint()
{
	CSearchCopyDlg* pWnd = (CSearchCopyDlg*)AfxGetApp()->m_pMainWnd;

	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CStatic::OnPaint()을(를) 호출하지 마십시오.

	RECT rt;
	GetClientRect(&rt);
	dc.FillSolidRect(&rt, RGB(0, 0, 0));

	if (pWnd->m_idMagnification != 32) {
		for (int i = 0; i < MAX_VIEW; i++) { //t
			pWnd->m_Win[i]->DrawImage(); //t
		}
	}
	else {
		pWnd->m_Win[pWnd->m_nCurCam]->DrawImage(); //t
	}
}
