#!/bin/sh

WebsiteDirectory="/home/users/dkabala/public_html/OpenSGToolbox"

#Move the Source
mv OpenSGToolbox-source*.tar.gz $WebsiteDirectory/downloads/daily_builds/trunk/

#Move the Doxygen Documentation
mv OpenSGToolbox-doxygen-doc* $WebsiteDirectory/downloads/daily_builds/trunk/

#Move the Linux Builds
mv OpenSGToolbox-rhe5-64bit* $WebsiteDirectory/downloads/daily_builds/trunk/
