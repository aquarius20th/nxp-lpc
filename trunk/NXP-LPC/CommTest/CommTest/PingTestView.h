#pragma once


// CPingTestView ��ͼ

class CPingTestView : public CView
{
	DECLARE_DYNCREATE(CPingTestView)

protected:
	CPingTestView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPingTestView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


