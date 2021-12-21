#pragma once
#include "CWndObj.h"


// CameraGroup

class CameraGroup : public CWndObj
{
	DECLARE_DYNAMIC(CameraGroup)

public:
	CameraGroup();
	virtual ~CameraGroup();

protected:
	DECLARE_MESSAGE_MAP()
};


