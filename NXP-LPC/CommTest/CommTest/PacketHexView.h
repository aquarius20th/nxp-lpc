#pragma once


// CPacketHexView ��ͼ

class CPacketHexView : public CView
{
	DECLARE_DYNCREATE(CPacketHexView)

protected:
	CPacketHexView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPacketHexView();

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


