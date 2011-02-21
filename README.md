OpenSGToolbox
=============

About
-----

This is a collection of libraries that add additional features to the OpenSG
library. To find out more go the the 
[OpenSGToolbox website](http://www.opensgtoolbox.org "OpenSGToolbox website"). 

Libraries:

* UserInterface
* FieldContainerEditor
* Lua
* ParticleSystem
* ParticleTrail
* Physics
* Sound
* TextDom
* Video
* Octree
* AStar

License
-------
[Lesser General Public License](http://www.gnu.org/licenses/lgpl-3.0-standalone.html "Lesser General Public License")

Screen shots
------------

Building
--------
1. Get the source code.
    * [OpenSGToolbox](http://github.com/djkabala/OpenSGToolbox "OpenSGToolbox")
    * [OpenSG](http://github.com/djkabala/OpenSGDevMaster_Toolbox "OpenSG")
    * [boost](http://www.boost.org/ "Boost")
    * [COLLADA](http://www.opencollada.org/download.html "COLLADA")
    * [ODE](http://www.ode.org/ "Open Dynamics Engine") **Optional** - Needed by ContribPhysics library
    * [Lua](http://www.lua.org/ "Lua") **Optional** - Needed by ContribLua, ContribLuaToolbox library
    * [Fmod](http://www.fmod.org/ "FMod") **Optional** - Needed by ContribSound library
    * [VLC](http://www.videolan.org/vlc/ "VLC") **Optional** - Needed by ContribVideo library
    * [Python](http://www.python.org/ "Python") **Optional** - Needed by FCDCompile
2. Get [cmake](http://www.cmake.org/ "cmake") for configuring the build system
3. Create a local directory for your local build
4. Run cmake in this directory
5. Build the binary using the build tool you selected with cmake
    * e.g. If you used the Makefile build tool: then run `make install` in the build
    directory
    * e.g. If you used the Visual Studio build tool: then open the Visual Studio
    project created by cmake.  Then build the "INSTALL" project.

Installation
------------
* Pre-built binaries

* From source
    1. Follow the previous Building instructions

Building Examples
-----------------

Authors
-------
David Kabala

Achyuthan Vasanth

Daniel Guilliams

Robert Goetz

Eric Langkamp

David Naylor

PJ Campbell

Alden Peterson

Jonathan Flory

Lee Zaniewski

Oyndamola (David) Oluwatimi

John Morales

Aaron Cronk

Reporting Errors
----------------
Ask a question on the OpenSGToolbox
[Google Group](http://groups.google.com/group/opensgtoolbox-users "Google Group").

If it is a bug, and is not already listed as one.  Then open a new Issue on the
[Issues page](https://github.com/djkabala/OpenSGToolbox/issues "Issues page") for GUIBuilder.

Contributing
------------

1. [Fork it](http://help.github.com/forking/ "Fork it")
2. Clone your forked repository (`git clone url/to/your/forked/repository`)
3. Create a branch (`git checkout -b cool_feature_x`)
4. Commit your changes (`git commit -am "Added Cool Feature X"`)
5. Push to the branch (`git push origin cool_feature_x`)
6. [Send a pull request](http://help.github.com/pull-requests/ "Send a pull request")
7. Enjoy a refreshing Mt. Dew and wait

