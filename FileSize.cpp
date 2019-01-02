// FileSize.cpp : implementation file
//

#include "stdafx.h"
#include "grasp95.h"
#include "FileSize.h"

CGraspFileSize::CGraspFileSize()
{
	hTreeItem = 0;
	bDirEntry = FALSE;
	ullFileSize = 0;
    lngFileCount = 0;
}

CGraspFileSize::~CGraspFileSize()
{
	strFileName.Empty();
}

LONGLONG CGraspFileSize::GetSize()
{
	return ullFileSize;
}

const CGraspFileSize::operator = (LONGLONG ullSize)
{

	ullFileSize = ullSize;
	return 0;
}

int CGraspFileSize::SetName(CString strName)
{
	strFileName = strName;
	return 0;
}

void CGraspFileSize::SetFileType(CString strType)
{
	strFileType = strType;
	return;
}

void CGraspFileSize::SetDate(CString strDt)
{
	strDate = strDt;
}

CString CGraspFileSize::GetName()
{
	return strFileName;
}

CString CGraspFileSize::GetFileType()
{
	return strFileType;
}

CString CGraspFileSize::GetDate()
{
	return strDate;
}

void CGraspFileSize::SetDir()
{
	bDirEntry = TRUE;
	return;
}

BOOL CGraspFileSize::IsDir()
{
	return bDirEntry;
}

void CGraspFileSize::SetItem(HTREEITEM hItem)
{
	hTreeItem = hItem;
	return;
}

HTREEITEM CGraspFileSize::GetItem()
{
	return hTreeItem;
}

CString CGraspFileSize::FormatSize()
{

	LONGLONG ulTemp = GetSize();

	TCHAR caTemp[256];
	CString sRetVal;
	size_t x, y;

	sprintf(caTemp,_T("%.0I64d"),ulTemp);
	y = strlen(caTemp);
	y = y % 3;

	for(x=0; x<strlen(caTemp); x++)
	{
		if (x == y)
		{
			if (x != 0)
				sRetVal += ',';
				
			y += 3;  
		}
		
		sRetVal += caTemp[x];
	}

	return sRetVal;
}

CString CGraspFileSize::FormatCount()
{

	LONG lTemp = GetFileCount();

	TCHAR caTemp[256];
	CString sRetVal;
	size_t x, y;

	sprintf(caTemp,_T("%d"),lTemp);
	y = strlen(caTemp);
	y = y % 3;

	for(x=0; x<strlen(caTemp); x++)
	{
		if (x == y)
		{
			if (x != 0)
				sRetVal += ',';
				
			y += 3;  
		}
		
		sRetVal += caTemp[x];
	}

	return sRetVal;
}

LONG CGraspFileSize::GetFileCount()
{
	return lngFileCount;
}

void CGraspFileSize::SetFileCount(LONG lngCount)
{
    lngFileCount = lngCount;
    return;
}
