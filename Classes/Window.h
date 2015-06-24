#pragma once

#include "Widget.h"
#include "Manager.h"
#include "Geometry.h"

class CxImage;

namespace wui{

class WIDGETUI_API Window : public Widget
{
public:
	Window(Widget *pOwner, const TopLevelDescription &description);
	Window(Manager *pManager, const TopLevelDescription &description);
	virtual ~Window(void);
	
	std::string GetTitle() const;
	bool IsMinimized() const;
	bool IsMaximized() const;
	Size GetPreferredSize();
	Rect GetClientArea() const;
	bool GetDraggable() const;

	void SetTitle(const std::string &str);
	void BringToFront();
	void SetDraggable(bool enable = true);
	
	void SetBkCenterImage(CxImage* pImage);
	void SetBorderTLImage(CxImage* pImage);
	void SetBorderTMImage(CxImage* pImage);
	void SetBorderTRImage(CxImage* pImage);
	void SetBorderLImage(CxImage* pImage);
	void SetBorderRImage(CxImage* pImage);
	void SetBorderBLImage(CxImage* pImage);
	void SetBorderBMImage(CxImage* pImage);
	void SetBorderBRImage(CxImage* pImage);
	void SetCloseBtnImage(CxImage* pImage);
	void SetCloseBtnRect(Rect rc);
	
protected:
	void CheckMoveWindow(Message &msg);
	virtual void RenderCaption(XGraphics& graphic, const Rect &rcUpdate);

	void OnProcessMessage(Message &msg);
	void OnRender(XGraphics& graphic, const Rect &rcUpdate);
	void OnStyleChanged();
	void OnResized();

protected:
	std::string m_strTitle;
	HFONT m_pFont;
	COLORREF m_TextColor;
	bool m_bDrawDecorations;
	bool m_bShowTitle;
	
	bool m_bDragStart;
	POINT m_lastMousePos;
	
	bool m_bDraggable;
	
	int m_nCaptionHeight;
	Rect m_rcCloseButton;
	bool m_bCloseBtnPressed;
	bool m_bCloseBtnHot;
	
	CxImage* m_pImageBtnClose;					// �رհ�ť	
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