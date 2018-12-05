
// zaqDlg.h : header file
//

#pragma once
// CzaqDlg dialog
class CFormDlg : public CDialogEx
{
	

// Construction
public:
	CFormDlg(CWnd* pParent = NULL);	// standard constructor
	
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZAQ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtnAnh();

	afx_msg void OnBnClickedbtnthoat();
	afx_msg void OnBnClickedbtnShow();
	afx_msg void OnBnClickedbtnVideo();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedbtnPause();
};
