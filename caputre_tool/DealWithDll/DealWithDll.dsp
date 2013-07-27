# Microsoft Developer Studio Project File - Name="DealWithDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DealWithDll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DealWithDll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DealWithDll.mak" CFG="DealWithDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DealWithDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DealWithDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DealWithDll - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "DealWithDll - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SkinMagicLibMT6Trial.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DealWithDll - Win32 Release"
# Name "DealWithDll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DealWithDll.cpp
# End Source File
# Begin Source File

SOURCE=.\DealWithDll.def
# End Source File
# Begin Source File

SOURCE=.\DealWithDll.rc
# End Source File
# Begin Source File

SOURCE=.\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAsh.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAshTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCarveRilievo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHsv.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLaplacSharp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLiner.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLiner.h
# End Source File
# Begin Source File

SOURCE=.\DlgLinTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMedianFilt.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRever.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRgb.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRot.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSoften.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DealWithDll.h
# End Source File
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\DlgAsh.h
# End Source File
# Begin Source File

SOURCE=.\DlgAshTrans.h
# End Source File
# Begin Source File

SOURCE=.\DlgCarveRilievo.h
# End Source File
# Begin Source File

SOURCE=.\DlgHsv.h
# End Source File
# Begin Source File

SOURCE=.\DlgLaplacSharp.h
# End Source File
# Begin Source File

SOURCE=.\DlgLinTrans.h
# End Source File
# Begin Source File

SOURCE=.\DlgMedianFilt.h
# End Source File
# Begin Source File

SOURCE=.\DlgRever.h
# End Source File
# Begin Source File

SOURCE=.\DlgRgb.h
# End Source File
# Begin Source File

SOURCE=.\DlgRot.h
# End Source File
# Begin Source File

SOURCE=.\DlgSoften.h
# End Source File
# Begin Source File

SOURCE=.\DlgTemplate.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DealWithDll.rc2
# End Source File
# Begin Source File

SOURCE=.\res\skinmagi.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\futuraIII.smf
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
