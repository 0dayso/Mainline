#pragma once
#include "Asyncsocketex.h"
#include "AsyncProxySocketLayer.h"
#include "AsyncSslSocketLayer.h"
#include <afxtempl.h>
#include <afxmt.h>
#include <sstream>

class CEtermSocket:
	public CAsyncSocketEx
{
public:
	typedef std::list<unsigned char*> t_HashList;	
	CEtermSocket();
	CEtermSocket(CRichEditCtrl *pResponse,t_HashList *pSslTrustedCertHashList);
	~CEtermSocket(void);

	BOOL AddSslCertHashToTrustedList(unsigned char * pHash);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CAsyncProxySocketLayer *m_pProxyLayer;
	CAsyncSslSocketLayer *m_pSslLayer;
	int OnLayerCallback(const CAsyncSocketExLayer *pLayer, int nType, int nParam1, int nParam2);	
	void SetSessionID(BYTE* btSessionID);
	void InitSocket(CRichEditCtrl *pResponse,t_HashList *pSslTrustedCertHashList);
	void ReleaseSocket(void);
	//���ʱ��
	CTime m_ActiveTime;
	CConfigure m_config;
	CEtermPacket m_EtermPacket;
public:
	bool UserLogin(CConfigure cfg);
	bool SendMsg(string sMsg);
	bool SendPrintMsg(string sMsg);	
	bool SendPNRMsg(string sMsg);
	deque<ClientData> ClientSocket;

	//�ͻ����ٽ���
	CCriticalSection m_cs;		
	CString m_strCmd;
	CString m_strResponse;
	HANDLE pEvent;
	HANDLE pReEvent;
	bool m_bRunXS;		//�Ƿ�����ִ��XSָ��
	BOOL SetKeepAlive();
	//EtermSocket״̬	
	int m_nState;		//-1���� 0��ʼ�� 1�ر����� 2��¼�ɹ� 3����ʧ��	5������
	CTime m_cmdTime;	//��ǰָ�񷢳�ʱ��
	int m_nSleep;		//�ȴ�
	float m_Rate;		//���ÿ�����

protected:
	void AddStringToLog(LPCTSTR pszString);
	t_HashList *m_pSslTrustedCertHashList;
	CRichEditCtrl *m_pResponse;	
	bool UpdateHeartWrap();
	
};
