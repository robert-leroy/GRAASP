// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "grasp95.h"

#include "MainFrm.h"
#include "Splash.h"
#include "EnumObj.h"
#include "ShellApi.h"
#include "dbt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// these constants represent the dimensions and number of buttons in
// the default MFC-generated toolbar. If you need something different,
// feel free to change them. For extra credit, you can load the
// toolbar's existing image list at runtime and copy the parameters from
// there.
static const int	kImageWidth (16);
static const int	kImageHeight (15);
static const int	kNumImages (8);

static const UINT	kToolBarBitDepth (ILC_COLOR24);

// this color will be treated as transparent in the loaded bitmaps --
// in other words, any pixel of this color will be set at runtime to
// the user's button color. The Visual Studio toolbar editor defaults
// to 192, 192, 192 (light gray).
static const RGBTRIPLE	kBackgroundColor = {192, 192, 192};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
//	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pwndDriveBar = NULL;	
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	 if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	 | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
 	 !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	 {
	  TRACE0("Failed to create toolbar\n");
	  return -1; // fail to create
	 }

	  // make high-color image lists for each of the bitmaps
	 ::MakeToolbarImageList (IDB_TOOLBAR, m_ToolbarImages);
	 ::MakeToolbarImageList (IDB_TOOLBAR_DISABLED, m_ToolbarImagesDisabled);
	 ::MakeToolbarImageList (IDB_TOOLBAR_HOT, m_ToolbarImagesHot);

	::MakeToolbarImageList (IDB_DRIVEBAR, m_DrivebarImages);
	::MakeToolbarImageList (IDB_DRIVEBAR_DISABLED, m_DrivebarImagesDisabled);
	::MakeToolbarImageList (IDB_DRIVEBAR_HOT, m_DrivebarImagesHot);

	  // get the toolbar control associated with the CToolbar object
	 CToolBarCtrl&	barCtrl = m_wndToolBar.GetToolBarCtrl();

	  // attach the image lists to the toolbar control
	 barCtrl.SetImageList (&m_ToolbarImages);
	 barCtrl.SetDisabledImageList (&m_ToolbarImagesDisabled);
	 barCtrl.SetHotImageList (&m_ToolbarImagesHot);

	// Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Get the System Directory
	CString strSystemDir;
	GetSystemDirectory(strSystemDir.GetBuffer(255),255);
	strSystemDir.ReleaseBuffer();

	// Get System Image List
	SHFILEINFO sfi;
	HIMAGELIST hmiSmall = (HIMAGELIST) SHGetFileInfo(strSystemDir,NULL,&sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_SHELLICONSIZE);
	HIMAGELIST hmiBig   = (HIMAGELIST) SHGetFileInfo(strSystemDir,NULL,&sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON | SHGFI_SYSICONINDEX | SHGFI_SHELLICONSIZE);
	m_imgSmallList.Attach(hmiSmall);
    m_imgBigList.Attach(hmiBig);

	// Determine Drive Icons
	ProcessShell();

	// Load the drive bar
	LoadDriveBar();

	// CG: The following line was added by the Splash Screen component.
	// CSplashWnd::ShowSplashScreen(this);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnDestroy() 
{
	m_imgSmallList.Detach();
	m_imgBigList.Detach();

	CMDIFrameWnd::OnDestroy();

	delete m_pwndDriveBar;
		
}

void CMainFrame::LoadDriveBar()
{

	CWaitCursor csr;

	if (m_pwndDriveBar != NULL)
	{
		m_pwndDriveBar->DestroyWindow();
		delete m_pwndDriveBar;
	}

	m_pwndDriveBar = new CToolBar;

	if (!m_pwndDriveBar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	| CBRS_GRIPPER | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("Failed to create drivebar\n");
		return ;      // fail to create
	}
	
	  // get the toolbar control associated with the CToolbar object
	 CToolBarCtrl&	barCtrl = m_pwndDriveBar->GetToolBarCtrl();

	  // attach the image lists to the toolbar control
	 barCtrl.SetImageList (&m_DrivebarImages);
	 barCtrl.SetDisabledImageList (&m_DrivebarImagesDisabled);
	 barCtrl.SetHotImageList (&m_DrivebarImagesHot);

	// Get drive letters
    for (int x=0; x < g_strDriveNames.GetCount(); x++)
	{
        int nLen = g_strDriveNames[x].Find('(');
		m_astrDriveList.Add(g_strDriveNames[x].Mid(nLen+1,2));
	}

	// Add new buttons
	TBBUTTON tbItems[26];
	int nDrivePos = 0;
	int nDriveNum = 0;
	int nDrive = 1;
	int nString = 0;

	// Delete all DriveBar buttons
	while (m_pwndDriveBar->GetToolBarCtrl().DeleteButton(0));

	// Init the Drive ID's for ToolTip use
	memset(m_aDriveID, 0, sizeof(m_aDriveID));

	// Scan through all the drives and create buttons for them
    for (nDrivePos = 0; nDrivePos < m_astrDriveList.GetCount(); nDrivePos++)
	{
		// Determine drive type and set the bitmap
		switch (GetDriveType(m_astrDriveList[nDrivePos]))
		{
			case DRIVE_REMOVABLE: 
				tbItems[nDrivePos].iBitmap = 0;
				break;
			case DRIVE_FIXED:     
				tbItems[nDrivePos].iBitmap = 1;
				break;
			case DRIVE_REMOTE:    
				tbItems[nDrivePos].iBitmap = 2;
				break;
			case DRIVE_CDROM:     
				tbItems[nDrivePos].iBitmap = 3;
				break;
			case DRIVE_RAMDISK:   
				tbItems[nDrivePos].iBitmap = 4;
				break;
            default:
                tbItems[nDrivePos].iBitmap = 5;
                break;
		}
			
#ifdef _SHAREWARE
		if (tbItems[nDrivePos].iBitmap != 2 && tbItems[nDrivePos].iBitmap != 5)
		{
			// Setup the command ID and styles
			m_aDriveID[nDrivePos] = ID_DRIVE_BASE + nDriveNum;
			tbItems[nDrivePos].idCommand = ID_DRIVE_BASE + m_astrDriveList[nDrivePos][0] - 65;
			tbItems[nDrivePos].fsState = TBSTATE_ENABLED;
			tbItems[nDrivePos].fsStyle = TBSTYLE_BUTTON;
			tbItems[nDrivePos].dwData = 0;
			tbItems[nDrivePos].iString = 0;

		}
#else
		// Setup the command ID and styles
        if (tbItems[nDrivePos].iBitmap != 5)
        {
    		m_aDriveID[nDrivePos] = ID_DRIVE_BASE + nDrivePos;
    		tbItems[nDrivePos].idCommand = ID_DRIVE_BASE + m_astrDriveList[nDrivePos][0] - 65;
            tbItems[nDrivePos].fsState = TBSTATE_ENABLED;
		    tbItems[nDrivePos].fsStyle = TBSTYLE_BUTTON;
		    tbItems[nDrivePos].dwData = 0;
		    tbItems[nDrivePos].iString = 0;
        }

#endif

    }

	// Get the toolbar control
	CToolBarCtrl &rBar = m_pwndDriveBar->GetToolBarCtrl();

	// Add all buttons at once
	rBar.AddButtons(nDrivePos,tbItems);

	// Setup tool tips and a resizeable toolbar
	m_pwndDriveBar->SetBarStyle(m_pwndDriveBar->GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// Dock the toolbar
	m_pwndDriveBar->EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(m_pwndDriveBar);

	return;

}

//
//void CMainFrame::OnDeviceChange(UINT nID, DWORD dwData) 
//{
//	CMDIFrameWnd::OnDeviceChange(nID, dwData);
//
//	if (nID == DBT_DEVICEARRIVAL || nID == DBT_DEVICEREMOVECOMPLETE)
//		LoadDriveBar();	
//	
//}

// find every pixel of the default background color in the specified
// bitmap and set each one to the user's button color.
static void	ReplaceBackgroundColor (CBitmap& ioBM)
{
 // figure out how many pixels there are in the bitmap
 BITMAP		bmInfo;

 VERIFY (ioBM.GetBitmap (&bmInfo));

 // add support for additional bit depths if you choose
 VERIFY (bmInfo.bmBitsPixel == 24);
 VERIFY (bmInfo.bmWidthBytes == (bmInfo.bmWidth * 3));

 const UINT		numPixels (bmInfo.bmHeight * bmInfo.bmWidth);

 // get a pointer to the pixels
 DIBSECTION  ds;

 VERIFY (ioBM.GetObject (sizeof (DIBSECTION), &ds) == sizeof (DIBSECTION));

 RGBTRIPLE*		pixels = reinterpret_cast<RGBTRIPLE*>(ds.dsBm.bmBits);
 VERIFY (pixels != NULL);

 // get the user's preferred button color from the system
 const COLORREF		buttonColor (::GetSysColor (COLOR_BTNFACE));
 const RGBTRIPLE		userBackgroundColor = {
 GetBValue (buttonColor), GetGValue (buttonColor), GetRValue (buttonColor)};

 // search through the pixels, substituting the user's button
 // color for any pixel that has the magic background color
 for (UINT i = 0; i < numPixels; ++i)
 {
  if (pixels [i].rgbtBlue == kBackgroundColor.rgbtBlue 
  && pixels [i].rgbtGreen == kBackgroundColor.rgbtGreen 
  && pixels [i].rgbtRed == kBackgroundColor.rgbtRed)
  {
   pixels [i] = userBackgroundColor;
  }
 }
}


// create an image list for the specified BMP resource
static void	MakeToolbarImageList (UINT inBitmapID,
                                  CImageList&	outImageList)
{
 CBitmap		bm;

 // if we use CBitmap::LoadBitmap() to load the bitmap, the colors
 // will be reduced to the bit depth of the main screen and we won't
 // be able to access the pixels directly. To avoid those problems,
 // we'll load the bitmap as a DIBSection instead and attach the
 // DIBSection to the CBitmap.
 VERIFY (bm.Attach (::LoadImage (::AfxFindResourceHandle(
 MAKEINTRESOURCE (inBitmapID), RT_BITMAP),
 MAKEINTRESOURCE (inBitmapID), IMAGE_BITMAP, 0, 0,
 (LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

 // replace the specified color in the bitmap with the user's
 // button color
 ::ReplaceBackgroundColor (bm);

 // create a 24 bit image list with the same dimensions and number
 // of buttons as the toolbar
 VERIFY (outImageList.Create (kImageWidth, kImageHeight, kToolBarBitDepth, kNumImages, 0));

 // attach the bitmap to the image list
 VERIFY (outImageList.Add (&bm, RGB (0, 0, 0)) != -1);
}


