!include FindFile.nsh

# name the installer
!define ProjectName "OpenSGToolbox"
!define SMPROGRAMSFolder $SMPROGRAMS\${ProjectName}
!define OutFileName ${ProjectName}.exe
!define InstallDirName ${ProjectName}
!define ProjectRootDirName "..\.."
!define InputDirName "..\..\Builds\Windows"
!define UninstallFileName "Uninstall ${ProjectName}.exe"

outFile "${OutFileName}"

icon "${InputDirName}\Data\OpenSGToolbox-Icon-32x32.ico"

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

# define the directory to install to, the desktop in this case as specified  
# by the predefined $DESKTOP variable

installDir $PROGRAMFILES\${InstallDirName}


Page license
   LicenseText "GNU Lesser Library General Public License v. 3"
   LicenseData "${ProjectRootDirName}\LICENSE"
   LicenseForceSelection checkbox
   
Page components
Page Directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Function InstallToolboxTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Toolbox\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallInputTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Input\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallAnimationTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Animation\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallDynamicsTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Dynamics\$R3.lnk" "$R4"
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

Function InstallUserInterfaceTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\User Interface\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

Function InstallGameTutorialLinks
   createShortCut "${SMPROGRAMSFolder}\Tutorials\Game\$R3.lnk" "$R4"
	Push "Continue"
FunctionEnd

# default section start; every NSIS script has at least one section.
section
	#IntCmp IsUserAdmin 0 is0 lessthan0 morethan0
	#is0:
	#  messageBox MB_OK "Adminsitrator"
	#  Goto done
	#lessthan0:
	#  messageBox MB_OK "Error"
	#  Goto done
	#morethan0:
	#  messageBox MB_OK "Not Administrator"
	#  Goto done
	#done:
   # define the output path for this file
   setOutPath $INSTDIR
   
   #Create the Install Directory
   CreateDirectory $INSTDIR
   
   # define what to install and place it in the output path
   #file test.txt
   
   # define uninstaller name
   writeUninstaller "$INSTDIR\${UninstallFileName}"
   
   #Create OpenSGToolbox environment variable
   
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
   sectionEnd

   section "Header Files"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Include Directory
      File /r "${InputDirName}\include"
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
      
      CreateDirectory $INSTDIR\Tutorials\Animation
      setOutPath $INSTDIR\Tutorials\Animation
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Animation\Tutorials\Data"
      
      CreateDirectory $INSTDIR\Tutorials\Dynamics
      setOutPath $INSTDIR\Tutorials\Dynamics
      File /nonfatal "${ProjectRootDirName}\Dynamics\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Dynamics\Tutorials\*.vcproj"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Dynamics\Tutorials\Data"
      
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
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Dynamics"
      CreateDirectory $INSTDIR\Tutorials\Dynamics
      setOutPath $INSTDIR\Tutorials\Dynamics
      File /nonfatal "${ProjectRootDirName}\Dynamics\Tutorials\*.exe"
      File /nonfatal /r /x Thumbs.db /x .svn "${ProjectRootDirName}\Dynamics\Tutorials\Data"
		
		Push "*.exe" ;File or folder to search. Wildcards are supported.
		Push "$INSTDIR\Tutorials\Dynamics" ;Path where to search for the file or folder.
		Push $0
		GetFunctionAddress $0 "InstallDynamicsTutorialLinks" ;Custom callback function name
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
			CreateDirectory $INSTDIR\Dependencies
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Include
		sectionEnd
		section "Development"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Dependencies
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Include
		sectionEnd
	SectionGroupEnd
	SectionGroup "boost"
		section "Release"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Dependencies
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Include
		sectionEnd
		section "Development"
			# define the output path for this file
			setOutPath $INSTDIR
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Dependencies
			
			#Create the Dependencies Install Directory
			CreateDirectory $INSTDIR\Include
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
   
   # now delete installed file
   #delete $INSTDIR\test.txt
   
   # second, remove the link from the start menu
   RMDir /r "${SMPROGRAMSFolder}"
   
   #Delete the registry key for add/remove program control panel
   DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenSGToolbox"
 
sectionEnd


