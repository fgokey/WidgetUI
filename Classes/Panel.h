#pragma once

#include "Widget.h"
#include "Geometry.h"

class CxImage;

namespace wui{

class WIDGETUI_API Panel : public Widget
{
public:
	Panel(Widget *pParent);
	virtual ~Panel(void);

	Size GetPreferredSize();
	
	void SetBkCenterImage(CxImage* pImage);
	void SetBorderTLImage(CxImage* pImage);
	void SetBorderTMImage(CxImage* pImage);
	void SetBorderTRImage(CxImage* pImage);
	void SetBorderLImage(CxImage* pImage);
	void SetBorderRImage(CxImage* pImage);
	void SetBorderBLImage(CxImage* pImage);
	void SetBorderBMImage(CxImage* pImage);
	void SetBorderBRImage(CxImage* pImage);

private:
	void OnRender(XGraphics& graphic, const Rect &rcUpdate);
	
private:
	CxImage* m_pImageBorderTL;					// ���Ͻ�ͼƬ
	CxImage* m_pImageBorderTM;					// �ϱ���ͼƬ
	CxImage* m_pImageBorderTR;					// ���Ͻ�ͼƬ
	CxImage* m_pImageBorderBL;					// ���½�ͼƬ
	CxImage* m_pImageBorderBM;					// ���б�ͼƬ
	CxImage* m_pImageBorderBR;					// ���½�ͼƬ
	CxImage* m_pImageBorderL;					// ��߿�ͼƬ
	CxImage* m_pImageBorderR;					// �ұ߿�ͼƬ
	CxImage* m_pImageBackCenter;				// �м�ͼƬ
};
}
