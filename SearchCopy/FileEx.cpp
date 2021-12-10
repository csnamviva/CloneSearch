// FileEx.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "FileEx.h"


// FileEx

IMPLEMENT_DYNAMIC(FileEx, CFileDialog)

FileEx::FileEx(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{

}

FileEx::~FileEx()
{
}


BEGIN_MESSAGE_MAP(FileEx, CFileDialog)
END_MESSAGE_MAP()



// FileEx 메시지 처리기


