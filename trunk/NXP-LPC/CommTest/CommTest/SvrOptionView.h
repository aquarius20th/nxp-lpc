#pragma once



// CSvrOptionView ������ͼ

class CSvrOptionView : public CFormView
{
	DECLARE_DYNCREATE(CSvrOptionView)

protected:
	CSvrOptionView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSvrOptionView();

public:
	enum { IDD = IDD_DLG_SVR_OPTIONS };
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


