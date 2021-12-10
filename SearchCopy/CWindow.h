#pragma once

#include "CDrawVideoClass.h"
// CWindow

class CWindow : public CButton
{
	DECLARE_DYNAMIC(CWindow)

public:
	CWindow();
	virtual ~CWindow();
	static CDrawVideoClass* m_ddraw;

	void FlushBuffer(void);

	BOOL				m_bShow;


protected:
	DECLARE_MESSAGE_MAP()
};


