#pragma once
class Proxy
{
public:
	Proxy();
	~Proxy();

	//�������� 0.��ʹ�ô��� 1.SOCKS4 2.SOCKS4A 3.SOCKS5 4.HTTP11
	int type;
	wstring host;
	unsigned int port;
	wstring user;
	wstring pwd;
};

