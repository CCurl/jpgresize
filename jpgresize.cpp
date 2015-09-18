
// jpgresize.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "jpgresize.h"
#include "jpgresizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CMyCLI : public CCommandLineInfo 
{
public:
	virtual void ParseParam( const char* pszParam, BOOL bFlag, BOOL bLast );

	CjpgresizeDlg *m_dlg;
};

void CMyCLI::ParseParam( const char* pszParam, BOOL bFlag, BOOL bLast )
{
	CString param = pszParam;
	if ( bFlag )
	{
		if ( param.Left(2).CompareNoCase("fn") == 0 )
		{
			m_dlg->m_fn = param.Mid(3);
		}
		if ( param.Left(5).CompareNoCase("width") == 0 )
		{
			m_dlg->m_width = atoi(param.Mid(6));
		}
	}
}

// CjpgresizeApp

BEGIN_MESSAGE_MAP(CjpgresizeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CjpgresizeApp construction

CjpgresizeApp::CjpgresizeApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CjpgresizeApp object

CjpgresizeApp theApp;


// CjpgresizeApp initialization

BOOL CjpgresizeApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CjpgresizeDlg dlg;
	m_pMainWnd = &dlg;
	CMyCLI myCLI;
	myCLI.m_dlg = &dlg;
	ParseCommandLine( myCLI );

	INT_PTR nResponse = IDOK;
	nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

