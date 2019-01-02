/* Logic to traverse the System Shell*/

#include "stdafx.h"
#include "grasp95.h"
#include "shlobj.h"
#include "EnumObj.h"
#include "EnumObj2.h"
#include "ShellApi.h"

// Global pointer to the shell's IMalloc interface. 
LPMALLOC g_pMalloc; 
 
// main - the application's entrypoint function 
int ProcessShell() 
{ 
    LPITEMIDLIST pidlPrograms; 
    LPSHELLFOLDER pFolder; 
 
    // Get the shell's allocator. 
    if (!SUCCEEDED(SHGetMalloc(&g_pMalloc))) 
        return 1; 
 
    // Get the PIDL for the Programs folder. 
    if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, 
            CSIDL_DRIVES, &pidlPrograms))) { 
 
        // Start with the desktop folder. 
        if (SUCCEEDED(SHGetDesktopFolder(&pFolder))) { 
            LPITEMIDLIST pidl; 
 
            // Process each item identifier in the list. 
            for (pidl = pidlPrograms; pidl != NULL; 
                    pidl = GetNextItemID(pidl)) { 
                STRRET sName; 
                LPSHELLFOLDER pSubFolder; 
                LPITEMIDLIST pidlCopy; 
 
                // Copy the item identifier to a list by itself. 
                if ((pidlCopy = CopyItemID(pidl)) == NULL) 
                    break; 
 
                // Display the name of the subfolder. 
                if (SUCCEEDED(pFolder->GetDisplayNameOf(pidlCopy, SHGDN_INFOLDER, &sName))) 
                    PrintStrRet(pidlCopy, &sName); 
 
                // Bind to the subfolder. 
                if (!SUCCEEDED(pFolder->BindToObject(pidlCopy, NULL, IID_IShellFolder, (void **)&pSubFolder))) 
				{ 
                    g_pMalloc->Free(pidlCopy); 
                    break; 
                } 
 
                // Free the copy of the item identifier. 
                g_pMalloc->Free(pidlCopy); 
 
                // Release the parent folder and point to the 
                // subfolder. 
                pFolder->Release(); 
                pFolder = pSubFolder; 
            } 
			
			IdentifyDrives(pFolder, pidlPrograms);

            // Release the last folder that was bound to. 
            if (pFolder != NULL) 
                pFolder->Release(); 
        } 
 
        // Free the PIDL for the Programs folder. 
        g_pMalloc->Free(pidlPrograms); 
    } 
 
    // Release the shell's allocator. 
    g_pMalloc->Release(); 
    return 0; 
} 
 
// GetNextItemID - points to the next element in an item identifier//     list. 
// Returns a PIDL if successful or NULL if at the end of the list. 
// pdil - previous element 
LPITEMIDLIST GetNextItemID(LPITEMIDLIST pidl) 
{ 
    // Get the size of the specified item identifier. 
    int cb = pidl->mkid.cb; 
 
    // If the size is zero, it is the end of the list. 
    if (cb == 0) 
        return NULL; 
 
    // Add cb to pidl (casting to increment by bytes). 
    pidl = (LPITEMIDLIST) (((LPBYTE) pidl) + cb); 
 
    // Return NULL if it is null-terminating or a pidl otherwise. 
    return (pidl->mkid.cb == 0) ? NULL : pidl; 
} 
 
// CopyItemID - creates an item identifier list containing the first 
//     item identifier in the specified list. 
// Returns a PIDL if successful or NULL if out of memory. 
LPITEMIDLIST CopyItemID(LPITEMIDLIST pidl) 
{ 
    // Get the size of the specified item identifier. 
    int cb = pidl->mkid.cb; 
 
    // Allocate a new item identifier list. 
    LPITEMIDLIST pidlNew = (LPITEMIDLIST) 
        g_pMalloc->Alloc(cb + sizeof(USHORT)); 
    if (pidlNew == NULL) 
        return NULL; 
 
    // Copy the specified item identifier. 
    CopyMemory(pidlNew, pidl, cb); 
 
    // Append a terminating zero. 
    *((USHORT *) (((LPBYTE) pidlNew) + cb)) = 0; 
 
    return pidlNew; 
} 
 
// PrintStrRet - prints the contents of a STRRET structure. 
// pidl - PIDL containing the display name if STRRET_OFFSET 
// lpStr - address of the STRRET structure 
void PrintStrRet(LPITEMIDLIST pidl, LPSTRRET lpStr) 
{ 
    LPSTR lpsz; 
    int cch; 
 
    switch (lpStr->uType) { 
 
        case STRRET_WSTR: 
            cch = WideCharToMultiByte(CP_OEMCP, WC_DEFAULTCHAR, 
                lpStr->pOleStr, -1, NULL, 0, NULL, NULL); 
            lpsz = (LPSTR) g_pMalloc->Alloc(cch); 
            if (lpsz != NULL) { 
                WideCharToMultiByte(CP_OEMCP, WC_DEFAULTCHAR, 
                    lpStr->pOleStr, -1, lpsz, cch, NULL, NULL); 
                printf("%s\n", lpsz); 
                g_pMalloc->Free(lpsz); 
            } 
            break; 
 
        case STRRET_OFFSET: 
            printf("%s\n", ((char *) pidl) + lpStr->uOffset); 
            break; 
 
        case STRRET_CSTR: 
            printf("%s\n", lpStr->cStr); 
            break; 
    } 
} 

void IdentifyDrives(LPSHELLFOLDER lpShellFolder,
                    LPITEMIDLIST  lpifq)
{
    LPSHELLFOLDER   lpsf2=0;
    LPENUMIDLIST    lpEnumList=0;
    LPITEMIDLIST    lpItemList=0, lpiTemp=0, lpifqThisItem;
	LPCITEMIDLIST	lpcItem;
    LPMALLOC        lpMalloc=0;
	unsigned long   ulFetched;
    HRESULT         hr;
	_TCHAR           szBuff[MAX_PATH];
    int				iSmallIcon, iBigIcon;

    hr = SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    if (SUCCEEDED(lpShellFolder->EnumObjects(NULL, 
											 SHCONTF_FOLDERS | SHCONTF_NONFOLDERS,
											 &lpEnumList)))
    {
		int xDriveCnt = 0;
        while (S_OK == lpEnumList->Next(1, &lpItemList, &ulFetched))
        {
            //Create a fully qualified path to the current item
            //The SH* shell api's take a fully qualified path pidl,
            //(see GetIcon above where I call SHGetFileInfo) whereas the
            //interface methods take a relative path pidl.

            ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER | SFGAO_FILESYSTEM;
			lpcItem = lpItemList;
            lpShellFolder->GetAttributesOf(1, &lpcItem, &ulAttrs);

            if (ulAttrs & (SFGAO_FILESYSTEM))
            {
			  //Now get the friendly name that we'll put in the treeview...

			  GetName(lpShellFolder, lpItemList, SHGDN_NORMAL, szBuff);
			  lpifqThisItem = ConcatPidls(lpifq, lpItemList);
			  GetNormalAndSelectedIcons(lpifqThisItem, &iSmallIcon, &iBigIcon);
			  TRACE(_T("%s, %d, %d\n"), szBuff, iSmallIcon, iBigIcon);	
			  g_strDriveNames.Add(szBuff);
			  g_naSmallDriveIcons[xDriveCnt] = iSmallIcon;
			  g_naBigDriveIcons[xDriveCnt] = iBigIcon;
			  xDriveCnt++;
			}



		}
	}
}


BOOL GetName(LPSHELLFOLDER lpsf,
             LPITEMIDLIST  lpi,
			 DWORD         dwFlags,
             LPTSTR        lpFriendlyName)
{
   BOOL   bSuccess=TRUE;
   STRRET str;

   if (NOERROR==lpsf->GetDisplayNameOf(lpi, dwFlags, &str))
   {
      switch (str.uType)
      {
         case STRRET_WSTR:

            WideCharToMultiByte(CP_ACP,                 // CodePage
                                0,		                // dwFlags
                                str.pOleStr,            // lpWideCharStr
                                -1,                     // cchWideChar
                                lpFriendlyName,         // lpMultiByteStr
                                MAX_PATH,				// cchMultiByte,
                                NULL,                   // lpDefaultChar,
                                NULL);                  // lpUsedDefaultChar

             break;

         case STRRET_OFFSET:

             lstrcpy(lpFriendlyName, (LPTSTR)lpi+str.uOffset);
             break;

         case STRRET_CSTR:
             
             lstrcpy(lpFriendlyName, (LPTSTR)str.cStr);
             break;

         default:
             bSuccess = FALSE;
             break;
      }
   }
   else
      bSuccess = FALSE;

   return bSuccess;
}

void GetNormalAndSelectedIcons(LPITEMIDLIST lpifq,
                               int* icon1, int* icon2)
{
   //Note that we don't check the return value here because if GetIcon()
   //fails, then we're in big trouble...

   SHFILEINFO    sfi;

   SHGetFileInfo((LPCTSTR)lpifq, 
                 0,
                 &sfi, 
                 sizeof(SHFILEINFO), 
				 SHGFI_PIDL | 
                 SHGFI_SYSICONINDEX | 
                 SHGFI_SMALLICON);

   *icon1 = sfi.iIcon;
   
   SHGetFileInfo((LPCTSTR)lpifq, 
                 0,
                 &sfi, 
                 sizeof(SHFILEINFO), 
				 SHGFI_PIDL | 
                 SHGFI_SYSICONINDEX | 
				 SHGFI_OPENICON | 
                 SHGFI_SMALLICON);

   *icon2 = sfi.iIcon;
   
   return;
}

LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    LPITEMIDLIST pidlNew;
    UINT cb1;
    UINT cb2;

    if (pidl1)  //May be NULL
       cb1 = GetSize(pidl1) - sizeof(pidl1->mkid.cb);
    else
       cb1 = 0;

    cb2 = GetSize(pidl2);

    pidlNew = Create(cb1 + cb2);
    if (pidlNew)
    {
        if (pidl1)
           memcpy(pidlNew, pidl1, cb1);
        memcpy(((LPSTR)pidlNew) + cb1, pidl2, cb2);
    }
    return pidlNew;
}

LPITEMIDLIST Next(LPCITEMIDLIST pidl)
{
   LPSTR lpMem=(LPSTR)pidl;

   lpMem+=pidl->mkid.cb;

   return (LPITEMIDLIST)lpMem;
}

UINT GetSize(LPCITEMIDLIST pidl)
{
    UINT cbTotal = 0;
    if (pidl)
    {
        cbTotal += sizeof(pidl->mkid.cb);       // Null terminator
        while (pidl->mkid.cb)
        {
            cbTotal += pidl->mkid.cb;
            pidl = Next(pidl);
        }
    }

    return cbTotal;
}

LPITEMIDLIST Create(UINT cbSize)
{
    LPMALLOC lpMalloc;
    HRESULT  hr;
    LPITEMIDLIST pidl=0;

    hr=SHGetMalloc(&lpMalloc);

    if (FAILED(hr))
       return 0;

    pidl=(LPITEMIDLIST)lpMalloc->Alloc(cbSize);

    if (pidl)
        memset(pidl, 0, cbSize);      // zero-init for external task   alloc

    if (lpMalloc) lpMalloc->Release();

    return pidl;
}

