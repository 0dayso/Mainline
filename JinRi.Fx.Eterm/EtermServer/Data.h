#pragma once

//���ظ�ʽ
enum RespnseFormat
{
	//�ı�
	text,
	//json��ʽ
	json
};

//��������
enum EtermLanguage
{
	//�ű�
	Script,
	//c#����
	CSharp,
	//c++
	CPP
};

class CData
{
public:
	CData();
	~CData();
	wstring ip;
	SOCKET sock;
	RespnseFormat format;
	EtermLanguage language;
	wstring config;
	wstring content;
	wstring source;
};

