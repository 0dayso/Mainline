#include "StdAfx.h"
#include "RxADO.h"
#include <time.h>
#include "Global.h"

using namespace ADODB;

RxADO::RxADO(void)
{

}

RxADO::~RxADO(void)
{
	ExitConnect();
}

void RxADO::ExitConnect()
{
		// �رռ�¼�� 
	if (m_pRecordset != NULL  
		&& m_pRecordset->State != adStateClosed) 
	{ 
		m_pRecordset->Close(); 
		m_pRecordset = NULL; 
	} 
 
	// �ر����� 
	if(m_pConnection != NULL  
		&& m_pConnection->State == adStateOpen) 
	{ 
 
		m_pConnection->Close(); 
		m_pConnection = NULL; 
	} 
 
	// �ͷŻ��� 
	::CoUninitialize();
}


//�����ݿ�����
bool RxADO::InitADOConn(TCHAR* strConnection)
{
	::CoInitialize(NULL);
	m_pConnection=NULL;
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pConnection->ConnectionString=strConnection;
	
	try
	{
		m_pConnection->Open("","","",adCmdUnspecified);
	}
	catch(_com_error& e)
	{
		ErrorsPtr pErrors=m_pConnection->GetErrors();
		if (pErrors->GetCount()==0)
		{			
			Global::WriteLog(CLog(e.ErrorMessage()));
			return false;
		}
		else
		{
			for (int i=0;i<pErrors->GetCount();i++)
			{
				_bstr_t desc=pErrors->GetItem((long)i)->GetDescription();
				Global::WriteLog(CLog(desc.GetBSTR()));
				return false;
			}
		}
	}
	return true;
}



// ִ�в�ѯָ����ؼ�¼�� 
_RecordsetPtr&  RxADO::GetRecordSet(TCHAR* strConnection, TCHAR* bstrSQL)
{ 
	try 
	{ 
		// �������ݿ⣬���Connection����Ϊ�� 
		// ���ߴ��ڹر�״̬���������������ݿ� 
		if(m_pConnection == NULL  
			|| m_pConnection->State == adStateClosed) 
		{ 
			InitADOConn(strConnection); 
		} 
 
		// �رմ�ǰ�ļ�¼�� 
		if (m_pRecordset != NULL && m_pRecordset->State != adStateClosed) 
		{ 
			m_pRecordset->Close(); 
			m_pRecordset = NULL; 
		} 
 
		// ������¼������ 
		m_pRecordset.CreateInstance(__uuidof(Recordset)); 
		// ȡ�ñ��еļ�¼ 
		m_pRecordset->Open(bstrSQL, 
			m_pConnection.GetInterfacePtr(), 
			adOpenDynamic, 
			adLockOptimistic, 
			adCmdText); 
	} 
	// ��׽�쳣 
	catch(_com_error e) 
	{ 
		// ��ʾ������Ϣ 
		Global::WriteLog(CLog(e.ErrorMessage()));
	} 
	// ���ؼ�¼�� 
	return m_pRecordset; 
} 
 
 // ִ��SQL���� 
BOOL RxADO::ExecuteSQL(TCHAR* strConnection, TCHAR* bstrSQL)
{ 
	try 
	{ 
		_variant_t RecordsAffected;
		 RecordsAffected.vt = VT_I4;
		 RecordsAffected.intVal = 0;
		// �������ݿ⣬���Connection����Ϊ�� 
		// ���ߴ��ڹر�״̬���������������ݿ� 
		if(m_pConnection==NULL  
			|| m_pConnection->State == adStateClosed) 
		{ 
			InitADOConn(strConnection); 
		} 
		 
		// ִ������ 
		m_pConnection->Execute(bstrSQL,&RecordsAffected,adCmdText|adExecuteNoRecords); 
		return RecordsAffected.intVal; 
	} 
	// ��׽�쳣 
	catch(_com_error e) 
	{ 
		Global::WriteLog(CLog(e.ErrorMessage()));
		return FALSE; 
	} 
} 

//CString RxADO::VariantToCString(VARIANT var)
//{  
//	CString   strValue;  
//	_variant_t   var_t;  
//	_bstr_t   bst_t;
//
//	double dbRowID=0;
//
//	switch(var.vt)  
//	{  
//		case   VT_EMPTY:  
//		strValue="";  
//		break;  
//		case   VT_UI1:  
//		strValue.Format("%d",var.bVal);  
//		break;  
//		case   VT_I2:  
//		strValue.Format("%d",var.iVal);  
//		break;  
//		case   VT_I4:  
//		strValue.Format("%d",var.lVal);  
//		break;  
//		case  VT_R4:
//		strValue.Format("%0.2f",var.fltVal);  
//		break;
//		case  VT_R8:  		
//			strValue.Format("%0.2f",var.dblVal);  
//			break;  
//		case VT_DECIMAL:
//			{
//				dbRowID = var.decVal.Lo32;  
//				dbRowID *= (var.decVal.sign == 128)? -1 : 1;  
//				dbRowID /= pow(10.00, var.decVal.scale); 
//				strValue.Format("%0.2f",dbRowID);
//			}
//			break;
//		case  VT_CY:
//		strValue=COleCurrency(var).Format(0,MAKELCID(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SINGAPORE), SORT_DEFAULT));  
//		break;  
//		case  VT_BSTR:  
//		var_t=var;  
//		bst_t=var_t;  
//		strValue.Format("%s",(const char*)bst_t);  
//		break;  
//		case  VT_NULL:  
//		strValue="";  
//		break;  
//		case  VT_DATE: 
//		strValue=COleDateTime(var).Format("%Y-%m-%d %H:%M:%S");  
//		break;  
//		case  VT_BOOL:  
//		strValue.Format("%d",var.boolVal);  
//		break;  
//		default:  
//		strValue="";  
//		break;  
//	}  
//	return strValue;  
//   
//}   

double RxADO::VariantToDouble(VARIANT var)
{
	double dret=0;

	if (var.vt == VT_DECIMAL)
	{
		dret = var.decVal.Lo32;  
		dret *= (var.decVal.sign == 128)? -1 : 1;  
		dret /= pow(10.00, var.decVal.scale);		
	}
	return dret;
}

/*
**time_tתSYSTEMTIME
*/
SYSTEMTIME Time_tToSystemTime(time_t t)
{
	tm temptm = *localtime(&t);
	SYSTEMTIME st = { 1900 + temptm.tm_year,
		1 + temptm.tm_mon,
		temptm.tm_wday,
		temptm.tm_mday,
		temptm.tm_hour,
		temptm.tm_min,
		temptm.tm_sec,
		0 };
	return st;
}

/*
**time_tתSYSTEMTIME
*/
SYSTEMTIME TimetToSystemTime(time_t t)
{
	FILETIME ft;
	SYSTEMTIME pst;
	LONGLONG nLL = Int32x32To64(t, 10000000) + 116444736000000000;
	ft.dwLowDateTime = (DWORD)nLL;
	ft.dwHighDateTime = (DWORD)(nLL >> 32);
	FileTimeToSystemTime(&ft, &pst);
	return pst;
}
/*
**SYSTEMTIMEתtime_t
*/
time_t SystemTimeToTimet(SYSTEMTIME st)
{
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);
	LONGLONG nLL;
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	nLL = (ft.dwHighDateTime << 32) + ft.dwLowDateTime;
	time_t pt = (long)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
	return pt;
}
wstring RxADO::DateTimeToString(VARIANT var, TCHAR* szFormat)
{
	SYSTEMTIME st;
	if (var.vt != VT_DATE) return _T("");	
	if (!VariantTimeToSystemTime(var.date, &st)) return _T("");
	TCHAR szTime[11] = { 0 };
	_stprintf(szTime, szFormat, st.wYear,st.wMonth,st.wDay);
	return wstring(szTime);
}


_RecordsetPtr& RxADO::ExecuteCommand(TCHAR* strConnection, TCHAR* bstrSQL)
{
	try
	{
		HRESULT hr;
		// �������ݿ⣬���Connection����Ϊ�� 
		// ���ߴ��ڹر�״̬���������������ݿ� 
		if (m_pConnection == NULL
			|| m_pConnection->State == adStateClosed)
		{
			::CoInitialize(NULL);
			m_pConnection = NULL;
			hr = m_pConnection.CreateInstance("ADODB.Connection");//����Connection����
			hr =m_pConnection->Open(strConnection,"", "", adCmdUnspecified);
			
		}
		if (m_pCommand == NULL || m_pCommand->State==adStateClosed)
		{
			m_pCommand.CreateInstance("ADODB.Command");
			m_pCommand->ActiveConnection = m_pConnection;
		}

		m_pCommand->CommandText = _bstr_t(bstrSQL);

		// �رմ�ǰ�ļ�¼�� 
		if (m_pRecordset != NULL && m_pRecordset->State != adStateClosed)
		{
			m_pRecordset->Close();
			m_pRecordset = NULL;
		}
		VARIANT vtEmpty, vtEmpty2;
		m_pRecordset = m_pCommand->Execute(NULL,NULL, adCmdText);
	}
	// ��׽�쳣 
	catch (_com_error e)
	{
		// ��ʾ������Ϣ 
		Global::WriteLog(CLog(e.ErrorMessage()));
	}
	// ���ؼ�¼�� 
	return m_pRecordset;
}