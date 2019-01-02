// graspDoc.h : interface of the CGraspDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRASPDOC_H__4747BA3D_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
#define AFX_GRASPDOC_H__4747BA3D_36B0_11D1_B041_00AA00200BC7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGraspDoc : public CDocument
{
protected: // create from serialization only
	CGraspDoc();
	DECLARE_DYNCREATE(CGraspDoc)

// Stuff I need for TopTen list
	CGraspFileSize*  aGraspSize[10];

// Attributes
public:

// Operations
public:

// Member Functions
	BOOL ScanDrive();
	LONGLONG ScanSubDir(CString strDir, HTREEITEM hParentItem);
	BOOL ListFromTree();
	BOOL ListFromDir(CString strDir);
	int CountRootDirs();
	BOOL DeleteDir(CString strDir);
	void FindTopTen(HTREEITEM hTreeItem);

// Grasp View Controls
	CTreeCtrl *m_pgraspTree;
	CListCtrl *m_pgraspList;

// Volume Information
	CString m_strDriveLetter;
	CString m_strVolumeName;
	CString m_strFileSysName;
	DWORD   m_dwVolumeSerial;
	DWORD   m_dwMaxFileNameLen;
	DWORD   m_dwFileSysFlags;
	LONGLONG  m_llSelectedSize;
	LONGLONG  m_llDriveSize;
	HTREEITEM m_hRootItem;
	BOOL	m_bDirDisk;
	BOOL    m_bTopTenShowing;

//  Other things
	CProgressDlg* m_pdlgProgress;
	CString m_strPath;
	BOOL m_bScanFlag;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraspDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraspDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	UINT m_nFolderOpen;
	UINT m_nFolderClosed;

// Generated message map functions
public:
	//{{AFX_MSG(CGraspDoc)
	afx_msg void OnFileProperties();
	afx_msg void OnGraspRefresh();
	afx_msg void OnGraspDirdisk();
	afx_msg void OnUpdateGraspDirdisk(CCmdUI* pCmdUI);
	afx_msg void OnGraspTopten();
	afx_msg void OnUpdateGraspTopTen(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRASPDOC_H__4747BA3D_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
