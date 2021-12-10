// CWindow.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "CWindow.h"

CDrawVideoClass* CWindow::m_ddraw;

// CWindow

IMPLEMENT_DYNAMIC(CWindow, CButton)

CWindow::CWindow()
{

}

CWindow::~CWindow()
{
}


BEGIN_MESSAGE_MAP(CWindow, CButton)
END_MESSAGE_MAP()



// CWindow 메시지 처리기


