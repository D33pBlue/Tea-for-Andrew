
!define PRODUCT_NAME "Tea for Andrew"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "Francesco Bizzaro"
!define PRODUCT_WEB_SITE "https://github.com/D33pBlue/Tea-for-Andrew"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\TeaForAndrew.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "coffee-cup.ico"
!define MUI_UNICON "delete.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "License.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\TeaForAndrew.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "TeaForAndrew_Setup.exe"
InstallDir "$PROGRAMFILES\Tea for Andrew"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "SezionePrincipale" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "coffee-cup.ico"
  File "delete.ico"
  File "libFLAC-8.dll"
  File "libfreetype-6.dll"
  File "libjpeg-9.dll"
  File "libmodplug-1.dll"
  File "libogg-0.dll"
  File "libpng16-16.dll"
  File "libtiff-5.dll"
  File "libvorbis-0.dll"
  File "libvorbisfile-3.dll"
  File "libwebp-4.dll"
  File "License.txt"
  SetOutPath "$INSTDIR\Risorse"
  File "Risorse\andrew.png"
  File "Risorse\atterraggio.ogg"
  File "Risorse\atterraggio.wav"
  File "Risorse\credits.ogg"
  File "Risorse\font.ttf"
  File "Risorse\fuoco.ogg"
  File "Risorse\fuoco.wav"
  File "Risorse\geiser.ogg"
  File "Risorse\geiser.wav"
  File "Risorse\geiserBase.png"
  File "Risorse\geiserGas.png"
  File "Risorse\intro.mp3"
  File "Risorse\intro.ogg"
  File "Risorse\lava.png"
  File "Risorse\ost.mp3"
  File "Risorse\ost.ogg"
  File "Risorse\t1.png"
  File "Risorse\t2.png"
  File "Risorse\t3.png"
  File "Risorse\t4.png"
  File "Risorse\t5.png"
  File "Risorse\tea.png"
  File "Risorse\terreni.svg"
  File "Risorse\wallp.jpg"
  File "Risorse\win.wav"
  SetOutPath "$INSTDIR"
  File "SDL2.dll"
  File "SDL2_image.dll"
  File "SDL2_mixer.dll"
  File "SDL2_ttf.dll"
  File "smpeg2.dll"
  File "TeaForAndrew.exe"
  CreateDirectory "$SMPROGRAMS\Tea for Andrew"
  CreateShortCut "$SMPROGRAMS\Tea for Andrew\Tea for Andrew.lnk" "$INSTDIR\TeaForAndrew.exe"
  CreateShortCut "$DESKTOP\Tea for Andrew.lnk" "$INSTDIR\TeaForAndrew.exe"
  File "zlib1.dll"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\Tea for Andrew\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\Tea for Andrew\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\TeaForAndrew.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\TeaForAndrew.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) � stato completamente rimosso dal tuo computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Sei sicuro di voler completamente rimuovere $(^Name) e tutti i suoi componenti?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\zlib1.dll"
  Delete "$INSTDIR\TeaForAndrew.exe"
  Delete "$INSTDIR\smpeg2.dll"
  Delete "$INSTDIR\SDL2_ttf.dll"
  Delete "$INSTDIR\SDL2_mixer.dll"
  Delete "$INSTDIR\SDL2_image.dll"
  Delete "$INSTDIR\SDL2.dll"
  Delete "$INSTDIR\Risorse\win.wav"
  Delete "$INSTDIR\Risorse\wallp.jpg"
  Delete "$INSTDIR\Risorse\terreni.svg"
  Delete "$INSTDIR\Risorse\tea.png"
  Delete "$INSTDIR\Risorse\t5.png"
  Delete "$INSTDIR\Risorse\t4.png"
  Delete "$INSTDIR\Risorse\t3.png"
  Delete "$INSTDIR\Risorse\t2.png"
  Delete "$INSTDIR\Risorse\t1.png"
  Delete "$INSTDIR\Risorse\ost.ogg"
  Delete "$INSTDIR\Risorse\ost.mp3"
  Delete "$INSTDIR\Risorse\lava.png"
  Delete "$INSTDIR\Risorse\intro.ogg"
  Delete "$INSTDIR\Risorse\intro.mp3"
  Delete "$INSTDIR\Risorse\geiserGas.png"
  Delete "$INSTDIR\Risorse\geiserBase.png"
  Delete "$INSTDIR\Risorse\geiser.wav"
  Delete "$INSTDIR\Risorse\geiser.ogg"
  Delete "$INSTDIR\Risorse\fuoco.wav"
  Delete "$INSTDIR\Risorse\fuoco.ogg"
  Delete "$INSTDIR\Risorse\font.ttf"
  Delete "$INSTDIR\Risorse\credits.ogg"
  Delete "$INSTDIR\Risorse\atterraggio.wav"
  Delete "$INSTDIR\Risorse\atterraggio.ogg"
  Delete "$INSTDIR\Risorse\andrew.png"
  Delete "$INSTDIR\License.txt"
  Delete "$INSTDIR\libwebp-4.dll"
  Delete "$INSTDIR\libvorbisfile-3.dll"
  Delete "$INSTDIR\libvorbis-0.dll"
  Delete "$INSTDIR\libtiff-5.dll"
  Delete "$INSTDIR\libpng16-16.dll"
  Delete "$INSTDIR\libogg-0.dll"
  Delete "$INSTDIR\libmodplug-1.dll"
  Delete "$INSTDIR\libjpeg-9.dll"
  Delete "$INSTDIR\libfreetype-6.dll"
  Delete "$INSTDIR\libFLAC-8.dll"
  Delete "$INSTDIR\delete.ico"
  Delete "$INSTDIR\coffee-cup.ico"

  Delete "$SMPROGRAMS\Tea for Andrew\Uninstall.lnk"
  Delete "$SMPROGRAMS\Tea for Andrew\Website.lnk"
  Delete "$DESKTOP\Tea for Andrew.lnk"
  Delete "$SMPROGRAMS\Tea for Andrew\Tea for Andrew.lnk"

  RMDir "$SMPROGRAMS\Tea for Andrew"
  RMDir "$INSTDIR\Risorse"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
