// CFileEx.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "CFileEx.h"


// CFileEx

IMPLEMENT_DYNAMIC(CFileEx, CWnd)

CFileEx::CFileEx()
{

}

CFileEx::~CFileEx()
{
}

CString CFileEx::IniFileReadStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefaultName)
{
	CString strTmp = _T("");
	char szBuffer[MAX_PATH + 1] = { NULL, };
	//The return value is the number of characters copied to the buffer,
	//not including the terminating null character.
	GetPrivateProfileString(lpAppName,// points to section name
		lpKeyName,// points to key name
		lpDefaultName,// points to default string
		szBuffer,// points to destination buffer
		MAX_PATH + 1,// size of destination buffer
		m_strFileName);// points to initialization filename
	return szBuffer;
}



BEGIN_MESSAGE_MAP(CFileEx, CWnd)
END_MESSAGE_MAP()



// CFileEx 메시지 처리기


