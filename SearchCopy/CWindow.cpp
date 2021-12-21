// CWindow.cpp: 구현 파일
//

#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include "SearchCopy.h"
#include "CWindow.h"
#include "SearchCopyDlg.h"

CDrawVideoClass* CWindow::m_pdraw;

//class CSearchCopyDlg;
// CWindow

IMPLEMENT_DYNAMIC(CWindow, CButton)

CWindow::CWindow()
{

}

CWindow::~CWindow()
{
}


void CWindow::SetArea(CRect* rc)
{
	m_rectImageArea = *rc;
	//if (m_pOwner->m_idMagnification != ID_BT_FULL)
	//{
	//	m_ddraw->SetArea(m_pOwner->m_ScreenRect, m_nScreenNo, rc); //t
	//}
	//else
	//{
	//	m_ddraw->SetArea(m_rectImageArea, m_nScreenNo, rc); //t
	//}
}

void CWindow::DrawImage()
{
	if (m_bShow == FALSE)
	{
		return;
	}
	//t	CDC			*pDC = GetDC();
	//CDC* pDC = m_pOwner->m_ViewPan->GetDC();
	CDC* pDC = ((CSearchCopyDlg*)GetParent())->m_ViewPan->GetDC();
	char		infoTxt[128];
	CString		strCamera;
	int			ch_no; //t

//t ---------------------------------------------------------------
	if (((CSearchCopyDlg*)GetParent())->m_iPanoPush == 28)
	{
		ch_no = ((CSearchCopyDlg*)GetParent())->m_nCurCam;
	}
	else
	{
		ch_no = m_nScreenNo;
	}
	//((CSearchCopyDlg*)GetParent())->m_BtnCamGroup.GetCameraID(ch_no, strCamera);


	char		infoChannel[64];
	char		infoTime[64];
	memset(infoChannel, 0x00, sizeof(infoChannel));
	memset(infoTime, 0x00, sizeof(infoTime));
	memset(infoTxt, 0x00, sizeof(infoTxt));

	if (((CSearchCopyDlg*)GetParent())->m_nOSDChannel != 6)
	{
		//sprintf(infoChannel, "%s", (LPCTSTR)strCamera);
		sprintf(infoTxt, "%s", infoChannel);
	}
	if (((CSearchCopyDlg*)GetParent())->m_nOSDTime != 6)
	{
		//sprintf(infoTime, "\x1f%02d:%02d:%02d", m_chunkLast.tm.wHour, m_chunkLast.tm.wMinute, m_chunkLast.tm.wSecond);
		sprintf(infoTxt, "%s%s", infoChannel, infoTime);
	}


	switch (((CSearchCopyDlg*)GetParent())->m_Split)
	{
	case 4:
		// change GSS
		if (((CSearchCopyDlg*)GetParent())->m_iZoom != 38)
		{
			//t				m_ddraw->SetZoom(FALSE, NULL);
			m_pdraw->SetZoom(m_nScreenNo, FALSE, NULL); //t
		}
		if (IsColorAdjust() == TRUE && ((CSearchCopyDlg*)GetParent())->m_nCurCam == m_nScreenNo)
		{
			DrawAdjustImage(pDC->m_hDC, m_rectPlaySelectArea, 0, 0, 0, infoTxt);
		}
		else
		{
			DrawImageSplit(pDC->m_hDC, infoTxt);
		}
		break;
	}
	ReleaseDC(pDC);
}


BOOL CWindow::IsColorAdjust(void)
{/*
	int		tempBright = ((CSearchCopyDlg*)GetParent())->m_sldBrightPos;
	int		tempContrast = ((CSearchCopyDlg*)GetParent())->m_sldContrastPos / 36;
	int		tempHue = ((CSearchCopyDlg*)GetParent())->m_sldHuePos;*/
	return FALSE;
}

void CWindow::DrawAdjustImage(HDC hDC, CRect rectArea, int BrightValue, int ContrastValue, int HueValue, LPSTR strText)
{
	//t	BITMAPINFO	bmi;
	//t	memcpy(&bmi, &m_bmi, sizeof(bmi));

	if (m_bImageReady)
	{
		OperateImageAll(FALSE);
		m_pdraw->DrawImage(m_nScreenNo, ((CSearchCopyDlg*)GetParent())->m_pImageRGBColor, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 1, strText, TRUE); //t
	}
	else
	{
		m_pdraw->DrawImage(m_nScreenNo, ((CSearchCopyDlg*)GetParent())->m_hMainLogoBitmap, 320, 240, 10, strText, FALSE); //t
	}
}


void CWindow::DrawImageSplit(HDC hDC, LPSTR strText)
{
	if (m_bImageReady)
	{
		m_pdraw->SetImageSize(m_nScreenNo, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight); //t
		if (((CSearchCopyDlg*)GetParent())->m_iPanoPush == 28)
		{
			if (m_pImageYUV != NULL)
			{
				if (m_bPanoramaEndDisplay)
					m_pdraw->DrawImage(m_nScreenNo, m_pImageYUV, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 0, strText, TRUE); //t
				else
					m_pdraw->DrawImage(m_nScreenNo, m_pImageYUV, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 0, strText, FALSE); //t
			}
		}
		else if (((CSearchCopyDlg*)GetParent())->m_nCurCam == m_nScreenNo)
		{
			if (m_pImageYUV != NULL)
			{
				if (m_bmi.bmiHeader.biWidth > 640 && m_bmi.bmiHeader.biHeight > 480)
				{
					m_pdraw->DrawImage(m_nScreenNo, m_pImageYUV, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 0, strText, TRUE); //t
				}
				else
				{
					m_pdraw->DrawImage(m_nScreenNo, m_pImageYUV, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 0, strText, TRUE); //t
				}
			}
		}
		else
		{
			if (m_pImageYUV != NULL)
			{
				if (m_bmi.bmiHeader.biWidth > 640 && m_bmi.bmiHeader.biHeight > 480)
				{
					m_pdraw->DrawImage(m_nScreenNo, m_pImageYUV, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 0, strText, TRUE); //t
				}
				else
				{
					m_pdraw->DrawImage(m_nScreenNo, m_pImageYUV, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 0, strText, TRUE); //t
				}
			}
		}
	}
	else
	{
		m_pdraw->SetImageSize(m_nScreenNo, 320, 240); //t
		m_pdraw->DrawImage(m_nScreenNo, ((CSearchCopyDlg*)GetParent())->m_hMainLogoBitmap, 320, 240, 10, strText, FALSE); //t
	}
}


void CWindow::OperateImageAll(BOOL bfUpdate)
{
	POSITION	position = this->m_listOperationImage.GetHeadPosition();

	//GetRGBImage(TRUE);

	//while (position)
	//{
	//	COperateImage* pObject = (COperateImage*)this->m_listOperationImage.GetNext(position);

	//	switch (pObject->m_nOperation)
	//	{
	//	case OPERATE_IMAGE_BLUR:
	//		BlurImage(FALSE);
	//		break;
	//	case OPERATE_IMAGE_SHARPEN:
	//		SharpenImage(FALSE);
	//		break;
	//	case OPERATE_IMAGE_GRAY:
	//		GrayScaleImage(FALSE);
	//		break;
	//	case OPERATE_IMAGE_BRIGHTNESS:
	//		//			BrightenImage(FALSE);
	//		break;
	//	case OPERATE_IMAGE_INTENSITY:
	//		//			IntensityImage(FALSE);
	//		break;
	//	case OPERATE_IMAGE_COLORING:
	//		//			ColoringImage(FALSE);
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//int		tempBright = ((CSearchCopyDlg*)GetParent())->m_sldBrightPos;
	//int		tempContrast = m_pOwner->m_sldContrastPos / 36;
	//int		tempHue = m_pOwner->m_sldHuePos;

	//if (tempBright != 0)	BrightenImage(FALSE, tempBright);
	//if (tempContrast > 1)	IntensityImage(FALSE, tempContrast);
	//if (tempHue != 0)		ColoringImage(FALSE, tempHue);

	//t	if (bfUpdate == TRUE)
	//t	{
	//t		this->Invalidate(FALSE);
	//t	}
}


void CWindow::GetRGBImage(BOOL bfAlways)
{
	/*if (((CSearchCopyDlg*)GetParent())->m_iAdjustPressed == ID_BT_ADJUSTMENT || bfAlways == TRUE)
	{
		if (m_pImageYUV != NULL)
		{
			YUV422_RGB(m_pImageYUV, m_pOwner->m_pImageRGB, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, FALSE);
			memcpy(m_pOwner->m_pImageRGBColor, m_pOwner->m_pImageRGB, m_bmi.bmiHeader.biWidth * m_bmi.bmiHeader.biHeight * 3);
		}
	}*/
}

BEGIN_MESSAGE_MAP(CWindow, CButton)
END_MESSAGE_MAP()



// CWindow 메시지 처리기


