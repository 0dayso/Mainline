#pragma once

enum Protocol
{
	GET,
	POST
};

class CHttpParse
{
public:
	CHttpParse();
	~CHttpParse();
	Protocol proto;				//Э��	
	string Content;			//http����
	int   nLen;					//post���ݳ���
	string PostData;			//post����	
	bool httpParse(char* pVoid,long len);
};

