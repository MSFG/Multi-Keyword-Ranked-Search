// RBTreeSearch1.0Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CRBTreeSearch10Dlg �Ի���
class CRBTreeSearch10Dlg : public CDialog
{
// ����
public:
	CRBTreeSearch10Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RBTREESEARCH10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTestbutton();
	CString m_keywords;


	//CString m_topk_result;
	CString m_time;
	CListCtrl m_ListCtrl;
	CString m_path;
	afx_msg void OnBnClickedBrowse();
	CString m_keywordNum;
	CString m_docNum;
	CString m_indexTime;
	int m_numK;
	CString m_WSTime;
	CString m_path_state;
};
