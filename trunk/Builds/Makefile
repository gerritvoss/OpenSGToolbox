# trivial makefile for OpenSG tutorials

# use debug or opt libs?
LIBTYPE ?= dbg
OSGUSERINTERFACEROOT ?= ../../Builds/Linux

ifeq ($(LIBTYPE),dbg)
	DGB_OPT_EXT := D
endif

# program dependencies

default:	toolbox input animation userinterface


# make rules

.PHONY: clean toolbox toolbox-opt toolbox-dbg toolbox-clean toolbox-clean-dbg toolbox-clean-opt  input input-opt input-dbg input-clean input-clean-dbg input-clean-opt userinterface userinterface-opt userinterface-dbg userinterface-clean userinterface-clean-dbg userinterface-clean-opt
       
#Toolbox 
toolbox-dbg:
	gmake -C ../Toolbox/Builds/Linux/dbg -j6 install
        
toolbox-opt:
	gmake -C ../Toolbox/Builds/Linux/opt -j6 install
        
toolbox: toolbox-dbg toolbox-opt

toolbox-clean-dbg:
	gmake -C ../Toolbox/Builds/Linux/dbg clean
        
toolbox-clean-opt:
	gmake -C ../Toolbox/Builds/Linux/opt clean
        
toolbox-clean: toolbox-clean-dbg toolbox-clean-opt
  
#Input 
input-dbg:
	gmake -C ../Input/Builds/Linux/dbg -j6 install
        
input-opt:
	gmake -C ../Input/Builds/Linux/opt -j6 install
        
input: input-dbg input-opt

input-clean-dbg:
	gmake -C ../Input/Builds/Linux/dbg clean
        
input-clean-opt:
	gmake -C ../Input/Builds/Linux/opt clean
        
input-clean: input-clean-dbg input-clean-opt

#UserInterface 
userinterface-dbg:
	gmake -C ../UserInterface/Builds/Linux/dbg -j6 install
        
userinterface-opt:
	gmake -C ../UserInterface/Builds/Linux/opt -j6 install
        
userinterface: userinterface-dbg userinterface-opt

userinterface-clean-dbg:
	gmake -C ../UserInterface/Builds/Linux/dbg clean
        
userinterface-clean-opt:
	gmake -C ../UserInterface/Builds/Linux/opt clean
        
userinterface-clean: userinterface-clean-dbg userinterface-clean-opt

#Animation
animation-dbg:
	   gmake -C ../Animation/Builds/Linux/dbg -j6 install

animation-opt:
	   gmake -C ../Animation/Builds/Linux/opt -j6 install

animation: animation-dbg animation-opt

animation-clean-dbg:
	   gmake -C ../Animation/Builds/Linux/dbg clean

animation-clean-opt:
	   gmake -C ../Animation/Builds/Linux/opt clean

animation-clean: animation-clean-dbg animation-clean-opt
clean: toolbox-clean input-clean userinterface-clean animation-clean
