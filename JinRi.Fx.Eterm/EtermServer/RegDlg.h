#pragma once


// CRegDlg �Ի���

class CRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegDlg)

public:
	CRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_REG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	virtual void OnCancel();
};
