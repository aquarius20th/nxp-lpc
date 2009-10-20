#pragma once


// CPacketDetailDlg �Ի���
class CPacket;
class CPacketDetailDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CPacketDetailDlg)

public:
	CPacketDetailDlg(CPacket *pPacket,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPacketDetailDlg();

	CPacket *m_pPacket;

private:
	CBCGPGridCtrl		m_wndGridTree;
	CImageList			m_Images;

	void  UpdateTree( );

	CBCGPGridRow* CreateNewRow ();
// �Ի�������
	enum { IDD = IDD_DLG_PACKET_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	UINT m_nId;
};
