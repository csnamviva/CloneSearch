// CFileSystem.cpp: 구현 파일
//

#include "pch.h"
#include "SearchCopy.h"
#include "CFileSystem.h"


// CFileSystem

IMPLEMENT_DYNAMIC(CFileSystem, CWnd)

CFileSystem::CFileSystem()
{

}

CFileSystem::~CFileSystem()
{
}



int CFileSystem::SetUsedChannels(BYTE* fChannel)
{
	int		nRet = 0;

	if (m_FSKind == 1)
	{
		for (int i = 0; i < 128; i++)
		{
			if (m_btAvailableChannel[i] == 0)
			{
				*(fChannel + i) = 0x00;
			}
		}

		//nRet = m_FSLocal->SetUsedChannels(fChannel);
	}
	else if (m_FSKind == 2)
	{
		//nRet = m_FSRemote->SetUsedChannels(fChannel);
	}
	else
	{
		nRet = 1;			// FS_NOT_SUPPORT
	}

	return (nRet);
}


BEGIN_MESSAGE_MAP(CFileSystem, CWnd)
END_MESSAGE_MAP()



// CFileSystem 메시지 처리기


