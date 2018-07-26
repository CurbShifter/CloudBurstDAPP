:: =====================================================================================
set root=%1
set root=%root:"=%
set folder=%root%
echo Project root folder set to: %root%
:: =====================================================================================
set SubWCRev="C:\Program Files\TortoiseSVN\bin\SubWCRev.exe"
%SubWCRev% "%folder%\" "%folder%Source\VersionTemplate.h" "%folder%Source\Version.h"
%SubWCRev% "%folder%\" "%folder%Builds\MacOSX\revnr-Template.h" "%folder%Builds\MacOSX\revnr.h"