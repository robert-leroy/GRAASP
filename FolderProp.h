#if !defined(AFX_FOLDERPROP_H__B539A9A3_54F9_11D1_8278_50D406C10000__INCLUDED_)
#define AFX_FOLDERPROP_H__B539A9A3_54F9_11D1_8278_50D406C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FolderProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFolderProp dialog

class CFolderProp : public CDialog
{
// Construction
public:
	CFolderProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFolderProp)
	enum { IDD = IDD_FOLDER_PROP };
	CString	m_strSpaceUsed;
	CString	m_strName;
	CString	m_strPercent;
	CString	m_strType;
	CString	m_strLastWritten;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFolderProp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERPROP_H__B539A9A3_54F9_11D1_8278_50D406C10000__INCLUDED_)
