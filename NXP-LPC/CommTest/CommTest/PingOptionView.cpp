// PingOptionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PingOptionView.h"
#include "PingTestDoc.h"

// CPingOptionView

IMPLEMENT_DYNCREATE(CPingOptionView, CBCGPFormView)

CPingOptionView::CPingOptionView()
	: CBCGPFormView(CPingOptionView::IDD)
	, m_nTaskCnt(1)
	, m_nPingDataSize(32)
	, m_nIntTime(300)
	, m_bAutoDelay(TRUE)
	, m_nPingCnt(0)
	, m_nReplyCnt(0)
	, m_nLostCnt(0)
{

}

CPingOptionView::~CPingOptionView()
{
}

void CPingOptionView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_PING_DEST_OPT, m_wndDestIp);
	DDX_Text(pDX, IDC_EDIT_PING_THREAD_CNT_OPT, m_nTaskCnt);
	DDV_MinMaxUInt(pDX, m_nTaskCnt, 1, 16);
	DDX_Text(pDX, IDC_EDIT_PING_DATA_SIZE, m_nPingDataSize);
	DDV_MinMaxUInt(pDX, m_nPingDataSize, 32, 64000);
	DDX_Text(pDX, IDC_EDIT_PING_INT_TIME, m_nIntTime);
	DDV_MinMaxUInt(pDX, m_nIntTime, 32, 50000);
	DDX_Check(pDX, IDC_CHECK_TIMEOUT_DELAY, m_bAutoDelay);
	DDX_Text(pDX, IDC_STATIC_PING_SND_CNT, m_nPingCnt);
	DDX_Text(pDX, IDC_STATIC_PING_RTN_CNT, m_nReplyCnt);
	DDX_Text(pDX, IDC_STATIC_PING_LOST_CNT, m_nLostCnt);
}

BEGIN_MESSAGE_MAP(CPingOptionView, CBCGPFormView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_PING_START, &CPingOptionView::OnBnClickedButtonPingStart)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CPingOptionView::OnBnClickedButtonReset)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPingOptionView ���

#ifdef _DEBUG
void CPingOptionView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPingOptionView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPingOptionView ��Ϣ�������

int CPingOptionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EnableVisualManagerStyle();
	return 0;
}

void CPingOptionView::OnUpdate(CView*  pSender , LPARAM lHint, CObject*  pHint )
{
	// TODO: �ڴ����ר�ô����/����û���
	if(lHint == UPDATA_VIEW_PING_NORMAL)
	{
		CPingTestDoc *pDoc = (CPingTestDoc *) GetDocument();
		ASSERT(pDoc);
		if (pDoc == NULL)
			return;

	 	m_wndDestIp.SetAddress(pDoc->m_dwDestIp);

		m_nTaskCnt = pDoc->m_nTaskCnt;
		m_nPingDataSize = pDoc->m_nPingDataSize;
		m_bAutoDelay = pDoc->m_bAutoDelay;
		m_nIntTime = pDoc->m_nIntTime;		

		UpdateData(FALSE);
	}
}
const UINT_PTR ID_PING_CNT_EVENT = 200911;
void CPingOptionView::OnBnClickedButtonPingStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPingTestDoc *pDoc = (CPingTestDoc *) GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;
	CWnd *pWnd = GetDlgItem(IDC_BUTTON_PING_START);
	ASSERT(pWnd);
	pWnd->EnableWindow(FALSE);

	if(pDoc->m_bPinging)
	{
		pDoc->StopTask();

		pWnd->SetWindowText(_T("��ʼ"));
		pWnd->EnableWindow();
		pDoc->m_bPinging = FALSE;
		KillTimer(ID_PING_CNT_EVENT);
	}
	else
	{
		pDoc->StartTask();

		pWnd->SetWindowText(_T("ֹͣ"));
		pWnd->EnableWindow();
		pDoc->m_bPinging = TRUE;
		SetTimer(ID_PING_CNT_EVENT,1000,NULL);
	}
}

void CPingOptionView::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPingTestDoc *pDoc = (CPingTestDoc *) GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;

	pDoc->m_PingMsgCntnr.ResetCnt();
}

void CPingOptionView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == ID_PING_CNT_EVENT)
	{
		KillTimer(nIDEvent);
		CPingTestDoc *pDoc = (CPingTestDoc *) GetDocument();
		ASSERT(pDoc);
		if (pDoc)
		{
			m_nPingCnt = pDoc->m_PingMsgCntnr.m_nPingCnt;
			m_nLostCnt = pDoc->m_PingMsgCntnr.m_nLostCnt;
			m_nReplyCnt = pDoc->m_PingMsgCntnr.m_nReplyCnt;
			UpdateData(FALSE);
		}
		SetTimer(ID_PING_CNT_EVENT,1000,NULL);
	}

	CBCGPFormView::OnTimer(nIDEvent);
}
