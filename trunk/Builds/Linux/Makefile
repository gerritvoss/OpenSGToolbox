LIBTYPE ?= dbg

#dbg:
#	LIBTYPE := dbg
#opt:
#	LIBTYPE := opt

build:
	gmake -C ../../Toolbox/Builds/Linux/$(LIBTYPE) build -j4
#	gmake -C ../../Animation/Builds/Linux/$(LIBTYPE) build
	gmake -C ../../Input/Builds/Linux/$(LIBTYPE) build -j4
	gmake -C ../../UserInterface/Builds/Linux/$(LIBTYPE) build -j4


install:
	gmake -C ../../Toolbox/Builds/Linux/$(LIBTYPE) install -j4
#	gmake -C ../../Animation/Builds/Linux/$(LIBTYPE) install
	gmake -C ../../Input/Builds/Linux/$(LIBTYPE) install -j4
	gmake -C ../../UserInterface/Builds/Linux/$(LIBTYPE) install -j4

default: install
	echo default

clean:
	gmake -C ../../Toolbox/Builds/Linux/$(LIBTYPE) clean
#	gmake -C ../../Animation/Builds/Linux/$(LIBTYPE) clean
	gmake -C ../../Input/Builds/Linux/$(LIBTYPE) clean
	gmake -C ../../UserInterface/Builds/Linux/$(LIBTYPE) clean

