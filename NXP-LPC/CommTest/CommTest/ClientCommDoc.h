
// CommTestDoc.h : CClientCommDoc ��Ľӿ�
//


#pragma once


class CClientCommDoc : public CDocument
{
protected: // �������л�����
	CClientCommDoc();
	DECLARE_DYNCREATE(CClientCommDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CClientCommDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


