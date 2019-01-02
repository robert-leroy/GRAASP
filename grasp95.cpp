// grasp95.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "grasp95.h"
#include "ProgDlg.h"

#include "FileSize.h"
#include "ToolBarEx.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "graspDoc.h"
#include "graspTree.h"
#include "Splash.h"
#include "BigIcon.h"
#include "Shareware.h"

#include <dos.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraspApp

BEGIN_MESSAGE_MAP(CGraspApp, CWinApp)
	//{{AFX_MSG_MAP(CGraspApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND_EX(ID_DRIVE_A, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_B, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_C, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_D, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_E, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_F, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_G, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_H, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_I, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_J, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_K, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_L, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_M, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_N, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_O, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_P, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_Q, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_R, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_S, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_T, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_U, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_V, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_W, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_X, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_Y, OnDriveCommand)
	ON_COMMAND_EX(ID_DRIVE_Z, OnDriveCommand)
	ON_COMMAND(ID_APP_HELP, OnAppHelp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
    ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraspApp construction

CGraspApp::CGraspApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGraspApp object

CGraspApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGraspApp initialization

BOOL CGraspApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

		AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Vero Software Architects"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	AddDocTemplate ( new CMultiDocTemplate(
		IDR_GRASPTREE,
		RUNTIME_CLASS(CGraspDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGraspTree)));

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// DON'T display a new MDI child window during startup!!!
	if (!cmdInfo.m_strFileName.IsEmpty())
	{
		CGraspDoc* pDoc = (CGraspDoc*) OpenDocumentFile(cmdInfo.m_strFileName);
		if (pDoc)
			pDoc->SetTitle(pDoc->m_strVolumeName);

	}

	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

    // Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


#ifdef _SHAREWARE
	CShareware dlg;
	dlg.DoModal();
#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
//	CBigIcon  m_icon;

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGraspApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGraspApp commands

BOOL CGraspApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow();
	
	// initialize the big icon control
//	m_icon.SubclassDlgItem(IDC_BIGICON, this);
//	m_icon.SizeToContent();


	return TRUE;

}

BOOL CGraspApp::OnDriveCommand(UINT nID) 
{
	TCHAR szBuff[3];

	szBuff[0] = nID - ID_DRIVE_BASE + 65;
	szBuff[1] = ':';
	szBuff[2] = 0;

	CGraspDoc* pDoc = (CGraspDoc*)	OpenDocumentFile(szBuff);
	if (pDoc)
		pDoc->SetTitle(pDoc->m_strVolumeName);

	return TRUE;
}



void CGraspApp::OnAppHelp() 
{
	WinHelp( 1 );
}
