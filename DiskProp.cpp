// DiskProp.cpp : implementation file
//

#include "stdafx.h"
#include "grasp95.h"
#include "DiskProp.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiskProp dialog


CDiskProp::CDiskProp(CWnd* pParent /*=NULL*/)
	: CDialog(CDiskProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiskProp)
	m_strAvail = _T("");
	m_strAvailClusters = _T("");
	m_strBytes = _T("");
	m_strClusters = _T("");
	m_strGrasp = _T("");
	m_strSectors = _T("");
	m_strTotal = _T("");
	m_strCompressed = _T("");
	m_strFileSystem = _T("");
	m_strSerialNumber = _T("");
	//}}AFX_DATA_INIT
}


void CDiskProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiskProp)
	DDX_Text(pDX, IDC_AVAIL, m_strAvail);
	DDX_Text(pDX, IDC_AVAILABLE, m_strAvailClusters);
	DDX_Text(pDX, IDC_BYTES, m_strBytes);
	DDX_Text(pDX, IDC_CLUSTERS, m_strClusters);
	DDX_Text(pDX, IDC_GRASP, m_strGrasp);
	DDX_Text(pDX, IDC_SECTORS, m_strSectors);
	DDX_Text(pDX, IDC_TOTAL, m_strTotal);
	DDX_Text(pDX, IDC_COMPRESSED, m_strCompressed);
	DDX_Text(pDX, IDC_FILE_SYSTEM, m_strFileSystem);
	DDX_Text(pDX, IDC_SERIAL_NO, m_strSerialNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiskProp, CDialog)
	//{{AFX_MSG_MAP(CDiskProp)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiskProp message handlers

BOOL CDiskProp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDiskProp::OnPaint() 
{

	CPaintDC dc(this); // device context for painting

	int PrevMM = dc.SetMapMode (MM_ISOTROPIC) ;
	CSize PrevWinExt = dc.SetWindowExt (400,400) ;
	CSize PrevViewExt = dc.SetViewportExt (350, -150) ;
	CPoint PrevViewOrg = dc.SetViewportOrg (350 / 2, 150 / 2) ;

	// Create Pens for drawing
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CBrush Brush1(RGB(0,255,0)); 
	CBrush Brush2(RGB(0,128,0));
	CBrush Brush3(RGB(0,0,255));

	// Select Objects and draw shadow circle
	CBrush *oldBrush = dc.SelectObject(&Brush2);
	CPen *oldPen = dc.SelectObject(&pen);
	dc.Ellipse(-100,100,105,-115);

	// Draw Pie chart circle
	dc.SelectObject(&Brush1);
	dc.Ellipse(-100,100,100,-100);

	// Get brush for Used pie slice
	dc.SelectObject(&Brush3);

	// Allocate hold areas
	long double a,b,c;
	float fPercentUsed;

	// Compute Percentage
	a = (long double) m_llUsedSpace;
	b = (long double) m_llFreeSpace;
	c = a + b;
	fPercentUsed = (float)(a / c);
	a = 0;

	// the following was swiped from MSDN
	#define TWO_PI (2.0 * 3.14159)
	#define NUM 2
	short   nValues [NUM];
	short   i, nSum [NUM + 1] ;

	nValues[0] = (short)(fPercentUsed * 100);
	nValues[1] = 100 - nValues[0];
  
	nSum [0] = 0 ;
	for (i = 0 ; i < NUM ; i++)
		 nSum [i + 1] = nSum [i] + nValues [i] ;
  
	i = 0;
	dc.Pie (-100, 100, 100, -100,
		  (short) (100.0 * cos (TWO_PI * nSum [i]     / nSum [NUM])),
		  (short) (100.0 * sin (TWO_PI * nSum [i]     / nSum [NUM])),
		  (short) (100.0 * cos (TWO_PI * nSum [i + 1] / nSum [NUM])),
		  (short) (100.0 * sin (TWO_PI * nSum [i + 1] / nSum [NUM]))) ;
	// end swipe

	// Re-Load GDI objects that were there before we changed them
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);

	dc.SetMapMode (PrevMM ) ;
	dc.SetWindowExt (PrevWinExt) ;
	dc.SetViewportExt (PrevViewExt) ;
	dc.SetViewportOrg (PrevViewOrg) ;
}
