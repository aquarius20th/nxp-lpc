#pragma once


// CSvrRecvView ��ͼ

class CSvrRecvView : public CView
{
	DECLARE_DYNCREATE(CSvrRecvView)

protected:
	CSvrRecvView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSvrRecvView();

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


