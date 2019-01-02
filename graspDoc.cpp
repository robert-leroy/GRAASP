// graspDoc.cpp : implementation of the CGraspDoc class
//

#include "stdafx.h"
#include "grasp95.h"
#include "progdlg.h"
#include "FileSize.h"
#include "graspDoc.h"
#include "graspTree.h"
#include "graspList.h"
#include "ToolBarEx.h"
#include "MainFrm.h"
#include "EnumObj.h"
#include "DiskProp.h"
#include "ShellApi.h"

#include <shlobj.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraspDoc

IMPLEMENT_DYNCREATE(CGraspDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraspDoc, CDocument)
	//{{AFX_MSG_MAP(CGraspDoc)
	ON_COMMAND(ID_FILE_PROP, OnFileProperties)
	ON_COMMAND(ID_GRASP_REFRESH, OnGraspRefresh)
	ON_COMMAND(ID_GRASP_DIRDISK, OnGraspDirdisk)
	ON_UPDATE_COMMAND_UI(ID_GRASP_DIRDISK, OnUpdateGraspDirdisk)
	ON_COMMAND(ID_GRASP_TOPTEN, OnGraspTopten)
	ON_UPDATE_COMMAND_UI(ID_GRASP_TOPTEN, OnUpdateGraspTopTen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraspDoc construction/destruction

CGraspDoc::CGraspDoc()
{

}

CGraspDoc::~CGraspDoc()
{
}

// Should never get here
BOOL CGraspDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return FALSE;
}

BOOL CGraspDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{

	if (!CDocument::OnNewDocument())
		return FALSE;

	// Let all windows know we are scanning
	m_bScanFlag = TRUE;
	m_hRootItem = NULL;
	m_bDirDisk = TRUE;

	// MFC adds the full path, truncate it	
	m_strDriveLetter = lpszPathName;
	m_strDriveLetter = m_strDriveLetter.Left(2);

	// Get Icons for Tree Control
	TCHAR szSysDir[MAX_PATH];
	GetSystemDirectory(szSysDir, MAX_PATH);

	SHFILEINFO    sfi;
	SHGetFileInfo((LPCTSTR)szSysDir, 
				 0,
				 &sfi, 
				 sizeof(SHFILEINFO), 
				 SHGFI_SYSICONINDEX | 
				 SHGFI_SMALLICON);

	m_nFolderClosed = sfi.iIcon;

	SHGetFileInfo((LPCTSTR)szSysDir, 
				 0,
				 &sfi, 
				 sizeof(SHFILEINFO), 
				 SHGFI_SYSICONINDEX | 
				 SHGFI_OPENICON | 
				 SHGFI_SMALLICON);

	m_nFolderOpen = sfi.iIcon;

	BOOL ok = ScanDrive();

	m_bScanFlag = FALSE;

	return ok;

}

/////////////////////////////////////////////////////////////////////////////
// CGraspDoc serialization

void CGraspDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraspDoc diagnostics

#ifdef _DEBUG
void CGraspDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraspDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraspDoc commands

BOOL CGraspDoc::ScanDrive()
{

	CWaitCursor Csr;

	m_bTopTenShowing = FALSE;

	// Declare Variables
	TV_INSERTSTRUCT tvInsertStruct;
	CGraspFileSize* pGraspSize;
	pGraspSize = new CGraspFileSize;

	// Get TreeCtrl
	POSITION pos = GetFirstViewPosition();
	CGraspTree* treeView = (CGraspTree*)GetNextView( pos );
	CTreeCtrl &graspTree = treeView->GetTreeCtrl();
	m_pgraspTree = &graspTree;

RETRY:
	// Make sure we can access the drive
  	SetErrorMode(SEM_FAILCRITICALERRORS);
	CString strRootDir = m_strDriveLetter + "\\";
    DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters;
	BOOL rc = GetDiskFreeSpace(strRootDir, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters);
  	SetErrorMode(FALSE);

	// Start scanning the drive, if we can read it
	if (!rc)
	{
		CString strPrompt;
		strPrompt = _T("Error reading drive ") + m_strDriveLetter;
		int rc = ::MessageBox(AfxGetMainWnd()->m_hWnd, strPrompt, _T("Error"), MB_RETRYCANCEL | MB_ICONERROR);
		if (rc == IDCANCEL)
			return(FALSE);
		else
			goto RETRY;
	}

	// Get Drive Volume Information
	strRootDir = m_strDriveLetter + "\\";

	GetVolumeInformation(
		LPCTSTR(strRootDir),
		m_strVolumeName.GetBuffer(256), 256,
		&m_dwVolumeSerial,
		&m_dwMaxFileNameLen,
		&m_dwFileSysFlags,
		m_strFileSysName.GetBuffer(256), 256);

	// Progress Dialog stuff
	m_pdlgProgress = new CProgressDlg;
	m_pdlgProgress->Create(AfxGetMainWnd());
	m_pdlgProgress->SetRange(1, CountRootDirs());
	m_pdlgProgress->SetStep(1);

	// Get Drive Icon from all the stuff we've already collected
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CStringArray* pDrives = &(pMain->m_astrDriveList);

	for (int nDrivePos=0; nDrivePos < pDrives->GetSize(); nDrivePos++)
	{
		CString strTemp = (*pDrives)[nDrivePos].Left(2);
		strTemp.MakeUpper();
		if  (!strTemp.Compare(m_strDriveLetter.MakeUpper()))
			break;
	}

	// Insert Root Item
	tvInsertStruct.hParent = TVI_ROOT;
	tvInsertStruct.hInsertAfter = TVI_FIRST;
	tvInsertStruct.item.mask = TVIF_TEXT | TVIF_STATE | TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE;
	tvInsertStruct.item.state = TVIS_EXPANDED;
	tvInsertStruct.item.stateMask = TVIS_EXPANDED;
	tvInsertStruct.item.iImage = g_naSmallDriveIcons[nDrivePos];
	tvInsertStruct.item.iSelectedImage = g_naSmallDriveIcons[nDrivePos];
	tvInsertStruct.item.pszText = g_strDriveNames[nDrivePos].GetBuffer(g_strDriveNames[nDrivePos].GetLength());
	g_strDriveNames[nDrivePos].ReleaseBuffer();
	tvInsertStruct.item.cchTextMax = g_strDriveNames[nDrivePos].GetLength();
	tvInsertStruct.item.lParam = (LPARAM) pGraspSize;
	*pGraspSize = 0;
	m_hRootItem = m_pgraspTree->InsertItem(&tvInsertStruct);

	// Find First Item
//	strDir = "\\\\?\\" + strDir;
	m_llSelectedSize = ScanSubDir(m_strDriveLetter, m_hRootItem);
	m_strVolumeName = g_strDriveNames[nDrivePos];

	// Update Tree Item
	*pGraspSize   = m_llSelectedSize;
	pGraspSize->SetName(m_strVolumeName);
	pGraspSize->SetFileType(g_strDriveNames[nDrivePos]);
	m_llDriveSize = m_llSelectedSize;

	// Sort Tree
	m_pgraspTree->SortChildren(m_hRootItem);

	// Kill the progress dialog
	m_pdlgProgress->DestroyWindow();
	delete m_pdlgProgress;

	// Check 'Cancel' scan
	if (m_llSelectedSize == -1)
		return FALSE;
	else
		return TRUE;

}


int CGraspDoc::CountRootDirs()
{

	// Declare Variables
	WIN32_FIND_DATA FindFileData;
	CString strDir, strFileName;
	int nDirs;

	// Init Variables
	strDir = m_strDriveLetter + "\\*.*";
	nDirs = 1;

	// Find First
	HANDLE hFind = FindFirstFile( strDir, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hFind, &FindFileData))
		{
			strFileName = FindFileData.cFileName;
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && 
				!(strFileName == "." || strFileName == ".."))
				nDirs++;
		}

		FindClose(hFind);
	}

	return nDirs;

}


LONGLONG CGraspDoc::ScanSubDir(CString strDir, HTREEITEM hParentItem)
{

	// Declare variables
	WIN32_FIND_DATA FindFileData;
	TV_INSERTSTRUCT tvInsertStruct;
	HTREEITEM hTreeItem;
	CString strSearch;
	CString strFileName;
	LONGLONG llDirSize, llSubDirSize;
	CGraspFileSize *pGraspSize, *pGraspParent;
    LONG lngDirFileCount;

	// Init Variables
	llDirSize = llSubDirSize = 0;
    lngDirFileCount = -2; // This is the handle current dir "." and parent dir ".." entries in the file system
	strSearch = strDir + "\\*.*";
    pGraspParent = (CGraspFileSize*)m_pgraspTree->GetItemData(hParentItem); 

	// Find First
	HANDLE hFind = FindFirstFile( strSearch, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		// Process all the files
		do
		{
			strFileName = FindFileData.cFileName;
			llDirSize += (FindFileData.nFileSizeHigh * MAXDWORD) + FindFileData.nFileSizeLow;
            lngDirFileCount++;

			// If this is a directory, add it to the tree
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && 
				!(strFileName == "." || strFileName == ".."))
			{

				pGraspSize = new CGraspFileSize;
				*pGraspSize = 0;
    
				// Insert Item into the Tree
				tvInsertStruct.hParent = hParentItem;
				tvInsertStruct.hInsertAfter = TVI_LAST;
				tvInsertStruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE;
				tvInsertStruct.item.iImage = m_nFolderClosed;
				tvInsertStruct.item.iSelectedImage = m_nFolderOpen;
				tvInsertStruct.item.pszText = FindFileData.cFileName;
				tvInsertStruct.item.cchTextMax = strlen(FindFileData.cFileName);
				tvInsertStruct.item.lParam = (LPARAM) pGraspSize;
				hTreeItem = m_pgraspTree->InsertItem(&tvInsertStruct);

				// Read subDir
				CString strSubDir;
				strSubDir = strDir + "\\";
				strSubDir += FindFileData.cFileName;
				llSubDirSize = ScanSubDir(strSubDir, hTreeItem);
				llDirSize += llSubDirSize;
                lngDirFileCount += pGraspSize->GetFileCount();

				// Was Cancel pressed
				if (llSubDirSize == -1)
					return (-1);

				// Update Tree Item
				*pGraspSize = llSubDirSize;
				pGraspSize->SetName(strFileName);
				pGraspSize->SetFileType("File Folder");

				// Save the Date and Time
				SYSTEMTIME sysTime;
				FileTimeToSystemTime(&FindFileData.ftLastWriteTime,&sysTime);
				CString strDate;
				strDate.Format("%d/%02d/%02d %02d:%02d:%02d",sysTime.wMonth,sysTime.wDay,sysTime.wYear,sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
				pGraspSize->SetDate(strDate);

				// Update the Progress Dialog
				CString strStatus;
				strStatus = strSubDir; 
				strStatus.MakeUpper();
				m_pdlgProgress->SetStatus(strStatus);
				if (strDir.GetLength() < 4)
					m_pdlgProgress->StepIt();

				// Check for user 'Cancel'
				if (m_pdlgProgress->CheckCancelButton())
					return (-1);

			}

		} while (FindNextFile(hFind, &FindFileData));
		
		FindClose(hFind);
	}

    pGraspParent->SetFileCount(lngDirFileCount);
    
	return llDirSize;
}

BOOL CGraspDoc::ListFromTree()
{

	CWaitCursor Csr;

	m_bTopTenShowing = FALSE;

	// Declare Variables
	HTREEITEM hTreeItem;
	LV_ITEM   lvItem;
	CString   strItemText;
	LONGLONG llItemData;
	CGraspFileSize* pGraspSize;

	// Get ListCtrl, this always works because the views 
	//				 are always created in the same order
	POSITION pos = GetFirstViewPosition();
	CGraspTree* treeView = (CGraspTree*)GetNextView( pos );
	CGraspList* listView = (CGraspList*)GetNextView( pos );
	CListCtrl &graspList = listView->GetListCtrl();
	m_pgraspList = &graspList;

	// Take the selected Tree Item
	hTreeItem = m_pgraspTree->GetSelectedItem();
	strItemText = m_pgraspTree->GetItemText(hTreeItem);
	pGraspSize = (CGraspFileSize*)m_pgraspTree->GetItemData(hTreeItem);
	m_llSelectedSize = llItemData = pGraspSize->GetSize();

	// Delete all item pointers, then all items
	int nItems = m_pgraspList->GetItemCount();
	for (int x=0; x < nItems; x++)
		delete (CGraspFileSize*) m_pgraspList->GetItemData(x);
	m_pgraspList->DeleteAllItems();

	// Get Full Path to this directory
	CString strFullPath, strPrevPath;
	HTREEITEM hPathTreeItem = m_pgraspTree->GetSelectedItem();
	strFullPath = m_pgraspTree->GetItemText(hPathTreeItem);
	while (hPathTreeItem = m_pgraspTree->GetParentItem(hPathTreeItem))
	{
		CString strDir = m_pgraspTree->GetItemText(hPathTreeItem);
		strPrevPath = strFullPath;
		strFullPath = strDir + "\\" + strFullPath;
	}
	if (strPrevPath.IsEmpty())
		strFullPath = m_strDriveLetter;
	else
		strFullPath = m_strDriveLetter + "\\" + strPrevPath;

	// Load all children of the selected item into the List
	if (m_pgraspTree->ItemHasChildren(hTreeItem))
	{
		// Get the child item information
		hTreeItem = m_pgraspTree->GetChildItem(hTreeItem);
		CString strPath;
		SHFILEINFO sfi;

		do 
		{
			// Create a new item here for the list
			CGraspFileSize* pSize;
			pSize = new CGraspFileSize;
            
			// Determine the Associated Icon
			strItemText = m_pgraspTree->GetItemText(hTreeItem);
			strPath = strFullPath + "\\";
			strPath += strItemText;
			SHGetFileInfo(strPath, NULL, &sfi, sizeof(sfi), SHGFI_TYPENAME | SHGFI_DISPLAYNAME | SHGFI_ICON | SHGFI_SMALLICON | SHGFI_TYPENAME);

			pGraspSize  = (CGraspFileSize*)m_pgraspTree->GetItemData(hTreeItem);
			*pSize = pGraspSize->GetSize();
			pSize->SetName(strItemText);
			pSize->SetFileType(sfi.szTypeName);
			pSize->SetDir();
			pSize->SetItem(hTreeItem);
			pSize->SetDate(pGraspSize->GetDate());
            pSize->SetFileCount(pGraspSize->GetFileCount());

			// Insert the item NAME into the ListCtrl
			lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
			lvItem.pszText = strItemText.GetBuffer(strItemText.GetLength());
			strItemText.ReleaseBuffer();
			lvItem.cchTextMax = strItemText.GetLength();
			lvItem.iItem = 1;
			lvItem.iImage = sfi.iIcon;
			lvItem.iSubItem = 0;
			lvItem.lParam = (LPARAM) pSize;
			int iItem = m_pgraspList->InsertItem(&lvItem);

		} while (hTreeItem = m_pgraspTree->GetNextSiblingItem(hTreeItem));

	}

	ListFromDir(strFullPath);

	return 0;
}

BOOL CGraspDoc::ListFromDir(CString strDir)
{
	
	CWaitCursor Csr;

	m_bTopTenShowing = FALSE;

	// Declare variables
	WIN32_FIND_DATA FindFileData;
	CString strSearch, strItemText, strFileName;
	LONGLONG	llItemData;
	LV_ITEM		lvItem;
	SHFILEINFO	sfi;
	CString		strPath;

	strSearch = strDir + "\\*.*";

	// Get the owner and set the current path
	POSITION pos = GetFirstViewPosition();
	CGraspTree* treeView = (CGraspTree*)GetNextView( pos );
	CGraspList* listView = (CGraspList*)GetNextView( pos );
	m_strPath = strDir;

	// Find First
	HANDLE hFind = FindFirstFile( strSearch, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		// Process all the files
		do
		{
			strFileName = FindFileData.cFileName;

			// If this is a directory, don't add it
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || 
				(strFileName == "." || strFileName == ".."))
			{}
			else
			{
				CGraspFileSize* pGraspSize = new CGraspFileSize;

				// Insert Item into the List
				strItemText = FindFileData.cFileName;
				llItemData  = (FindFileData.nFileSizeHigh * MAXDWORD) + FindFileData.nFileSizeLow;

				// Determine the Associated Icon
				strPath = strDir + "\\";
				strPath += strItemText;
				SHGetFileInfo(strPath, NULL, &sfi, sizeof(sfi), SHGFI_TYPENAME | SHGFI_DISPLAYNAME | SHGFI_ICON | SHGFI_SMALLICON | SHGFI_TYPENAME);

				// Insert the item NAME into the ListCtrl
				lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
				lvItem.pszText = strItemText.GetBuffer(strItemText.GetLength());
				strItemText.ReleaseBuffer();
				lvItem.cchTextMax = strItemText.GetLength();
				lvItem.iItem = 1;
				lvItem.iSubItem = 0;
				lvItem.iImage = sfi.iIcon;
				lvItem.lParam = (LPARAM) pGraspSize;
				*pGraspSize = llItemData;
				pGraspSize->SetName(strItemText);
				pGraspSize->SetFileType(sfi.szTypeName);
                pGraspSize->SetFileCount(1);
				
				SYSTEMTIME sysTime;
				FileTimeToSystemTime(&FindFileData.ftLastWriteTime,&sysTime);
				CString strDate;
				strDate.Format("%d/%02d/%02d %02d:%02d:%02d",sysTime.wMonth,sysTime.wDay,sysTime.wYear,sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
				pGraspSize->SetDate(strDate);

				int iItem = m_pgraspList->InsertItem(&lvItem);

			}

		} while (FindNextFile(hFind, &FindFileData));
		
		FindClose(hFind);
	}

	// Initital Sort
	// Structure to pass info to the sort routines
	CSortData sd;

	// Determine which column sort function to call
	sd.pfSortFunction = &CGraspList::SortSize;
	sd.bSortAscending = FALSE;

	// Call the list view sort member function
	m_pgraspList->SortItems( CGraspList::ListViewCompare, (LPARAM)(&sd));
	m_pgraspList->SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

	return 0;
}

void CGraspDoc::OnFileProperties() 
{
	CDiskProp dlgProp;
	CString strDrive;
	DWORD lpSectorsPerCluster, lpBytesPerSector;
	DWORD lpNumberOfFreeClusters, lpTotalNumberOfClusters;

	strDrive = m_strDriveLetter + "\\";

	GetDiskFreeSpace( strDrive, 
					 &lpSectorsPerCluster, 
					 &lpBytesPerSector, 
					 &lpNumberOfFreeClusters, 
					 &lpTotalNumberOfClusters); 
 
	dlgProp.m_strSectors.Format(_T("%ld"),lpSectorsPerCluster);
	dlgProp.m_strBytes.Format(_T("%ld"),lpBytesPerSector);
	dlgProp.m_strAvailClusters.Format(_T("%ld"),lpNumberOfFreeClusters);
	dlgProp.m_strClusters.Format(_T("%ld"),lpTotalNumberOfClusters);

	if (m_dwFileSysFlags & FS_VOL_IS_COMPRESSED)
		dlgProp.m_strCompressed = "Drive is compressed";

	dlgProp.m_strFileSystem = m_strFileSysName;

	CString strTemp1, strTemp2;
	strTemp1.Format(_T("%X"),(m_dwVolumeSerial & 0xFFFF0000));
	strTemp1 = strTemp1.Left(4);
	strTemp2.Format(_T("-%X"),(m_dwVolumeSerial & 0x0000FFFF));
	dlgProp.m_strSerialNumber = strTemp1 + strTemp2;
	
	FARPROC pGetDiskFreeSpaceEx = GetProcAddress( GetModuleHandle("kernel32.dll"),
							 "GetDiskFreeSpaceExA");

	if (pGetDiskFreeSpaceEx)
	{
		int iResult;
		ULARGE_INTEGER i64FreeBytesToCaller;
		ULARGE_INTEGER i64TotalBytes;
		ULARGE_INTEGER i64FreeBytes;

	    iResult = GetDiskFreeSpaceEx (strDrive,
					&i64FreeBytesToCaller,
					&i64TotalBytes,
					&i64FreeBytes);

//		dlgProp.m_strTotal.Format("%I64d",i64TotalBytes.QuadPart);
		CGraspFileSize dSize;
		dSize = i64TotalBytes.QuadPart;
		dlgProp.m_strTotal = dSize.FormatSize();


//		dlgProp.m_strAvail.Format("%I64d",i64FreeBytesToCaller.QuadPart);
		dSize = i64FreeBytes.QuadPart;
		dlgProp.m_strAvail = dSize.FormatSize();

//		dlgProp.m_strGrasp.Format("%I64d",i64TotalBytes.QuadPart - i64FreeBytes.QuadPart);
		dSize = i64TotalBytes.QuadPart - i64FreeBytes.QuadPart;
		dlgProp.m_strGrasp = dSize.FormatSize();

		dlgProp.m_llFreeSpace = i64FreeBytes.QuadPart;
		dlgProp.m_llUsedSpace = i64TotalBytes.QuadPart  - i64FreeBytes.QuadPart;

	}
	else
	{

		LONGLONG llDiskSize = lpTotalNumberOfClusters * lpBytesPerSector * lpSectorsPerCluster;
		LONGLONG llFreeSpace = lpNumberOfFreeClusters * lpBytesPerSector * lpSectorsPerCluster;
		LONGLONG llSpaceUsed = llDiskSize - llFreeSpace;

		CGraspFileSize dSize;
		dSize = llDiskSize;
		dlgProp.m_strTotal = dSize.FormatSize();

		dSize = llFreeSpace;
		dlgProp.m_strAvail = dSize.FormatSize();

		dSize = llSpaceUsed;
		dlgProp.m_strGrasp = dSize.FormatSize();

		dlgProp.m_llFreeSpace = llFreeSpace;
		dlgProp.m_llUsedSpace = llDiskSize - llFreeSpace;
	}

	dlgProp.DoModal();
}

BOOL CGraspDoc::DeleteDir(CString strDir)
{

	// Declare variables
	WIN32_FIND_DATA FindFileData;
	CString strSearch;
	CString strFileName;
	CString strSubDir;

	strSearch = strDir + "\\*.*";

	// Find First
	HANDLE hFind = FindFirstFile( strSearch, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		// Process all the files
		do
		{
			strFileName = FindFileData.cFileName;

			if (!(strFileName == "." || strFileName == ".."))
			{
				// If this is a directory, delete all items in it
				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{

					// Delete subDir
					strSubDir = strDir + "\\";
					strSubDir += FindFileData.cFileName;
					DeleteDir(strSubDir);
				}
				else
				{
					strFileName = strDir + "\\" + FindFileData.cFileName;
					DeleteFile(strFileName);
				}
			}
		} while (FindNextFile(hFind, &FindFileData));
		
		FindClose(hFind);
	}

	RemoveDirectory(strDir);
	return TRUE;
}


void CGraspDoc::OnGraspRefresh() 
{

	m_bScanFlag = TRUE;

	// Get TreeCtrl
	POSITION pos = GetFirstViewPosition();
	CGraspTree* treeView = (CGraspTree*)GetNextView( pos );
	
	// Delete Everything in the Tree
	treeView->DeleteAllPointers();
	treeView->GetTreeCtrl().DeleteAllItems();
	
	BOOL ok = ScanDrive();
	
	if (ok)
	{
		HTREEITEM hItem = treeView->GetTreeCtrl().GetRootItem();
		treeView->GetTreeCtrl().SelectItem(hItem);
	}
	else
	{
		// Get MDI Window and Kill it!
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		CWnd* pMDI = pMain->GetActiveFrame();

		pMDI->PostMessage(WM_CLOSE, 0, 0);
	}

	m_bScanFlag = FALSE;

	// Reload all items in the tool bar
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	//pMain->LoadDriveBar();

	return;

}

void CGraspDoc::OnGraspDirdisk() 
{

	if (m_bDirDisk == TRUE)
		m_bDirDisk = FALSE;
	else
		m_bDirDisk = TRUE;

	UpdateAllViews(NULL);
}

void CGraspDoc::OnUpdateGraspDirdisk(CCmdUI* pCmdUI) 
{
	if (m_bDirDisk == TRUE)
		pCmdUI->SetCheck(0);
	else
		pCmdUI->SetCheck(1);
}

void CGraspDoc::OnGraspTopten() 
{
	
	CWaitCursor Csr;

	// Declare Variables
	HTREEITEM hTreeItem;
	LV_ITEM   lvItem;

	if (m_bTopTenShowing)
	{
		m_bTopTenShowing = FALSE;
		ListFromTree();
	}
	else
	{
		m_bTopTenShowing = TRUE;

		for (int x=0; x<10;x++)
			aGraspSize[x] = NULL;

		// Get ListCtrl, this always works because the views 
		//				 are always created in the same order
		POSITION pos = GetFirstViewPosition();
		CGraspTree* treeView = (CGraspTree*)GetNextView( pos );
		CGraspList* listView = (CGraspList*)GetNextView( pos );
		CListCtrl &graspList = listView->GetListCtrl();
		m_pgraspList = &graspList;

		// Delete all list item pointers, then all items
		int nItems = m_pgraspList->GetItemCount();
		for (int y=0; y < nItems; y++)
			delete (CGraspFileSize*) m_pgraspList->GetItemData(y);
		m_pgraspList->DeleteAllItems();

		// Find the top ten children 
		hTreeItem = m_pgraspTree->GetRootItem();

		if (m_pgraspTree->ItemHasChildren(hTreeItem))
			FindTopTen(hTreeItem);

		for (int z=0; z < 10; z++)
		{
			if (aGraspSize[z] != NULL)
			{
				CGraspFileSize* pSize = new CGraspFileSize;

				if (aGraspSize[z]->IsDir())
					pSize->SetDir();
				pSize->SetFileType(aGraspSize[z]->GetFileType());
				pSize->SetItem(aGraspSize[z]->GetItem());
				pSize->SetName(aGraspSize[z]->GetName());
				*pSize = aGraspSize[z]->GetSize();

				// Insert the item NAME into the ListCtrl
				lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
				CString strName = aGraspSize[z]->GetName();
				lvItem.pszText = strName.GetBuffer(strName.GetLength());
				lvItem.cchTextMax = strName.GetLength();
				strName.ReleaseBuffer();
				lvItem.iItem = 1;
				lvItem.iImage = m_nFolderClosed;
				lvItem.iSubItem = 0;
				lvItem.lParam = (LPARAM) pSize;
				int iItem = m_pgraspList->InsertItem(&lvItem);
			}
		}

		// Initital Sort
		// Structure to pass info to the sort routines
		CSortData sd;

		// Determine which column sort function to call
		sd.pfSortFunction = &CGraspList::SortSize;
		sd.bSortAscending = FALSE;

		// Call the list view sort member function
		m_pgraspList->SortItems( CGraspList::ListViewCompare, (LPARAM)(&sd));
		m_pgraspList->SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
	}

}

void CGraspDoc::FindTopTen(HTREEITEM hTreeItem)
{

	// Declare Variables
	CString   strItemText;
	CGraspFileSize* pGraspSize;

	m_llSelectedSize = m_llDriveSize;

	// Get the child item information
	hTreeItem = m_pgraspTree->GetChildItem(hTreeItem);

	do 
	{
		// Process for children
		if (m_pgraspTree->ItemHasChildren(hTreeItem))
			FindTopTen(hTreeItem);
		else
		{
			pGraspSize  = (CGraspFileSize*)m_pgraspTree->GetItemData(hTreeItem);

			// Findout if ten have been selected
			int x;
			for (x=0; x < 10; x++)
			{
				if (aGraspSize[x] == NULL)
				{
					aGraspSize[x] = pGraspSize;
					aGraspSize[x]->SetItem(hTreeItem);
					break;
				}
			}

			// Finout if this is bigger than any other item
			if (aGraspSize[9])
			{
				for (x=0; x < 10; x++)
				{
					if (aGraspSize[x]->GetSize() < pGraspSize->GetSize())
					{
						aGraspSize[x] = pGraspSize;
						aGraspSize[x]->SetItem(hTreeItem);
						break;
					}
				}
			}
		}

	} while (hTreeItem = m_pgraspTree->GetNextSiblingItem(hTreeItem));

	return;
}

void CGraspDoc::OnUpdateGraspTopTen(CCmdUI* pCmdUI) 
{
	if (m_bTopTenShowing)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
	
}

