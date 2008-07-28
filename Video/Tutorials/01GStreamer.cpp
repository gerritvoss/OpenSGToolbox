// OpenSG Tutorial Example: Creating a Button
//
// This tutorial explains how to edit the basic features of
// a button created in the OSG User Interface library.
// 
// Includes: button size, button font and text, button color, button border,
// and adding a button to a scene.


//Dynamics Distributions
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/Video/OSGGStreamerManager.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    //Init
    osgInit(argc, argv);
    GStreamerManager::the()->init(argc, argv);
    
    GStreamerManager::the()->doSomething();

    //DeInit
    GStreamerManager::the()->exit();
    osgExit();

    return 0;
}
