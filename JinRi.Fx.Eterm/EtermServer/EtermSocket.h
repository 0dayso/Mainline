#pragma once
#include <list>
#include <deque>
#include "Config.h"
#include "EtermPacket.h"
#include "CAsyncSocketEx\AsyncSocketEx.h"
#include "CAsyncSocketEx\AsyncSslSocketLayer.h"
#include "CAsyncSocketEx\AsyncProxySocketLayer.h"
#include "LockEterm.h"
#include "Data.h"
#include "Script.h"
#include <mutex>
#include <condition_variable>

enum CONFIG_STATE
{
	ETERM_OVER = -1,		//���� 
	INIT = 0,				//��ʼ�� 
	CLOSE_CONN = 1,		//�ر����� 
	LOGIN_SUCCESS = 2,	//��¼�ɹ� 
	CONNECT_FAIL = 3,		//����ʧ��	
	CONNECTED = 5,			//������
	AVAILABLE=6              //��ǩ������
};

class CEtermSocket
	:public CAsyncSocketEx
{
public:
	typedef std::list<unsigned char*> t_HashList;
	CEtermSocket(void);
	CEtermSocket(CRichEditCtrl *pResponse, t_HashList *pSslTrustedCertHashList);
	void InitEtermSocket(CRichEditCtrl *pResponse, t_HashList *pSslTrustedCertHashList);
	void ReleaseEtermSocket();
	~CEtermSocket(void);

	BOOL AddSslCertHashToTrustedList(unsigned char * pHash);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CAsyncSslSocketLayer *m_pSslLayer;
	CAsyncProxySocketLayer *m_pProxyLayer;
	int OnLayerCallback(const CAsyncSocketExLayer *pLayer, int nType, int nParam1, int nParam2);
	void SetSessionID(BYTE* btSessionID);

	//���ʱ��
	CTime m_ActiveTime;
	Config m_config;
	CEtermPacket m_EtermPacket;
	deque<CData> clients;

	std::mutex              g_lockqueue;
	std::condition_variable g_queuecheck;
	bool                    g_notified;
	CLockEterm m_lock;			   //��������
public:
	bool UserLogin();
	bool SendMsg(string sMsg);
	bool SendPrintMsg(string sMsg, bool bEn = false);

	//�ͻ����ٽ���
	CCriticalSection m_cs;
	CCriticalSection m_configCS;
	CCriticalSection m_cmdCS;			 //ȡ�������ʱ����
	CCriticalSection m_reloadCS;
	deque<CScript> cmdlist;			 //�������

	CString m_strCmd;
	CString m_strResponse;
	HANDLE pEvent;
	HANDLE m_hNotify;			   //����ִ���¼�֪ͨ
	bool m_bRunXS;		//�Ƿ�����ִ��XSָ��
	BOOL SetKeepAlive();
	//EtermSocket״̬	
	CONFIG_STATE m_nState;		//-1���� 0��ʼ�� 1�ر����� 2��¼�ɹ� 3����ʧ��	5������ 6����ʹ��
	CTime m_cmdTime;	//��ǰָ�񷢳�ʱ��
	CTime m_lastReboot;	//�ϴ�����ʱ��
	//float m_Rate;		//���ÿ�����

protected:
	void AddStringToLog(LPCTSTR pszString);
	t_HashList *m_pSslTrustedCertHashList;
	CRichEditCtrl *m_pResponse;
private:
	void UsasToGb(byte& c1, byte& c2);
	void GetCmd(string smsg, BYTE* btCmd, int& nlen);
};

