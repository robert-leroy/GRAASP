#if !defined(AFX_SHAREWARE_H__4AAEB221_6510_11D1_8278_006097894831__INCLUDED_)
#define AFX_SHAREWARE_H__4AAEB221_6510_11D1_8278_006097894831__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Shareware.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShareware dialog

class CShareware : public CDialog
{
// Construction
public:
	CShareware(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShareware)
	enum { IDD = IDD_SPLASH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareware)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShareware)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAREWARE_H__4AAEB221_6510_11D1_8278_006097894831__INCLUDED_)
