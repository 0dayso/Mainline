#pragma once


//�궨��
#define SENDIDLENGTH sizeof(SENDCMDOUTPARAMS) + IDENTTIFY_BUFFER_SIZE
#define IDENTTIFY_BUFFER_SIZE 512
#define FILE_DEVICE_SCSI	0X00140106b
#define IOCTL_SCSI_MINIPORT_IDENTIFY ((FILE_DEVICE_SCSI<<16)+0x0501)
#define IOCTL_SCSI_MINIPORT 0x0004d008
#define IDE_ATAPI_IDENTIFY 0xA1
#define IDE_ATA_IDENTIFY 0xEC
#define IOCTL_GET_DRIVE_INFO 0x0007c088
#define IOCTL_GET_VERSION 0x00074080

//����IDSECTOR�ṹ
typedef struct _IDSECTOR
{
	USHORT wGenConfig;
	USHORT wNumCyls;
	USHORT wReserved;
	USHORT wNumHeads;
	USHORT wBytesPerTrack;
	USHORT wBytesPerSector;
	USHORT wSectorsPerTrack;
	USHORT wVendorUnique[3];
	CHAR   sSerialNumber[20];
	USHORT wBufferType;
	USHORT wBufferSize;
	USHORT wECCSize;
	CHAR   sFirmwareRev[8];
	CHAR   sModelNumber[40];
	USHORT wMoreVeWndorUnique;
	USHORT wDoubleWordIO;
	USHORT wCapabilities;
	USHORT wReserved1;
	USHORT wPIOTiming;
	USHORT wDMATiming;
	USHORT wBS;
	USHORT wNumCurrentCyls;	
	USHORT wNumCurrentHeads;
	USHORT wNumCurrentSectorsPerTrack;
	ULONG  ulCurrentSectorCapacity;
	USHORT wMultSectorStuff;
	ULONG  ulTotalAddressableSectors;
	USHORT wSingleWordDMA;
	USHORT wMultiWordDMA;
	BYTE   bReserved[128];
}IDSECTOR,*PIDSECTOR;

//����DRIVERSTATUS�ṹ
typedef struct _DRIVERSTATUS
{
	BYTE  bDriverError;	//�������ش������
	BYTE  bIDEStatus;	//IDE���ݴ����¼
						//����bDriverErrorΪSMART_IDE_ERRORʱ��Ч
	BYTE  bReserved[2];
	DWORD dwReserved[2];
}DRIVERSTATUS,*PDRIVERSTATUS,*LPDRIVERSTATUS;

//����SENDCMDOUTPARAMS�ṹ
typedef struct _SENDCMDOUTPARAMS
{
	DWORD		 cBufferSize;	//bBuffer�Ĵ�С
	DRIVERSTATUS DriverStatus;	//��������״̬�ṹ
	BYTE		 bBuffer[1];
}SENDCMDOUTPARAMS,*PSENDCMDOUTPARAMS,*LPSENDCMDOUTPARAMS;

//����SRB_IO_CONTROL �ṹ
typedef struct _SRB_IO_CONTROL
{
	ULONG HeaderLength;
	UCHAR Signauture[8];
	ULONG Timeout;
	ULONG ControlCode;
	ULONG ReturnCode;
	ULONG Length;
}SRB_IO_CONTROL,*PSRB_IO_CONTROL;

//����IDEREGS�ṹ
typedef struct _IDEREGS
{
	BYTE bFeaturesReg;
	BYTE bSectorCountReg;
	BYTE bSectorNumberReg;
	BYTE bCylLowReg;
	BYTE bCylHighReg;
	BYTE bDriveHeadReg;
	BYTE bCommandReg;
	BYTE bReserved;
}IDEREGS,*PIDEREGS,*LPIDEREGS;

//����SENDCMDINPARAMS�ṹ
typedef struct _SENDCMDINPARAMS
{
	DWORD	cBufferSize;	//�������Ĵ�С
	IDEREGS irDriveRegs;	//��������ע���Ľṹ
	BYTE	bDriveNumber;	//��4�����������ʽ��0��1��2��3��
	DWORD	dwReserved[4]; //�����ֶ�
	BYTE	bBusffer[1];	//���������
}SENDCMDINPARAMS,*PSENDCMDINPARAMS,*LPSENDINPARAMS;

//����GETVERSIONOUTPARAMS�ṹ
typedef struct _GETVERSIONOUTPARAMS
{
	BYTE	bVersion;	//�������İ汾
	BYTE	bRevision;	//���������°汾
	BYTE	bReserved;	//û��Ӧ��
	BYTE	bIDEDeviceMap;	//IDE��������mapͼ
	DWORD	fCapabilities;	//�������Ĵ�С
	DWORD	dwReservedc[4];	//Ϊ�������Ա���
}GETVERSIONOUTPARAMS,*PGETVERSIONOUTPARAMS,*LPGETVERSIONOUTPARAMS;

class CGetHDSerial
{
public:
	CGetHDSerial(void);
	virtual ~CGetHDSerial(void);
	void _stdcall Win9xReadHDSerial(WORD* buffer);
	char* GetHDSerial();
	DWORD GetCPUID();
	char* WORDToChar(WORD diskdata[256],int firstIndex,int lastIndex);
	char* DWORDToChar(DWORD diskdata[256],int firstIndex,int lastIndex);
	BOOL WinNTReadSCSIHDSerial(DWORD* buffer);
	BOOL WinNTReadIDEHDSerial(DWORD* buffer);
	BOOL WinNTGetIDEHDInfo(HANDLE hPhysicalDriveIOCTL,
						   PSENDCMDINPARAMS pSCIP,
						   PSENDCMDOUTPARAMS pSCOP,
						   BYTE bIDCmd,
						   BYTE bDriveNum,
						   PDWORD lpcbBytesReturned);
};
