; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGraspList
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "grasp95.h"
LastPage=0

ClassCount=16
Class1=CBigIcon
Class2=CChildFrame
Class3=CDiskProp
Class4=CDriveBar
Class5=CFlatToolBar
Class6=CFolderProp
Class7=CGraspApp
Class8=CAboutDlg
Class9=CGraspDoc
Class10=CGraspList
Class11=CGraspTree
Class12=CMainFrame
Class13=CProgressDlg
Class14=CShareware
Class15=CSplashWnd
Class16=CToolBarEx

ResourceCount=9
Resource1=IDD_FOLDER_PROP
Resource2=IDR_DRIVEBAR
Resource3=IDR_GRASP9TYPE
Resource4=IDR_MAINFRAME
Resource5=IDD_DISK_PROP
Resource6=CG_IDD_PROGRESS
Resource7=CG_IDR_POPUP_GRASP_LIST
Resource8=IDD_ABOUTBOX
Resource9=IDD_SPLASH

[CLS:CBigIcon]
Type=0
BaseClass=CButton
HeaderFile=BigIcon.h
ImplementationFile=BigIcon.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame
Filter=M
VirtualFilter=mfWC

[CLS:CDiskProp]
Type=0
BaseClass=CDialog
HeaderFile=DiskProp.h
ImplementationFile=DiskProp.cpp

[CLS:CDriveBar]
Type=0
BaseClass=CToolBarCtrl
HeaderFile=DriveBar.h
ImplementationFile=DriveBar.cpp

[CLS:CFlatToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=Flatbar.h
ImplementationFile=Flatbar.cpp

[CLS:CFolderProp]
Type=0
BaseClass=CDialog
HeaderFile=FolderProp.h
ImplementationFile=FolderProp.cpp
Filter=D
VirtualFilter=dWC
LastObject=CFolderProp

[CLS:CGraspApp]
Type=0
BaseClass=CWinApp
HeaderFile=grasp95.h
ImplementationFile=grasp95.cpp
LastObject=CGraspApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=grasp95.cpp
ImplementationFile=grasp95.cpp
LastObject=CAboutDlg

[CLS:CGraspDoc]
Type=0
BaseClass=CDocument
HeaderFile=graspDoc.h
ImplementationFile=graspDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CGraspDoc

[CLS:CGraspList]
Type=0
BaseClass=CListView
HeaderFile=graspList.h
ImplementationFile=graspList.cpp
LastObject=CGraspList
Filter=C
VirtualFilter=VWC

[CLS:CGraspTree]
Type=0
BaseClass=CTreeView
HeaderFile=graspTree.h
ImplementationFile=graspTree.cpp
LastObject=CGraspTree

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CProgressDlg]
Type=0
BaseClass=CDialog
HeaderFile=ProgDlg.h
ImplementationFile=ProgDlg.cpp

[CLS:CShareware]
Type=0
BaseClass=CDialog
HeaderFile=Shareware.h
ImplementationFile=Shareware.cpp

[CLS:CSplashWnd]
Type=0
BaseClass=CWnd
HeaderFile=Splash.h
ImplementationFile=Splash.cpp

[CLS:CToolBarEx]
Type=0
BaseClass=CToolBar
HeaderFile=ToolBarEx.h
ImplementationFile=ToolBarEx.cpp

[DLG:IDD_DISK_PROP]
Type=1
Class=CDiskProp
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308354
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_SECTORS,static,1342308352
Control7=IDC_STATIC,static,1342308354
Control8=IDC_BYTES,static,1342308352
Control9=IDC_CLUSTERS,static,1342308352
Control10=IDC_STATIC,static,1342308354
Control11=IDC_TOTAL,static,1342308354
Control12=IDC_AVAIL,static,1342308354
Control13=IDC_STATIC,static,1342308354
Control14=IDC_GRASP,static,1342308354
Control15=IDC_AVAILABLE,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342177294
Control21=IDC_STATIC,static,1342177294
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,static,1342308354
Control24=IDC_STATIC,static,1342308354
Control25=IDC_SERIAL_NO,static,1342308354
Control26=IDC_FILE_SYSTEM,static,1342308354
Control27=IDC_COMPRESSED,static,1342308353

[DLG:IDD_FOLDER_PROP]
Type=1
Class=CFolderProp
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308354
Control3=IDC_FOLDER_SPACE,static,1342308352
Control4=IDC_STATIC,static,1342308354
Control5=IDC_FOLDER_NAME,static,1342308352
Control6=IDC_STATIC,static,1342308354
Control7=IDC_FOLDER_PERCENT,static,1342308352
Control8=IDC_STATIC,static,1342308354
Control9=IDC_FOLDER_TYPE,static,1342308352
Control10=IDC_STATIC,static,1342308354
Control11=IDC_LAST_WRITTEN,static,1342308352

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342181380
Control9=IDC_STATIC,static,1342181380
Control10=IDC_STATIC,static,1342177294

[DLG:CG_IDD_PROGRESS]
Type=1
Class=CProgressDlg
ControlCount=4
Control1=IDCANCEL,button,1342242817
Control2=CG_IDC_PROGDLG_PROGRESS,msctls_progress32,1350565888
Control3=CG_IDC_PROGDLG_PERCENT,static,1342308352
Control4=CG_IDC_PROGDLG_STATUS,static,1342308352

[DLG:IDD_SPLASH]
Type=1
Class=CShareware
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342181380
Control5=IDC_STATIC,static,1342181380
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342177294
Control8=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_PRINT
Command2=ID_GRASP_REFRESH
Command3=ID_GRASP_LIST_CLOSE
Command4=ID_GRASP_DIRDISK
Command5=ID_GRASP_TOPTEN
Command6=ID_GRASP_LIST_DELETE
Command7=ID_GRASP_LIST_PROP
CommandCount=7

[TB:IDR_DRIVEBAR]
Type=1
Class=?
Command1=ID_DRIVE_A
Command2=ID_DRIVE_B
Command3=ID_DRIVE_C
Command4=ID_DRIVE_E
Command5=ID_DRIVE_F
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_APP_HELP
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_GRASP9TYPE]
Type=1
Class=CGraspDoc
Command1=ID_FILE_PROP
Command2=ID_FILE_CLOSE
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_APP_EXIT
Command7=ID_GRASP_LIST_OPEN
Command8=ID_GRASP_LIST_DELETE
Command9=ID_GRASP_REFRESH
Command10=ID_GRASP_LIST_CLOSE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_GRASP_DIRDISK
Command14=ID_GRASP_TOPTEN
Command15=ID_GRASP_LIST_PROP
Command16=ID_WINDOW_CASCADE
Command17=ID_WINDOW_TILE_HORZ
Command18=ID_WINDOW_ARRANGE
Command19=ID_WINDOW_SPLIT
Command20=ID_APP_HELP
Command21=ID_APP_ABOUT
CommandCount=21

[MNU:CG_IDR_POPUP_GRASP_LIST]
Type=1
Class=?
Command1=ID_GRASP_LIST_OPEN
Command2=ID_GRASP_LIST_DELETE
Command3=ID_GRASP_LIST_PROP
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_APP_HELP
Command9=ID_GRASP_REFRESH
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

