// ClientOptionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "ClientOptionView.h"
#include "ClientCommDoc.h"


// CClientOptionView

IMPLEMENT_DYNCREATE(CClientOptionView, CBCGPFormView)

CClientOptionView::CClientOptionView()
	: CBCGPFormView(CClientOptionView::IDD)
	, m_nDestPortNum(0)
	, m_bRandromLocalPort(FALSE)
	, m_nLocalPortNum(4001)
	, m_nProtocolType(0)
	, m_nSendCnt(0)
	, m_nRecvCnt(0)
	, m_nAutoTime(800)
	, m_bAutoClose(FALSE)
{

}

CClientOptionView::~CClientOptionView()
{
}

void CClientOptionView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_DEST_OPT, m_wndDestIp);
	DDX_Text(pDX, IDC_EDIT_DEST_PORT_OPT, m_nDestPortNum);
	DDX_Check(pDX, IDC_CHECK_LOCAL_PORT, m_bRandromLocalPort);
	DDX_Text(pDX, IDC_EDIT_LOCAL_PORT_OPT, m_nLocalPortNum);
	DDX_CBIndex(pDX, IDC_CB_PROTO_TYPE_OPT, m_nProtocolType);
	DDX_Text(pDX, IDC_STATIC_SND_CNT, m_nSendCnt);
	DDX_Text(pDX, IDC_STATIC_RCV_CNT, m_nRecvCnt);
	DDX_Text(pDX, IDC_EDIT_AUTO_TIME, m_nAutoTime);
	DDX_Check(pDX, IDC_CHECK_AUTO_CLOSE, m_bAutoClose);
}

BEGIN_MESSAGE_MAP(CClientOptionView, CBCGPFormView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CHECK_LOCAL_PORT, &CClientOptionView::OnBnClickedCheckLocalPort)
	ON_BN_CLICKED(IDC_BUTTON_START, &CClientOptionView::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CClientOptionView::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_CHECK_AUTO_CLOSE, &CClientOptionView::OnBnClickedCheckAutoClose)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClientOptionView ���

#ifdef _DEBUG
void CClientOptionView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClientOptionView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CClientOptionView ��Ϣ�������

int CClientOptionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EnableVisualManagerStyle();
	return 0;
}

const int ID_DATA_FRESH = 1002;
void CClientOptionView::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	SetTimer(ID_DATA_FRESH,1000,NULL);

}

void CClientOptionView::OnUpdate(CView*  pSender , LPARAM  lHint, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(lHint == UPDATA_VIEW_CLIENT_NORMAL)
	{
		CClientCommDoc *pDoc = (CClientCommDoc *) GetDocument();
		ASSERT(pDoc);
		if (pDoc == NULL)
			return;

		//	DWORD dwIp = htonl( inet_addr("192.9.200.101"));
		m_wndDestIp.SetAddress(pDoc->m_dwDestIp);
		m_nDestPortNum = pDoc->m_nDestPort;
		if (pDoc->m_nLocalPort)
		{
			m_bRandromLocalPort = TRUE;
		}
		else
		{
			m_bRandromLocalPort = FALSE;
			m_nLocalPortNum = pDoc->m_nLocalPort;
		}
	
		CWnd *pLocalPort =GetDlgItem(IDC_EDIT_LOCAL_PORT_OPT);
		ASSERT(pLocalPort);

		if (m_bRandromLocalPort)
		{
			if (pLocalPort)
			{
				pLocalPort->EnableWindow(TRUE);
			}
		}
		else
		{
			if (pLocalPort)
			{
				pLocalPort->EnableWindow(FALSE);			 
			}
		}
		m_nProtocolType = pDoc->m_nProtocolType;
		
		UpdateData(FALSE);
	}
}

void CClientOptionView::OnBnClickedCheckLocalPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CWnd *pLocalPort =GetDlgItem(IDC_EDIT_LOCAL_PORT_OPT);
	ASSERT(pLocalPort);

	if (m_bRandromLocalPort)
	{
		if (pLocalPort)
		{
			pLocalPort->EnableWindow(TRUE);
		}
	}
	else
	{
		if (pLocalPort)
		{
			pLocalPort->EnableWindow(FALSE);			 
		}
	}

}
void CClientOptionView::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CClientCommDoc *pDoc = (CClientCommDoc *) GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;

	pDoc->m_ClientComm.m_bAutoClose = m_bAutoClose;
	if (m_nAutoTime <= 500)
	{
		m_nAutoTime = 500;
		UpdateData(FALSE);
	}
	pDoc->m_ClientComm.m_nAutoCloseTime = m_nAutoTime;

	CWnd *pWnd = GetDlgItem(IDC_BUTTON_START);
	ASSERT(pWnd);
	pWnd->EnableWindow(FALSE);
	if(pDoc->m_bConnected == FALSE)
	{//δ������	
		//��������������ݣ�Ȼ��У��һ���Ƿ�Ϸ�
		pDoc->m_nProtocolType = m_nProtocolType; //Э������ 0 TCP 1 UDP	 
		pDoc->m_nDestPort = m_nDestPortNum;
		//	pDoc->m_nLocalPort = ; //0 ��ʾ����˿� ��0Ϊָ���˿�

		if (m_bRandromLocalPort)
		{
			pDoc->m_nLocalPort = m_nLocalPortNum;		 
		}
		else
		{
			pDoc->m_nLocalPort = 0;
		}

		m_wndDestIp.GetAddress(pDoc->m_dwDestIp);

		BOOL bRet = pDoc->Connect();

		if (bRet)
		{
 			pWnd->SetWindowText(_T("�Ͽ�����"));
		}
		pWnd->EnableWindow();
	}
	else
	{//�Ͽ�����

		pDoc->Disconnect( );
		pWnd->SetWindowText(_T("����"));
		pWnd->EnableWindow();
	}
	
	return ;
}

void CClientOptionView::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nRecvCnt = m_nSendCnt = 0;
	UpdateData(FALSE);
}

void CClientOptionView::OnBnClickedCheckAutoClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

void CClientOptionView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientCommDoc *pDoc = (CClientCommDoc *) GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;

	if (nIDEvent == ID_DATA_FRESH)
	{
		m_nSendCnt = pDoc->m_ClientComm.m_nSendPacketCnt;
		m_nRecvCnt = pDoc->m_ClientComm.m_nRecvPacketCnt;
		UpdateData(FALSE);
	}

	CBCGPFormView::OnTimer(nIDEvent);
}
