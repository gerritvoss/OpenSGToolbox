import os
import sys
import glob
import shutil

def convertPathToOutput(Path):
   if os.name == "posix":
        return Path
   else:
       return '"' + Path + '"'

def GenFCsFromFile(GenFCsPyDir, FcdCompilePath, Path):
   os.system(convertPathToOutput(FcdCompilePath + " -b -f " + convertPathToOutput(Path)))

   BaseHeaderFile = "OSG" + os.path.splitext(os.path.split(Path)[1])[0] + "Base.h"
   BaseInlineFile = "OSG" + os.path.splitext(os.path.split(Path)[1])[0] + "Base.inl"
   FieldsFile = "OSG" + os.path.splitext(os.path.split(Path)[1])[0] + "Fields.h"
   BaseCodeFile = "OSG" + os.path.splitext(os.path.split(Path)[1])[0] + "Base.cpp"

   HeaderFile = "OSG" + os.path.splitext(os.path.split(Path)[1])[0] + ".h"
   InlineFile = "OSG" + os.path.splitext(os.path.split(Path)[1])[0] + ".inl"
   CodeFile = "OSG" + os.path.splitext(os.path.split(Path)[1])[0] + ".cpp"

   BaseDir = os.path.dirname(Path)
   if(BaseDir == ""):
       BaseDir = os.getcwd()

   #Only move the files if the current working directory is not where they should be put
   if(os.name != "posix" or (not os.path.samefile(os.getcwd(), BaseDir))):
       shutil.move(BaseHeaderFile, os.path.join(os.path.split(Path)[0],BaseHeaderFile))
       shutil.move(BaseInlineFile, os.path.join(os.path.split(Path)[0],BaseInlineFile))
       shutil.move(FieldsFile, os.path.join(os.path.split(Path)[0],FieldsFile))
       shutil.move(BaseCodeFile, os.path.join(os.path.split(Path)[0],BaseCodeFile))

       if(not os.path.exists(os.path.join(os.path.split(Path)[0],HeaderFile))):
           shutil.move(HeaderFile, os.path.join(os.path.split(Path)[0],HeaderFile))
       else:
          print(os.path.join(os.path.split(Path)[0],HeaderFile) + " already exists.")
          os.remove(HeaderFile)

       if(not os.path.exists(os.path.join(os.path.split(Path)[0],InlineFile))):
           shutil.move(InlineFile, os.path.join(os.path.split(Path)[0],InlineFile))
       else:
          print(os.path.join(os.path.split(Path)[0],InlineFile) + " already exists.")
          os.remove(InlineFile)

       if(not os.path.exists(os.path.join(os.path.split(Path)[0],CodeFile))):
           shutil.move(CodeFile, os.path.join(os.path.split(Path)[0],CodeFile))
       else:
          print(os.path.join(os.path.split(Path)[0],CodeFile) + " already exists.")
          os.remove(CodeFile)

   #Cleanup code with sed script
   print("Running Sed script to clean up generated code ...")

   if os.name == "posix":
       SedPath = "sed"
   elif os.name == "nt":
       SedPath = convertPathToOutput(os.path.join(GenFCsPyDir, "..\\External\\GnuWin32\\bin\\sed.exe"))

   SedScriptPath = convertPathToOutput(os.path.join(GenFCsPyDir, "CleanUpFC.sed"))

   os.system(convertPathToOutput(SedPath + " -f " + SedScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseHeaderFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseHeaderFile) + ".temp")))
   os.system(convertPathToOutput(SedPath + " -f " + SedScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],HeaderFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],HeaderFile) + ".temp")))
   os.system(convertPathToOutput(SedPath + " -f " + SedScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],FieldsFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],FieldsFile) + ".temp")))

   shutil.move(os.path.join(os.path.split(Path)[0],BaseHeaderFile) + ".temp", os.path.join(os.path.split(Path)[0],BaseHeaderFile))
   shutil.move(os.path.join(os.path.split(Path)[0],HeaderFile) + ".temp", os.path.join(os.path.split(Path)[0],HeaderFile))
   shutil.move(os.path.join(os.path.split(Path)[0],FieldsFile) + ".temp", os.path.join(os.path.split(Path)[0],FieldsFile))

   #Cleanup License

   #Determine which library this is for
   if os.path.join("Input", "src") in Path:
       SedLicenseScript = "CleanUpInputLicense.sed"
   elif os.path.join("ParticleSystem", "src") in Path:
       SedLicenseScript = "CleanUpParticleSystemLicense.sed"
   elif os.path.join("Toolbox", "src") in Path:
       SedLicenseScript = "CleanUpToolboxLicense.sed"
   elif os.path.join("Animation", "src") in Path:
       SedLicenseScript = "CleanUpAnimationLicense.sed"
   elif os.path.join("Game", "src") in Path:
       SedLicenseScript = "CleanUpGameLicense.sed"
   elif os.path.join("Sound", "src") in Path:
       SedLicenseScript = "CleanUpSoundLicense.sed"
   elif os.path.join("Physics", "src") in Path:
       SedLicenseScript = "CleanUpPhysicsLicense.sed"
   elif os.path.join("Metabolic", "src") in Path:
       SedLicenseScript = "CleanUpMetabolicLicense.sed"
   else:
       SedLicenseScript = "CleanUpUILicense.sed"
   SedLicenseScriptPath = convertPathToOutput(os.path.join(GenFCsPyDir, SedLicenseScript))

   os.system(convertPathToOutput(SedPath + " -f " + SedLicenseScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseHeaderFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseHeaderFile) + ".temp")))
   os.system(convertPathToOutput(SedPath + " -f " + SedLicenseScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseInlineFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseInlineFile) + ".temp")))
   os.system(convertPathToOutput(SedPath + " -f " + SedLicenseScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],FieldsFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],FieldsFile) + ".temp")))
   os.system(convertPathToOutput(SedPath + " -f " + SedLicenseScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseCodeFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],BaseCodeFile) + ".temp")))

   os.system(convertPathToOutput(SedPath + " -f " + SedLicenseScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],HeaderFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],HeaderFile) + ".temp")))
   os.system(convertPathToOutput(SedPath + " -f " + SedLicenseScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],InlineFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],InlineFile) + ".temp")))
   os.system(convertPathToOutput(SedPath + " -f " + SedLicenseScriptPath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],CodeFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],CodeFile) + ".temp")))

   shutil.move(os.path.join(os.path.split(Path)[0],BaseHeaderFile) + ".temp", os.path.join(os.path.split(Path)[0],BaseHeaderFile))
   shutil.move(os.path.join(os.path.split(Path)[0],BaseInlineFile) + ".temp", os.path.join(os.path.split(Path)[0],BaseInlineFile))
   shutil.move(os.path.join(os.path.split(Path)[0],FieldsFile) + ".temp", os.path.join(os.path.split(Path)[0],FieldsFile))
   shutil.move(os.path.join(os.path.split(Path)[0],BaseCodeFile) + ".temp", os.path.join(os.path.split(Path)[0],BaseCodeFile))

   shutil.move(os.path.join(os.path.split(Path)[0],HeaderFile) + ".temp", os.path.join(os.path.split(Path)[0],HeaderFile))
   shutil.move(os.path.join(os.path.split(Path)[0],InlineFile) + ".temp", os.path.join(os.path.split(Path)[0],InlineFile))
   shutil.move(os.path.join(os.path.split(Path)[0],CodeFile) + ".temp", os.path.join(os.path.split(Path)[0],CodeFile))

   #Add Header Includes
   #SedAddHeaderIncludePath = os.path.join(GenFCsPyDir, "AddHeaderInclude.sed")

   #os.system(SedPath + " -f " + SedAddHeaderIncludePath + " " + convertPathToOutput(os.path.join(os.path.split(Path)[0],HeaderFile)) + " > " + convertPathToOutput(os.path.join(os.path.split(Path)[0],HeaderFile) + ".temp"))

   #shutil.move(os.path.join(os.path.split(Path)[0],HeaderFile) + ".temp", os.path.join(os.path.split(Path)[0],HeaderFile))

def main():
   print("Operating System:", os.name)
   print("System Platform:", sys.platform)
   if len(sys.argv) < 2:
      print("Must specify a Field Container Description file(.fcd).")
      sys.exit(1)

   GenFCsPyDir = os.path.split(sys.argv[0])[0]
   if os.name == "posix":
      if sys.platform == "darwin":
          FcdCompilePath = os.path.join(GenFCsPyDir, "../External/fcdCompile/fcdCompile")
      else:
          FcdCompilePath = os.path.join(GenFCsPyDir, "../External/fcdCompile/fcdCompile")
   else:
       FcdCompilePath = convertPathToOutput(os.path.join(GenFCsPyDir, "..\\External\\fcdCompile\\Windows\\fcdCompile.exe")) 

   print("Using fcdCompile to Generate Code...")

   for i in range(1,len(sys.argv)):
       GenFCsFromFile(GenFCsPyDir, FcdCompilePath, sys.argv[i])

   print("Done")

main()

