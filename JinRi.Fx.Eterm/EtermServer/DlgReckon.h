#pragma once


// CDlgReckon �Ի���

class CDlgReckon : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReckon)

public:
	CDlgReckon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgReckon();

// �Ի�������
	enum { IDD = IDD_DLG_RECKON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
