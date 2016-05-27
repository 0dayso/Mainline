#pragma once
#include <string>

#import "msado15.dll" rename ("EOF", "adoEOF") rename ("BOF","adoBOF")
#import "msjro.dll" rename("ReplicaTypeEnum", "_ReplicaTypeEnum") 

using namespace ADODB;

class RxADO
{
public:
	RxADO(void);
	~RxADO(void);
public:
	void ExitConnect();	
	bool InitADOConn(TCHAR* strConnection);
	//��¼��
	_RecordsetPtr pRecordset;
	// ִ�в�ѯָ����ؼ�¼�� 
	_RecordsetPtr& GetRecordSet(TCHAR* strConnection, TCHAR* bstrSQL);
	//ִ�� Command
	_RecordsetPtr& ExecuteCommand(TCHAR* strConnection, TCHAR* bstrSQL);
	// ִ��SQL���� 
	BOOL ExecuteSQL(TCHAR* strConnection, TCHAR* bstrSQL);
	//��ȡ����ָ��
	_ConnectionPtr GetConnection(){return m_pConnection;}
public:
	//static CString VariantToCString(VARIANT var);
	double VariantToDouble(VARIANT var); 
	std::wstring DateTimeToString(VARIANT var,TCHAR* szFormat);
private:	
	// ָ��Connection�����ָ��: 
	_ConnectionPtr m_pConnection; 
	// ָ��Recordset�����ָ��: 
	_RecordsetPtr m_pRecordset; 
	//ָ��Command�����ָ��
	_CommandPtr m_pCommand;
};
