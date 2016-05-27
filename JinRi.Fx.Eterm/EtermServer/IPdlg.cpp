// IPdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EtermServer.h"
#include "IPdlg.h"
#include "afxdialogex.h"
#include "limitIP.h"
#include "lip.h"
#include "Global.h"
#include <algorithm>

// CIPdlg �Ի���

IMPLEMENT_DYNAMIC(CIPdlg, CDialogEx)

CIPdlg::CIPdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIPdlg::IDD, pParent)
{

}

CIPdlg::~CIPdlg()
{
}

void CIPdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


BEGIN_MESSAGE_MAP(CIPdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CIPdlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CIPdlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CIPdlg::OnBnClickedButtonModify)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CIPdlg::OnLvnItemchangedList)
END_MESSAGE_MAP()


// CIPdlg ��Ϣ�������


void CIPdlg::OnBnClickedButtonAdd()
{
	CString strIP, strRemark;
	GetDlgItem(IDC_EDIT_IP)->GetWindowText(strIP);
	strIP = strIP.Trim();
	if (strIP.IsEmpty())
	{
		MessageBox(_T("IP��ַ����Ϊ�գ�������IP��ַ��"), _T("Eterm������"), MB_OK | MB_ICONEXCLAMATION);
		GetDlgItem(IDC_EDIT_IP)->SetFocus();
		return;
	}
	GetDlgItem(IDC_EDIT_REMARK)->GetWindowText(strRemark);

	limitIP lipd;
	if (lipd.AppendIP(strIP, strRemark))
	{
		int i = m_list.GetItemCount();
		m_list.InsertItem(i, strIP);
		m_list.SetItemText(i, 1, strRemark);

		Global::cs_ip.Lock();
		lip ip;
		ip.szIP = strIP;
		ip.remark = strRemark;
		auto it = find_if(Global::iplist.begin(), Global::iplist.end(), [=](lip _ip){ return ip.szIP == _ip.szIP; });
		if (it == Global::iplist.end())
			Global::iplist.push_back(ip);
		Global::cs_ip.Unlock();

		TCHAR buf[255] = { 0 };
		_stprintf(buf, _T("IP�б�[%d]"), m_list.GetItemCount());
		GetDlgItem(IDC_INFO)->SetWindowText(buf);
	}
	else
	{
		MessageBox(_T("���IPʧ�ܣ���������IP"), _T("Eterm������"), MB_OK | MB_ICONEXCLAMATION);
	}
}


void CIPdlg::OnBnClickedButtonDelete()
{
	CString strIP;
	GetDlgItem(IDC_EDIT_IP)->GetWindowText(strIP);
	strIP = strIP.Trim();
	if (strIP.IsEmpty())
	{
		MessageBox(_T("IP��ַ����Ϊ�գ�������IP��ַ��"), _T("Eterm������"), MB_OK | MB_ICONEXCLAMATION);
		GetDlgItem(IDC_EDIT_IP)->SetFocus();
		return;
	}

	if (MessageBox(_T("���Ƿ���Ҫɾ��[") + strIP + _T("]���IP��"), _T("����Eterm������"), MB_YESNO | MB_ICONINFORMATION) == IDNO)
		return;

	limitIP lipd;
	if (lipd.DeleteIP(strIP))
	{
		LVFINDINFO fi;
		fi.flags = LVFI_STRING;
		fi.psz = strIP;
		int nPos = m_list.FindItem(&fi);

		if (nPos != -1)
		{
			m_list.DeleteItem(nPos);

			Global::cs_ip.Lock();
			lip ip;
			ip.szIP = strIP;
			auto it = find_if(Global::iplist.begin(), Global::iplist.end(), [=](lip _ip){ return ip.szIP == _ip.szIP; });
			if (it != Global::iplist.end())
				Global::iplist.erase(it);
			Global::cs_ip.Unlock();

			TCHAR buf[255] = { 0 };
			_stprintf(buf, _T("IP�б�[%d]"), m_list.GetItemCount());
			GetDlgItem(IDC_INFO)->SetWindowText(buf);
		}
	}
	else
	{
		MessageBox(_T("ɾ��IPʧ��"), _T("Eterm������"), MB_OK | MB_ICONEXCLAMATION);
	}
}


void CIPdlg::OnBnClickedButtonModify()
{
	CString strIP, strRemark;
	GetDlgItem(IDC_EDIT_IP)->GetWindowText(strIP);
	strIP = strIP.Trim();
	if (strIP.IsEmpty())
	{
		MessageBox(_T("IP��ַ����Ϊ�գ�������IP��ַ��"), _T("Eterm������"), MB_OK | MB_ICONEXCLAMATION);
		GetDlgItem(IDC_EDIT_IP)->SetFocus();
		return;
	}
	GetDlgItem(IDC_EDIT_REMARK)->GetWindowText(strRemark);

	limitIP lipd;
	if (lipd.UpdateIP(strIP, strRemark))
	{	
		LVFINDINFO fi;
		fi.flags = LVFI_STRING;
		fi.psz = strIP;
		int nPos = m_list.FindItem(&fi);
		if (nPos != -1)
		{
			m_list.SetItemText(nPos, 1, strRemark);
		}
		Global::cs_ip.Lock();
		lip ip;
		ip.szIP = strIP;
		ip.remark = strRemark;
		auto it = find_if(Global::iplist.begin(), Global::iplist.end(), [=](lip _ip){ return ip.szIP == _ip.szIP; });
		if (it == Global::iplist.end())
			Global::iplist.push_back(ip);
		else
			*it = ip;
		Global::cs_ip.Unlock();
	}
	else
	{
		MessageBox(_T("IP��ַ����ʧ��"), _T("����Eterm�����"), MB_OK | MB_ICONWARNING);
	}
		
}


BOOL CIPdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("IP��ַ"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("��ע��Ϣ"), LVCFMT_LEFT, 400);

	limitIP lipd;
	vector<lip> lips = lipd.GetIPList();
	for (int i = 0; i < lips.size();i++)
	{
		m_list.InsertItem(i,lips[i].szIP);
		m_list.SetItemText(i, 1, lips[i].remark);
	}

	TCHAR buf[255] = { 0 };
	_stprintf(buf, _T("IP�б�[%d]"), m_list.GetItemCount());
	GetDlgItem(IDC_INFO)->SetWindowText(buf);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CIPdlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	CString strIP = m_list.GetItemText(pNMLV->iItem, 0);
	CString strRemark = m_list.GetItemText(pNMLV->iItem, 1);

	GetDlgItem(IDC_EDIT_IP)->SetWindowText(strIP);
	GetDlgItem(IDC_EDIT_REMARK)->SetWindowText(strRemark);

	*pResult = 0;
}
