# trivial makefile for OpenSG tutorials

# use debug or opt libs?
LIBTYPE ?= dbg
OSGUSERINTERFACEROOT ?= ../../Builds/Linux

ifeq ($(LIBTYPE),dbg)
	DGB_OPT_EXT := D
endif

# program dependencies

default:	toolbox input animation sound dynamics particlesystem userinterface game


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

#ParticleSystem
particlesystem-dbg:
	   gmake -C ../ParticleSystem/Builds/Linux/dbg -j6 install

particlesystem-opt:
	   gmake -C ../ParticleSystem/Builds/Linux/opt -j6 install

particlesystem: particlesystem-dbg particlesystem-opt

particlesystem-clean-dbg:
	   gmake -C ../ParticleSystem/Builds/Linux/dbg clean

particlesystem-clean-opt:
	   gmake -C ../ParticleSystem/Builds/Linux/opt clean

particlesystem-clean: particlesystem-clean-dbg particlesystem-clean-opt

#Dynamics
dynamics-dbg:
	   gmake -C ../Dynamics/Builds/Linux/dbg -j6 install

dynamics-opt:
	   gmake -C ../Dynamics/Builds/Linux/opt -j6 install

dynamics: dynamics-dbg dynamics-opt

dynamics-clean-dbg:
	   gmake -C ../Dynamics/Builds/Linux/dbg clean

dynamics-clean-opt:
	   gmake -C ../Dynamics/Builds/Linux/opt clean

dynamics-clean: dynamics-clean-dbg dynamics-clean-opt

#Sound
sound-dbg:
	   gmake -C ../Sound/Builds/Linux/dbg -j6 install

sound-opt:
	   gmake -C ../Sound/Builds/Linux/opt -j6 install

sound: sound-dbg sound-opt

sound-clean-dbg:
	   gmake -C ../Sound/Builds/Linux/dbg clean

sound-clean-opt:
	   gmake -C ../Sound/Builds/Linux/opt clean

sound-clean: sound-clean-dbg sound-clean-opt

#Game
game-dbg:
	   gmake -C ../Game/Builds/Linux/dbg -j6 install

game-opt:
	   gmake -C ../Game/Builds/Linux/opt -j6 install

game: game-dbg game-opt

game-clean-dbg:
	   gmake -C ../Game/Builds/Linux/dbg clean

game-clean-opt:
	   gmake -C ../Game/Builds/Linux/opt clean

game-clean: game-clean-dbg game-clean-opt

clean: toolbox-clean input-clean animation-clean sound-clean dynamics-clean particlesystem-clean userinterface-clean game-clean
