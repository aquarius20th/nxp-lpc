// LogEx.h : LogEx DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLogExApp
// �йش���ʵ�ֵ���Ϣ������� LogEx.cpp
//

class CLogExApp : public CWinApp
{
public:
	CLogExApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance(); 
};
