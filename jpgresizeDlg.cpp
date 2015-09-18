
// jpgresizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "jpgresize.h"
#include "jpgresizeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CjpgresizeDlg dialog


CjpgresizeDlg::CjpgresizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CjpgresizeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_width = 500;
	m_fn.Empty();
	m_visible = TRUE;
}

void CjpgresizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CjpgresizeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CjpgresizeDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CjpgresizeDlg message handlers

BOOL CjpgresizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if ( (!m_fn.IsEmpty()) && (m_width > 0 ) )
	{
		m_visible = FALSE;
		SetTimer( 1, 50, 0 );
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CjpgresizeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CjpgresizeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CjpgresizeDlg::DoResize( LPCTSTR FN, int NewWidth )
{
	try
	{
		CImage image;
		if ( image.Load( FN ) != S_OK )
			return;

		int diff = image.GetWidth() - NewWidth;
		if ( abs(diff) <= 10 )
			return;

		int Pct = NewWidth * 100 / image.GetWidth();
		if ( (Pct < 10) || (Pct > 150) )
			return;

		int newHeight = image.GetHeight() * Pct / 100;

		CImage image2;
		image2.Create( NewWidth, newHeight, image.GetBPP(), 0);
		CDC *pDC = CDC::FromHandle( image2.GetDC());

		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		image.StretchBlt(pDC->m_hDC, 0, 0, NewWidth, newHeight, SRCCOPY);

		image2.Save( FN, Gdiplus::ImageFormatJPEG );
		image2.ReleaseDC();
	}
	catch (...)
	{
	}
}

void CjpgresizeDlg::OnBnClickedOk()
{
	CString txt;

	GetDlgItem( IDC_FN )->GetWindowText( m_fn );
	GetDlgItem( IDC_PCT )->GetWindowText( txt );

	m_width = atoi(txt);

	DoResize( m_fn, m_width );
	CDialogEx::OnOK();
}


void CjpgresizeDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer( nIDEvent );
	DoResize( m_fn, m_width );
	CDialogEx::OnOK();
}


void CjpgresizeDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	if ( ! m_visible )
	{
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
	}

  CDialog::OnWindowPosChanging(lpwndpos);
}
