#pragma once



// CClientOptionView ������ͼ

class CClientOptionView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CClientOptionView)

protected:
	CClientOptionView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CClientOptionView();

public:
	enum { IDD = IDD_DLG_CLIENT_OPTIONS };
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


