#pragma once


// CPacketDecodeFrm ���

class CPacketDecodeFrm : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CPacketDecodeFrm)
protected:
	CPacketDecodeFrm();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPacketDecodeFrm();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


