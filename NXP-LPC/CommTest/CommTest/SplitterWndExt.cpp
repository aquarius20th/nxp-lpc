
// ClientChildFrame.cpp : CClientChildFrame ���ʵ��
//

#include "stdafx.h" 
#include "SplitterWndExt.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CSplitterWndExt,CBCGPSplitterWnd)

/////////////////////////////////////////////////////////////////////////////
// CBCGPSplitterWnd

CSplitterWndExt::CSplitterWndExt()
{
	m_nX1=m_nX2=m_nY1=m_nY2 = 0;
}

CSplitterWndExt::~CSplitterWndExt()
{
}


BEGIN_MESSAGE_MAP(CSplitterWndExt ,CBCGPSplitterWnd)
	//{{AFX_MSG_MAP(CSplitterWndExt)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitterWndExt message handlers 

void CSplitterWndExt::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// �����з������˶���Χ�� 
	if (m_nX1 && m_nX2)
	{
		if(point.x< m_nX1 ||point.x > m_nX2) 
		{ 
			CWnd::OnMouseMove(nFlags, point); 
			return;
		} 
	}
	else if ( m_nY1 && m_nY2 )
	{
		if(point.x< m_nY1 ||point.x > m_nY2) 
		{ 
			CWnd::OnMouseMove(nFlags, point); 
			return;
		} 
	}

	CBCGPSplitterWnd::OnMouseMove(nFlags, point); 


 //	CBCGPSplitterWnd::OnMouseMove(nFlags, point);
}

 