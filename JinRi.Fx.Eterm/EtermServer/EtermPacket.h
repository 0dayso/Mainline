#pragma once

//������
enum PACKET_TYPE
{
	UNHNOWN,	//δ֪��
	LOGIN,		//��¼��
	SEND,		//���Ͱ�
	RECIVE,		//���հ�
	HALF,		//������ݰ�
	COMPLETE	//������
};

enum CMD_TYPE
{
	normal,			//��ͨ����
	print,			//��ӡ����
	xs,				//XSָ��
	pnr,			//PNR
	login
};

class CEtermPacket
{
public:
	CEtermPacket(void);
	~CEtermPacket(void);
public:
	byte SID;						//����SID
	byte RID;						//����RID
	int  nPacketLength;				//������
	int	 nPatcketTotalLength;		//���ܳ���
	int  m_nFirstLegnth;			//��ʼ����
	int  m_unlessLength;			//δβ����
	PACKET_TYPE		m_pt;			//������
	CMD_TYPE		m_cmdType;		//��������
	vector<CString> m_vecRev;		//�������ݼ���	
	CString         m_cmd;			//���͵�����
	CString         m_strResponse;	//��ǰ���յ�������
	//��֤���ݰ�����Ч��
	bool ValidatePakcet(byte* lpBuf,int nlen);
	//�������ݰ������ؽ��
	void ParseData(BYTE* pData,int nSize);
private:
	//���ݰ�����
	void UnPacket(CString& buffer);
	//���ֱ���
	void UsasToGb(byte& c1,byte& c2);
	void PrintParse();
	void xsParse();
	void ParseHZ(BYTE* pData, char* szHZ);
	BYTE* m_btye;
};

