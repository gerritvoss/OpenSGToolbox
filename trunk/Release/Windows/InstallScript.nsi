
!include FindFile.nsh
!include LogicLib.nsh
!include EnvVarUpdate.nsh
!include MUI.nsh


# name the installer
!define ProjectName "OpenSGToolbox"
!define SMPROGRAMSFolder $SMPROGRAMS\${ProjectName}
!define InstallDirName ${ProjectName}
!define ProjectRootDirName "..\.."
!define InputDirName "..\..\Builds\Windows"
!define UninstallFileName "Uninstall ${ProjectName}.exe"
!define BoostDepDir "C:\Program Files\boost\boost_1_39"
!define ODEDepDir "C:\Users\David\Documents\Work\ode-0.11.1"
!define LuaDepDir "C:\Program Files\Lua\5.1"
!define OpenSGDepDir "C:\Users\David\Documents\Work\OpenSG-1.8\OpenSG\Build\win32-msvc90\installed"
!define Version "0.8.0.0"
!define VisualStudioVersion "2008"
!define OutFileName "${ProjectName}-Windows-${Version}-vs${VisualStudioVersion}.exe"

outFile "${OutFileName}"

VIProductVersion "${Version}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${ProjectName}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "..."
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${Version}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "InternalName" "${OutFileName}"

icon "${ProjectRootDirName}\Data\OpenSGToolbox-Icon-32x32.ico"

Var AddLibsToPATH

# http://nsis.sourceforge.net/Shortcuts_removal_fails_on_Windows_Vista
RequestExecutionLevel admin


#Version Information
#Function InitVersion
#    ClearErrors
#    FileOpen $0 "${ProjectRootDirName}\VERSION" r
#    IfErrors done
#    FileRead $0 $Version
#    DetailPrint $Version
#    FileClose $0
#    done:
#FunctionEnd


!macro IsUserAdmin RESULT
 !define Index "Line${__LINE__}"
   StrCpy ${RESULT} 0
   System::Call '*(&i1 0,&i4 0,&i1 5)i.r0'
   System::Call 'advapi32::AllocateAndInitializeSid(i r0,i 2,i 32,i 544,i 0,i 0,i 0,i 0,i 0, \
   i 0,*i .R0)i.r5'
   System::Free $0
   System::Call 'advapi32::CheckTokenMembership(i n,i R0,*i .R1)i.r5'
   StrCmp $5 0 ${Index}_Error
   StrCpy ${RESULT} $R1
   Goto ${Index}_End
 ${Index}_Error:
   StrCpy ${RESULT} -1
 ${Index}_End:
   System::Call 'advapi32::FreeSid(i R0)i.r5'
 !undef Index
!macroend

installDir $PROGRAMFILES\${InstallDirName}


Page license
   LicenseText "GNU Lesser Library General Public License v. 3"
   LicenseData "${ProjectRootDirName}\LICENSE.txt"
   LicenseForceSelection checkbox
   
Page components
Page Directory
Page custom OptionsPage OptionsPageLeave ": Install Options page"
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

#Define Install Options page
Function OptionsPage
   ReserveFile "InstallOptionsFile.ini"

  # If you need to skip the page depending on a condition, call Abort.
  !insertmacro MUI_INSTALLOPTIONS_EXTRACT "InstallOptionsFile.ini"
  !insertmacro MUI_INSTALLOPTIONS_DISPLAY "InstallOptionsFile.ini"
FunctionEnd
 
Function OptionsPageLeave
  # Form validation here. Call Abort to go back to the page.
  # Use !insertmacro MUI_INSTALLOPTIONS_READ $Var "InstallOptionsFile.ini" ...
  # to get values.
  
  # Get control window handle.
  !insertmacro MUI_INSTALLOPTIONS_READ $R0 "InstallOptionsFile.ini" "Field 1" "HWND"

  !insertmacro MUI_INSTALLOPTIONS_READ $AddLibsToPATH "InstallOptionsFile.ini" "Field 1" "State"
FunctionEnd

Function InstallToolboxTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Toolbox\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallInputTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Input\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallPhysicsTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Physics\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallAnimationTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Animation\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallLuaTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Lua\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallParticleSystemTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Particle System\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallSoundTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Sound\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallVideoTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Video\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallMetabolicTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Metabolic\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallUserInterfaceTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\User Interface\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallGameTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Game\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function .onInit
  #call InitVersion
	UserInfo::GetName
	Pop $0
	UserInfo::GetAccountType
	Pop $1
	# GetOriginalAccountType will check the tokens of the original user of the
	# current thread/process. If the user tokens were elevated or limited for
	# this process, GetOriginalAccountType will return the non-restricted
	# account type.
	# On Vista with UAC, for example, this is not the same value when running
	# with `RequestExecutionLevel user`. GetOriginalAccountType will return
	# "admin" while GetAccountType will return "user".
	UserInfo::GetOriginalAccountType
	Pop $2
	StrCmp $1 "Admin" HasPrivlages 0
	
	StrCmp $1 "Power" HasPrivlages 0
	
	StrCmp $1 "User" DoesntHavePrivlages 0
	
	StrCmp $1 "Guest" DoesntHavePrivlages 0
	
	MessageBox MB_OK "Unknown error"
	
	DoesntHavePrivlages:
		MessageBox MB_OK 'User "$0" Needs Admin Privlages to install'
	    Goto done
	    
	HasPrivlages:
		MessageBox MB_OK 'User "$0" has nessicary privlages to install'
	    Goto done
	done:
FunctionEnd

# default section start; every NSIS script has at least one section.
section
   #Create the Install Directory
   CreateDirectory $INSTDIR
   
   # define the output path for this file
   setOutPath $INSTDIR
   
   # define uninstaller name
   writeUninstaller "$INSTDIR\${UninstallFileName}"
   
   #Include the Licence file
   File "${ProjectRootDirName}\LICENSE.txt"
   
   # create a shortcut in the start menu programs directory
   # presently, the new shortcut doesn't call anything (the second field is blank)
   CreateDirectory "${SMPROGRAMSFolder}"
   createShortCut "${SMPROGRAMSFolder}\${ProjectName} Directory.lnk" "$INSTDIR"
   createShortCut "${SMPROGRAMSFolder}\Uninstall ${ProjectName}.lnk" "$INSTDIR\${UninstallFileName}"
   
    #Create the Registry keys for the Add/Remove program control panel
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenSGToolbox" \
                     "DisplayName" "OpenSG Toolbox"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenSGToolbox" \
                     "UninstallString" "$INSTDIR\${UninstallFileName}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenSGToolbox" \
                     "QuietUninstallString" "$\"$INSTDIR\${UninstallFileName}$\" /S"

    ${If} $AddLibsToPATH == 1
        #Set up the Path
        ${EnvVarUpdate} $0 "PATH" "A" "HKCU" "$INSTDIR\lib"
    ${EndIf}
# default section end
sectionEnd

SectionGroup "Devolopment"
   section "Libraries"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Add lib directory to the path
      
      #Create the Install Directory
      CreateDirectory $INSTDIR\lib
      
      setOutPath $INSTDIR\lib
      
      File "${InputDirName}\lib\OSG*D.lib"
      File "${InputDirName}\lib\OSG*D.dll"
      
       #Add The OPENSG_TOOLBOX_DIR Environment Variable
       ${EnvVarUpdate} $0 "OPENSG_TOOLBOX_DIR" "A" "HKCU" "$INSTDIR"
   sectionEnd

   section "Header Files"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Include Directory
      File /r "${InputDirName}\include"
      
       #Add The OPENSG_TOOLBOX_DIR Environment Variable
       ${EnvVarUpdate} $0 "OPENSG_TOOLBOX_DIR" "A" "HKCU" "$INSTDIR"
   sectionEnd
   
   
   
   section "Tutorials"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Create the Install Directory
      CreateDirectory $INSTDIR\Tutorials
      
      #Create StartMenu Tutorial Directory
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials"
      setOutPath $INSTDIR\Tutorials
      
      #Create Tutorial Directory for each Library
      CreateDirectory $INSTDIR\Tutorials\Toolbox
      setOutPath $INSTDIR\Tutorials\Toolbox
      File /nonfatal "${ProjectRootDirName}\Toolbox\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Toolbox\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Toolbox\Tutorials\Data"
		
      
      CreateDirectory $INSTDIR\Tutorials\Input
      setOutPath $INSTDIR\Tutorials\Input
      File /nonfatal "${ProjectRootDirName}\Input\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Input\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Input\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\Physics
      setOutPath $INSTDIR\Tutorials\Physics
      File /nonfatal "${ProjectRootDirName}\Physics\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Physics\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Physics\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\Animation
      setOutPath $INSTDIR\Tutorials\Animation
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Animation\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\Lua
      setOutPath $INSTDIR\Tutorials\Lua
      File /nonfatal "${ProjectRootDirName}\Lua\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Lua\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Lua\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\ParticleSystem
      setOutPath $INSTDIR\Tutorials\ParticleSystem
      File /nonfatal "${ProjectRootDirName}\ParticleSystem\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\ParticleSystem\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\ParticleSystem\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\Sound
      setOutPath $INSTDIR\Tutorials\Sound
      File /nonfatal "${ProjectRootDirName}\Sound\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Sound\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Sound\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\UserInterface
      setOutPath $INSTDIR\Tutorials\UserInterface
      File /nonfatal "${ProjectRootDirName}\UserInterface\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\UserInterface\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\UserInterface\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\Game
      setOutPath $INSTDIR\Tutorials\Game
      File /nonfatal "${ProjectRootDirName}\Game\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Game\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Game\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\Video
      setOutPath $INSTDIR\Tutorials\Video
      File /nonfatal "${ProjectRootDirName}\Video\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Video\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Video\Tutorials\Data"
		
      CreateDirectory $INSTDIR\Tutorials\Metabolic
      setOutPath $INSTDIR\Tutorials\Metabolic
      File /nonfatal "${ProjectRootDirName}\Metabolic\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Metabolic\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Metabolic\Tutorials\Data"
      
   sectionEnd
SectionGroupEnd

SectionGroup "Release"
   section "Libraries"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Add lib directory to the path
      
      #Create the Install Directory
      CreateDirectory $INSTDIR\lib
         
      setOutPath $INSTDIR\lib
      File /x *D.lib "${InputDirName}\lib\OSG*.lib"
      File /x *D.dll "${InputDirName}\lib\OSG*.dll"
		
   sectionEnd
   section "Tutorials"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Create the Install Directory
      CreateDirectory $INSTDIR\Tutorials
      
      #Create StartMenu Tutorial Directory
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials"
      setOutPath $INSTDIR\Tutorials
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Toolbox"
      CreateDirectory $INSTDIR\Tutorials\Toolbox
      setOutPath $INSTDIR\Tutorials\Toolbox
      #File /nonfatal /x *D.exe "${ProjectRootDirName}\Toolbox\Tutorials\*.exe"
      File /nonfatal "${ProjectRootDirName}\Toolbox\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Toolbox\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Toolbox" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallToolboxTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Input"
      CreateDirectory $INSTDIR\Tutorials\Input
      setOutPath $INSTDIR\Tutorials\Input
      File /nonfatal "${ProjectRootDirName}\Input\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Input\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Input" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallInputTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
        
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Physics"
      CreateDirectory $INSTDIR\Tutorials\Physics
      setOutPath $INSTDIR\Tutorials\Physics
      File /nonfatal "${ProjectRootDirName}\Physics\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Physics\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Physics" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallPhysicsTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Animation"
      CreateDirectory $INSTDIR\Tutorials\Animation
      setOutPath $INSTDIR\Tutorials\Animation
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Animation\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Animation" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallAnimationTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Lua"
      CreateDirectory $INSTDIR\Tutorials\Lua
      setOutPath $INSTDIR\Tutorials\Lua
      File /nonfatal "${ProjectRootDirName}\Lua\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Lua\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Lua" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallLuaTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Particle System"
      CreateDirectory $INSTDIR\Tutorials\ParticleSystem
      setOutPath $INSTDIR\Tutorials\ParticleSystem
      File /nonfatal "${ProjectRootDirName}\ParticleSystem\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\ParticleSystem\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\ParticleSystem" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallParticleSystemTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Sound"
      CreateDirectory $INSTDIR\Tutorials\Sound
      setOutPath $INSTDIR\Tutorials\Sound
      File /nonfatal "${ProjectRootDirName}\Sound\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Sound\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Sound" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallSoundTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\User Interface"
      CreateDirectory $INSTDIR\Tutorials\UserInterface
      setOutPath $INSTDIR\Tutorials\UserInterface
      File /nonfatal "${ProjectRootDirName}\UserInterface\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\UserInterface\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\UserInterface" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallUserInterfaceTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Game"
      CreateDirectory $INSTDIR\Tutorials\Game
      setOutPath $INSTDIR\Tutorials\Game
      File /nonfatal "${ProjectRootDirName}\Game\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Game\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Game" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallGameTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Video"
      CreateDirectory $INSTDIR\Tutorials\Video
      setOutPath $INSTDIR\Tutorials\Video
      File /nonfatal "${ProjectRootDirName}\Video\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Video\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Video" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallVideoTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Metabolic"
      CreateDirectory $INSTDIR\Tutorials\Metabolic
      setOutPath $INSTDIR\Tutorials\Metabolic
      File /nonfatal "${ProjectRootDirName}\Metabolic\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Metabolic\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Metabolic" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallMetabolicTutorialLinks" ;Custom callback function name
		Exch $0
		Push "0" ;Include subfolders in search. (0 = false, 1 = true)
		Push "0" ;Enter subfolders with ".". This only works if "Include subfolders in search" is set to 1 (true). (0 = false, 1 = true)
		Call SearchFile
        

   sectionEnd
SectionGroupEnd

section "Documentation"
   # define the output path for this file
   setOutPath $INSTDIR
   
   #Create the Install Directory
   CreateDirectory $INSTDIR\Documentation
sectionEnd

SectionGroup "Dependencies"
	SectionGroup "OpenSG"
		section "Release"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\lib
            
            setOutPath $INSTDIR\lib
            File "${OpenSGDepDir}\lib\OSGBase.*"
            File "${OpenSGDepDir}\lib\OSGSystem.*"
            File "${OpenSGDepDir}\lib\OSGWindowWIN32.*"
            File "${OpenSGDepDir}\lib\OSGWindowGLUT.*"
            File "${OpenSGDepDir}\lib\glut32.dll"
            File "${OpenSGDepDir}\lib\msvcp*.dll"
            File "${OpenSGDepDir}\lib\msvcr*.dll"
            File "${OpenSGDepDir}\lib\msvcrt.dll"
		sectionEnd
		section "Development"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\lib
			
            setOutPath $INSTDIR\lib
            File "${OpenSGDepDir}\lib\OSGBaseD.*"
            File "${OpenSGDepDir}\lib\OSGSystemD.*"
            File "${OpenSGDepDir}\lib\OSGWindowWIN32D.*"
            File "${OpenSGDepDir}\lib\OSGWindowGLUTD.*"
            File "${OpenSGDepDir}\lib\glut32.*"
            File "${OpenSGDepDir}\lib\msvcp*.dll"
            File "${OpenSGDepDir}\lib\msvcr*.dll"
            File "${OpenSGDepDir}\lib\msvcrt.dll"
            File "${OpenSGDepDir}\lib\libjpeg.*"
            File "${OpenSGDepDir}\lib\libpng.*"
            File "${OpenSGDepDir}\lib\libmmd.*"
            File "${OpenSGDepDir}\lib\tif32.*"
            File "${OpenSGDepDir}\lib\zlib.*"
            File "${OpenSGDepDir}\lib\libjasper.*"
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Dependencies
            setOutPath $INSTDIR\Dependencies
             File "..\OpenSG-LICENSE.txt"
             
			CreateDirectory $INSTDIR\include
			
            setOutPath $INSTDIR\include
         
             #Include Directory
             File /r "${OpenSGDepDir}\include\*"
             
             #Add The OPENSG Environment Variable
             ${EnvVarUpdate} $0 "OPENSG" "A" "HKCU" "$INSTDIR\lib"
		sectionEnd
	SectionGroupEnd
	SectionGroup "boost"
		section "Release"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\lib
            
            setOutPath $INSTDIR\lib
            File "${BoostDepDir}\lib\boost_filesystem-*"
            File "${BoostDepDir}\lib\boost_system-*"
            File "${BoostDepDir}\lib\boost_program_options-*"
            
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Include
		sectionEnd
		section "Development"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies include Directory
			CreateDirectory $INSTDIR\Dependencies
            setOutPath $INSTDIR\Dependencies
             File "..\Boost-LICENSE.txt"
            
            
			CreateDirectory $INSTDIR\include
			CreateDirectory $INSTDIR\include\boost
			
            setOutPath $INSTDIR\include\boost
         
             #Include Directory
             File /r "${BoostDepDir}\boost\*"
             
             #Add The Boost Environment Variable
             ${EnvVarUpdate} $0 "BOOST_BASE_DIR" "A" "HKCU" "$INSTDIR"
		sectionEnd
	SectionGroupEnd
	SectionGroup "ODE"
		section "Release"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\lib
            
            setOutPath $INSTDIR\lib
            File "${ODEDepDir}\lib\ode_single.*"
            File "${ODEDepDir}\lib\ode_singled.*"
            
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Include
		sectionEnd
		section "Development"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Dependencies
            setOutPath $INSTDIR\Dependencies
             File "..\ODE-LICENSE.txt"
             
			CreateDirectory $INSTDIR\include
			
            setOutPath $INSTDIR\include
         
             #Include Directory
             File /r "${ODEDepDir}\include\*"
             
             #Add The ODE Environment Variable
             ${EnvVarUpdate} $0 "ODE_BASE_DIR" "A" "HKCU" "$INSTDIR"
		sectionEnd
	SectionGroupEnd
	SectionGroup "Lua"
		section "Release"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\lib
            
            setOutPath $INSTDIR\lib
            File "${LuaDepDir}\lib\lua*.*"
            
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Include
		sectionEnd
		section "Development"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Dependencies
            setOutPath $INSTDIR\Dependencies
             File "..\Lua-LICENSE.txt"
             
			CreateDirectory $INSTDIR\include
			
            setOutPath $INSTDIR\include
         
             #Include Directory
             File /r "${LuaDepDir}\include\*"
             
             #Add The Lua Environment Variable
             ${EnvVarUpdate} $0 "LUA_BASE_DIR" "A" "HKCU" "$INSTDIR"
		sectionEnd
	SectionGroupEnd
SectionGroupEnd


# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
section "un.Uninstall ${ProjectName}"

   # Always delete uninstaller first
   delete "$INSTDIR\${UninstallFileName}"
    
   #Remove the Install Directory
   RMDir /r $INSTDIR
   
   # second, remove the link from the start menu
   RMDir /r "${SMPROGRAMSFolder}"
   
   #Delete the registry key for add/remove program control panel
   DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenSGToolbox"
   
   #Remove from path
   ${un.EnvVarUpdate} $0 "PATH" "R" "HKCU" "$INSTDIR\lib"
   
   #Remove The OPENSG Environment Variable
   ${un.EnvVarUpdate} $0 "OPENSG_TOOLBOX_DIR" "R" "HKCU" "$INSTDIR"
   
   #Remove The OPENSG Environment Variable
   ${un.EnvVarUpdate} $0 "OPENSG" "R" "HKCU" "$INSTDIR\lib"
   
   #Remove The Boost Environment Variable
   ${un.EnvVarUpdate} $0 "BOOST_BASE_DIR" "R" "HKCU" "$INSTDIR"
   
   #Remove The ODE Environment Variable
   ${un.EnvVarUpdate} $0 "ODE_BASE_DIR" "R" "HKCU" "$INSTDIR"
   
   #Remove The Lua Environment Variable
   ${un.EnvVarUpdate} $0 "LUA_BASE_DIR" "R" "HKCU" "$INSTDIR"
 
sectionEnd


