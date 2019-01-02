// graspTree.h : interface of the CGraspTree class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRASPTREE_H__4747BA3F_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
#define AFX_GRASPTREE_H__4747BA3F_36B0_11D1_B041_00AA00200BC7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGraspTree : public CTreeView
{
protected: // create from serialization only
	CGraspTree();
	DECLARE_DYNCREATE(CGraspTree)

// Attributes
public:
	CGraspDoc* GetDocument();
	CImageList m_imgList;
	void DeleteAllPointers();
	void DeleteChildren(HTREEITEM hTreeItem);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraspTree)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnFilePrint();
	virtual void OnFilePrintPreview();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraspTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraspTree)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnGraspListClose();
	afx_msg void OnGraspListDelete();
	afx_msg void OnGraspListOpen();
	afx_msg void OnGraspListProp();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in graspTree.cpp
inline CGraspDoc* CGraspTree::GetDocument()
   { return (CGraspDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRASPTREE_H__4747BA3F_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
