# Microsoft Developer Studio Project File - Name="MightyCasl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MightyCasl - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "MightyCasl.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "MightyCasl.mak" CFG="MightyCasl - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "MightyCasl - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "MightyCasl - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MightyCasl II", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MightyCasl - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386 /out:"Release/MightyCasl2.exe"

!ELSEIF  "$(CFG)" == "MightyCasl - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/MightyCasl2.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MightyCasl - Win32 Release"
# Name "MightyCasl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AssembleError.cpp
# End Source File
# Begin Source File

SOURCE=.\Assembler.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CometCore.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceView.cpp
# End Source File
# Begin Source File

SOURCE=.\DumpView.cpp
# End Source File
# Begin Source File

SOURCE=.\Environment.cpp
# End Source File
# Begin Source File

SOURCE=.\EnvironmentDLg.cpp
# End Source File
# Begin Source File

SOURCE=.\HorzSplitterWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDeviceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\LicenseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\listvwex.cpp
# End Source File
# Begin Source File

SOURCE=.\Literal.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\MightyCasl.cpp
# End Source File
# Begin Source File

SOURCE=.\MightyCasl.rc
# End Source File
# Begin Source File

SOURCE=.\MightyCaslDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MightyCaslFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MightyCaslStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MightyCaslView.cpp
# End Source File
# Begin Source File

SOURCE=.\Mnemonic.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicAcc.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicBase.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicCompare.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicJump.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicMacro.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicShift.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicStack.cpp
# End Source File
# Begin Source File

SOURCE=.\MnemonicSuspect.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputView.cpp
# End Source File
# Begin Source File

SOURCE=.\Register.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterView.cpp
# End Source File
# Begin Source File

SOURCE=.\SimulateView.cpp
# End Source File
# Begin Source File

SOURCE=.\SourceFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\SourceView.cpp
# End Source File
# Begin Source File

SOURCE=.\StackView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SymbolView.cpp
# End Source File
# Begin Source File

SOURCE=.\WatchDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WatchInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\WatchView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AssembleError.h
# End Source File
# Begin Source File

SOURCE=.\Assembler.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\comet.h
# End Source File
# Begin Source File

SOURCE=.\CometCore.h
# End Source File
# Begin Source File

SOURCE=.\DeviceView.h
# End Source File
# Begin Source File

SOURCE=.\DumpView.h
# End Source File
# Begin Source File

SOURCE=.\Environment.h
# End Source File
# Begin Source File

SOURCE=.\EnvironmentDLg.h
# End Source File
# Begin Source File

SOURCE=.\HorzSplitterWnd.h
# End Source File
# Begin Source File

SOURCE=.\InputDeviceDlg.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\LicenseDlg.h
# End Source File
# Begin Source File

SOURCE=.\listvwex.h
# End Source File
# Begin Source File

SOURCE=.\Literal.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Memory.h
# End Source File
# Begin Source File

SOURCE=.\MightyCasl.h
# End Source File
# Begin Source File

SOURCE=.\MightyCaslDoc.h
# End Source File
# Begin Source File

SOURCE=.\MightyCaslFrame.h
# End Source File
# Begin Source File

SOURCE=.\MightyCaslStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\MightyCaslView.h
# End Source File
# Begin Source File

SOURCE=.\Mnemonic.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicAcc.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicBase.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicCompare.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicJump.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicMacro.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicShift.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicStack.h
# End Source File
# Begin Source File

SOURCE=.\MnemonicSuspect.h
# End Source File
# Begin Source File

SOURCE=.\OutputView.h
# End Source File
# Begin Source File

SOURCE=.\Register.h
# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegisterView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SimulateView.h
# End Source File
# Begin Source File

SOURCE=.\SourceFrame.h
# End Source File
# Begin Source File

SOURCE=.\SourceView.h
# End Source File
# Begin Source File

SOURCE=.\StackView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SymbolView.h
# End Source File
# Begin Source File

SOURCE=.\WatchDlg.h
# End Source File
# Begin Source File

SOURCE=.\WatchInfo.h
# End Source File
# Begin Source File

SOURCE=.\WatchView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon_sou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon_sta.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_migh.ico
# End Source File
# Begin Source File

SOURCE=.\res\MightyCasl.ico
# End Source File
# Begin Source File

SOURCE=.\res\MightyCasl.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MightyCaslDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "htm"
# Begin Source File

SOURCE=.\Help\0001.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0002.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0003.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0004.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0005.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0006.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0007.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0008.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0009.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0010.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0011.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0012.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0013.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0014.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0015.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0016.htm
# End Source File
# Begin Source File

SOURCE=.\Help\0017.htm
# End Source File
# Begin Source File

SOURCE=.\Help\mightycasl.htm
# End Source File
# End Group
# Begin Group "Help Image Files"

# PROP Default_Filter "gif;jpg"
# Begin Source File

SOURCE=.\Help\images\0001.h1.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0001.h2.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0001.h3.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0001.h4.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0001.h5.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0002.h1.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0003.h2.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0003.h3.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0003.h4.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0003.h5.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0003.h6.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0003.h7.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0009.h8.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0010.h10.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0010.h9.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0011.h1.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0013.h2.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0014.h3.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0014.h4.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0015.h5.jpg
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h1.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h10.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h11.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h12.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h13.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h14.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h15.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h16.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h17.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h18.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h2.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h3.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h4.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h5.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h6.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h7.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h8.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0016.h9.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\0017.h1.gif
# End Source File
# Begin Source File

SOURCE=.\Help\images\BD10297_.GIF
# End Source File
# Begin Source File

SOURCE=.\Help\images\square_blue.gif
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section MightyCasl : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:24:CG_IDR_POPUP_SOURCE_VIEW:104
# 	1:22:CG_IDR_POPUP_DUMP_VIEW:108
# 	1:29:CG_IDR_POPUP_MIGHTY_CASL_VIEW:106
# 	1:24:CG_IDR_POPUP_OUTPUT_VIEW:105
# 	1:22:CG_IDR_POPUP_WATCH_DLG:103
# End Section
