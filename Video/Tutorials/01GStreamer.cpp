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
#include <OpenSG/Video/OSGDirectShowManager.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    //Init
    osgInit(argc, argv);
    DirectShowManager::the()->init(argc, argv);
    
	DirectShowManager::the()->openVideo(std::string("C:\\Test.avi"));
    //DirectShowManager::the()->openVideo(std::string("C:\\Documents and Settings\\David\\My Documents\\Work\\OpenSGToolbox\\Video\\Tutorials\\Test.ogg"));

    //DeInit
    DirectShowManager::the()->exit();
    osgExit();

    return 0;
}
