#pragma once

// CSkinVerticleScrollbar

class CSkinVerticleScrollbar : public CStatic
{
	DECLARE_DYNAMIC(CSkinVerticleScrollbar)

public:
	CSkinVerticleScrollbar();
	virtual ~CSkinVerticleScrollbar();
	int m_nThumbTop;
	void Init(void);
	void UpdateThumbPosition();
	void LimitThumbPosition();
	void Draw();

	double m_dbThumbInterval;

private:
	CRect		m_rectVScrollUp;
	CRect		m_rectVScrollDown;
	CRect		m_rectVScrollThumb;
	CRect		m_rectVScrollSpan;

	CBitmap		m_bmVScrollUp;
	CBitmap		m_bmVScrollDown;
	CBitmap		m_bmVScrollThumb;
	CBitmap		m_bmVScrollSpan;

protected:
	DECLARE_MESSAGE_MAP()
};


