
// CommTestDoc.h : CCommTestDoc ��Ľӿ�
//


#pragma once


class CCommTestDoc : public CDocument
{
protected: // �������л�����
	CCommTestDoc();
	DECLARE_DYNCREATE(CCommTestDoc)

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
	virtual ~CCommTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


