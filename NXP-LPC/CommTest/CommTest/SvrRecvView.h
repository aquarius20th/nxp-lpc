#pragma once


// CSvrRecvView ��ͼ

class CSvrRecvView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CSvrRecvView)

protected:
	CSvrRecvView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSvrRecvView();

public:
	enum { IDD = IDD_DLG_SVR_RECV };
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


