#pragma once


// CSvrCommFrm ���

class CSvrCommFrm : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CSvrCommFrm)
protected:
	CSvrCommFrm();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSvrCommFrm();

	CBCGPSplitterWnd m_wndSplitter;
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnClose();
};


