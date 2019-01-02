// DiskProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiskProp dialog
//{{AFX_INCLUDES()
//}}AFX_INCLUDES

class CDiskProp : public CDialog
{
// Construction
public:
	CDiskProp(CWnd* pParent = NULL);   // standard constructor

	LONGLONG m_llFreeSpace;
	LONGLONG m_llUsedSpace;

// Dialog Data
	//{{AFX_DATA(CDiskProp)
	enum { IDD = IDD_DISK_PROP };
	CString	m_strAvail;
	CString	m_strAvailClusters;
	CString	m_strBytes;
	CString	m_strClusters;
	CString	m_strGrasp;
	CString	m_strSectors;
	CString	m_strTotal;
	CString	m_strCompressed;
	CString	m_strFileSystem;
	CString	m_strSerialNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiskProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiskProp)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
