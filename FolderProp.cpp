// FolderProp.cpp : implementation file
//

#include "stdafx.h"
#include "grasp95.h"
#include "FolderProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFolderProp dialog


CFolderProp::CFolderProp(CWnd* pParent /*=NULL*/)
	: CDialog(CFolderProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFolderProp)
	m_strSpaceUsed = _T("");
	m_strName = _T("");
	m_strPercent = _T("");
	m_strType = _T("");
	m_strLastWritten = _T("");
	//}}AFX_DATA_INIT
}


void CFolderProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFolderProp)
	DDX_Text(pDX, IDC_FOLDER_SPACE, m_strSpaceUsed);
	DDX_Text(pDX, IDC_FOLDER_NAME, m_strName);
	DDX_Text(pDX, IDC_FOLDER_PERCENT, m_strPercent);
	DDX_Text(pDX, IDC_FOLDER_TYPE, m_strType);
	DDX_Text(pDX, IDC_LAST_WRITTEN, m_strLastWritten);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFolderProp, CDialog)
	//{{AFX_MSG_MAP(CFolderProp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFolderProp message handlers
