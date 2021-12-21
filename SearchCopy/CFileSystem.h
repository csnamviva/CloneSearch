#pragma once


// CFileSystem

class CFileSystem : public CWnd
{
	DECLARE_DYNAMIC(CFileSystem)

public:
	CFileSystem();
	virtual ~CFileSystem();

	int		SetUsedChannels(BYTE* fChannel);

	long			m_FSKind;			// 0 = None, 1 = Local, 2 = Remote

	BYTE			m_btAvailableChannel[128];

	//CDBHandler* m_FSLocal;
	//CRDBHandler* m_FSRemote;

protected:
	DECLARE_MESSAGE_MAP()
};


