// CWndObj.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "CWndObj.h"


// CWndObj

IMPLEMENT_DYNAMIC(CWndObj, CWnd)

CWndObj::CWndObj()
{

}

CWndObj::~CWndObj()
{
}


void CWndObj::Refresh(BOOL bErase)
{
    if (m_pWnd && ::IsWindow(m_pWnd->m_hWnd))
    {
        m_pWnd->InvalidateRect(&m_rcPosition, bErase);
    }
}

void CWndObj::SetPosition(stPICTURE_FILE* stpicinfo)
{
    // 메인 윈도우에 대한 절대 위치
    m_rcPosition.left = stpicinfo->iLeft;
    m_rcPosition.top = stpicinfo->iTop;
    m_rcPosition.right = stpicinfo->iLeft + stpicinfo->iWidth;
    m_rcPosition.bottom = stpicinfo->iTop + stpicinfo->iHeight;

    // 상대위치 윈도우
    m_rcRealPosition.left = 0;
    m_rcRealPosition.top = 0;
    m_rcRealPosition.right = stpicinfo->iWidth;
    m_rcRealPosition.bottom = stpicinfo->iHeight;
}

void CWndObj::SetID(CWnd* pWnd, stPICTURE_FILE* stpicinfo)
{
    m_pWnd = pWnd;
    m_ID = stpicinfo->iIdNumber;
}


BOOL CWndObj::PtInRect(POINT point)
{
    return m_rcPosition.PtInRect(point);
}

BEGIN_MESSAGE_MAP(CWndObj, CWnd)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CWndObj 메시지 처리기




void CWndObj::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    m_bPressed = TRUE;
    m_pWnd->InvalidateRect(&m_rcPosition, FALSE);

    CStatic::OnLButtonDown(nFlags, point);
}
