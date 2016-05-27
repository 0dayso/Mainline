#include "StdAfx.h"
#include "GetHDSerial.h"

#pragma warning(disable: 4996)

//����ȫ�ֱ���
char m_buffer[256];
WORD m_serial[256];
DWORD m_OldInterruptAddress;
DWORDLONG m_IDTR;

#define IsChar(c) (c>=48&&c<=57)||(c>=65&&c<=90) ||(c>=97&&c<=122)

/*	���ܣ��ȴ�Ӳ�̿���
����ֵ��Static unsigned int
*/
static unsigned int WaitHardDiskIdle()
{
	BYTE byTemp;
Waiting:
	_asm
	{
		mov dx, 0x1f7
		in al, dx
		cmp al, 0x80
		jb EndWaiting
		jmp Waiting
	}
EndWaiting:
	_asm
	{
		mov byTemp, al
	}
	return byTemp;
}

/*
���ܣ��жϽ���
����ֵ��void
*/
void _declspec(naked)InterruptProcess(void)
{
	int byTemp;
	int i;
	WORD temp;
	//����Ĵ���ֵ
	_asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
	}

	WaitHardDiskIdle();	//�ȴ�Ӳ�̿���״̬
	__asm
	{
		mov dx, 0x1f6
		mov al, 0xa0
		out dx, al
	}
	byTemp = WaitHardDiskIdle();	//��ֱ����Ring3��ִ�еȴ�����������ѭ��
	if ((byTemp & 0x50) != 0x50)
	{
		_asm	//�ָ��ж��ֳ����˳� �жϷ������
		{
			pop esi
			pop edx
			pop edx
			pop ebx
			pop eax
			iretd
		}
	}

	_asm
	{
		mov dx, 0x1f6	//������Ʒ1f6,ѡ��������0
		{
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			iretd
		}
	}
	//��ȡӲ�̲�ڵ�ȫ����Ϣ
	for (i = 0; i<256; i++)
	{
		_asm
		{
			mov dx, 0x1f0
			in ax, dx
			mov temp, ax
		}
		m_serial[i] = temp;
	}
	_asm
	{
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		iretd
	}
}

CGetHDSerial::CGetHDSerial(void)
{
}

CGetHDSerial::~CGetHDSerial(void)
{
}

/*
���ܣ�Window0x/MEϵ���¶�ȡӲ�����к�
*/
void _stdcall CGetHDSerial::Win9xReadHDSerial(WORD* buffer)
{
	int i;
	for (i = 0; i<256; i++)
		buffer[i] = 0;
	_asm
	{
		push eax
		//��ȡ�޸��жϵ��ж����������ж��ţ���ַ
		sidt m_IDTR
		mov eax, dword ptr[m_IDTR + 02h]
		add eax, 3 * 08h + 04h
		cli
		//����ԭ�ȵ��ж���ڵ�ַ
		push ecx
		mov ecx, dword ptr[eax]
		mov cx, word ptr[eax - 04h]
		mov dword ptr m_OldInterruptAddress, ecx
		pop ecx
		//�����޸ĵ��ж���ڵ�ַΪ�µ��жϴ��������ڵ�ַ
		push ebx
		lea ebx, InterruptProcess
		mov word ptr[eax + 04h], bx
		shr ebx, 10h
		mov word ptr[eax + 02h], cx
		pop ecx
		//ִ���жϣ�ת��Ring 0
		int 3h
		//�ָ�ԭ�ȵ��ж���ڵ�ַ
		push ecx
		mov ecx, dword ptr m_OldInterruptAddress
		mov word ptr[eax - 04h], cx
		shr ecx, 10h
		mov word ptr[eax + 02h], cx
		pop ecx
		sti
		pop eax
	}
	for (i = 0; i<256; i++)
		buffer[i] = m_serial[i];
}

/*
���ܣ����ͺͻ�ȡ����˼����Ӳ�����к�
����ֵ�����óɹ�����TRUE,���򷵻�FALSE
*/
char* CGetHDSerial::GetHDSerial()
{
	m_buffer[0] = '\n';
	//�õ���ǰ����ϵͳ�汾
	OSVERSIONINFO OSVersionInfo;
	OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSVersionInfo);
	if (OSVersionInfo.dwPlatformId != VER_PLATFORM_WIN32_NT)
	{
		//Window9x/Me�¶�ȡӲ�����к�
		WORD m_wWin9xHDSerial[256];
		Win9xReadHDSerial(m_wWin9xHDSerial);
		strcpy(m_buffer, WORDToChar(m_wWin9xHDSerial, 10, 19));
	}
	else
	{
		//Windows NT/2000/XP �¶�ȡӲ�����к�
		DWORD m_wWinNTHDSerial[256];
		//�ж��Ƿ���SCSIӲ��
		if (!WinNTReadIDEHDSerial(m_wWinNTHDSerial))
			WinNTReadSCSIHDSerial(m_wWinNTHDSerial);
		strcpy(m_buffer, DWORDToChar(m_wWinNTHDSerial, 10, 19));
	}

	char szBuf[255] = { 0 };
	int ii = 0;
	for (int i = 0; i < strlen(m_buffer);i++)
	if (IsChar(m_buffer[i]))
		szBuf[ii++] = m_buffer[i];
	szBuf[ii++] = 0;
	if (strlen(szBuf) <5)
	{
		DWORD dw = GetCPUID();
		sprintf(szBuf, "%d", dw);
	}
	strcpy(m_buffer, szBuf);
	return m_buffer;
}

/*
���ܣ�Windows 9x/MEϵͳ�£���������(WORD)��Ӳ����Ϣת��Ϊ�ַ�����(char)
*/
char* CGetHDSerial::WORDToChar(WORD diskdata[256], int firstIndex, int lastIndex)
{
	static char string[1024];
	int index = 0;
	int position = 0;
	//���ո��ֽ���ǰ�����ֽ��ں��˳���ַ����ַ�����diskdata�����ݴ��뵽�ַ���string��
	for (index = firstIndex; index <= lastIndex; index++)
	{
		//�������еĸ��ֽ�
		string[position] = (char)(diskdata[index] / 256);
		position++;
		//�������еĵ��ֽ�
		string[position] = (char)(diskdata[index] % 256);
		position++;
	}
	//����ַ���������־
	string[position] = '\0';
	//ɾ���ַ����пո�
	for (index = position - 1; index>0 && ' ' == string[index]; index--)
		string[index] = '\0';

	return string;
}

/*
���ܣ�Window NT/2000/XPϵͳ�£���˫�����ͣ�DWORD)��Ӳ����Ϣת��Ϊ�ַ�����(char)
*/
char* CGetHDSerial::DWORDToChar(DWORD diskdata[256], int firstIndex, int lastIndex)
{
	static char string[1024];
	int index = 0;
	int position = 0;

	//���ո��ֽ���ǰ�����ֽ��ں��˳��˫�ֽ��еĵ��ִ��뵽�ַ���string��
	for (index = firstIndex; index <= lastIndex; index++)
	{
		//��������еĸ��ֽ�
		string[position] = (char)(diskdata[index] / 256);
		position++;
		//��������еĵ��ֽ�
		string[position] = (char)(diskdata[index] % 256);
		position++;
	}

	//����ַ���������־
	string[position] = '\0';

	//ɾ���ַ����пո�
	for (index = position - 1; index>0 && ' ' == string[index]; index--)
		string[index] = '\0';
	return string;
}

/*
���ܣ�Windows NT/2000/xpϵͳ�¶�ȡSCSIӲ�����к�
*/
BOOL CGetHDSerial::WinNTReadSCSIHDSerial(DWORD* buffer)
{
	buffer[0] = '\n';
	int controller = 0;
	HANDLE hScsiDriveIOCTL = 0;
	char driveName[256];
	sprintf(driveName, "\\\\.\\Scsi%d:", controller);
	//Windows NT/2000/xp ���κ�Ȩ�޶����Խ���
	hScsiDriveIOCTL = CreateFileA(driveName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
	{
		int drive = 0;
		DWORD dummy;
		for (drive = 0; drive<2; drive++)
		{
			char buffer[sizeof(SRB_IO_CONTROL)+SENDIDLENGTH];
			SRB_IO_CONTROL *p = (SRB_IO_CONTROL*)buffer;
			SENDCMDINPARAMS* pin = (SENDCMDINPARAMS*)(buffer + sizeof(SRB_IO_CONTROL));
			//׼������
			memset(buffer, 0, sizeof(buffer));
			p->HeaderLength = sizeof(SRB_IO_CONTROL);
			p->Timeout = 10000;
			p->Length = SENDIDLENGTH;
			p->ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
			strncpy((char*)p->Signauture, "SCSIDISK", 8);
			pin->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
			pin->bDriveNumber = drive;
			//�õ�SCSIӲ����Ϣ
			if (DeviceIoControl(hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT,
				buffer,
				sizeof(SRB_IO_CONTROL)+sizeof(SENDCMDINPARAMS)-1,
				buffer,
				sizeof(SRB_IO_CONTROL)+SENDIDLENGTH,
				&dummy, NULL))
			{
				SENDCMDOUTPARAMS* pOut = (SENDCMDOUTPARAMS*)(buffer + sizeof(SRB_IO_CONTROL));
				IDSECTOR* pId = (IDSECTOR*)(pOut->bBuffer);
				if (pId->sModelNumber[0])
				{
					int n = 0;
					USHORT* pIdSector = (USHORT*)pId;
					for (n = 0; n<256; n++)
						buffer[n] = pIdSector[n];
					return TRUE;	//��ȡ�ɹ�
				}
			}

		}
		CloseHandle(hScsiDriveIOCTL);	//�رվ��
	}
	return FALSE;	//��ȡʧ��
}

/*
���ܣ�Window NT/2000/xp�¶�ȡIDEӲ�����к�
*/
BOOL CGetHDSerial::WinNTReadIDEHDSerial(DWORD* buffer)
{
	BYTE IdOutCmd[sizeof(SENDCMDOUTPARAMS)+IDENTTIFY_BUFFER_SIZE - 1];
	BOOL bFlag = FALSE;
	int drive = 0;
	char driveName[256];
	HANDLE hPhysicalDriveIOCTL = 0;

	sprintf(driveName, "\\\\.\\physicalDrive%d", drive);
	//Windows NT/200/xp �´����ļ���Ҫ����ԱȨ��
	hPhysicalDriveIOCTL = CreateFileA(driveName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
	{
		GETVERSIONOUTPARAMS VersionParams;
		DWORD cbBytesReturned = 0;
		//�õ���������IO�������汾
		memset((void*)&VersionParams, 0, sizeof(VersionParams));
		if (DeviceIoControl(hPhysicalDriveIOCTL, IOCTL_GET_VERSION,
			NULL, 0, &VersionParams,
			sizeof(VersionParams),
			&cbBytesReturned, NULL))
		{
			if (VersionParams.bIDEDeviceMap >= 0)
			{
				BYTE bIDCmd = 0;	//IDE����ATAPI ʶ������
				SENDCMDINPARAMS scip;

				//����������ǹ�������������IDE_ATAIP_IDENTIFY,
				//�����������IDE_ATA_IDENTIFY��ȡ��������Ϣ
				bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

				memset(&scip, 0, sizeof(scip));
				memset(IdOutCmd, 0, sizeof(IdOutCmd));
				//��ȡ��������Ϣ
				if (WinNTGetIDEHDInfo(hPhysicalDriveIOCTL,
					&scip,
					(PSENDCMDOUTPARAMS)&IdOutCmd,
					(BYTE)bIDCmd,
					(BYTE)drive,
					&cbBytesReturned))
				{
					int m = 0;
					USHORT* PIdSector = (USHORT*)((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;
					for (m = 0; m<256; m++)
						buffer[m] = PIdSector[m];
					bFlag = TRUE;	//��ȡӲ����Ϣ�ɹ�
				}
			}
		}
		CloseHandle(hPhysicalDriveIOCTL);	//�رվ��
	}
	return bFlag;
}

/*
���ܣ�Windows NT/2000/XP�¶�ȡIDE�豸��Ϣ
*/
BOOL CGetHDSerial::WinNTGetIDEHDInfo(HANDLE hPhysicalDriveIOCTL,
	PSENDCMDINPARAMS pSCIP,
	PSENDCMDOUTPARAMS pSCOP,
	BYTE bIDCmd,
	BYTE bDriveNum,
	PDWORD lpcbBytesReturned)
{
	//Ϊ��ȡ�豸��Ϣ׼������
	pSCIP->cBufferSize = IDENTTIFY_BUFFER_SIZE;
	pSCIP->irDriveRegs.bFeaturesReg = 0;
	pSCIP->irDriveRegs.bSectorCountReg = 1;
	pSCIP->irDriveRegs.bSectorNumberReg = 1;
	pSCIP->irDriveRegs.bCylLowReg = 0;
	pSCIP->irDriveRegs.bCylHighReg = 0;

	//����������λ��
	pSCIP->irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

	//�豸��ȡ����
	pSCIP->irDriveRegs.bCommandReg = bIDCmd;
	pSCIP->bDriveNumber = bDriveNum;
	pSCIP->cBufferSize = IDENTTIFY_BUFFER_SIZE;

	//��ȡ��������Ϣ
	return (DeviceIoControl(hPhysicalDriveIOCTL, IOCTL_GET_DRIVE_INFO,
		(LPVOID)pSCIP,
		sizeof(SENDCMDINPARAMS)-1,
		(LPVOID)pSCOP,
		sizeof(SENDCMDOUTPARAMS)+IDENTTIFY_BUFFER_SIZE - 1,
		lpcbBytesReturned, NULL));
}

DWORD CGetHDSerial::GetCPUID()
{
	DWORD   dwId1, dwId2, dwId3, dwId4;
	char   szCompany[13];
	PCHAR   pCompany = szCompany;

	//DWORD dwCPU;  

	szCompany[12] = 0;
	_asm
	{
		pushfd
			pushad
			//ȡ��CPU��ID��     
			mov   eax, 1   //���ܺ�     
			_emit   0x0f
			_emit   0xa2
			mov   dwId1, eax
			mov   dwId2, ebx
			mov   dwId3, ecx
			mov   dwId4, edx

			//ȡ��CPU�����칫˾����  
			mov   edi, pCompany   //���ܺ�     
			mov   eax, 0
			_emit   0x0f
			_emit   0xa2
			mov   eax, ebx
			stosd
			mov   eax, edx
			stosd
			mov   eax, ecx
			stosd
			popad
			popfd
	}

	DWORD dwResult = 0;
	DWORD dwTemp1 = dwId1 << 12;
	DWORD dwTemp2 = dwId2 << 8;
	DWORD dwTemp3 = dwId3 << 4;

	dwResult = dwTemp1 + dwTemp2 + dwTemp3 + dwId4;

	return dwResult;
}