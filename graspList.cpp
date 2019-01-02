// graspView.cpp : implementation of the CGraspList class
//

#include "stdafx.h"
#include "grasp95.h"
#include "ProgDlg.h"

#include "FileSize.h"
#include "ToolBarEx.h"
#include "MainFrm.h"
#include "graspDoc.h"
#include "graspList.h"
#include "resource.h"
#include "FolderProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraspList

IMPLEMENT_DYNCREATE(CGraspList, CListView)

BEGIN_MESSAGE_MAP(CGraspList, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CGraspList)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_GRASP_LIST_OPEN, OnGraspListOpen)
	ON_COMMAND(ID_GRASP_LIST_PROP, OnGraspListProp)
	ON_COMMAND(ID_GRASP_LIST_DELETE, OnGraspListDelete)
	ON_WM_SYSKEYDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_GRASP_LIST_CLOSE, OnGraspListClose)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemChanged)
	ON_NOTIFY(HDN_DIVIDERDBLCLICK , 0, OnDividerDblClick)
	//}}AFX_MSG_MAP
#ifndef _SHAREWARE
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraspList construction/destruction

CGraspList::CGraspList()
{
	// Init the Col Size array to zero
	for (int x=0; x<4; x++)
		m_aiColSize[x] = 0;
}

CGraspList::~CGraspList()
{
}

BOOL CGraspList::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SORTASCENDING | LVS_OWNERDRAWFIXED | LVS_SHAREIMAGELISTS | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraspList drawing
//		Because this view is really an ListControl, 
//		OnDraw is really only called when we print

void CGraspList::OnDraw(CDC* pDC)
{
	CGraspDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	return;
}

/////////////////////////////////////////////////////////////////////////////
// CGraspList diagnostics

#ifdef _DEBUG
void CGraspList::AssertValid() const
{
	CListView::AssertValid();
}

void CGraspList::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CGraspDoc* CGraspList::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraspDoc)));
	return (CGraspDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraspList message handlers

void CGraspList::OnInitialUpdate() 
{
	// Wizard added
	CListView::OnInitialUpdate();

	// Declare Variables
	LV_COLUMN lvc;

	// Get ListCtrl Reference
	CListCtrl& graspList = GetListCtrl();

	// Init sort orders
	memset(m_abSortOrder,TRUE,sizeof(m_abSortOrder));

	// Insert NAME Column
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvc.pszText = _T("Name");
	lvc.cchTextMax = 4;
	lvc.cx = 150;
	lvc.iSubItem = 0;
	graspList.InsertColumn(0,&lvc);

	// Insert SIZE Column
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvc.pszText = _T("Size");
	lvc.cchTextMax = 4;
	lvc.cx = 100;
	lvc.iSubItem = 1;
	graspList.InsertColumn(1,&lvc);

	// Insert BAR Column
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvc.pszText = _T("Size");
	lvc.cchTextMax = 4;
	lvc.cx = 150;
	lvc.iSubItem = 2;
	graspList.InsertColumn(2,&lvc);

	// Insert PERCENT Column
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvc.pszText = _T("Percent");
	lvc.cchTextMax = 4;
	lvc.cx = 50;
	lvc.iSubItem = 3;
	graspList.InsertColumn(3,&lvc);

	// Insert DATE Column
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvc.pszText = _T("Date");
	lvc.cchTextMax = 4;
	lvc.cx = 100;
	lvc.iSubItem = 4;
	graspList.InsertColumn(4,&lvc);

    // Insert ITEMS Column
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvc.pszText = _T("Items");
	lvc.cchTextMax = 4;
	lvc.cx = 50;
	lvc.iSubItem = 5;
	graspList.InsertColumn(5,&lvc);

	m_brushYellow.CreateSolidBrush(RGB(255,255,0));
	m_brushGreen.CreateSolidBrush(RGB(0,255,0));
	m_brushRed.CreateSolidBrush(RGB(255,0,0));
	m_brushWindow.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	m_brushSelected.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
	
	m_penWindow.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
	m_penBlack.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	m_penSelected.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_HIGHLIGHT));

	CGraspApp* pApp = (CGraspApp*)AfxGetApp();
	CMainFrame* pWnd = (CMainFrame*)pApp->m_pMainWnd;
	CImageList* pList = &(pWnd->m_imgSmallList);
	graspList.SetImageList(pList, LVSIL_SMALL);

}

void CGraspList::DrawItem(LPDRAWITEMSTRUCT lpDrawItem) 
{
    CString strTextOut;
    LV_ITEM lvi;
    RECT rcClip;
	UINT uiFlags = ILD_TRANSPARENT;
	TCHAR szText[256];

	// Get a reference to the ListCtrl
	CListCtrl &pgraspList = GetListCtrl();

    // Get the item image to be displayed
    lvi.mask = LVIF_IMAGE | LVIF_STATE | LVIF_PARAM | LVIF_TEXT;
    lvi.iItem = lpDrawItem->itemID;
    lvi.iSubItem = 0;
	lvi.pszText = szText;
	lvi.cchTextMax = 256;
    pgraspList.GetItem(&lvi);
	
    // Check to see if this item is selected
    if (lpDrawItem->itemState & ODS_SELECTED)
    {
        // Set the text background and foreground colors
        ::SetTextColor(lpDrawItem->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
        ::SetBkColor(lpDrawItem->hDC, GetSysColor(COLOR_HIGHLIGHT));

		// Also add the ILD_BLEND50 so the images come out selected
		uiFlags |= ILD_BLEND50;
    }
    else
    {
        // Set the text background and foreground colors to the standard window
        // colors
        ::SetTextColor(lpDrawItem->hDC, GetSysColor(COLOR_WINDOWTEXT));
        ::SetBkColor(lpDrawItem->hDC, GetSysColor(COLOR_WINDOW));
    }

	int iSubItem = 0;

	CDC cdc;
	cdc.Attach(lpDrawItem->hDC);

    // Get the image list and draw the image
    CImageList *pImgList = pgraspList.GetImageList(LVSIL_SMALL);
    if (pImgList)
    {
		POINT pt;
		pt.x = lpDrawItem->rcItem.left;
		pt.y = lpDrawItem->rcItem.top;

		pImgList->Draw(&cdc, lvi.iImage, pt, ILD_NORMAL);
    }

	// Set up the new clipping rect for the NAME column text and draw it
	rcClip.left = lpDrawItem->rcItem.left + 16;
	rcClip.right = lpDrawItem->rcItem.left + pgraspList.GetColumnWidth(iSubItem++);
	rcClip.top = lpDrawItem->rcItem.top;
	rcClip.bottom = lpDrawItem->rcItem.bottom;
	m_iDrawCol = 0;
	DrawItemColumn(&cdc, lvi.pszText, &rcClip);

    // Update the clip rect and draw the SIZE column
	rcClip.left = rcClip.right;
	rcClip.right = rcClip.left + pgraspList.GetColumnWidth(iSubItem++);
	ULONGLONG  llFileSize = ((CGraspFileSize*)lvi.lParam)->GetSize();
	strTextOut = ((CGraspFileSize*)lvi.lParam)->FormatSize();
	m_iDrawCol = 1;
	DrawItemColumnRight(&cdc, strTextOut, &rcClip);

	// BARGRAPH Column
	rcClip.left = rcClip.right;
	rcClip.right = rcClip.left + pgraspList.GetColumnWidth(iSubItem++);
	m_iDrawCol = 2;
	double fPercent = DrawBar(cdc.m_hDC, llFileSize, &rcClip, lpDrawItem->itemState & ODS_SELECTED);

    // PERCENT column
	rcClip.left = rcClip.right;
	rcClip.right = rcClip.left + pgraspList.GetColumnWidth(iSubItem++);
	strTextOut.Format(_T("%.1f%%"),fPercent * 100);
	m_iDrawCol = 3;
	DrawItemColumnRight(&cdc, strTextOut, &rcClip);

    // DATE column
	rcClip.left = rcClip.right;
	rcClip.right = rcClip.left + pgraspList.GetColumnWidth(iSubItem++);
	m_iDrawCol = 4;
    // Chop up the date/time and grab just the date part
    CString strTmp = ((CGraspFileSize*)lvi.lParam)->GetDate();
    int Pos = strTmp.Find(" ");
    strTmp = strTmp.Left(Pos);
    // Print out the date string
	DrawItemColumnRight(&cdc, strTmp, &rcClip);

    // COUNT column
	rcClip.left = rcClip.right;
	rcClip.right = rcClip.left + pgraspList.GetColumnWidth(iSubItem++);
	m_iDrawCol = 5;
    DrawItemColumnRight(&cdc, ((CGraspFileSize*)lvi.lParam)->FormatCount(), &rcClip);

	// If we changed the colors for the selected item, undo it
    if (lpDrawItem->itemState & ODS_SELECTED)
    {
        // Set the text background and foreground colors
        ::SetTextColor(cdc.m_hDC, GetSysColor(COLOR_WINDOWTEXT));
        ::SetBkColor(cdc.m_hDC, GetSysColor(COLOR_WINDOW));
    }

    // If the item is focused, now draw a focus rect around the entire row
    if (lpDrawItem->itemState & ODS_FOCUS)
	{
		// Only draw to the last column, not the filler column
		lpDrawItem->rcItem.right = rcClip.right;
        DrawFocusRect(cdc.m_hDC, &lpDrawItem->rcItem);
	}

	cdc.Detach();

    return;	
}

void CGraspList::DrawItemColumn(CDC* cdc, CString strOut, LPRECT prcClip)
{
    CString szString;

    // Check to see if the string fits in the clip rect.  If not, truncate
    // the string and add "...".
    szString = strOut;
    CalcStringEllipsis(cdc->m_hDC, &szString, 256, prcClip->right - prcClip->left);

    // print the text
    cdc->ExtTextOut(prcClip->left + 2, prcClip->top + 1, ETO_CLIPPED | ETO_OPAQUE,
               prcClip, szString, szString.GetLength(), NULL);

}

void CGraspList::DrawItemColumnRight(CDC* cdc, CString strOut, LPRECT prcClip)
{
    CString szString;

    // Check to see if the string fits in the clip rect.  If not, truncate
    // the string and add "...".
    szString = strOut;
    CalcStringEllipsis(cdc->m_hDC, &szString, 256, prcClip->right - prcClip->left);

    // print the text
	cdc->SetTextAlign(TA_RIGHT);
    cdc->ExtTextOut(prcClip->right - 1, prcClip->top + 1, ETO_CLIPPED | ETO_OPAQUE,
               prcClip, szString, szString.GetLength(), NULL);
	cdc->SetTextAlign(TA_LEFT);

}

BOOL CGraspList::CalcStringEllipsis(HDC hdc, CString* strString, int cchMax, UINT uColWidth)
{
    CString strEllipsis = TEXT("...");
    SIZE   sizeString;
    SIZE   sizeEllipsis;
    int    cbString;
    CString strTemp;
    BOOL   fSuccess = FALSE;
    

    // Adjust the column width to take into account the edges
    uColWidth -= 4;
    strTemp = *strString;

    // Get the width of the string in bytes
    cbString = strTemp.GetLength();

    if (GetTextExtentPoint32(hdc, strTemp, cbString, &sizeString))
    {
	    if (sizeString.cx > m_aiColSize[m_iDrawCol])
			m_aiColSize[m_iDrawCol] = sizeString.cx;

		// If the width of the string is greater than the column width shave
		// the string and add the ellipsis
		if ((ULONG)sizeString.cx > uColWidth)
		{
			if (GetTextExtentPoint32(hdc, strEllipsis, strEllipsis.GetLength(), &sizeEllipsis))
			{

				while (cbString > 0)
				{
					strTemp = strTemp.Left(--cbString -1);
					if (GetTextExtentPoint32(hdc, strTemp, cbString, &sizeString))
					{
						if ((ULONG)(sizeString.cx + sizeEllipsis.cx) <= uColWidth)
						{
							// The string with the ellipsis finally fits, now make sure
							// there is enough room in the string for the ellipsis
							if (cchMax >= (cbString + strEllipsis.GetLength()))
							{
								// Concatenate the two strings and break out of the loop
								strTemp += strEllipsis;
								*strString = strTemp;
								fSuccess = TRUE;
								cbString = 0; // Exits loop
							}
						}
					}
				}
			}
		}
		else
		{
			// Nothing to do
			fSuccess = TRUE;
		}
    }

	return (fSuccess);
}

double CGraspList::DrawBar(HDC hdc, LONGLONG llDirSize, LPRECT prcClip, BOOL bSelected)
{

	// Declare Variables
	long double fSize, fDir;
	double fPercent;
	HGDIOBJ gdiPrev;
	
	// Initialize Variables
	fSize = fDir = 0;
	fPercent = 0;

	CGraspDoc *pDoc = GetDocument();
	
	if (GetDocument()->m_llSelectedSize > 0)
	{
		
		// Calculate Percentage
		fSize = (long double)llDirSize;

		// Compare to this directory or the Drive
		if (pDoc->m_bDirDisk)
			fDir  = (long double) pDoc->m_llSelectedSize;
		else
			fDir  = (long double) pDoc->m_llDriveSize;

		// Calculate the Size
		fPercent = (double)(fSize / fDir);
		
		// Erase everything
		if (bSelected)
		{
			gdiPrev = SelectObject(hdc, m_brushSelected);
			SelectObject(hdc, m_penSelected);
		}
		else
		{
			gdiPrev = SelectObject(hdc, m_brushWindow);
			SelectObject(hdc, m_penWindow);
		}
		Rectangle(hdc,prcClip->left, prcClip->top, prcClip->right, prcClip->bottom);

		// Draw the bar only when there's some to draw
		if (fPercent > .01)
		{
			double nRight = prcClip->left + (prcClip->right - prcClip->left) * fPercent;
			if (fPercent > .5)
				SelectObject(hdc, m_brushRed);
			else
				if (fPercent > .25)
					SelectObject(hdc, m_brushYellow);
				else
					SelectObject(hdc, m_brushGreen);
			SelectObject(hdc, m_penBlack);
			Rectangle(hdc, prcClip->left + 2, prcClip->top + 1, (long) nRight, prcClip->bottom - 1);
		}
	
		SelectObject(hdc,gdiPrev);

	}
	
	return(fPercent);

}

void CGraspList::OnDestroy() 
{
	DeleteAllPointers();
	CListView::OnDestroy();
}

void CGraspList::DeleteAllPointers()
{
	// Delete all item pointers, then all items
	int nItems = GetListCtrl().GetItemCount();
	for (int x=0; x < nItems; x++)
		delete (CGraspFileSize*) GetListCtrl().GetItemData(x);
	GetListCtrl().DeleteAllItems();
}

void CGraspList::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	// Change the cursor to an hour glass
	CWaitCursor csr;

	// Structure to pass info to the sort routines
	CSortData sd;

	// Determine which column sort function to call
    switch (pNMListView->iSubItem)
    {
        case  0:
		    sd.pfSortFunction = &SortName;
            break;
        case  4:
            sd.pfSortFunction = &SortDate;
            break;
        case  5:
            sd.pfSortFunction = &SortCount;
            break;
        default:
			sd.pfSortFunction = &SortSize;
            break;
    }

	// Determine which sort order to use
	if (m_iCurrSortColumn == pNMListView->iSubItem)
		sd.bSortAscending = m_abSortOrder[pNMListView->iSubItem];
	else
		sd.bSortAscending = m_abSortOrder[pNMListView->iSubItem] = TRUE;

	m_iCurrSortColumn = pNMListView->iSubItem;

	// Call the list view sort member function
	GetListCtrl().SortItems( ListViewCompare, (LPARAM)(&sd));

	// Flip the sort order for the next time true
	m_abSortOrder[pNMListView->iSubItem] = !m_abSortOrder[pNMListView->iSubItem];

	*pResult = 0;
}

// Sort function called for every item that needs to be sorted
int CALLBACK CGraspList::ListViewCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{

	// Get the data passed
	CSortData *psd = (CSortData*) lParamSort;
	int nRet;

	// Call the approriate sort function
	nRet = (*psd->pfSortFunction)(lParam1, lParam2, psd);

	// This 'if' handles the flipping of orders when columns are clicked on 
	// multiple times.  The sort routines assume ascending order.  Therefore;
	// if we are ascending or the values are equal, just return it
	// if we are descending, then invert the return value
	if (psd->bSortAscending || nRet == 0)
		return nRet;
	else
		return (nRet * -1);

}

// Sort the NAME Column
int CGraspList::SortName(LPARAM lParam1, LPARAM lParam2, CSortData *psd)
{

	CGraspFileSize *psi1, *psi2;

	// Get pointers to the items
	psi1 = (CGraspFileSize*) lParam1;
	psi2 = (CGraspFileSize*) lParam2;

	CString strOne = psi1->GetName();
	CString strTwo = psi2->GetName();
	strOne.MakeUpper();
	strTwo.MakeUpper();

	// Return the sort order
	if (strOne > strTwo)
		return 1;
	else
		if (strOne < strTwo)
			return -1;
		else
			return 0;

}

// Sort the COUNT Column
int CGraspList::SortCount(LPARAM lParam1, LPARAM lParam2, CSortData *psd)
{

	CGraspFileSize *psi1, *psi2;

	// Get pointers to the items
	psi1 = (CGraspFileSize*) lParam1;
	psi2 = (CGraspFileSize*) lParam2;

	LONG lngOne = psi1->GetFileCount();
	LONG lngTwo = psi2->GetFileCount();

	// Return the sort order
	if (lngOne > lngTwo)
		return 1;
	else
		if (lngOne < lngTwo)
			return -1;
		else
			return 0;
}

// Sort the DATE Column
int CGraspList::SortDate(LPARAM lParam1, LPARAM lParam2, CSortData *psd)
{

	CGraspFileSize *psi1, *psi2;

	// Get pointers to the items
	psi1 = (CGraspFileSize*) lParam1;
	psi2 = (CGraspFileSize*) lParam2;

	CString strOne = psi1->GetDate();
	CString strTwo = psi2->GetDate();
	CTime dtOne = ConvertDate(strOne);
	CTime dtTwo = ConvertDate(strTwo);

 	// Return the sort order
	if (dtOne > dtTwo)
		return 1;
	else
		if (dtOne < dtTwo)
			return -1;
		else
			return 0;

}

// Sort the SIZE Column
int CGraspList::SortSize(LPARAM lParam1, LPARAM lParam2, CSortData *psd)
{

	CGraspFileSize *psi1, *psi2;

	// Get pointers to the items
	psi1 = (CGraspFileSize*) lParam1;
	psi2 = (CGraspFileSize*) lParam2;

	// Return the sort order
	ULONGLONG   d1 = psi1->GetSize();
	ULONGLONG   d2 = psi2->GetSize();

	if (d1 > d2)
		return 1;
	else
		if (d1 < d2)
			return -1;
		else
			return 0;

}

CTime CGraspList::ConvertDate(CString dt)
{
    struct tm tm;

    if (sscanf(dt,"%d/%d/%d %d:%d:%d",&tm.tm_mon,&tm.tm_mday,&tm.tm_year,&tm.tm_hour,&tm.tm_min,&tm.tm_sec)==6)
    {
        CTime tt(tm.tm_year,tm.tm_mon,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
        return tt;
    }
    return 0;
}
void CGraspList::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_GRASP_LIST));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}


void CGraspList::OnGraspListOpen() 
{
	OpenItem();
}

void CGraspList::OnGraspListDelete() 
{
	DeleteItem();
}

void CGraspList::OnGraspListProp() 
{
	CListCtrl& pList = GetListCtrl();
	int iItem = pList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem > -1)
	{
		CGraspFileSize* pSize = (CGraspFileSize*)(pList.GetItemData(iItem));
		CGraspDoc* pDoc = GetDocument();

		CFolderProp dlgProp;
		dlgProp.m_strSpaceUsed = pSize->FormatSize();
		dlgProp.m_strName = pSize->GetName();
		dlgProp.m_strType = pSize->GetFileType();
		dlgProp.m_strLastWritten = pSize->GetDate();
		
		// Move the values from my longlong to long doubles to handle the math
		long double a = (long double) (pSize->GetSize());
		long double b = (long double) (pDoc->m_llDriveSize);
		double pct = (double)(a / b) * 100;

		dlgProp.m_strPercent.Format(_T("%.0f%%"),pct);

		dlgProp.DoModal();
	}
}

void CGraspList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	switch (nChar)
	{
		// Enter Key
		case VK_RETURN:
		{
			OpenItem();
			break;
		}

		// F5 = Refresh
		case VK_F5:
		{
			GetDocument()->OnGraspRefresh();
			break;
		}

		// Backspce Key
		case VK_BACK:
		{
			ShowParent();
			break;
		}

		//Delete Key
		case VK_DELETE:
		{
			DeleteItem();
			break;
		}
	}

	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraspList::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	switch (nChar)
	{
		// Alt-Enter Key
		case VK_RETURN:
		{
			if (nFlags & KF_ALTDOWN)
				OnGraspListProp();
			break;
		}

	}

	CListView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGraspList::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	OpenItem();

	CListView::OnLButtonDblClk(nFlags, point);
}

void CGraspList::OpenItem()
{

	CListCtrl& pList = GetListCtrl();
	int iItem = pList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem > -1)
	{
		CGraspFileSize* pSize = (CGraspFileSize*)(GetListCtrl().GetItemData(iItem));
		CGraspDoc* pDoc = GetDocument();

		if (pSize->IsDir())
		{
			HTREEITEM hTreeItem = pSize->GetItem();
			pDoc->m_pgraspTree->Select(hTreeItem,TVGN_CARET);
			pDoc->m_pgraspTree->SelectItem(hTreeItem);
		}
		else
		{
			CString strName = pDoc->m_strPath + "\\" + pSize->GetName();
			ShellExecute(this->m_hWnd, "open", strName, NULL, NULL, SW_SHOWNORMAL );
		}
	}

}

void CGraspList::DeleteItem()
{
	CListCtrl& pList = GetListCtrl();
	int iItem = pList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem > -1)
	{
		CGraspFileSize* pSize = (CGraspFileSize*)(GetListCtrl().GetItemData(iItem));
		CGraspDoc* pDoc = GetDocument();
		CString strName = pDoc->m_strPath + "\\" + pSize->GetName();
		CString strPrompt = "Do you want to permanently delete this?\n";
		strPrompt += strName;

 		int rtn = MessageBox(strPrompt, _T("Delete"), MB_YESNO | MB_ICONQUESTION);
		
		if (rtn == IDYES)
		{
			// Add the deleted size back into the directory
			HTREEITEM hItem = pDoc->m_pgraspTree->GetSelectedItem();
			CGraspFileSize* ps = (CGraspFileSize*) pDoc->m_pgraspTree->GetItemData(hItem);
			*ps = ps->GetSize() - pSize->GetSize();

			// This includes all parent items too...
			while (hItem = pDoc->m_pgraspTree->GetParentItem(hItem))
			{
				CGraspFileSize* ps = (CGraspFileSize*) pDoc->m_pgraspTree->GetItemData(hItem);
				*ps = ps->GetSize() - pSize->GetSize();
			}

			// Now, if it's a directory, go through and delete everything!
			if (pSize->IsDir())
			{
				pDoc->DeleteDir(strName);
				pDoc->m_pgraspTree->DeleteItem(pSize->GetItem());
			}
			else
				DeleteFile(strName);

			pList.DeleteItem(iItem);
		}
	}
}

void CGraspList::ShowParent()
{
	CGraspDoc* pDoc = GetDocument();
	HTREEITEM hItem = pDoc->m_pgraspTree->GetSelectedItem();
	if (hItem)
	{
		HTREEITEM hParent = pDoc->m_pgraspTree->GetParentItem(hItem);
		if (hParent)
		{
			pDoc->m_pgraspTree->Select(hParent,TVGN_CARET);
		}
	}
}

void CGraspList::OnGraspListClose() 
{
	ShowParent();	
}


void CGraspList::OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	CGraspFileSize* pSize = (CGraspFileSize*) pNMListView->lParam;
	if (pSize)
	{
		CGraspDoc* pDoc = GetDocument();

		if (pDoc->m_bTopTenShowing)
		{
			if (pSize->GetItem() != pDoc->m_pgraspTree->GetSelectedItem())
				pDoc->m_pgraspTree->Select(pSize->GetItem(), TVGN_CARET);
		}
	}
	
	*pResult = 0;
}

void CGraspList::OnDividerDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	
	CHeaderCtrl* pHdrCtrl = (CHeaderCtrl*) CWnd::FromHandle(phdn->hdr.hwndFrom);

	HDITEM hdi;
	hdi.mask = HDI_WIDTH;

	// Get width calculated in the CalcEllipse function.
	hdi.cxy = this->m_aiColSize[phdn->iItem] + 4;

	switch (phdn->iItem)
	{
		// If this is the first col, add space for the icon
		case 0:
			hdi.cxy += 16;
			break;
		// If this is the bar col, default the space
		case 2:
			hdi.cxy = 125;
			break;
	}

	// Update the item width
	pHdrCtrl->SetItem(phdn->iItem, &hdi);

	*pResult = 0;
}

BOOL CGraspList::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// Set number of pages

	// default preparation

	return DoPreparePrinting(pInfo);
}

void CGraspList::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{

	// To set num of pages based on DC
	// We need to know how big this device is....
	int nHorzRes = pDC->GetDeviceCaps(HORZRES);
	int nVertRes = pDC->GetDeviceCaps(VERTRES);

	// And how big the current font is...
	// Initializes a CFont object with the specified characteristics. 
	m_nHeight = -MulDiv(11, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	VERIFY(m_FontGrasp.CreateFont(
	   m_nHeight,                 // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_NORMAL,                 // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   "Arial"));           // lpszFacename

	// Add 10% to height
	m_nHeight *= 1.20;

	// Calculate Space used by Headers and Footers 
	//      8 Header Lines
	//      1 Footer Line
	int nHeaderSpace = -(8 * m_nHeight);
	int nFooterSpace = -(1 * m_nHeight);

	// Reduce nVertRes by space for Headers and Footers
	nVertRes -= nHeaderSpace - nFooterSpace;

	// So, Number of pages = 
	//            (Number of Items * Font Height) / Vertical Page Size (less hdr/ftr)
	CListCtrl& pList = GetListCtrl();
	int nPages = -(pList.GetItemCount() * m_nHeight / nVertRes) +1;

	// Calculate hHow many items fit on page for use when printing
	m_nItemsPerPage = -(nVertRes / m_nHeight);

	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(nPages);

//	CListView::OnBeginPrinting(pDC, pInfo);
}


void CGraspList::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CListView::OnPrepareDC(pDC, pInfo);

}


void CGraspList::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CGraspDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFont* pFontPrev = pDC->SelectObject(&m_FontGrasp);

	// Declare Variables
	CString   strItemText;
	CGraspFileSize* pGraspSize;

	// Get Full Path to this directory
	CString strFullPath, strPrevPath;
	HTREEITEM hPathTreeItem = pDoc->m_pgraspTree->GetSelectedItem();
	strFullPath = pDoc->m_pgraspTree->GetItemText(hPathTreeItem);
	while (hPathTreeItem = pDoc->m_pgraspTree->GetParentItem(hPathTreeItem))
	{
		CString strDir = pDoc->m_pgraspTree->GetItemText(hPathTreeItem);
		strPrevPath = strFullPath;
		strFullPath = strDir + "\\" + strFullPath;
	}
	if (strPrevPath.IsEmpty())
		strFullPath = pDoc->m_strDriveLetter;
	else
		strFullPath = pDoc->m_strDriveLetter + "\\" + strPrevPath;

	// In the case of multiple pages
	// Determine which row to start with
	int nItem = ((pInfo->m_nCurPage -1) * m_nItemsPerPage);
	int nItemCount = 0;

	// Now determine how to display the five columns, plus one for margin
	int nHorzRes = pDC->GetDeviceCaps(HORZRES);
	int nVertRes = pDC->GetDeviceCaps(VERTRES);
	int nColWidth = nHorzRes / 7;
	RECT rectItemBox;

	int x, y;
	x = y = 0;

	// Print Current Date and Time
	CTime t = CTime::GetCurrentTime();
	CString strTemp = t.Format( "%B %d, %Y %H:%M" );
	pDC->TextOut(0,0,strTemp);

    // Print the current page number right aligned
    SIZE   sizeString;
	strTemp.Format("Page: %d",pInfo->m_nCurPage);
    int cbString = strTemp.GetLength();
    GetTextExtentPoint32(pDC->m_hDC, strTemp, cbString, &sizeString);
	pDC->TextOut(nHorzRes - sizeString.cx, y, strTemp);
	y += -(m_nHeight);

	// Print our name centered
	strTemp = "Graphical Space Viewer";
    cbString = strTemp.GetLength();
    GetTextExtentPoint32(pDC->m_hDC, strTemp, cbString, &sizeString);
	pDC->TextOut((nHorzRes / 2) - (sizeString.cx / 2), y, strTemp);
	y += -(m_nHeight);

	// Print report name centered
	strTemp = "Directory Report";
    cbString = strTemp.GetLength();
    GetTextExtentPoint32(pDC->m_hDC, strTemp, cbString, &sizeString);
	pDC->TextOut((nHorzRes / 2) - (sizeString.cx / 2), y, strTemp);
	y += -(m_nHeight);

	// Print current path centered
	if (pDoc->m_bTopTenShowing)
		strTemp = "Top 10 largest directories";
	else
		strTemp = strFullPath;

    cbString = strTemp.GetLength();
    GetTextExtentPoint32(pDC->m_hDC, strTemp, cbString, &sizeString);
	pDC->TextOut((nHorzRes / 2) - (sizeString.cx / 2), y, strTemp);
	y += -(m_nHeight);

	// Blank line
	y += -(m_nHeight);

	// Load all children of the selected item into the List
	CListCtrl& pList = GetListCtrl();

	for (; nItem < pList.GetItemCount() && nItemCount++ < m_nItemsPerPage; nItem++)
	{

		pGraspSize = (CGraspFileSize*)pList.GetItemData(nItem);

		// Draw File Name, This gets 1.5 times the column width of other columns
		rectItemBox.left = nColWidth / 2;
		rectItemBox.right = rectItemBox.left + nColWidth + (nColWidth / 2);
		rectItemBox.top = y;
		rectItemBox.bottom = rectItemBox.top + -(m_nHeight);
		DrawItemColumn(pDC,pGraspSize->GetName(), &rectItemBox);

		// Draw Size
		rectItemBox.left = rectItemBox.right;
		rectItemBox.right = rectItemBox.left + nColWidth;
		DrawItemColumnRight(pDC,pGraspSize->FormatSize(), &rectItemBox);

		// Draw Bar
		rectItemBox.left = rectItemBox.right;
		rectItemBox.right = rectItemBox.left + nColWidth;
		ULONGLONG  llFileSize = pGraspSize->GetSize();
		double fPercent = DrawBar(pDC->m_hDC, llFileSize, &rectItemBox, NULL);

		// Percent column.  This column only get half a column
		rectItemBox.left = rectItemBox.right;
		rectItemBox.right = rectItemBox.left + (nColWidth / 2);
		CString strTextOut;
		strTextOut.Format(_T("%.1f%%"),fPercent * 100);
		DrawItemColumnRight(pDC, strTextOut, &rectItemBox);

        // DATE column
        rectItemBox.left = rectItemBox.right;
        rectItemBox.right = rectItemBox.left + nColWidth;
        m_iDrawCol = 4;
        // Chop up the date/time and grab just the date part
        CString strTmp = pGraspSize->GetDate();
        int Pos = strTmp.Find(" ");
        strTmp = strTmp.Left(Pos);
        // Print out the date string
        DrawItemColumnRight(pDC, strTmp, &rectItemBox);

        // COUNT column
        rectItemBox.left = rectItemBox.right;
        rectItemBox.right = rectItemBox.left + nColWidth;
        m_iDrawCol = 5;
        DrawItemColumnRight(pDC, pGraspSize->FormatCount(), &rectItemBox);

		y += -(m_nHeight);
	}

	//  Print footers
	CGdiObject* objPrev = pDC->SelectStockObject(BLACK_PEN);
	pDC->MoveTo(0,nVertRes - -(m_nHeight));
	pDC->LineTo(nHorzRes,nVertRes - -(m_nHeight));
	pDC->SelectObject(objPrev);
//	pDC->SelectObject(m_FontGrasp);
	pDC->TextOut(0,nVertRes - -(m_nHeight) + 10,"Copyright 2004, Robert LeRoy - All Rights Reserved");

	pDC->SelectObject(pFontPrev);

}

void CGraspList::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{

	// Done with the font.  Delete the font object.
	m_FontGrasp.DeleteObject(); 

	
//	CListView::OnEndPrinting(pDC, pInfo);
}



