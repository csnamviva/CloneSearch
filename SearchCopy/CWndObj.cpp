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


BEGIN_MESSAGE_MAP(CWndObj, CWnd)
END_MESSAGE_MAP()



// CWndObj 메시지 처리기


