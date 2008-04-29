# trivial makefile for OpenSG tutorials

# use debug or opt libs?
LIBTYPE ?= dbg
OSGUSERINTERFACEROOT ?= ../../Builds/Linux

ifeq ($(LIBTYPE),dbg)
	DGB_OPT_EXT := D
endif

# set the path to the installed osg-config executable here
# if you don't set it, the makefile tries to guess
# e.g. if you installed in /usr/local:
# OSGCONFIG := /usr/local/bin/osg-config


# *****************************************************
# you shouldn't have to change anything after this line
# *****************************************************

# try to guess the OSGCONFIG path

OSGCONFIG := notset

# use OSGPOOL if set

OSGPOOL ?= ..

# try to get configured information first, will not work if more
# than one system is configured from one dir. Just for the 1.0

OSGINSTALLPREFIX := notset

PREFIXSUFFIX := $(shell $(OSGPOOL)/CommonConf/config.guess)
-include .prefix.$(PREFIXSUFFIX)

ifneq ($(OSGINSTALLPREFIX),notset)
    OSGCONFIG := $(OSGINSTALLPREFIX)/bin/osg-config
endif

ifneq ($(OSGROOT),)
	OSGCONF := $(wildcard $(OSGROOT)/bin/osg-config)

    ifneq ($(OSGCONF),)
		OSGCONFIG := $(OSGCONF)
	endif

endif

# if configure info wasn't found, maybe a Builds/* install?
ifeq ($(OSGCONFIG),notset)
    INSTALLROOT := $(wildcard ../Builds/$(shell ../CommonConf/config.guess)-*)
    OSGCONF := $(wildcard $(INSTALLROOT)/bin/osg-config)
    ifneq ($(OSGCONF),)
        OSGCONFIG := $(OSGCONF)
    endif
endif

# maybe we can find it in the path?
ifeq ($(OSGCONFIG),notset)
    OSGCONF := \
       $(shell if which osg-config >/dev/null 2>&1; then which osg-config; fi )  
    OSGCONF := $(strip $(OSGCONF))
    ifneq ($(OSGCONF),)
        OSGCONFIG := $(OSGCONF)
    endif
endif

# ok, give up
ifeq ($(OSGCONFIG),notset)
    $(error Can't find osg-config, please configure the Makefile or \
            add it to your PATH)
endif

### System dependencies ###############################################

# Set the system we're running on
SYSTEM := $(shell uname)

# which extension to be used for executables
EXEEXT :=

# which extension to be used for executables
ADDLIB :=

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

ifeq ($(SYSTEM),IRIX)
        CCOUT  := -o 
        LDOUT  := -o 
	LINK   := 
	ADDLIB := X
endif
ifeq ($(SYSTEM),IRIX64)
        CCOUT  := -o 
        LDOUT  := -o 
	LINK   := 
	ADDLIB := X
endif
ifeq ($(SYSTEM),Linux)
        CCOUT  := -o 
        LDOUT  := -o 
	LINK   := 
	ADDLIB := X
endif
ifeq ($(findstring WIN,$(SYSTEM)),WIN)
        OS := WIN32
        CCOUT := -Fo
        LDOUT := /out:
	LINK   := -link
	EXEEXT :=.exe
endif
ifeq ($(SYSTEM),HP-UX)
        CCOUT  := -o 
        LDOUT  := -o 
	LINK   := 
	ADDLIB := X
endif
ifeq ($(SYSTEM),Darwin)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif

# Var settings

ifeq ($(findstring WIN,$(SYSTEM)),WIN)
CC = "$(shell $(OSGCONFIG) --compiler)"
else
CC = $(shell $(OSGCONFIG) --compiler) 
endif

CCFLAGS = $(shell $(OSGCONFIG) --cflags --$(LIBTYPE) Base System $(ADDLIB) GLUT) -I$(OSGUSERINTERFACEROOT)/include -I../../External/Boost

LDFLAGS = $(LINK) $(shell $(OSGCONFIG) --libs --$(LIBTYPE) Base System $(ADDLIB) GLUT) -L$(OSGUSERINTERFACEROOT)/lib -lOSGUserInterface$(DGB_OPT_EXT) -lOSGInput$(DGB_OPT_EXT) -lOSGToolbox$(DGB_OPT_EXT) -lboost_filesystem


# all tutorials in this directory

TUTS :=  $(wildcard [0-9][0-9]*.cpp) 
PROGS := $(TUTS:.cpp=$(EXEEXT)) 

ifeq ($(findstring WIN,$(SYSTEM)),WIN)
TUTS := $(filter-out %X.cpp, $(TUTS))
endif

# program dependencies

default:	$(PROGS)

# make rules

.PHONY: clean Clean

clean:
	rm -f  *.o 
	rm -f  *.obj 
	rm -rf ii_files
	rm -f *.pdb
	rm -f *.ilk
	rm -f *.idb
	rm -f $(PROGS)

Clean: clean
	rm -f $(PROGS) 

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) $(LDOUT)$@ $< $(LDFLAGS)

%$(EXEEXT): %.cpp
	$(CC) $(CCFLAGS) $< $(LDFLAGS) $(LDOUT)$@ 
