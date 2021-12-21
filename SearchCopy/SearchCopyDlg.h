
// SearchCopyDlg.h: 헤더 파일
//

#include "CFileEx.h"
#include "ViewSpeed.h"
#include "Split.h"
#include "CWindow.h"
#include "CameraUpDown.h"
#include "CHourMin.h"
#include "CameraGroup.h"
#include "CWndZoom.h"
#include "CPanorama.h"
#include "CPZoomBtn.h"
#include "CAdjustment.h"
#include "CPlayTab.h"
#include "CPrint.h"
#include "CSave.h"
#include "CSmartSearch.h"
#include "CLogViewer.h"
#include "CBackup.h"
#include "CTimeSearch.h"
#include "CPlaySearch.h"
#include "CRealPlay.h"
#include "CBookMark.h"
#include "CSelectFolder.h"
#include "CExit.h"
#include "CSetup.h"
#include "CSkinVerticleScrollbar.h"
#include "CViewPan.h"
#include "CFileSystem.h"



#define MAX_VIEW 64
#define ID_BT_CAMANALOG 8
#define ID_BT_ADJUSTMENT 36

#pragma once


// CSearchCopyDlg 대화 상자
class CSearchCopyDlg : public CDialogEx
{
// 생성입니다.
public:
	CSearchCopyDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	int				m_iZoom;
	int					m_nOSDChannel;
	int					m_nOSDTime;
	int					m_nOSDSize;
	int					m_nOSDColor;


	BOOL m_bMulti;

	CFileSystem			*m_FindFS;

	int					m_sldBrightPos;
	int					m_sldContrastPos;
	int					m_sldHuePos;

	CViewPan* m_ViewPan;

	void OnMainSkinLoad();
	void InitSearch();
	void OnMainLogoLoad();
	void InitializeBtns();
	void		SetItems(CWnd* pWnd, CWndObj* pObj, stPICTURE_FILE* stpicinfo, CPtrList* pList, BOOL bAdd);
	CRect GetSplit4Pos(int nChannel);
	CRect m_ViewPos[4];

	void SetSplit(long nSplit);
	void SplitScreenUpdate(long nSplit, BOOL bfSplitDown = FALSE);
	long m_lMaxGroup;

	int				m_idMagnification;

	static CWndObj* m_WndObj;

	UINT			m_CamGroup;
	
	WORD			m_wGUIWidth, m_wGUIHeight;
	CBitmap*		m_hMainBitmap;
	CBitmap*		m_hMainLogoBitmap;
	CDC*			m_pDc;

	UINT			m_PlayID;

	Split			m_BtnSplit[4];


	CWindow			*m_Win[MAX_VIEW];

	CString			m_strSysPathUpper;

	BOOL			m_bReadDataThreadPause;
	HANDLE			hevent_readdatathread_start;
	HANDLE			hevent_readdatathread_pause;
	HANDLE			hevent_readdatathread_stop;
	HANDLE			hevent_readdata_paused;
	BOOL			m_bReadDataThreadStop;
	int				m_SplitPage;
	long			m_nCurCam;
	int				m_iPanoPush;
	BOOL			m_bIFramepass[MAX_CHANNEL];

	//CImageEx		m_ImageFunc;
	ViewSpeed*		m_ViewSpeed;

	BYTE			m_btUsedChannel[128];
	BOOL			m_ViewChannel[MAX_VIEW];

	CameraUpDown	m_BtnCamUpDown[4];
	CHourMin		m_BtnHourMin;
	CameraGroup		m_BtnCamGroup;
	CWndZoom		m_BtnMagnification[4];
	CPanorama		m_BtnPanorama;
	CPZoomBtn		m_BtnZoom;
	CAdjustment		m_BtnAdjustment;
	CPlayTab		m_BtnPlayControl;
	CPrint			m_BtnPrint;
	CSave				m_BtnSave;
	CSmartSearch		m_BtnSmartSearch;
	CLogViewer			m_BtnLogViewer;
	CBackup				m_BtnBackup;
	CTimeSearch			m_BtnTimeSearch;
	CPlaySearch			m_BtnPlaySearch[7];
	CRealPlay			m_BtnRealPlay;
	CBookMark			m_BtnBookMark[2];
	CSelectFolder		m_BtnSelectFolder;
	CExit				m_BtnExit;
	CSetup				m_BtnSetup;
	CSkinVerticleScrollbar m_SkinVerticleScrollbar;


	LPBYTE			m_pImageRGBColor;


	CPtrList m_lstSearch;

	static long		m_Split;
	

	int				m_iAnalogChannelPressed;
	int				m_iIPChannelPressed;
	int					m_iAdjustPressed;


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
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
