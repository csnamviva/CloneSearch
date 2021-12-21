#pragma once

#include "CWndObj.h"

// CLogViewer

class CLogViewer : public CWndObj
{
	DECLARE_DYNAMIC(CLogViewer)

public:
	CLogViewer();
	virtual ~CLogViewer();

protected:
	DECLARE_MESSAGE_MAP()
};


