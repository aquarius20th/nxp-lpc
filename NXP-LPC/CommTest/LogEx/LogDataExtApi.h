/****************************************Copyright (c)**************************************************
**                         ���ڴ�LOGEX.DLL�е��뺯��
**                                      
**                                      
**
**                           
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:  
**��   ��   ��:  
**����޸�����: 
**��        ��:   
**
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������:  
** ��  ��:  
** �ա���:  
** �衡��: 
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���:
** �ա���:
** �衡��:  
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

#pragma once

#ifndef LOG_EXT
#define LOG_DATA_EXT extern "C"   __declspec(dllimport)
#else 
#define LOG_DATA_EXT extern "C"  __declspec(dllexport)
#endif



LOG_DATA_EXT  bool RegisterLogEx(TCHAR *szModuleName  );
LOG_DATA_EXT  void UnregisterLogEx( TCHAR *szModuleName  ); 
LOG_DATA_EXT void LogStringEx( TCHAR * szModuleName, TCHAR *  lpszTxt ,int nStrType);
LOG_DATA_EXT void LogStringTmEx( TCHAR * szModuleName,SYSTEMTIME st,  TCHAR *  lpszTxt ,int nStrType);