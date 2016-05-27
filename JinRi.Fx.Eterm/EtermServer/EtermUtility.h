#pragma once
class EtermUtility
{
public:
	EtermUtility();
	~EtermUtility();

	enum CmdType
	{
		/// <summary>
		/// ��λ
		/// </summary>
		SS = 0,
		/// <summary>
		/// P�ؼ�
		/// </summary>
		SSPAT = 1,
		/// <summary>
		/// RT����
		/// </summary>
		RT = 2,
		/// <summary>
		/// RT+PAT ���˱���
		/// </summary>
		RT_PAT = 3,
		/// <summary>
		/// RT+PAT *CH ��ͯ����
		/// </summary>
		RT_PATCH = 4,
		/// <summary>
		/// RT+PAT *INF ���˱���
		/// </summary>
		RT_PATINF,
		/// <summary>
		/// DETR�����
		/// </summary> 
		DETR_CN,
		/// <summary>
		/// DETRƱ�� ��Ʊ��״̬
		/// </summary> 
		DETR_TN,
		/// <summary>
		/// DETRƱ��,S
		/// </summary> 
		DETR_TNS,
		/// <summary>
		/// DETRƱ��,F
		/// </summary> 
		DETR_TNF,
		/// <summary>
		/// DETRƱ��,H ��Ʊ����ʷ��¼
		/// </summary> 
		DETR_TNH,
		/// <summary>
		/// ��Ȩ
		/// </summary>
		RMK,
		/// <summary>
		/// ������
		/// </summary>
		XEPNR
	};

	enum ConfigState
	{
		/// <summary>
		/// ������
		/// </summary>
		connect,
		/// <summary>
		/// ���ӹر�
		/// </summary>
		disconnect,
		/// <summary>
		/// ����
		/// </summary>
		suspend
	};

	//����
	CmdType Utility;

	//�����ַ
	CString ServerUrl;

	//OfficeNo
	CString OfficeNo;

	//��ǰ״̬
	ConfigState State;

};

