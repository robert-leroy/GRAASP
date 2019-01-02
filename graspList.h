// graspView.h : interface of the CGraspList class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRASPVIEW_H__4747BA3F_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
#define AFX_GRASPVIEW_H__4747BA3F_36B0_11D1_B041_00AA00200BC7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// This structure is used to pass information to the sort routines
// It can be modified when new information is required for sorting
class CSortData;
 
// Create a pionter datatype for the sort functions
typedef int (* pfSort)(LPARAM lParam1, LPARAM lParam2, CSortData *psd);

// Structure used to pass values to the sort routines
class CSortData
{
public:
	BOOL	bSortAscending;
	pfSort	pfSortFunction;
};

class CGraspList : public CListView
{
private:
    static CTime ConvertDate(CString dt);

protected: // create from serialization only
	CGraspList();
	DECLARE_DYNCREATE(CGraspList)

	BOOL CalcStringEllipsis(HDC hdc, CString *strString, int cchMax, UINT uColWidth);
	void DrawItemColumn(CDC* cdc, CString lpsz, LPRECT prcClip);
	void DrawItemColumnRight(CDC* cdc, CString lpsz, LPRECT prcClip);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItem);
	double DrawBar(HDC hdc, LONGLONG llDirSize, LPRECT prcClip, BOOL bSelected);

// Sorting routines
	static int CALLBACK ListViewCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int SortName(LPARAM lParam1, LPARAM lParam2, CSortData *psd);
	static int SortSize(LPARAM lParam1, LPARAM lParam2, CSortData *psd);
	static int SortCount(LPARAM lParam1, LPARAM lParam2, CSortData *psd);
	static int SortDate(LPARAM lParam1, LPARAM lParam2, CSortData *psd);

	void OpenItem();
	void ShowParent();
	void DeleteAllPointers();
	void DeleteItem();

// Attributes
	CBrush m_brushYellow;
	CBrush m_brushGreen;
	CBrush m_brushRed;
	CBrush m_brushWindow;
	CBrush m_brushSelected;
	CPen   m_penWindow;
	CPen   m_penBlack;
	CPen   m_penSelected;

    int	   m_iCurrSortColumn;
	BOOL   m_abSortOrder[7];
	int    m_iDrawCol;
	int    m_aiColSize[6];

// Printing Variables
	CFont  m_FontGrasp;
	int m_nHeight;
	int m_nItemsPerPage;

public:
	CGraspDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraspList)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraspList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CGraspList)
	afx_msg void OnDestroy();
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGraspListOpen();
	afx_msg void OnGraspListProp();
	afx_msg void OnGraspListDelete();
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnGraspListClose();
	afx_msg void OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDividerDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in graspView.cpp
inline CGraspDoc* CGraspList::GetDocument()
   { return (CGraspDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRASPVIEW_H__4747BA3F_36B0_11D1_B041_00AA00200BC7__INCLUDED_)
