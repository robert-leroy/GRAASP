// Shareware.cpp : implementation file
//

#include "stdafx.h"
#include "grasp95.h"
#include "Shareware.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShareware dialog


CShareware::CShareware(CWnd* pParent /*=NULL*/)
	: CDialog(CShareware::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShareware)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShareware::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareware)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareware, CDialog)
	//{{AFX_MSG_MAP(CShareware)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareware message handlers
