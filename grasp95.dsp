# Microsoft Developer Studio Project File - Name="grasp95" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=grasp95 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "grasp95.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "grasp95.mak" CFG="grasp95 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "grasp95 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "grasp95 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "grasp95 - Win32 Share Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Graphical Space Viewer (GRASP)", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "grasp95 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /pdb:none /machine:I386 /out:"Release/grasp97.exe"
# SUBTRACT LINK32 /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "grasp95 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/grasp97.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "grasp95 - Win32 Share Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "grasp95_"
# PROP BASE Intermediate_Dir "grasp95_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Shareware"
# PROP Intermediate_Dir "Shareware"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_SHAREWARE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/grasp97.exe"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Shareware/grasp97.exe"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "grasp95 - Win32 Release"
# Name "grasp95 - Win32 Debug"
# Name "grasp95 - Win32 Share Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BigIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DiskProp.cpp
# End Source File
# Begin Source File

SOURCE=.\DriveBar.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumObj.cpp
# End Source File
# Begin Source File

SOURCE=.\FileSize.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderProp.cpp
# End Source File
# Begin Source File

SOURCE=.\grasp95.cpp
# End Source File
# Begin Source File

SOURCE=.\grasp95.rc
# End Source File
# Begin Source File

SOURCE=.\graspDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\graspList.cpp
# End Source File
# Begin Source File

SOURCE=.\graspTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Shareware.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarEx.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\DiskProp.h
# End Source File
# Begin Source File

SOURCE=.\DriveBar.h
# End Source File
# Begin Source File

SOURCE=.\EnumObj.h
# End Source File
# Begin Source File

SOURCE=.\EnumObj2.h
# End Source File
# Begin Source File

SOURCE=.\FileSize.h
# End Source File
# Begin Source File

SOURCE=.\FolderProp.h
# End Source File
# Begin Source File

SOURCE=.\grasp95.h
# End Source File
# Begin Source File

SOURCE=.\graspDoc.h
# End Source File
# Begin Source File

SOURCE=.\graspList.h
# End Source File
# Begin Source File

SOURCE=.\graspTree.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Shareware.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\drivebar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\drivebar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\grasp95.ico
# End Source File
# Begin Source File

SOURCE=.\res\grasp95.rc2
# End Source File
# Begin Source File

SOURCE=.\res\graspDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Res\GraspSplash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hcdrivebar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hcdrivebard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hcdrivebarh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hctoolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hctoolbard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hctoolbarh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Res\ledgend2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\legend1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\list.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree.bmp
# End Source File
# Begin Source File

SOURCE=".\Res\Vero Logo.bmp"
# End Source File
# End Group
# End Target
# End Project
# Section grasp95 : {5F524449-414D-4E49-4652-414D45005000}
# 	1:17:CG_IDS_DISK_SPACE:104
# 	1:19:CG_IDS_PHYSICAL_MEM:103
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:105
# 	2:14:PhysicalMemory:CG_IDS_PHYSICAL_MEM
# 	2:9:DiskSpace:CG_IDS_DISK_SPACE
# 	2:16:SpaceUnavailable:CG_IDS_DISK_SPACE_UNAVAIL
# 	2:7:NewFunc:1
# 	2:10:SysInfoKey:1234
# End Section
# Section grasp95 : {8BD21D60-EC42-11CE-9E0D-00AA006002F3}
# 	1:23:CG_IDR_POPUP_GRASP_TREE:110
# 	1:23:CG_IDR_POPUP_GRASP_LIST:109
# End Section
# Section grasp95 : {00000000-0033-0000-0501-0000443A5C50}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
