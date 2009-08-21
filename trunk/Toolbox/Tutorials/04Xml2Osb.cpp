// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive scene viewer.
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGNode.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGGraphOpSeq.h>
#include <OpenSG/OSGVerifyGeoGraphOp.h>
#include <OpenSG/OSGStripeGraphOp.h>
#include <OpenSG/OSGMaterialMergeGraphOp.h>
#include <OpenSG/OSGSharePtrGraphOp.h>

#include <boost/filesystem/operations.hpp>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

NodePtr createScene(void);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: 04Xml2Osb.exe [Filename]" << std::endl;
        return -1;
    }

    Path FilePath(argv[1]);
    if(!boost::filesystem::exists(FilePath))
    {
        std::cout << "No file by name: "<< FilePath.string() << " exists." << std::endl;
        return -1;
    }

    // OSG init
    osgInit(argc,argv);
    
    NodePtr TheScene(NullFC);

    //Load the Scene
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(FilePath);

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {

        if( (*Itor)->getType() == Node::getClassType() &&
            Node::Ptr::dcast(*Itor)->getParent() == NullFC)
        {
            TheScene =  Node::Ptr::dcast(*Itor);
        }
    }

    //Check if the scene was loaded
    if(TheScene == NullFC)
    {
        std::cout << "Failed to load a scene from: "<< FilePath.string() << "." << std::endl;
        return -1;
    }

    //Run Graph optimizations
    GraphOpSeq *graphop = new GraphOpSeq;
    graphop->addGraphOp(new VerifyGeoGraphOp);
    graphop->addGraphOp(new StripeGraphOp);
    //graphop->addGraphOp(new MaterialMergeGraphOp);
    //graphop->addGraphOp(new SharePtrGraphOp);

    if(graphop != NULL)
    {
        graphop->run(TheScene);
    }



    //Export the Scene to an osb file

    std::string ExportFileName(FilePath.string().substr(0,FilePath.string().size()-3) + "osb");
    
    SceneFileHandler::the().write(TheScene, ExportFileName.c_str());
    
	// OSG exit
    osgExit();

    return 0;
}

