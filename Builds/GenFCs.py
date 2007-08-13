import os
import sys
import glob
import shutil


def main():
   if len(sys.argv) != 2:
      print "Must specify a Field Container Description file(.fcd)."
      sys.exit(1)
      
   GenFCsPyDir = os.path.split(sys.argv[0])[0]
   if os.name == "posix":
      FcdCompilePath = os.path.join(GenFCsPyDir, "../External/fcdCompile/Linux/fcdCompile")
   elif os.name == "nt":
      FcdCompilePath = os.path.join(GenFCsPyDir, "../External/fcdCompile/Windows/fcdCompile.exe")
      
   print "Using fcdCompile to Generate Code..."
   
   os.system(FcdCompilePath + " -b -f " + sys.argv[1])
   
   BaseHeaderFile = "OSG" + os.path.splitext(os.path.split(sys.argv[1])[1])[0] + "Base.h"
   BaseInlineFile = "OSG" + os.path.splitext(os.path.split(sys.argv[1])[1])[0] + "Base.inl"
   FieldsFile = "OSG" + os.path.splitext(os.path.split(sys.argv[1])[1])[0] + "Fields.h"
   BaseCodeFile = "OSG" + os.path.splitext(os.path.split(sys.argv[1])[1])[0] + "Base.cpp"
   
   HeaderFile = "OSG" + os.path.splitext(os.path.split(sys.argv[1])[1])[0] + ".h"
   InlineFile = "OSG" + os.path.splitext(os.path.split(sys.argv[1])[1])[0] + ".inl"
   CodeFile = "OSG" + os.path.splitext(os.path.split(sys.argv[1])[1])[0] + ".cpp"
   
   shutil.move(BaseHeaderFile, os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile))
   shutil.move(BaseInlineFile, os.path.join(os.path.split(sys.argv[1])[0],BaseInlineFile))
   shutil.move(FieldsFile, os.path.join(os.path.split(sys.argv[1])[0],FieldsFile))
   shutil.move(BaseCodeFile, os.path.join(os.path.split(sys.argv[1])[0],BaseCodeFile))
   
   if(not os.path.exists(os.path.join(os.path.split(sys.argv[1])[0],HeaderFile))):
      shutil.move(HeaderFile, os.path.join(os.path.split(sys.argv[1])[0],HeaderFile))
   else:
      print os.path.join(os.path.split(sys.argv[1])[0],HeaderFile) + " already exists."
      os.remove(HeaderFile)
      
   if(not os.path.exists(os.path.join(os.path.split(sys.argv[1])[0],InlineFile))):
      shutil.move(InlineFile, os.path.join(os.path.split(sys.argv[1])[0],InlineFile))
   else:
      print os.path.join(os.path.split(sys.argv[1])[0],InlineFile) + " already exists."
      os.remove(InlineFile)
      
   if(not os.path.exists(os.path.join(os.path.split(sys.argv[1])[0],CodeFile))):
      shutil.move(CodeFile, os.path.join(os.path.split(sys.argv[1])[0],CodeFile))
   else:
      print os.path.join(os.path.split(sys.argv[1])[0],CodeFile) + " already exists."
      os.remove(CodeFile)
      
   #Cleanup code with sed script
   print "Running Sed script to clean up generated code ..."
   
   if os.name == "posix":
      SedPath = "sed"
   elif os.name == "nt":
      SedPath = os.path.join(GenFCsPyDir, "../External/GnuWin32/bin/sed.exe")
      
   SedScriptPath = os.path.join(GenFCsPyDir, "CleanUpFC.sed")
   
   os.system(SedPath + " -f " + SedScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile) + ".temp")
   os.system(SedPath + " -f " + SedScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],HeaderFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],HeaderFile) + ".temp")
   os.system(SedPath + " -f " + SedScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],FieldsFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],FieldsFile) + ".temp")
   
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile))
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],HeaderFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],HeaderFile))
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],FieldsFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],FieldsFile))
   
   #Cleanup License
   SedLicenseScriptPath = os.path.join(GenFCsPyDir, "CleanUpUILicense.sed")
   
   os.system(SedPath + " -f " + SedLicenseScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile) + ".temp")
   os.system(SedPath + " -f " + SedLicenseScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],BaseInlineFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],BaseInlineFile) + ".temp")
   os.system(SedPath + " -f " + SedLicenseScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],FieldsFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],FieldsFile) + ".temp")
   os.system(SedPath + " -f " + SedLicenseScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],BaseCodeFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],BaseCodeFile) + ".temp")
   
   os.system(SedPath + " -f " + SedLicenseScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],HeaderFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],HeaderFile) + ".temp")
   os.system(SedPath + " -f " + SedLicenseScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],InlineFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],InlineFile) + ".temp")
   os.system(SedPath + " -f " + SedLicenseScriptPath + " " + os.path.join(os.path.split(sys.argv[1])[0],CodeFile) + " > " + os.path.join(os.path.split(sys.argv[1])[0],CodeFile) + ".temp")
   
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],BaseHeaderFile))
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],BaseInlineFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],BaseInlineFile))
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],FieldsFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],FieldsFile))
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],BaseCodeFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],BaseCodeFile))
   
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],HeaderFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],HeaderFile))
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],InlineFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],InlineFile))
   shutil.move(os.path.join(os.path.split(sys.argv[1])[0],CodeFile) + ".temp", os.path.join(os.path.split(sys.argv[1])[0],CodeFile))
   
   print "Done"

main()
