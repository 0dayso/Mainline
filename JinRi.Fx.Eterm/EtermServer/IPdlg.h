#pragma once
#include "afxcmn.h"


// CIPdlg �Ի���

class CIPdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIPdlg)

public:
	CIPdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIPdlg();

// �Ի�������
	enum { IDD = IDD_DLG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonModify();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
};
