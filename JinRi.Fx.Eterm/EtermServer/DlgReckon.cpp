// DlgReckon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EtermServer.h"
#include "DlgReckon.h"
#include "afxdialogex.h"


// CDlgReckon �Ի���

IMPLEMENT_DYNAMIC(CDlgReckon, CDialogEx)

CDlgReckon::CDlgReckon(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgReckon::IDD, pParent)
{

}

CDlgReckon::~CDlgReckon()
{
}

void CDlgReckon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgReckon, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgReckon ��Ϣ�������


void CDlgReckon::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static unsigned short inum = 10;

	CString strInfo;
	strInfo.Format(_T("��⵽��ͬ�˿ڵ�����������У��������%d���ڹرգ�"), inum);
	GetDlgItem(IDC_INFO)->SetWindowTextW(strInfo);	
	if (inum <= 0)
	{
		OnCancel();
	}
	inum--;

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CDlgReckon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTimer(1, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
