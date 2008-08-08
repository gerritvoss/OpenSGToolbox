// OpenSG Tutorial Example: Show an animated texture in hte background
//
// This example shows how to use the TextureBackground to show animated
// pictures behind the 3D graphics, and how to do it as efficiently as 
// possible
//
// Most video is not a power-of-two (POT) size, which makes it interesting.
// OpenSG handles most of that behind the scenes, but you have to set some
// options to make it efficient (see below).
//
// Based on 02move.cpp

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>

// new headers: 

// For the access to OpenGL extensions
#include <OpenSG/OSGGLEXT.h>

// For the image(s) to display
#include <OpenSG/OSGImage.h>

// For textures
#include <OpenSG/OSGTextureChunk.h>

// To put a texture into the background
#include <OpenSG/OSGTextureBackground.h>
#include <OpenSG/Video/OSGVideoManager.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr trans;

// The pointer to the dynamic image and the texture
ImagePtr        image;
TextureChunkPtr tex;

// Some helper flags for different code pathes

// flag to indicate whether the images are power-of-two (POT) in size or not
bool  isPOT = false;

// flag to indicate whether NPOT textures are available
// Purely informative, the code doesn't really care.
bool  hasNPOT = false;


// flag to indicate that only a small part of the image should be changed
// per frame. The random image generation can get slow for large
// images.
bool  changeOnlyPart = false;
VideoWrapperPtr TheVideo;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


// Grab/update the image
// This just update the image's data and tells the texture that it changed.
// For a video this would grab the next frame
void grabImage(ImagePtr img)
{

    ImagePtr TheImage = TheVideo->getCurrentFrame();

    if(TheImage != NullFC)
    {
        beginEditCP(tex, TextureChunk::ImageFieldMask);
            tex->setImage(TheImage);
        endEditCP(tex, TextureChunk::ImageFieldMask);
    }
    //ImageFileHandler::the().write(TheImage, "K:\\TestImage.jpg");

    /*beginEditCP(img, Image::PixelFieldMask);
    
    UInt8* data = img->getData();
    
    // for this example, just fill it with random junk    
    if(changeOnlyPart)
    {
        // Just change a small rectangular area
        UInt32 x = rand() % (img->getWidth() - 100);
        UInt32 y = rand() % (img->getHeight() - 100);
        UInt32 w = rand() % 100;
        UInt32 h = rand() % 100;
       
        UInt32 bpp = img->getBpp();
        UInt32 bpl = img->getWidth() * bpp;
        UInt32 bytes = w * bpp;
        
        data += y * bpl + x * bpp;
        
        UInt8 val = (rand() & 0x7f + 0x80);
        
        for(UInt32 i = h; i > 0; --i, data += bpl)
        {
            UInt8 *d = data;
            
            for(UInt32 j = bytes; j > 0; --j)
                *d++ = val;
        }
        
        // If only a part of the image changed, only that part needs to 
        // be updated. The speed of the update operation is pretty
        // directly dependent on the amount of data changed.
        tex->imageContentChanged(x, x + w, y, y + h);
    }
    else
    {       
        // Fill the whole picture
        for(UInt32 i = img->getHeight(); i > 0; --i)
        {
            UInt8 val = (rand() & 0x3f + 0x80);
            
            for(UInt32 j = img->getWidth() * img->getBpp(); j > 0; --j)
                *data++ = val;
        }
        
        // Everything changed
        tex->imageContentChanged();
    }
        
    endEditCP(img, Image::PixelFieldMask);*/
}


// redraw the window
void display( void )
{
    // update the geometry
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(Vec3f(      osgsin(t / 1000.f), 
                               osgcos(t / 1000.f), 
                               osgsin(t / 1000.f)),
                   Quaternion( Vec3f(0,1,0), 
                               t / 1000.f));

    beginEditCP(trans, Transform::MatrixFieldMask);
    {
        trans->setMatrix(m);
    }   
    endEditCP  (trans, Transform::MatrixFieldMask);
    
    // update the image
    grabImage(image);
    
    // redraw the screen
    mgr->redraw();
}

void update(void)
{
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    getDefaultVideoManager()->init(argc, argv);
    
    TheVideo = getDefaultVideoManager()->createVideoWrapper();
    
    if( TheVideo->open(Path("K:\\Test.avi")) )
    {
        TheVideo->play();
    }


    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene

    NodePtr torus = makeTorus( .5, 2, 16, 32 );
    NodePtr scene = Node::create();
    trans = Transform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(trans);
        scene->addChild(torus);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    
    // Create the parts needed for the video background
    
    UInt32 width = 640;
    UInt32 height = 480;
    
    // get the desired size from the command line
    if(argc >= 3)
    {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }    
    
    // To check OpenGL extensions, the Window needs to have run through
    // frameInit at least once. This automatically happens when rendering,
    // but we don't don't to wait for that here.
    gwin->activate();
    gwin->frameInit();
    
    // Now we can check for OpenGL extensions    
    hasNPOT = gwin->hasExtension("GL_ARB_texture_non_power_of_two");
   
    // Print what we've got
    SLOG << "Got " << (isPOT?"":"non-") << "power-of-two images and "
         << (hasNPOT?"can":"cannot") << " use NPOT textures, changing " 
         << (changeOnlyPart?"part":"all") 
         << " of the screen"
         << endLog;
    
    
    // Ok, now for the meat of the code...
    // first we need an Image to hold the picture(s) to show
    image = Image::create();
    
    beginEditCP(image);
    {
        // set the image's size and type, and allocate memory
        // this example uses RGB. On some systems (e.g. Windows) BGR
        // or BGRA might be faster, it depends on how the images are 
        // acquired
        image->set(Image::OSG_RGB_PF, width, height);
    }
    endEditCP(image);
    
    // Now create the texture to be used for the background
    tex = TextureChunk::create();
    
    beginEditCP(tex);
    {
        // Associate image and texture
        tex->setImage(image);
        
        // Set filtering modes. LINEAR is cheap and good if the image size
        // changes very little (i.e. the window is about the same size as 
        // the images).
        tex->setMinFilter(GL_LINEAR);
        tex->setMagFilter(GL_LINEAR);        
        
        // Set the wrapping modes. We don't need repetition, it might actually
        // introduce artifactes at the borders, so switch it off.
        tex->setWrapS(GL_CLAMP_TO_EDGE);
        tex->setWrapT(GL_CLAMP_TO_EDGE);             
        
        // Newer versions of OpenGl can handle NPOT textures directly.
        // OpenSG will do that internally automatically.
        //
        // Older versions need POT textures. By default OpenSG
        // will scale an NPOT texture to POT while defining it.
        // For changing textures that's too slow.
        // So tell OpenSG not to scale the image, but use the texture
        // matrix to scale. This only works if we're not using the
        // texture matrix for anything else, which is fine for video
        // backgrounds.
        // This does not do anything if NPOT textures are supported, so
        // it is safe to just set it.
        
        tex->setScale(false);            
        tex->setNPOTMatrixScale(true);
    }
    endEditCP(tex);
    
    // Create the background
    TextureBackgroundPtr back = TextureBackground::create();
    
    beginEditCP(back);
    {
        // Set the texture to use
        back->setTexture(tex);
    }
    endEditCP(back);
    

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->setStatistics(true);
    
    // replace the background
    // This has to be done after the viewport has been created, which the 
    // SSM does in setRoot().
    ViewportPtr vp = gwin->getPort()[0];
    
    beginEditCP(vp, Viewport::BackgroundFieldMask);
    {
        vp->setBackground(back);
    }
    endEditCP(vp, Viewport::BackgroundFieldMask);
    
    
    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    //DeInit
    getDefaultVideoManager()->exit();
    osgExit();

    return 0;
}

//
// GLUT callback functions
//

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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:  
        {
            OSG::osgExit();
            exit(0);
        }
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(update);

    return winid;
}



















/* OpenSG Tutorial Example: Creating a Button
//
// This tutorial explains how to edit the basic features of
// a button created in the OSG User Interface library.
// 
// Includes: button size, button font and text, button color, button border,
// and adding a button to a scene.


//Dynamics Distributions
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/Video/OSGVideoManager.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    //Init
    osgInit(argc, argv);
    getDefaultVideoManager()->init(argc, argv);
    
    VideoWrapperPtr TheVideo = getDefaultVideoManager()->createVideoWrapper();
    
    if( TheVideo->open(Path("K:\\Test.avi")) )
    {
        TheVideo->play();

        ImagePtr TheImage = TheVideo->getCurrentFrame();

        while(TheImage.getBaseCPtr() == NULL)
        {
            TheImage = TheVideo->getCurrentFrame();
        }
        ImageFileHandler::the().write(TheImage, "K:\\TestImage.jpg");

        TheVideo->stop();
        TheVideo->close();
    }

    //DeInit
    getDefaultVideoManager()->exit();
    osgExit();

    return 0;
}*/
