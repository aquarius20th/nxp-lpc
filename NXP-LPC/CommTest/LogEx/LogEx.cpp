// LogEx.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "LogEx.h"
#include "LogData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CLogExApp

BEGIN_MESSAGE_MAP(CLogExApp, CWinApp)
END_MESSAGE_MAP()


// CLogExApp ����

CLogExApp::CLogExApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CLogExApp ����

CLogExApp theApp;

extern CLogDataMgr g_LogMsgMgr;
// CLogExApp ��ʼ��

BOOL CLogExApp::InitInstance()
{
	CWinApp::InitInstance();
 	g_LogMsgMgr.InitMgr( );
	return TRUE;
}

int CLogExApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	g_LogMsgMgr.ExitMgr();

	return CWinApp::ExitInstance();
}
 