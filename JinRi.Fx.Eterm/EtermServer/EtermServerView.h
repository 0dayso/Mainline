
// EtermServerView.h : CEtermServerView ��Ľӿ�
//

#pragma once
#include "EtermSocket.h"
#include "EtermServerDoc.h"
#include <memory>
#include <deque>
#include "Data.h"

class CEtermServerCntrItem;

class CEtermServerView : public CRichEditView
{
protected: // �������л�����
	CEtermServerView();
	DECLARE_DYNCREATE(CEtermServerView)

// ����
public:
	CEtermServerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CEtermServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	void InitControl(void);
	COLORREF m_backcolor;
	COLORREF m_forecolor;
	LOGFONT  m_font;
	int      m_fontHeight;

	
	DECLARE_MESSAGE_MAP()
public:	
			
	typedef std::list<unsigned char *> t_HashList;
	t_HashList m_SslTrustedCertHashList;
	afx_msg void OnBackground();
	afx_msg void OnForcolor();
	afx_msg void OnFontSet();
	void OnSendMsg();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT ConnectServer(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVerifyCert(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SystemCommand(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // EtermServerView.cpp �еĵ��԰汾
inline CEtermServerDoc* CEtermServerView::GetDocument() const
   { return reinterpret_cast<CEtermServerDoc*>(m_pDocument); }
#endif

