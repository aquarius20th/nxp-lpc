// PacketDecodeFrm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PacketDecodeFrm.h"


// CPacketDecodeFrm

IMPLEMENT_DYNCREATE(CPacketDecodeFrm, CBCGPMDIChildWnd)

CPacketDecodeFrm::CPacketDecodeFrm()
{

}

CPacketDecodeFrm::~CPacketDecodeFrm()
{
}


BEGIN_MESSAGE_MAP(CPacketDecodeFrm, CBCGPMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPacketDecodeFrm ��Ϣ�������

BOOL CPacketDecodeFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style &= ~WS_SYSMENU;
//	cs.style  &= ~FWS_ADDTOTITLE ;

	return CBCGPMDIChildWnd::PreCreateWindow(cs);
}

int CPacketDecodeFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

BOOL CPacketDecodeFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CBCGPMDIChildWnd::OnCreateClient(lpcs, pContext);
}
