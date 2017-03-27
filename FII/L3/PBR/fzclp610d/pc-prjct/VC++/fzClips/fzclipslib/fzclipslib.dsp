# Microsoft Developer Studio Project File - Name="fzclipslib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=fzclipslib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fzclipslib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fzclipslib.mak" CFG="fzclipslib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fzclipslib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fzclipslib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fzclipslib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "fzclipslib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\..\source" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "fzclipslib - Win32 Release"
# Name "fzclipslib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\..\source\agenda.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\analysis.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\argacces.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\bload.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\bmathfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\bsave.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classcom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classexm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classinf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classini.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\clsltpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\commline.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\conscomp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\constrct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\constrnt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\crstrtgy.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrcbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrccom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrcpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnchk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrncmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnops.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnutl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\default.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\defins.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\developr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctbsc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctdef.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxexe.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dfinsbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dfinscmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\drive.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\edbasic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\edmain.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\edmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\edstruct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\edterm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\emathfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\engine.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\evaluatn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\expressn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\exprnbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\exprnops.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\exprnpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\extnfunc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factbld.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factcom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factgen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\facthsh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factlhs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factmch.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factmngr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factprt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factrete.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factrhs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\filecom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\filertr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzycom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzydef.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzylhs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzymod.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzypsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzyrhs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzyutl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\generate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrccmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrccom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcexe.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlbsc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlcom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globldef.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\immthpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\incrrset.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\inherpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\inscom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insfile.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insmngr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insmoddp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insmult.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\inspsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insquery.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insqypsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\iofun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\lgcldpnd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\memalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\miscfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulbsc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\moduldef.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulutl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgcom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgpass.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\multifld.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\multifun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtbld.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtfnx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtgen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtmch.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\parsefun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\pattern.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\pprint.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prccode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prcdrfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prcdrpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prdctfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prntutil.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\proflfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\reorder.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\reteutil.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\retract.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\router.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulebin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulebld.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulebsc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulecmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulecom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulecstr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\ruledef.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\ruledlt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulelhs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulepsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\scanner.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\sortfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\strngfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\strngrtr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\symblbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\symblcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\symbol.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\sysdep.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\textpro.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltbin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltbsc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltcmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltdef.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltlhs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltpsr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltrhs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltutl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\userdata.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\utility.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\watch.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\source\agenda.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\analysis.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\argacces.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\bload.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\bmathfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\bsave.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classcom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classexm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classinf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classini.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\classpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\clips.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\clsltpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cmptblty.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\commline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\conscomp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\constrct.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\constrnt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\crstrtgy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrcbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrccmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrccom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrcpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnchk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrncmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnops.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\cstrnutl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\default.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\defins.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\developr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctbsc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctdef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffctpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxexe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dffnxpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dfinsbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\dfinscmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\drive.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\ed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\emathfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\engine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\evaluatn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\expressn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\exprnbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\exprnops.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\exprnpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\extnfunc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\extobj.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factbld.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factcom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factgen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\facthsh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factlhs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factmch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factmngr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factprt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factrete.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\factrhs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\filecom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\filertr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzycom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzydef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzylhs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzylv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzymod.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzypsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzyrhs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzyutl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\fuzzyval.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\generate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrccmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrccom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcexe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\genrcpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlbsc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlcom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globldef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\globlpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\immthpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\incrrset.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\inherpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\inscom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insfile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insmngr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insmoddp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insmult.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\inspsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insquery.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\insqypsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\iofun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\lgcldpnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\match.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\memalloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\miscfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulbsc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\moduldef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\modulutl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgcom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgpass.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\msgpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\multifld.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\multifun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\network.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\object.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtbld.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtfnx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtgen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\objrtmch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\parsefun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\pattern.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\pprint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prccode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prcdrfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prcdrpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prdctfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\prntutil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\proflfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\reorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\reteutil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\retract.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\router.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulebin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulebld.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulebsc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulecmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulecom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulecstr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\ruledef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\ruledlt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulelhs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\rulepsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\scanner.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\setup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\shrtlnkn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\sortfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\strngfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\strngrtr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\symblbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\symblcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\symbol.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\sysdep.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\textpro.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltbin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltbsc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltcmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltdef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltlhs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltpsr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltrhs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\tmpltutl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\userdata.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\utility.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\watch.h
# End Source File
# End Group
# End Target
# End Project
