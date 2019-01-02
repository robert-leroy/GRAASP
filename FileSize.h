class CGraspFileSize : public CObject
{
private:
	LONGLONG ullFileSize;
	CString strFileName;
	BOOL	bDirEntry;
	HTREEITEM hTreeItem;
	CString strFileType;
	CString strDate;
    LONG    lngFileCount;

public:
	CGraspFileSize();
	~CGraspFileSize();
	//CGraspFileSize CGraspFileSize::operator = (LONGLONG dblSize);
	void    SetSize(LONGLONG ullSize);
	int	    SetName(CString strName);
	CString GetName();
	LONGLONG  GetSize();
	BOOL	IsDir();
	void	SetDir();
	HTREEITEM GetItem();
	void	SetItem(HTREEITEM hItem);
	CString FormatSize();
	void	SetFileType(CString strType);
	CString GetFileType();
	CString GetDate();
	void    SetDate(CString strDate);
    LONG    GetFileCount();
    void    SetFileCount(LONG lngFileCount);
	CString FormatCount();
};

