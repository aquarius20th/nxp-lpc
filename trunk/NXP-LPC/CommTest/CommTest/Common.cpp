
#include "stdafx.h"
#include "Common.h"

namespace Common
{
	unsigned short  GetCrc16(unsigned char *pData,int nDataLen)  
	{
		unsigned short reg,temp1,temp2;
		int i,j;
		reg=0xffff;
		for(i=0;i<nDataLen;i++)
		{
			j=0;
			temp1=(unsigned short)pData[i];
			reg=(unsigned short)(reg^temp1);
			do
			{
				temp2=(unsigned short)(reg&0x0001);
				reg=(unsigned short)(reg>>1);
				j++;
				if (temp2==0x0001)  reg=(unsigned short)(reg^0xa001);
			} while(j<8);
		}
		return (reg);	
	}


	void WaitForThreadToTerminate(HANDLE hThread)
	{
		CString szLog = _T("�̳߳�ʱ�˳�\n");

		DWORD dwRet = ::WaitForSingleObject( hThread,  2000);
		switch (dwRet)
		{
		case WAIT_OBJECT_0:
			//  The thread has terminated - do something
			break;

		case WAIT_TIMEOUT:
			//  The timeout has elapsed but the thread is still running
			//  do something appropriate for a timeout
			OutputDebugString(szLog);
			TerminateThread(hThread,0x88);
			break;
		default:
			ASSERT(false);
			break;
		}		 
	}

	unsigned char HexAscToInt( TCHAR data )
	{
		if ( isdigit(data) )
		{
			return static_cast <unsigned char>(_ttoi(&data));
		}
		else
		{
			if ((data >= L'a' && data <= L'f')) 
			{
				data -= L'a';
				return static_cast <unsigned char>(10+data);
			}
			else if ((data >= L'A' && data <= L'F'))
			{
				data -= L'A';
				return static_cast <unsigned char>(10+data);
			}			   
		}
		return 0;
	}

}