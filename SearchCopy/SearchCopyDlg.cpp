
// SearchCopyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SearchCopy.h"
#include "SearchCopyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

long CSearchCopyDlg::m_Split = 1;

CWndObj* CSearchCopyDlg::m_WndObj = NULL;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSearchCopyDlg 대화 상자



CSearchCopyDlg::CSearchCopyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCHCOPY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSearchCopyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CSearchCopyDlg 메시지 처리기

BOOL CSearchCopyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	char		szConfigMain[MAX_PATH];
	TCHAR		chPath[MAX_PATH + 1];
	memset(chPath, 0, sizeof(chPath));
	CFile file;
	CString strTmp = _T("");

	//int k = file.GetLength();
	//file.Read(chPath, file.GetLength());
	//file.Close();
	//m_strSysPathUpper.Format("%s\\work\\Test\\SearchCopy\\Image", chPath);
	::GetCurrentDirectory(MAX_PATH, chPath);
	strTmp = chPath;


	theApp.m_strImageFolder = strTmp;
	theApp.m_strImageFolder += "\\Image";

	theApp.m_SearchImage.m_strFileName = theApp.m_strImageFolder;
	theApp.m_SearchImage.m_strFileName += "\\search.txt";

	theApp.m_LogoImage.m_strFileName = theApp.m_strImageFolder;
	theApp.m_LogoImage.m_strFileName += "\\search.txt";

	//m_strImageFolder += "\\search.txt";
	//m_SearchImage.m_strFileName = m_strImageFolder;
	m_pDc = GetDC();
	OnMainSkinLoad();

	OnMainLogoLoad();
	//InitSearch();

	InitializeBtns();

	char	szText[MAX_PATH];
	CRect	rect;
	//sprintf_s(szText, "%s", theApp.m_SearchImage.IniFileReadStringEx("Speed View", "Pos", "0,0,0,0"));
	rect = theApp.m_ImageFunc.AnalyzeRect2(szText);
	COLORREF	rgbSVBack = theApp.m_ImageFunc.AnalyzeRGB(theApp.m_SearchImage.IniFileReadStringEx("Speed View", "rgbBack", "0,0,0"));
	COLORREF	rgbSVTect = theApp.m_ImageFunc.AnalyzeRGB(theApp.m_SearchImage.IniFileReadStringEx("Speed View", "rgbText", "240,255,0"));
	CString		strFont = theApp.m_SearchImage.IniFileReadStringEx("Speed View", "optFont", "14,6,1,0,0,Arial");
	//m_ViewSpeed->InitCtrl(rgbSVBack, rgbSVTect, strFont);
	//m_ViewSpeed->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());

	ShowWindow(SW_SHOW);

	SetSplit(4);

	//m_bMoving = theApp.m_SearchImage.IniFileReadInt("Search Main", "Moving", 0);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSearchCopyDlg::OnMainSkinLoad()
{
	stPICTURE_FILE	MainImageInfo;
	MainImageInfo = theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Main", "Main Skin", _T("")), FALSE);

	m_wGUIWidth = MainImageInfo.iWidth;
	m_wGUIHeight = MainImageInfo.iHeight;

	MoveWindow(MainImageInfo.iLeft, MainImageInfo.iTop, m_wGUIWidth, m_wGUIHeight);
	m_hMainBitmap = NULL;
	m_hMainBitmap = theApp.m_ImageFunc.GetBitmap(m_pDc, MainImageInfo.strFileName);
}

void CSearchCopyDlg::OnMainLogoLoad()
{
	stPICTURE_FILE MainLogoInfo;
	MainLogoInfo = theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder,
		theApp.m_LogoImage.IniFileReadStringEx("Search Main", "Logo", _T("")));
	m_hMainLogoBitmap = NULL;
	m_hMainLogoBitmap = theApp.m_ImageFunc.GetBitmap(m_pDc, MainLogoInfo.strFileName);
}


void CSearchCopyDlg::InitializeBtns()
{
	// 각각의 원도우에 ID값을 부여한다.
//[Search Timebar]
	SetItems(this, &m_BtnCamUpDown[0], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Timebar", "Cam_Down", "cam_down.bmp,0,0,0,0,ID_BT_CAMDOWN,1")), &m_lstSearch, TRUE);
	SetItems(this, &m_BtnCamUpDown[1], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Timebar", "Cam_up", "cam_up.bmp,0,0,0,0,ID_BT_CAMUP,2")), &m_lstSearch, TRUE);
	SetItems(this, &m_BtnCamUpDown[2], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Timebar", "Cam_ip", "cam_ip.bmp,0,0,0,0,ID_BT_CAMIP,7")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnCamUpDown[3], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Timebar", "Cam_analog", "cam_analog.bmp,0,0,0,0,ID_BT_CAMANALOG,8")), &m_lstSearch, TRUE);//

	SetItems(this, &m_BtnHourMin, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Timebar", "MINTIME", "hour.bmp,0,0,0,0,ID_BT_MINTIME,49")), &m_lstSearch, TRUE);
	SetItems(this, &m_BtnCamGroup, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Timebar", "CamGroup", "cam1_16.bmp,0,0,0,0,ID_BT_CAM1_4,3")), &m_lstSearch, TRUE);

	//[Search Screen]
	SetItems(this, &m_BtnSplit[0], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "Split_1", "ch_1.bmp,0,0,0,0,ID_BT_SPLIT1,23")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnSplit[1], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "Split_4", "ch_4.bmp,0,0,0,0,ID_BT_SPLIT4,24")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnSplit[2], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "Split_9", "ch_9.bmp,0,0,0,0,ID_BT_SPLIT9,25")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnSplit[3], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "Split_16", "ch_16.bmp,0,0,0,0,ID_BT_SPLIT16,26")), &m_lstSearch, TRUE);//

	SetItems(this, &m_BtnMagnification[0], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "X1_zoom", "x1_zoom.bmp,0,0,0,0,ID_BT_X1ZOOM,29")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnMagnification[1], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "X1.5_zoom", "x1.5_zoom.bmp,0,0,0,0,ID_BT_X15ZOOM,30")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnMagnification[2], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "X2_zoom", "x2_zoom.bmp,0,0,0,0,ID_BT_X2ZOOM,31")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnMagnification[3], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "Full", "full.bmp,0,0,0,0,ID_BT_FULL,32")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPanorama, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "Panorama", "panorama.bmp,0,0,0,0,ID_BT_CHPANORAMA,28")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnZoom, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Screen", "pzoom", "zoom_btn.bmp,0,0,0,0,ID_BT_ZOOM,38")), &m_lstSearch, TRUE);//

//[Search Button]
	SetItems(this, &m_BtnAdjustment, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Adjustment", "adjustment.bmp,0,0,0,0,ID_BT_ADJUSTMENT,36")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPlayControl, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "playcontrol", "playcontrol.bmp,0,0,0,0,ID_BT_PLAYCONTROL,59")), &m_lstSearch, TRUE); // 2010.01.14
	SetItems(this, &m_BtnPrint, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Print", "print.bmp,0,0,0,0,ID_BT_PRINT,37")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnSave, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Save", "save.bmp,0,0,0,0,ID_BT_SAVE,33")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnSmartSearch, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Smartsearch", "smartsearch.bmp,0,0,0,0,ID_BT_SMARTSEARCH,34")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnLogViewer, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Logviewer", "esearch.bmp,0,0,0,0,ID_BT_LOGVIEWER,56")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnBackup, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Backup", "backup.bmp,0,0,0,0,ID_BT_BACKUP,57")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnTimeSearch, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "TimeSearch", "backup.bmp,0,0,0,0,ID_BT_TIMESEARCH,58")), &m_lstSearch, TRUE);//

//[Search Play]
	SetItems(this, &m_BtnPlaySearch[0], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "PlayB1MinStep", "PlayB1MinStep.bmp,0,0,0,0,ID_BT_PLAYB1MINSTEP,39")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPlaySearch[1], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "PlayB1Step", "PlayB1Step.bmp,0,0,0,0,ID_BT_PLAYB1STEP,40")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPlaySearch[2], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "PlayF1MinStep", "PlayF1MinStep.bmp,0,0,0,0,ID_BT_PLAYF1MINSTEP,41")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPlaySearch[3], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "PlayF1Step", "PlayF1Step.bmp,0,0,0,0,ID_BT_PLAYF1STEP,42")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPlaySearch[4], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "PlayForward", "PlayForward.bmp,0,0,0,0,ID_BT_PLAYFORWARD,43")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPlaySearch[5], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "PlayReverse", "PlayReverse.bmp,0,0,0,0,ID_BT_PLAYREVERSE,44")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnPlaySearch[6], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "Playstop", "Playstop.bmp,0,0,0,0,ID_BT_PLAYSTOP,45")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnRealPlay, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Play", "Realtime", "realtime.bmp,0,0,0,0,ID_BT_REALTIME,46")), &m_lstSearch, TRUE);//

//[Search SpeedButton]
	//SetItems(this, &m_BtnSpeedBt[0],&theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder,theApp.m_SearchImage.IniFileReadStringEx("Search SpeedButton","speed_m","speed_m.bmp,0,0,0,0,ID_BT_SPEEDMINUS,50")),&m_lstSearch,TRUE);//
	//SetItems(this, &m_BtnSpeedBt[1],&theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder,theApp.m_SearchImage.IniFileReadStringEx("Search SpeedButton","speed_p","speed_p.bmp,0,0,0,0,ID_BT_SPEEDPLUS,51")),&m_lstSearch,TRUE);//

	//[Search Button]
	SetItems(this, &m_BtnBookMark[0], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "bookmark", "bookmark.bmp,0,0,0,0,ID_BT_BOOKMARK,53")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnBookMark[1], &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "bookmark_add", "bookmark_add.bmp,0,0,0,0,ID_BT_BOOKMARK_ADD,54")), &m_lstSearch, TRUE);//
	SetItems(this, &m_BtnSelectFolder, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "selectfolder", "folderselect.bmp,0,0,0,0,ID_BT_SELECTFOLDER,55")), &m_lstSearch, TRUE);//

//[Search Exit]
	SetItems(this, &m_BtnExit, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Exit", "exit.bmp,0,0,0,0,ID_BT_EXIT,47")), &m_lstSearch, TRUE);
	SetItems(this, &m_BtnSetup, &theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Search Button", "Setup", "setup.bmp,0,0,0,0,ID_BT_SETUP,60")), &m_lstSearch, TRUE);

//	 20131004
	stPICTURE_FILE	pic;
	pic = theApp.m_ImageFunc.GetPictureInfo(theApp.m_strImageFolder, theApp.m_SearchImage.IniFileReadStringEx("Timebar VScroll", "ScrollBar", "dummy.bmp,0,0,0,0,ID_BT_NONE,255"));
	m_SkinVerticleScrollbar.Create(NULL, WS_CHILD | SS_LEFT | SS_NOTIFY | WS_VISIBLE | WS_GROUP, CRect(0, 0, 0, 0), this);
	m_SkinVerticleScrollbar.SetWindowPos(NULL, pic.iLeft, pic.iTop, pic.iWidth, pic.iHeight, SWP_NOZORDER);
	m_SkinVerticleScrollbar.Init();
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	
	//window
	//for (int i = 0; i < MAX_VIEW; i++)
	//{
	//	m_Win[i]->m_nScreenNo = i;
	//	//m_Win[i]->m_pOwner = this;
	//}
	
	m_iAnalogChannelPressed = ID_BT_CAMANALOG; // 8
	m_iIPChannelPressed = 0;
	m_BtnCamUpDown[2].Refresh();
	m_BtnCamUpDown[3].Refresh();
}


void CSearchCopyDlg::SetItems(CWnd* pWnd, CWndObj* pObj, stPICTURE_FILE* stpicinfo, CPtrList* pList, BOOL bAdd)
{
	pObj->SetPosition(stpicinfo);
	// ID 설정
	pObj->SetID(pWnd, stpicinfo);
	// list에 추가
	if (bAdd)   pList->AddTail(pObj);
}



void CSearchCopyDlg::SetSplit(long nSplit)
{
	TRACE("\nSetSplit(%d)\n", nSplit);

	// delete GSS
	//	if (m_nScreenMode == 0)	return;		// 검색의 영상상태 = 1, 달력상태 = 0

	//	if (m_Split == nSplit)	return;		// 일단 화면이 1분할이면 계속 여기서 리턴한다

	long	nOldMode = m_Split;			// 화면 분할 모드 상태
	BOOL	bfSplitDown;

	//이전 분할모드 선택 그림을 clear한다.
	if (nOldMode == 1)			m_BtnSplit[0].Refresh();
	else if (nOldMode == 4)		m_BtnSplit[1].Refresh();
	else if (nOldMode == 9)		m_BtnSplit[2].Refresh();
	else if (nOldMode == 16)	m_BtnSplit[3].Refresh();
	else						return;

	if (m_Split > nSplit)
	{
		bfSplitDown = TRUE;
	}
	else
	{
		bfSplitDown = FALSE;
	}

	m_Split = nSplit;

	// 새로이 선택한 분할모드 선택된 그림으로 채운다.
	if (m_Split == 1)
	{
		m_SplitPage = m_nCurCam;
		m_BtnSplit[0].Refresh();
	}
	else if (m_Split == 4)
	{
		m_SplitPage = m_nCurCam / 4;
		m_BtnSplit[1].Refresh();
	}
	else if (m_Split == 9)
	{
		m_SplitPage = m_nCurCam / 9;
		m_BtnSplit[2].Refresh();
	}
	else if (m_Split == 16)
	{
		m_SplitPage = m_nCurCam / 16;
		m_BtnSplit[3].Refresh();
	}

	//m_idMagnification = ID_BT_X2ZOOM;

	// 확대 모드를 보통으로 설정한다
/*	if (m_Split != 1)
	{
		m_idMagnification = ID_BT_X1ZOOM;
		m_BtnMagnification[0].Refresh();
		m_BtnMagnification[1].Refresh();
		m_BtnMagnification[2].Refresh();
		m_BtnMagnification[3].Refresh();
	}
*/
	//SplitScreenUpdate(nSplit, bfSplitDown);
}



void CSearchCopyDlg::InitSearch()
{
	//for (int i = 0; i < MAX_VIEW; i++)
	//{
	//	CRect	rc(0, 0, 0, 0);
	//	m_Win[i]->MoveWindow(&rc);
	//	m_Win[i]->SetArea(&rc); //t
	//}
}


void CSearchCopyDlg::SplitScreenUpdate(long nSplit, BOOL bfSplitDown)
{
	//	EnterCriticalSection(&m_CriticalPlay);

	DWORD dw = WAIT_TIMEOUT;
	m_bReadDataThreadPause = TRUE;
	ResetEvent(hevent_readdatathread_start);
	SetEvent(hevent_readdatathread_pause);
	dw = WaitForSingleObject(hevent_readdata_paused, 200);
	MSG msg;
	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
		
	int		i;
	for (i = 0; i < MAX_VIEW; i++) {
		m_Win[i]->m_bShow = FALSE;
	}
	CWindow::m_pdraw->EmptyCanvas(); //t

	if (bfSplitDown == TRUE)
	{
		for (i = 0; i < MAX_CHANNEL; i++)
		{
			if (i != m_nCurCam)
			{
				m_bIFramepass[i] = FALSE;
			}
		}
	}


	//for (i = 0; i < MAX_VIEW; i++)
	//{
	//	m_Win[i]->FlushBuffer();
	//}
	memset(m_btUsedChannel, 0x00, sizeof(m_btUsedChannel));
	memset(m_ViewChannel, 0x00, sizeof(m_ViewChannel));

	//	TRACE("SplitScreenUpdateF(%d, %c)\n", nSplit, bfSplitDown?'T':'F');

		///////////////////////////////////////////////////////////////////
	int		nSplitPage = m_SplitPage;

//	t if (m_nScreenMode)
	CRect	rc[MAX_VIEW]; //t
		switch (nSplit)
		{
		case 4:
			m_bMulti = TRUE;  // 멀티 상태임을 의미
			for (i = 0; i < 4; i++) { //t
				rc[i] = GetSplit4Pos(i); //t
			} //t

			for (i = 0; i < MAX_VIEW; i++)
			{
//				t				CRect	rc;
//				t				rc = GetSplit4Pos(i);

				if (nSplit * nSplitPage <= i && i < nSplit * (nSplitPage + 1))
				{
					if (m_iPanoPush && i != m_nCurCam)
					{
						m_Win[i]->m_bImageReady = FALSE;
					}
					m_btUsedChannel[i] = 1;
					m_ViewChannel[i] = TRUE;
					m_Win[i]->SetArea(&rc[i % 4]); //t
					m_Win[i]->m_bShow = TRUE;
					m_Win[i]->DrawImage();
				}
				else
				{
					CRect rt = CRect(0, 0, 0, 0); //t
					m_Win[i]->SetArea(&rt); //t
					m_Win[i]->m_bImageReady = FALSE;	// add GSS
					m_Win[i]->m_bShow = FALSE;
				}
			}
			m_FindFS->SetUsedChannels(m_btUsedChannel);
			break;
		}
	if (m_PlayID != 0)
	{
//				TRACE("readdata thread started\n");
		ResetEvent(hevent_readdatathread_pause);
		SetEvent(hevent_readdatathread_start);
	}

//		LeaveCriticalSection(&m_CriticalPlay);
}



void CSearchCopyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSearchCopyDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = m_wGUIWidth;
		rect.bottom = m_wGUIHeight;
		theApp.m_ImageFunc.MoveSkinButton(&dc, m_hMainBitmap, &rect);

	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSearchCopyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSearchCopyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPtrList* pList;

	pList = &m_lstSearch;   // 메인 화면에 사용되는 ITEM들 
	POSITION pos = pList->GetTailPosition();
	while (pos)
	{
		CWndObj* pWnd = (CWndObj*)pList->GetPrev(pos);
		ASSERT(pWnd);

		if (pWnd->PtInRect(point))
		{
			if (m_iAdjustPressed == ID_BT_ADJUSTMENT)
			{
				CSearchCopyDlg::m_WndObj = pWnd;
				pWnd->OnLButtonDown(nFlags, point);
				return;
			}
			else
			{
				CSearchCopyDlg::m_WndObj = pWnd; //image tool open
				pWnd->OnLButtonDown(nFlags, point);
				return;
			}
		}
	}

	//t --------------------------------------------------------------
	//if (m_nScreenMode && m_iPanoPush != ID_BT_CHPANORAMA)
	//{
	//	int nCurCam = FindSelectedChannel(point);
	//	if (nCurCam >= 0 && nCurCam != m_nCurCam) {
	//		m_Win[nCurCam]->PostMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x, point.y));
	//		return;
	//	}
	//}
	//t --------------------------------------------------------------

		//////0828 SDLEE
	//if (m_bMoving)
	//{
	//	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	//}

	CDialogEx::OnLButtonDown(nFlags, point);
}


CRect CSearchCopyDlg::GetSplit4Pos(int nChannel)
{
	CRect	rc;
	int		nPosition = nChannel % 4;
	int		x = nPosition % 2;
	int		y = nPosition / 2;

	rc.left = m_ViewPos[1].left + (m_ViewPos[1].right * x);
	rc.top = m_ViewPos[1].top + (m_ViewPos[1].bottom * y);
	rc.right = rc.left + m_ViewPos[1].right;
	rc.bottom = rc.top + m_ViewPos[1].bottom;

	return rc;
}