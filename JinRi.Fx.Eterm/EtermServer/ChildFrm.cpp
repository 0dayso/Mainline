
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "EtermServer.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


void CChildFrame::OnClose()
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain)
	{
		LVFINDINFO info;
		info.flags = LVFI_STRING;
		info.psz = GetActiveView()->GetDocument()->GetTitle();
		int nIndex=pMain->m_wndConfigureListBar.m_ConfigureList.FindItem(&info);
		if (nIndex == -1)
		{
			CMDIChildWndEx::OnClose();
		}
		return;
	}

	CMDIChildWndEx::OnClose();
}
