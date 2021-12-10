#pragma once


// Split

class Split : public CWndObj
{
	DECLARE_DYNAMIC(Split)

public:
	Split();
	virtual ~Split();

	CBitmap* m_pbmpSplit;


protected:
	DECLARE_MESSAGE_MAP()
};


