// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "grasp95.h"
#include "MainFrm.h"

#include "ProgDlg.h"
#include "ChildFrm.h"

#include "FileSize.h"
#include "graspDoc.h"
#include "graspTree.h"
#include "graspList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
		ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
		ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	BOOL ok = m_wndSplitter.CreateStatic( this, 1, 2);
	ok = m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CGraspTree),
										CSize(200,200),pContext);
	ok = m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CGraspList),
										CSize(100,100),pContext);

	return ok;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
/////////////////////////////////////////////////////////////////////////////
// CMyChildFrame message handlers
extern CStringArray g_strDriveNames;
BOOL CChildFrame::GetToolText( UINT nID, CString& strTipText )
{
	CString m_strVolumeName;
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();

    for (int x = 0; x < g_strDriveNames.GetCount(); x++)
    {
        int nLen = g_strDriveNames[x].Find('(');
        if (nID == ID_DRIVE_BASE + g_strDriveNames[x][nLen+1] - 65)
            strTipText = g_strDriveNames[x];
    }

	return TRUE;
}

#define _countof(array) (sizeof(array)/sizeof(array[0]))

BOOL CChildFrame::OnToolTipText(UINT nID, NMHDR* pNMHDR,LRESULT*pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
	
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	
	CString strTipText;
	if ( GetToolText( pNMHDR->idFrom, strTipText ) )
	{
#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
			lstrcpyn(pTTTA->szText, strTipText, _countof(pTTTA->szText));
		else
			_mbstowcsz(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
			_wcstombsz(pTTTA->szText, strTipText, _countof(pTTTA->szText));
		else
			lstrcpyn(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#endif
		return TRUE;
	}

	return CMDIChildWnd::OnToolTipText( nID, pNMHDR, pResult );
}

