// GraspTree.cpp : implementation of the CGraspTree class
//

#include "stdafx.h"
#include "grasp95.h"
#include "ProgDlg.h"

#include "FileSize.h"
#include "ToolBarEx.h"
#include "MainFrm.h"
#include "graspDoc.h"
#include "GraspTree.h"
#include "resource.h"
#include "FolderProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraspTree

IMPLEMENT_DYNCREATE(CGraspTree, CTreeView)

BEGIN_MESSAGE_MAP(CGraspTree, CTreeView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CGraspTree)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_DESTROY()
	ON_COMMAND(ID_GRASP_LIST_CLOSE, OnGraspListClose)
	ON_COMMAND(ID_GRASP_LIST_DELETE, OnGraspListDelete)
	ON_COMMAND(ID_GRASP_LIST_OPEN, OnGraspListOpen)
	ON_COMMAND(ID_GRASP_LIST_PROP, OnGraspListProp)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
#ifndef _SHAREWARE
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraspTree construction/destruction

CGraspTree::CGraspTree()
{

}

CGraspTree::~CGraspTree()
{
}

BOOL CGraspTree::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_SHOWSELALWAYS | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraspTree drawing

void CGraspTree::OnDraw(CDC* pDC)
{
	CGraspDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

}

/////////////////////////////////////////////////////////////////////////////
// CGraspTree diagnostics

#ifdef _DEBUG
void CGraspTree::AssertValid() const
{
	CTreeView::AssertValid();
}

void CGraspTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CGraspDoc* CGraspTree::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraspDoc)));
	return (CGraspDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraspTree message handlers

void CGraspTree::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	// Set ImageList for the Tree
	CGraspApp* pApp = (CGraspApp*)AfxGetApp();
	CMainFrame* pWnd = (CMainFrame*)pApp->m_pMainWnd;
	CImageList* pList = &(pWnd->m_imgSmallList);
	GetTreeCtrl().SetImageList(pList, TVSIL_NORMAL);
	
}

void CGraspTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!GetDocument()->m_bScanFlag)
		if (!GetDocument()->m_bTopTenShowing)
			GetDocument()->ListFromTree();	
	
	*pResult = 0;
}

void CGraspTree::OnDestroy() 
{
	if (!GetDocument()->m_bScanFlag)
		DeleteAllPointers();

	CTreeView::OnDestroy();
	
}

void CGraspTree::DeleteAllPointers()
{
	
	CGraspFileSize* sFileSize;

	if (!GetDocument()->m_bScanFlag)
	{
		if (GetDocument()->m_hRootItem)
		{
			sFileSize = (CGraspFileSize*)(GetTreeCtrl().GetItemData(GetDocument()->m_hRootItem));
			delete sFileSize;

			if (GetTreeCtrl().ItemHasChildren(GetDocument()->m_hRootItem))
				DeleteChildren(GetDocument()->m_hRootItem);
		}
	}

	return;
}

void CGraspTree::DeleteChildren(HTREEITEM hTreeItem)
{
	CGraspFileSize* sFileSize;

	// Get the child item information
	hTreeItem = GetTreeCtrl().GetChildItem(hTreeItem);

	do 
	{
		sFileSize = (CGraspFileSize*)GetTreeCtrl().GetItemData(hTreeItem);
		delete sFileSize;

		if (GetTreeCtrl().ItemHasChildren(hTreeItem))
			DeleteChildren(hTreeItem);

	} while (hTreeItem = GetTreeCtrl().GetNextSiblingItem(hTreeItem));

}


void CGraspTree::OnGraspListClose() 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem)
	{
		hItem = GetTreeCtrl().GetParentItem(hItem);
		if (hItem)
			GetTreeCtrl().SelectItem(hItem);
	}
	
}

void CGraspTree::OnGraspListDelete() 
{
	CTreeCtrl& pTree = GetTreeCtrl();
	HTREEITEM hItem = pTree.GetSelectedItem();
	if (hItem)
	{
		CGraspFileSize* pSize = (CGraspFileSize*)(pTree.GetItemData(hItem));
		CGraspDoc* pDoc = GetDocument();
		CString strName = pDoc->m_strPath;
		CString strPrompt = "Do you want to permanently delete this?\n";
		strPrompt += strName;

		int rtn = MessageBox(strPrompt, _T("Delete"), MB_YESNO | MB_ICONQUESTION);
		
		// Now, if it's a directory, go through and delete everything!
		if (rtn == IDYES)
		{
			if (pSize->IsDir())
				pDoc->DeleteDir(strName);
			else
				DeleteFile(strName);

			pTree.DeleteItem(hItem);
		}
	}	
}

void CGraspTree::OnGraspListOpen() 
{
	
}

void CGraspTree::OnGraspListProp() 
{	
	CTreeCtrl& pTree = GetTreeCtrl();
	HTREEITEM hItem = pTree.GetSelectedItem();
	if (hItem)
	{
		CGraspFileSize* pSize = (CGraspFileSize*)(pTree.GetItemData(hItem));
		CGraspDoc* pDoc = GetDocument();

		CFolderProp dlgProp;
		dlgProp.m_strSpaceUsed = pSize->FormatSize();
		dlgProp.m_strName = pSize->GetName();
		dlgProp.m_strType = pSize->GetFileType();
		dlgProp.m_strLastWritten = pSize->GetDate();
		
		double pct = (double)(pSize->GetSize() / pDoc->m_llDriveSize) * 100;
		dlgProp.m_strPercent.Format(_T("%.0f%%"),pct);

		dlgProp.DoModal();
	}
}

void CGraspTree::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	switch (nChar)
	{
		// F5 = Refresh
		case VK_F5:
		{
			GetDocument()->OnGraspRefresh();
			break;
		}

	}	
	CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraspTree::OnFilePrint()
{
	CGraspDoc* pDoc = GetDocument();
	::PostMessage(pDoc->m_pgraspList->m_hWnd,WM_COMMAND,ID_FILE_PRINT, 0);
}

void CGraspTree::OnFilePrintPreview()
{
	CGraspDoc* pDoc = GetDocument();
	::PostMessage(pDoc->m_pgraspList->m_hWnd,WM_COMMAND,ID_FILE_PRINT_PREVIEW, 0);
}

