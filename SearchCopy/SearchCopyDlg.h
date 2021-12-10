
// SearchCopyDlg.h: 헤더 파일
//

#include "CFileEx.h"
#include "ViewSpeed.h"
#include "Split.h"
#include "CWindow.h"

#define MAX_VIEW 64

#pragma once


// CSearchCopyDlg 대화 상자
class CSearchCopyDlg : public CDialogEx
{
// 생성입니다.
public:
	CSearchCopyDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.


	void OnMainSkinLoad();
	void InitSearch();
	void OnMainLogoLoad();
	void SetSplit(long nSplit);
	void SplitScreenUpdate(long nSplit, BOOL bfSplitDown = FALSE);
	
	WORD		m_wGUIWidth, m_wGUIHeight;
	CBitmap* m_hMainBitmap;
	CBitmap* m_hMainLogoBitmap;
	CDC* m_pDc;

	UINT m_PlayID;

	Split		m_BtnSplit[4];

	CFileEx		m_SearchImage;
	CFileEx		m_LogoImage;

	CWindow* m_Win[MAX_VIEW];

	CString		m_strImageFolder;
	CString		m_strSysPathUpper;

	BOOL		m_bReadDataThreadPause;
	HANDLE		hevent_readdatathread_start;
	HANDLE		hevent_readdatathread_pause;
	HANDLE		hevent_readdatathread_stop;
	HANDLE		hevent_readdata_paused;
	BOOL		m_bReadDataThreadStop;
	int			m_SplitPage;
	long		m_nCurCam;
	BOOL		m_bIFramepass[MAX_CHANNEL];

	CImageEx	m_ImageFunc;
	ViewSpeed* m_ViewSpeed;

	BYTE			m_btUsedChannel[128];
	BOOL			m_ViewChannel[MAX_VIEW];

	static long		m_Split;
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCHCOPY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
