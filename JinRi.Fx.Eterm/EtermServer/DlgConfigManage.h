#pragma once
#include "afxwin.h"
#include "EtermConfigData.h"
#include "xmlHelper.h"
// CDlgConfigManage �Ի���

class CDlgConfigManage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfigManage)

public:
	CDlgConfigManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConfigManage();

// �Ի�������
	enum { IDD = IDD_DLG_UTILITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitControl();
	void GetXmlData();
	void InitUntility(CString types=_T(""));
	void InitAircom(CString strAllow = _T(""), CString strNoAllow = _T(""));
	CComboBox m_cmbEtermLevel;
	EtermConfig* config;
	afx_msg void OnBnClickedButtonOperator();
};
