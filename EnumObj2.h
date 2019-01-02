// EnumObj2.h

void IdentifyDrives(LPSHELLFOLDER lpShellFolder,
                    LPITEMIDLIST  lpifq);
BOOL GetName(LPSHELLFOLDER lpsf,
             LPITEMIDLIST  lpi,
			 DWORD         dwFlags,
             LPTSTR         lpFriendlyName);
void GetNormalAndSelectedIcons(LPITEMIDLIST lpifq,
                               int* icon1, int* icon2);
LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);
UINT GetSize(LPCITEMIDLIST pidl);
LPITEMIDLIST Create(UINT cbSize);
LPITEMIDLIST Next(LPCITEMIDLIST pidl);
LPITEMIDLIST CopyItemID(LPITEMIDLIST pidl);
LPITEMIDLIST GetNextItemID(LPITEMIDLIST pidl);
void PrintStrRet(LPITEMIDLIST pidl, LPSTRRET lpStr);

CStringArray g_strDriveNames;
int			 g_naSmallDriveIcons[256];
int			 g_naBigDriveIcons[256];
