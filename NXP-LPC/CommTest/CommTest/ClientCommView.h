
// CommTestView.h : CClientCommView ��Ľӿ�
//


#pragma once

class CClientCommDoc;
class CClientCommView : public CView
{
protected: // �������л�����
	CClientCommView();
	DECLARE_DYNCREATE(CClientCommView)

// ����
public:
	CClientCommDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected: 

// ʵ��
public:
	virtual ~CClientCommView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
 	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CommTestView.cpp �еĵ��԰汾
inline CClientCommDoc* CClientCommView::GetDocument() const
   { return reinterpret_cast<CClientCommDoc*>(m_pDocument); }
#endif

