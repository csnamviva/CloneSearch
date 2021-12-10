#pragma once


// CFileEx

class CFileEx : public CWnd
{
	DECLARE_DYNAMIC(CFileEx)

public:
	CString m_strFileName;

	CFileEx();
	virtual ~CFileEx();

	CString IniFileReadStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefaultName);


protected:
	DECLARE_MESSAGE_MAP()
};


