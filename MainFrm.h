// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4747BA39_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
#define AFX_MAINFRM_H__4747BA39_36B0_11D1_B041_00AA00200BC7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ToolBarEx.h"

void ReplaceBackgroundColor (CBitmap& ioBM);
void MakeToolbarImageList (UINT inBitmapID, CImageList&	outImageList);

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

	CStringArray m_astrDriveList;
	UINT  m_aDriveID[26];

// Operations
public:
	void LoadDriveBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar*	m_pwndDriveBar;
	CToolBar	m_wndToolBar;
	CToolTipCtrl m_wndToolTips;

public:
	CImageList m_ToolbarImagesDisabled;
	CImageList m_ToolbarImagesHot;
	CImageList m_ToolbarImages;

	CImageList m_DrivebarImagesDisabled;
	CImageList m_DrivebarImagesHot;
	CImageList m_DrivebarImages;

	CImageList  m_imgSmallList;
	CImageList  m_imgBigList;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnDeviceChange(UINT nID, DWORD dwData);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4747BA39_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
