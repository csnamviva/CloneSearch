#pragma once


// CFileEx

class CFileEx
{
public:
	CString m_strFileName;

	CFileEx();
	virtual ~CFileEx();

	CString IniFileReadStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefaultName);

};


