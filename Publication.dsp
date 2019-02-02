# Microsoft Developer Studio Project File - Name="Publication" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Publication - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Publication.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Publication.mak" CFG="Publication - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Publication - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Publication - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Publication - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Publication - Win32 Release"
# Name "Publication - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddCategorie.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AjouterAuteurDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AjouterGenreDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AjouterMotClefDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AjouterPublicationPropSheet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AjouterSujetDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AjouterTypeDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AuteurSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CategorieSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DateEdit.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DES.c

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogNouvelUtilisateur.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogOptionBaseGal.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DocumentSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EnterLogin.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GenreSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\InfoGalSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ListUtilisateurDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LoginSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\modifierPassWordDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ModifierPublicationPropSheet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ModifierUtilisateurDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MotClefSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NationaliteSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NouvellePublication.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OptionBaseDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropCategorieDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropInfoMotClef.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropInfoResume.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubFile.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubGal.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubMotClef.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubResume.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropPagePubFileOpen.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropPubInfoGal.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PubContainer.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PubDocument.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PubElement.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Publication.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Publication.hpj
USERDEP__PUBLI="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

!IF  "$(CFG)" == "Publication - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Publication
InputPath=.\hlp\Publication.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Publication
InputPath=.\hlp\Publication.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Publication.rc

!IF  "$(CFG)" == "Publication - Win32 Release"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PublicationDoc.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PublicationInfo.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PublicationInfoGal.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PublicationView.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PubRacine.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheAuteur.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheAvdDocument.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheCategorieDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheDocument.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheGenre.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheMotClef.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheSujet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheType.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RechercheUtilisateurDialog.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RelationDocumentMotClefSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RepertoireTreeCtrl.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelectionRepertoire.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN" /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SujetSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TypeSet.cpp

!IF  "$(CFG)" == "Publication - Win32 Release"

# ADD CPP /D "VC_EXTRALEAN"

!ELSEIF  "$(CFG)" == "Publication - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddCategorie.h
# End Source File
# Begin Source File

SOURCE=.\AjouterAuteurDialog.h
# End Source File
# Begin Source File

SOURCE=.\AjouterGenreDialog.h
# End Source File
# Begin Source File

SOURCE=.\AjouterMotClefDialog.h
# End Source File
# Begin Source File

SOURCE=.\AjouterPublicationPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\AjouterSujetDialog.h
# End Source File
# Begin Source File

SOURCE=.\AjouterTypeDialog.h
# End Source File
# Begin Source File

SOURCE=.\AuteurSet.h
# End Source File
# Begin Source File

SOURCE=.\CategorieSet.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\constElement.h
# End Source File
# Begin Source File

SOURCE=.\DateEdit.h
# End Source File
# Begin Source File

SOURCE=.\DES.h
# End Source File
# Begin Source File

SOURCE=.\DialogNouvelUtilisateur.h
# End Source File
# Begin Source File

SOURCE=.\DialogOptionBaseGal.h
# End Source File
# Begin Source File

SOURCE=.\DocumentSet.h
# End Source File
# Begin Source File

SOURCE=.\EnterLogin.h
# End Source File
# Begin Source File

SOURCE=.\GenreSet.h
# End Source File
# Begin Source File

SOURCE=.\InfoGalSet.h
# End Source File
# Begin Source File

SOURCE=.\ListUtilisateurDialog.h
# End Source File
# Begin Source File

SOURCE=.\LoginSet.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\modifierPassWordDialog.h
# End Source File
# Begin Source File

SOURCE=.\ModifierPublicationPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\ModifierUtilisateurDialog.h
# End Source File
# Begin Source File

SOURCE=.\MotClefSet.h
# End Source File
# Begin Source File

SOURCE=.\NationaliteSet.h
# End Source File
# Begin Source File

SOURCE=.\NouvellePublication.h
# End Source File
# Begin Source File

SOURCE=.\OptionBaseDialog.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\PropCategorieDialog.h
# End Source File
# Begin Source File

SOURCE=.\PropInfoMotClef.h
# End Source File
# Begin Source File

SOURCE=.\PropInfoResume.h
# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubFile.h
# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubGal.h
# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubMotClef.h
# End Source File
# Begin Source File

SOURCE=.\PropPageAjouterPubResume.h
# End Source File
# Begin Source File

SOURCE=.\PropPagePubFileOpen.h
# End Source File
# Begin Source File

SOURCE=.\PropPubInfoGal.h
# End Source File
# Begin Source File

SOURCE=.\PubContainer.h
# End Source File
# Begin Source File

SOURCE=.\PubDocument.h
# End Source File
# Begin Source File

SOURCE=.\PubElement.h
# End Source File
# Begin Source File

SOURCE=.\Publication.h
# End Source File
# Begin Source File

SOURCE=.\PublicationDoc.h
# End Source File
# Begin Source File

SOURCE=.\PublicationInfo.h
# End Source File
# Begin Source File

SOURCE=.\PublicationInfoGal.h
# End Source File
# Begin Source File

SOURCE=.\PublicationView.h
# End Source File
# Begin Source File

SOURCE=.\PubRacine.h
# End Source File
# Begin Source File

SOURCE=.\RechercheAuteur.h
# End Source File
# Begin Source File

SOURCE=.\RechercheAvdDocument.h
# End Source File
# Begin Source File

SOURCE=.\RechercheCategorieDialog.h
# End Source File
# Begin Source File

SOURCE=.\RechercheDocument.h
# End Source File
# Begin Source File

SOURCE=.\RechercheGenre.h
# End Source File
# Begin Source File

SOURCE=.\RechercheMotClef.h
# End Source File
# Begin Source File

SOURCE=.\RechercheSujet.h
# End Source File
# Begin Source File

SOURCE=.\RechercheType.h
# End Source File
# Begin Source File

SOURCE=.\RechercheUtilisateurDialog.h
# End Source File
# Begin Source File

SOURCE=.\RelationDocumentMotClefSet.h
# End Source File
# Begin Source File

SOURCE=.\RepertoireTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SelectionRepertoire.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SujetSet.h
# End Source File
# Begin Source File

SOURCE=.\TypeSet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\aper_fichier.ico
# End Source File
# Begin Source File

SOURCE=.\res\Crdfle12.ico
# End Source File
# Begin Source File

SOURCE=.\res\fichier.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_publ.ico
# End Source File
# Begin Source File

SOURCE=.\res\prop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Publication.ico
# End Source File
# Begin Source File

SOURCE=.\res\Publication.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PublicationDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\repertoire.ico
# End Source File
# Begin Source File

SOURCE=.\res\repertoire_ouvert.ico
# End Source File
# Begin Source File

SOURCE=.\res\root.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\MakeHelp.bat
# End Source File
# Begin Source File

SOURCE=.\hlp\Publication.cnt
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Publication.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
