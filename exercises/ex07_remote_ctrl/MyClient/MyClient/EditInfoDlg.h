#pragma once


// EditInfoDlg dialog

class EditInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(EditInfoDlg)

public:
	EditInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditInfoDlg();

// Dialog Data
	enum { IDD = IDD_EDITINFODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl  m_list1;
	//WCsrDw m_dw1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
