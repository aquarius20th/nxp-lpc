//�ڲ���

#pragma once


#ifndef LOG_DATA_DEF
#define LOG_DATA_DEF
typedef enum LOG_STR_TYPE
{
	NORMAL_STR = 1,ALARM_STR =2,ERR_STR =3
}STRING_TYPE ;
#endif


bool RegisterLog(TCHAR *szModuleName  );
void UnregisterLog( TCHAR *szModuleName  );
//�Ƿ���Ҫд��
void EnableWriteDB(bool bFlag);

//��������
void LogString( TCHAR* lpszTxt ,int nStrType);
void LogStringTm( SYSTEMTIME st, TCHAR* lpszTxt ,int nStrType);

//����ģ��ʹ��
void AppLogString( TCHAR *szModuleName, TCHAR *szTxt, int nStrType );
void AppLogStringTm (TCHAR *szModuleName,SYSTEMTIME st, TCHAR* lpszTxt ,int nStrType);
