// SvrListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrListView.h"
#include "SvrCommDoc.h"
#include <algorithm>


typedef enum  SVR_GRID_COL
{
	SVR_GRID_COLUMN_IDX,  // ���
	SVR_GRID_COLUMN_IP,  // 
	SVR_GRID_COLUMN_PORT , // 
	SVR_GRID_COLUMN_STATUS , //����״̬ 
	SVR_GRID_COLUMN_RECV, //�շ�����
	SVR_GRID_COLUMN_SEND  // 
};

BEGIN_MESSAGE_MAP(CSvrListGridCtrl, CBCGPGridCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CSvrListGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBCGPGridCtrl::OnLButtonDblClk(nFlags, point);
	if (GetParent() && GetParent()->IsKindOf(RUNTIME_CLASS(CSvrListView)))
	{
		CBCGPGridRow* pSel = GetCurSel ();
		if (pSel)
		{
			DWORD_PTR pData = pSel->GetData();
			((CSvrListView*)GetParent())->OnDblclkGrid(pData);
		}
	}
}


// CSvrListView

IMPLEMENT_DYNCREATE(CSvrListView, CView)

CSvrListView::CSvrListView()
{

}

CSvrListView::~CSvrListView()
{
}

BEGIN_MESSAGE_MAP(CSvrListView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSvrListView ��ͼ

void CSvrListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CSvrListView ���

#ifdef _DEBUG
void CSvrListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSvrListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSvrListView ��Ϣ�������

int CSvrListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rectGrid;
	rectGrid.SetRectEmpty();

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, ID_SEVER_LIST);

	m_wndGrid.SetSingleSel(TRUE);
	m_wndGrid.SetWholeRowSel (TRUE);
	m_wndGrid.EnableMarkSortedColumn (FALSE);
	m_wndGrid.EnableMultipleSort(FALSE);
	m_wndGrid.EnableHeader (TRUE,BCGP_GRID_HEADER_MOVE_ITEMS); 		 
	m_wndGrid.EnableLineNumbers(TRUE);

	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_IDX, _T("���"), 70);
	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_IP, _T("�ͻ���IP"), 140);
	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_PORT, _T("�˿ں�"), 70);
	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_STATUS, _T("״̬"), 70);

  	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_RECV, _T("�������ݰ�"),80);
  	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_SEND, _T("�������ݰ�"),80);
 
	return 0;
}

void CSvrListView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if ( m_wndGrid.GetSafeHwnd())
	{
		 m_wndGrid.SetWindowPos (NULL, -1, -1, cx, cy,SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	}
	// TODO: �ڴ˴������Ϣ����������
}

void CSvrListView::OnDblclkGrid(DWORD_PTR pClient ) 
{
	CSvrCommDoc *pDoc = (CSvrCommDoc *)GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;

	//TEST
 	pDoc->OpenSvrCommFrm((CClientNode *)pClient);
}

void CSvrListView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
}

BOOL CSvrListView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}

void CSvrListView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	if (m_wndGrid.GetSafeHwnd() != NULL)
	{
		m_wndGrid.SetFocus();
	}
	// TODO: �ڴ˴������Ϣ����������
}
void  CSvrListView::CreateRow(int nIdx, CBCGPGridRow *pRow, CClientNode *pInfo )
{
	ASSERT(pRow && pInfo);
	if (pInfo == NULL || pRow == NULL)
		return;
	CString szTxt;

	szTxt.Format( _T("%d"),nIdx);
	CBCGPGridItem *pItem = pRow->GetItem(SVR_GRID_COLUMN_IDX);
	ASSERT(pItem);
	pItem->SetValue(_variant_t (szTxt),FALSE);

	szTxt.Format(_T("%d.%d.%d.%d"),pInfo->m_addr.sin_addr.s_net ,pInfo->m_addr.sin_addr.s_host ,
		pInfo->m_addr.sin_addr.s_lh ,pInfo->m_addr.sin_addr.s_impno);	
	pItem = pRow->GetItem(SVR_GRID_COLUMN_IP);
	ASSERT(pItem); 
	pItem->SetValue(_variant_t (szTxt),FALSE);

//	szTxt.Format(_T("%d"),pInfo->m_addr.sin_port );	
	pItem = pRow->GetItem(SVR_GRID_COLUMN_PORT);
	ASSERT(pItem); 
	pItem->SetValue(_variant_t ( htons(pInfo->m_addr.sin_port) ),FALSE);

	if (pInfo->m_bOnline)
	{
		szTxt = _T("����");
	}
	else
	{
		szTxt = _T("����");
	}
	pItem = pRow->GetItem(SVR_GRID_COLUMN_STATUS);
	ASSERT(pItem); 
	pItem->SetValue(_variant_t (szTxt),FALSE);

	pRow->SetData((DWORD_PTR)pInfo); 
} 
void CSvrListView::UpdateRowInfo( CBCGPGridRow *pRow, CClientNode *pInfo )
{
	ASSERT(pRow && pInfo);
	if (pInfo == NULL || pRow == NULL)
		return;

	CString szTxt;
	CBCGPGridItem *pItem = NULL;
	if (pInfo->m_bOnline)
	{
		szTxt = _T("����");
	}
	else
	{
		szTxt = _T("����");
	}
	pItem = pRow->GetItem(SVR_GRID_COLUMN_STATUS);
	ASSERT(pItem); 
	pItem->SetValue(_variant_t (szTxt),FALSE);

//	szTxt.Format(_T("%d"), pInfo->m_nRecvCnt);
	pItem = pRow->GetItem(SVR_GRID_COLUMN_RECV);
	ASSERT(pItem); 
	pItem->SetValue(_variant_t (pInfo->m_nRecvCnt),FALSE);

	pItem = pRow->GetItem(SVR_GRID_COLUMN_SEND);
	ASSERT(pItem); 
	pItem->SetValue(_variant_t (pInfo->m_nSendCnt),FALSE);
}

void CSvrListView::UpdateClientInfo( )
{
	CSvrCommDoc *pDoc = (CSvrCommDoc *)GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;

	if (m_wndGrid.GetSafeHwnd() == NULL)
		return;
	int nRowCnt = m_wndGrid.GetRowCount();
	int i = 0;
	CBCGPGridRow *pRow = NULL;
	CClientNode *pClient = NULL;
	std::vector <CClientNode *> arrTmp ;
	std::vector <CClientNode *> arrClientNode = pDoc->m_SvrComm.GetClientNodeArr() ; 
	std::vector <CClientNode *>::iterator iter ,iter_tmp;

	for (i = 0 ; i < nRowCnt;i++)
	{
		pRow = m_wndGrid.GetRow(i);
		ASSERT(pRow);
		if (pRow)
		{
			pClient = (CClientNode *)pRow->GetData();
		 	ASSERT(pClient);
			if (pClient)
			{
				//ˢ�½���
				UpdateRowInfo(pRow,pClient);
				arrTmp.push_back(pClient);				
			}
		}
	}
	
	if (!arrClientNode.empty() && arrTmp != arrClientNode)
	{//����µĽڵ�
		for (iter_tmp = arrTmp.begin(); iter_tmp != arrTmp.end(); ++iter_tmp)
		{
			iter = std::find(arrClientNode.begin(),arrClientNode.end(),(*iter_tmp));
			if (iter != arrClientNode.end())
			{
				arrClientNode.erase(iter);
			}
		}
		int nIdx = m_wndGrid.GetRowCount();
		for (iter = arrClientNode.begin();iter != arrClientNode.end();++iter)
		{
			pRow = m_wndGrid.CreateNewRow ();
			ASSERT(pRow);
			if (pRow)
			{
				CreateRow(++nIdx,pRow,(*iter));
				m_wndGrid.AddRow(pRow,FALSE);
			}
		}	 
	}
	m_wndGrid.AdjustLayout();
}

const UINT_PTR ID_CLIENT_NODE_EVENT = 200804;

void CSvrListView::StartUpdateClientInfo( )
{
	SetTimer(ID_CLIENT_NODE_EVENT,1000,NULL);

}
void CSvrListView::StopUpdateClientInfo( )
{
	KillTimer(ID_CLIENT_NODE_EVENT);

	//ɾ������������Ϣ
	if (m_wndGrid.GetSafeHwnd())
	{
		m_wndGrid.RemoveAll();
	}
}


void CSvrListView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == ID_CLIENT_NODE_EVENT)
	{
		KillTimer(ID_CLIENT_NODE_EVENT);
		UpdateClientInfo( );
		SetTimer(ID_CLIENT_NODE_EVENT,1000,NULL);
	}

	CView::OnTimer(nIDEvent);
}

void CSvrListView::OnDestroy()
{
	KillTimer(ID_CLIENT_NODE_EVENT);
	m_wndGrid.DestroyWindow();
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}