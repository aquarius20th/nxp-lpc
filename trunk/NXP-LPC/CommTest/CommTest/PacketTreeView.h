#pragma once


// CPacketTreeView ��ͼ

class CPacketTreeView : public CView
{
	DECLARE_DYNCREATE(CPacketTreeView)

protected:
	CPacketTreeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPacketTreeView();

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


