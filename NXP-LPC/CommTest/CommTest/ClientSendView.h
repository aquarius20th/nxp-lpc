#pragma once



// CClientSendView ������ͼ

class CClientSendView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CClientSendView)

protected:
	CClientSendView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CClientSendView();

public:
	enum { IDD = IDD_DLG_SEND };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


