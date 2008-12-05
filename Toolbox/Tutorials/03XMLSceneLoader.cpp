// OpenSG Tutorial Example: Loading
//
// This example shows how to load a scene file using OpenSG.
// The supported formats right now are VRML97, OBJ, OFF and RAW, so just
// calling this program with a scene file as a parameter should load the scene
// file.
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>

#include <OpenSG/OSGStatElemDesc.h>
#include <OpenSG/OSGStatIntElem.h>

// New Headers

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/Toolbox/OSGFCFileHandler.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


// helper class to find a named node
// names are handled as simple attachments, get the header for that
#include <OpenSG/OSGSimpleAttachments.h>

void printAllStatDescs(void);
NodePtr Load(std::string FilePath);
NodePtr LoadXML(std::string FilePath);
bool isFileXML(std::string FilePath);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    printAllStatDescs();

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // load the scene

    NodePtr scene;
    
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
        
        std::list<const char*> suffixes;
        SceneFileHandler::the().getSuffixList(suffixes);
        
        for(std::list<const char*>::iterator it  = suffixes.begin();
                                             it != suffixes.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        std::vector<std::string> suffixesVec;
        suffixesVec = FCFileHandler::the()->getSuffixList();
        
        for(std::vector<std::string>::iterator it  = suffixesVec.begin();
                                             it != suffixesVec.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        scene = makeTorus(.5, 2, 16, 16);
        glutSetWindowTitle("No file Loaded");
    }
    else
    {
        glutSetWindowTitle(argv[1]);
        scene = Load(std::string(argv[1]));
    }

    //Create Statistics Foreground
    SimpleStatisticsForegroundPtr TheStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(TheStatForeground);
        TheStatForeground->setSize(25);
        TheStatForeground->setColor(Color4f(0,1,0,0.7));
        TheStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        TheStatForeground->addElement(DrawActionBase::statTravTime, "TravTime: %.3f s");
        TheStatForeground->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
        TheStatForeground->addElement(DrawActionBase::statCullTestedNodes, 
                           "%d Nodes culltested");
        TheStatForeground->addElement(DrawActionBase::statCulledNodes, 
                           "%d Nodes culled");
        TheStatForeground->addElement(RenderAction::statNMaterials, 
                           "%d material changes");
        TheStatForeground->addElement(RenderAction::statNMatrices, 
                           "%d matrix changes");
        TheStatForeground->addElement(RenderAction::statNGeometries, 
                           "%d Nodes drawn");
        TheStatForeground->addElement(RenderAction::statNTransGeometries, 
                           "%d transparent Nodes drawn");
        TheStatForeground->addElement(Drawable::statNTriangles, 
                           "%d triangles drawn");
        TheStatForeground->addElement(Drawable::statNLines, 
                           "%d lines drawn");
        TheStatForeground->addElement(Drawable::statNPoints, 
                           "%d points drawn");
        TheStatForeground->addElement(Drawable::statNPrimitives,
                            "%d primitive groups drawn");
        TheStatForeground->addElement(Drawable::statNVertices, 
                           "%d vertices transformed");
        TheStatForeground->addElement(Drawable::statNGeoBytes, "%d bytes of geometry used");
        TheStatForeground->addElement(RenderAction::statNTextures, "%d textures used");
        TheStatForeground->addElement(RenderAction::statNTexBytes, "%d bytes of texture used");
    endEditCP(TheStatForeground);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->turnHeadlightOff();

    beginEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
        mgr->getWindow()->getPort(0)->getForegrounds().push_back(TheStatForeground);
    endEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
    StatCollector *collector = &TheStatForeground->getCollector();
    
    // add optional elements
    collector->getElem(Drawable::statNTriangles);
    
    mgr->getAction()->setStatistics(collector);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    mgr->idle();
    mgr->redraw();
}

void update(void)
{
    glutPostRedisplay();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{

    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{

    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:    
        {
            OSG::osgExit();
            exit(0);
        }
        break;
        
        case 'f': 
        {  
            mgr->setNavigationMode(Navigator::FLY);
        }
        break;
        
        case 't':   
        {
            mgr->setNavigationMode(Navigator::TRACKBALL);
        }
        break;

        case 'h':
            if(mgr->getHeadlightState())
            {
                mgr->turnHeadlightOff();
            }
            else
            {
                mgr->turnHeadlightOn();
            }
            break;
    }
}

NodePtr Load(std::string FilePath)
{
    /*
        All scene file loading is handled via the SceneFileHandler.
    */
    NodePtr LoadedScene;

    Time start = getSystemTime();
    
    if(isFileXML(FilePath))
    {
        LoadedScene = LoadXML(FilePath);
    }
    else
    {
        LoadedScene = SceneFileHandler::the().read(FilePath.c_str());
    }
    
    Time end = getSystemTime();

    std::cerr << "Took " << end-start << " to load" << std::endl;

    return LoadedScene;
}

NodePtr LoadXML(std::string FilePath)
{
    std::cout << "Loading xml File: " << FilePath << std::endl;

	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path(FilePath));

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {

        if( (*Itor)->getType() == Node::getClassType() &&
            Node::Ptr::dcast(*Itor)->getParent() == NullFC)
        {
            return Node::Ptr::dcast(*Itor);
        }
    }

    return NullFC;
}

bool isFileXML(std::string FilePath)
{
    std::string::size_type LastDotPos = FilePath.find_last_of(".");
    ++LastDotPos;
    std::string Extension(FilePath.substr(LastDotPos, FilePath.length() - LastDotPos));

    return Extension.compare("xml") == 0;
}

void printAllStatDescs(void)
{
    UInt32 NumOfStatDescs(StatElemDesc<StatIntElem>::getNumOfDescs());
    std::cout << "Number of StatIntElem Stat Descriptions: "<< NumOfStatDescs << std::endl;

    for(UInt32 i(0) ; i<NumOfStatDescs ; ++i)
    {
        std::cout << i << " : " << StatElemDesc<StatIntElem>::getDesc(i)->getName() << std::endl;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1280,1024);
    glutInitWindowPosition(100,100);
    int winid = glutCreateWindow("OpenSG Loader");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
