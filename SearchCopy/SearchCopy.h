
// SearchCopy.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//
#include "CImageEx.h"
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "CFileEx.h"

// CSearchCopyApp:
// 이 클래스의 구현에 대해서는 SearchCopy.cpp을(를) 참조하세요.
//

class CSearchCopyApp : public CWinApp
{
public:
	CSearchCopyApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();


	CString			m_strImageFolder;
	CFileEx			m_SearchImage;
	CFileEx			m_LogoImage;
	CImageEx	m_ImageFunc;
	
	
	float w_ratio;
	float h_ratio;


// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CSearchCopyApp theApp;
