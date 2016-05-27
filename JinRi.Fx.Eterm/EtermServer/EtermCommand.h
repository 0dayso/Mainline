#pragma once
#include <list>
#include <map>
#include "EtermPacket.h"

enum ETERM_STATE
{
	NONE,							//δ֪����
	NO_FIND_CONFIG,					//û�з��ֿ�������
	CONFIG_INVALID,					//���ò�����
	CONFIG_LOCKED,					//��ǰ����������
	STRING_FORMAT,					//wstring�����������
	INT_FORMAT,						//int�����������
	FLOAT_FORMAT,					//float�����������
	LIST_FORMAT,					//list�����������
	SET_VALUE,						//���ñ���ʧ��
	INVALID_BUSINESS,				//��Ч��ҵ������
	NONE_TYPE,						//δ֪������
	FUN_SUC,						//�������óɹ�
	SEND_FAIL,						//����Eterm����ʧ��
	SUCCESS							//�ɹ�		
};

struct EtermDATA
{
	EtermDATA(wstring _cmd,wstring _rec)
	{
		cmd = _cmd;
		rec = _rec;
		time = CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	}
	wstring time;    //ʱ��  
	wstring cmd;		//����
	wstring rec;		//����	
};

struct PARAM
{
	PARAM()
	{
		ival = 0;
		fval = 0;
		type = 0;
	}
	wstring key;
	wstring sval;
	int     ival;
	float   fval;
	vector<wstring> lval;
	int     type;			//1 wstring 2int 3float 4list<wstring>
};

struct FUN
{
	vector<wstring> sources;
	vector<PARAM> params;		
};

struct FOR
{
	FOR()
	{		
		bif = false;		
		ns = 0;
		ne = 0;
	}	
	int ns;
	int ne;
	bool bif;
	wstring step;
	wstring sif;
	wstring sinit;
};

class CEtermCommand
{
public:
	CEtermCommand(void);
	~CEtermCommand(void);
	std::map<wstring,wstring> stringMap;
	std::map<wstring,int>    intMap;
	std::map<wstring,float>  floatMap;	
	std::map<wstring, vector<wstring>> listMap;
	std::map<wstring, FUN> funMap;
	wstring strDATA;
	ETERM_STATE ScanSourceCode(wstring sourceCode);
	bool syntaxcheck(wstring sline,wstring type);
	bool syntaxcheck(wstring& strErr);
	bool analyseIF(wstring sline);
	void InputSourceCode(const TCHAR* szFile);

	wstring m_sret;			//��������
	wstring m_config;		//����
	SOCKET m_sock;			//�ͻ���
private:
	bool Judge(wstring left,wstring right,int bEqual);	//== != > <
	bool InitConfig(TCHAR* szConfig);
	void SetValue(wstring left,wstring right);
	wstring get_system(wstring sline, int& nwait);
	wstring get_return(wstring sline);
	void ret(wstring sline);
	wstring FindStr(wstring sitem);
	wstring Replace(wstring sline);
	wstring Format(wstring sline);
	wstring getparams(wstring szData);
	vector<wstring> getParams(wstring sline);
	vector<wstring> FindStrs(wstring sitem);
	wstring SubStr(wstring sitem);
	FUN InitFun(wstring sline, vector<wstring> codelist, int& i);
	vector<wstring> codelist;	
	vector<EtermDATA> etermData;
	map<wstring,int> steplist;

	bool SetVal(wstring left, wstring right, wstring sline, vector<wstring> codelist, int i);

	int intValue(wstring right);
	float floatValue(wstring right);

	ETERM_STATE function(FUN fun, int type, wstring& sret, int& iret, float& fret, vector<wstring>& listret);
	wstring SetintVal(wstring sline);
	bool Using(wstring sline);
	bool Invoke(wstring sline);
	CMD_TYPE cmdType(wstring& cmd,bool& bEn);
	//int maxStep;
	int curStep;
	map<int,FOR> m_fors;
	wstring GetListValue(wstring sline);
};

