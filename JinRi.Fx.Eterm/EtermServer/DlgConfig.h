#pragma once
#include "afxwin.h"
#include "Config.h"

// CDlgConfig �Ի���

class CDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConfig();

// �Ի�������
	enum { IDD = IDD_DLG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	bool m_bEdit;
	void InitControl();
	virtual BOOL OnInitDialog();
	CComboBox m_cmbServer;
	CComboBox m_cmbType;
	Config* m_config;
	afx_msg void OnBnClickedSecret();
	afx_msg void OnBnClickedOk();
};
