#pragma once



// CClientRecvView ������ͼ

class CClientRecvView : public CFormView
{
	DECLARE_DYNCREATE(CClientRecvView)

protected:
	CClientRecvView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CClientRecvView();

public:
	enum { IDD = IDD_DLG_RECV };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


