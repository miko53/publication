@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by PUBLICATION.HPJ. >"hlp\Publication.hm"
echo. >>"hlp\Publication.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Publication.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Publication.hm"
echo. >>"hlp\Publication.hm"
echo // Prompts (IDP_*) >>"hlp\Publication.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Publication.hm"
echo. >>"hlp\Publication.hm"
echo // Resources (IDR_*) >>"hlp\Publication.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Publication.hm"
echo. >>"hlp\Publication.hm"
echo // Dialogs (IDD_*) >>"hlp\Publication.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Publication.hm"
echo. >>"hlp\Publication.hm"
echo // Frame Controls (IDW_*) >>"hlp\Publication.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Publication.hm"
REM -- Make help for Project PUBLICATION


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Publication.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Publication.hlp" goto :Error
if not exist "hlp\Publication.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Publication.hlp" Debug
if exist Debug\nul copy "hlp\Publication.cnt" Debug
if exist Release\nul copy "hlp\Publication.hlp" Release
if exist Release\nul copy "hlp\Publication.cnt" Release
echo.
goto :done

:Error
echo hlp\Publication.hpj(1) : error: Problem encountered creating help file

:done
echo.
