// grasp95.h : main header file for the GRASP95 application
//

#if !defined(AFX_GRASP95_H__4747BA35_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
#define AFX_GRASP95_H__4747BA35_36B0_11D1_B041_00AA00200BC7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraspApp:
// See grasp95.cpp for the implementation of this class
//

class CGraspApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGraspApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraspApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGraspApp)
	afx_msg void OnAppAbout();
	afx_msg BOOL OnDriveCommand(UINT nID);
	afx_msg void OnAppHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRASP95_H__4747BA35_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
