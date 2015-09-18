
// jpgresizeDlg.h : header file
//

#pragma once


// CjpgresizeDlg dialog
class CjpgresizeDlg : public CDialogEx
{
// Construction
public:
	CjpgresizeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_JPGRESIZE_DIALOG };

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
	afx_msg void OnBnClickedOk();
	void DoResize( LPCTSTR FN, int NewWidth );

	int m_width;
	CString m_fn;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL m_visible;
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
