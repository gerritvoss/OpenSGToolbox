# name the installer
!define ProjectName "OpenSGToolbox"
!define SMPROGRAMSFolder $SMPROGRAMS\${ProjectName}
!define OutFileName ${ProjectName}.exe
!define InstallDirName ${ProjectName}
!define ProjectRootDirName "..\.."
!define InputDirName "..\..\Builds\Windows"
!define UninstallFileName "Uninstall ${ProjectName}.exe"

outFile "${OutFileName}"

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

# default section start; every NSIS script has at least one section.
section
   
   # define the output path for this file
   setOutPath $INSTDIR
   
   #Create the Install Directory
   CreateDirectory $INSTDIR
   
   # define what to install and place it in the output path
   #file test.txt
   
   # define uninstaller name
   writeUninstaller "$INSTDIR\${UninstallFileName}"
   
   #Create OpenSGToolbox environment variable
   
   # create a shortcut named "new shortcut" in the start menu programs directory
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
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Toolbox"
      CreateDirectory $INSTDIR\Tutorials\Toolbox
      setOutPath $INSTDIR\Tutorials\Toolbox
      File /nonfatal "${ProjectRootDirName}\Toolbox\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\Toolbox\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Toolbox\Tutorials\*.vcproj"
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Input"
      CreateDirectory $INSTDIR\Tutorials\Input
      setOutPath $INSTDIR\Tutorials\Input
      File /nonfatal "${ProjectRootDirName}\Input\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\Input\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Input\Tutorials\*.vcproj"
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Animation"
      CreateDirectory $INSTDIR\Tutorials\Animation
      setOutPath $INSTDIR\Tutorials\Animation
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Animation\Tutorials\*.vcproj"
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Dynamics"
      CreateDirectory $INSTDIR\Tutorials\Dynamics
      setOutPath $INSTDIR\Tutorials\Dynamics
      File /nonfatal "${ProjectRootDirName}\Dynamics\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\Dynamics\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Dynamics\Tutorials\*.vcproj"
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\ParticleSystem"
      CreateDirectory $INSTDIR\Tutorials\ParticleSystem
      setOutPath $INSTDIR\Tutorials\ParticleSystem
      File /nonfatal "${ProjectRootDirName}\ParticleSystem\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\ParticleSystem\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\ParticleSystem\Tutorials\*.vcproj"
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Sound"
      CreateDirectory $INSTDIR\Tutorials\Sound
      setOutPath $INSTDIR\Tutorials\Sound
      File /nonfatal "${ProjectRootDirName}\Sound\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\Sound\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Sound\Tutorials\*.vcproj"
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\UserInterface"
      CreateDirectory $INSTDIR\Tutorials\UserInterface
      setOutPath $INSTDIR\Tutorials\UserInterface
      File /nonfatal "${ProjectRootDirName}\UserInterface\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\UserInterface\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\UserInterface\Tutorials\*.vcproj"
      
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials\Game"
      CreateDirectory $INSTDIR\Tutorials\Game
      setOutPath $INSTDIR\Tutorials\Game
      File /nonfatal "${ProjectRootDirName}\Game\Tutorials\*D.exe"
      File /nonfatal "${ProjectRootDirName}\Game\Tutorials\*.cpp"
      File /nonfatal "${ProjectRootDirName}\Game\Tutorials\*.vcproj"
      
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
      
      #File "${InputDirName}\lib\OSG*[^D].lib"
      #File "${InputDirName}\lib\OSG*[^D].dll"
      
      File "${InputDirName}\lib\OSGAnimation.lib"
      File "${InputDirName}\lib\OSGDynamics.lib"
      File "${InputDirName}\lib\OSGInput.lib"
      File "${InputDirName}\lib\OSGToolbox.lib"
      File "${InputDirName}\lib\OSGParticleSystem.lib"
      File "${InputDirName}\lib\OSGUserInterface.lib"
      File "${InputDirName}\lib\OSGGame.lib"
      File "${InputDirName}\lib\OSGSound.lib"
      
      File "${InputDirName}\lib\OSGAnimation.dll"
      File "${InputDirName}\lib\OSGDynamics.dll"
      File "${InputDirName}\lib\OSGInput.dll"
      File "${InputDirName}\lib\OSGToolbox.dll"
      File "${InputDirName}\lib\OSGParticleSystem.dll"
      File "${InputDirName}\lib\OSGUserInterface.dll"
      File "${InputDirName}\lib\OSGGame.dll"
      File "${InputDirName}\lib\OSGSound.dll"
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
      File "${ProjectRootDirName}\Toolbox\Tutorials\*D.exe"
      
   sectionEnd
SectionGroupEnd

section "Documentation"
   # define the output path for this file
   setOutPath $INSTDIR
   
   #Create the Install Directory
   CreateDirectory $INSTDIR\Documentation
sectionEnd


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

