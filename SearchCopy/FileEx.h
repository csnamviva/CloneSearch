#pragma once


// FileEx

class FileEx : public CFileDialog
{
	DECLARE_DYNAMIC(FileEx)

public:
	CString m_strFileName;

	FileEx(BOOL bOpenFileDialog, // FileOpen은 TRUE, FileSaveAs는 FALSE입니다.
		LPCTSTR lpszDefExt = nullptr,
		LPCTSTR lpszFileName = nullptr,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = nullptr,
		CWnd* pParentWnd = nullptr);
	virtual ~FileEx();

protected:
	DECLARE_MESSAGE_MAP()
};


