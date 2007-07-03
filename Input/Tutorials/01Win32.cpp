#include <OpenSG/OSGConfig.h>

// just compile this under Windows
#ifdef WIN32

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <OpenSG/OSGGL.h>

#include <iostream>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSFSysTypes.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGBoxVolume.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGDirectionalLight.h>

#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGWIN32Window.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGSolidBackground.h>

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "RAW/OSGRAWSceneFileType.h"
#endif

#include <OpenSG/OSGTrackball.h>

using namespace osg;


HWND           hwnd;

WIN32WindowPtr win;
//WIN32WindowPtr win;

DrawAction     *ract;
NodePtr            root;
NodePtr            file;
PerspectiveCameraPtr cam;
ViewportPtr    vp;
TransformPtr   cam_trans;
Trackball      tball;

int            lastx,
               lasty,
               mouseb;

double  basetime;
#define dpr std::cout << getSystemTime()-basetime << ":" << Thread::getAspect() << ":"


void display ( void )
{
    Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
    m1.mult( m2 );
    cam_trans->getSFMatrix()->setValue( m1 );

    glClearColor( 0.f, 0.f, 1.0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    win->draw( ract );
}


LRESULT CALLBACK WndProc(HWND hwnd2, UINT uMsg,
                         WPARAM wParam, LPARAM lParam)
{
    int  eventThread = 0, x, y;

    PIXELFORMATDESCRIPTOR   pfd;    
    HDC           hDC;

    int iPixelFormat;

    switch(uMsg)
    {       
        case WM_LBUTTONDOWN:
            mouseb |= 1 << 1;
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;
        case WM_MBUTTONDOWN:
            tball.setAutoPosition(true);
            mouseb |= 1 << 2;
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;
        case WM_RBUTTONDOWN:
            tball.setAutoPositionNeg(true);     
            mouseb |= 1 << 3;
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;   
        case WM_LBUTTONUP:
            mouseb &= ~(1 << 1);
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;              
        case WM_MBUTTONUP:
            tball.setAutoPositionNeg(false); 
            mouseb &= ~(1 << 2);
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;
        case WM_RBUTTONUP:
            tball.setAutoPositionNeg(false); 
            mouseb &= ~(1 << 3);
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;

        case WM_MOUSEMOVE:
            {
            Real32 w,h,a,b,c,d;
            
            x = (int)LOWORD(lParam);
            y = (int)HIWORD(lParam);
            w = win->getWidth();
            h = win->getHeight();
    
            a = -2.f * ( lastx / w - .5f );
            b = -2.f * ( .5f - lasty / h );
            c = -2.f * ( x / w - .5f );
            d = -2.f * ( .5f - y / h );
                    
            if ( mouseb & ( 1 << 1 ) )
            {
                dpr << "Left button dragged" << std::endl;
                tball.updateRotation( a, b, c, d );
                display();
            }
            else if ( mouseb & ( 1 << 2 ) )
            {
                dpr << "Middle button dragged" << std::endl;
                tball.updatePosition( a, b, c, d );
                display();
            }
            else if ( mouseb & ( 1 << 3 ) )
            {
                dpr << "Right button dragged" << std::endl;
                tball.updatePositionNeg( a, b, c, d );
                display();
            }
            }
            lastx = x;
            lasty = y;
            break;
                                    
        case WM_KEYDOWN:
            dpr << "Key pressed: " << wParam << std::endl;
            if ( (int)wParam == VK_ESCAPE )
            {
                exit(0);
            }
            break;
                                    
        case WM_SIZE:
            dpr << "Resize: " << wParam << " " << LOWORD(lParam)
                << " " << HIWORD( lParam ) << std::endl;
			//std::cout << "Resize: " << wParam << " " << LOWORD(lParam)
            //    << " " << HIWORD( lParam ) << std::endl;
            if ( win != NullFC)
                win->resize( LOWORD(lParam), HIWORD( lParam ) );
            break;
                                    
        case WM_PAINT:
            if ( win != NullFC)
                display();
            break;

        case WM_CREATE:
            dpr << "Create " << std::endl;

            memset(&pfd, 0, sizeof(pfd));
            pfd.nSize = sizeof(pfd);
            pfd.nVersion = 1;
            pfd.dwFlags = 
                PFD_DRAW_TO_WINDOW | 
                PFD_SUPPORT_OPENGL | 
                PFD_DOUBLEBUFFER;
            pfd.iPixelType = PFD_TYPE_RGBA;
            pfd.iLayerType = PFD_MAIN_PLANE;
            pfd.cDepthBits = 16;            



            // init the OSG window  
            hDC = GetDC(hwnd2);

            iPixelFormat = ChoosePixelFormat(hDC, &pfd);
            SetPixelFormat(hDC, iPixelFormat, &pfd);    
            
            beginEditCP(win);
               win->setHwnd ( hwnd2 );
               //win->setHdc ( hDC ); // This is done in the init() function of WindowWIN32
               //win->setHglrc (  ); // This is done in the init() function of WindowWIN32
            endEditCP(win);
            
            win->init();
            win->deactivate();
            break;

        case WM_CLOSE:
            return DefWindowProc(hwnd2,uMsg,wParam,lParam);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd2, uMsg, wParam, lParam);
    }
    return 0;
}

int main (int argc, char **argv)
{   
    WNDCLASS  wndClass;
    MSG           msg;

    // OSG init

    osgInit(argc,argv);
    basetime = getSystemTime();

    SceneFileHandler::the().print();

    // create the graph

    // beacon for camera and light  
    NodePtr b1n = Node::create();
    GroupPtr b1 = Group::create();
    beginEditCP(b1n);
    b1n->setCore( b1 );
    endEditCP(b1n);

    // transformation
    NodePtr t1n = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1n);
    t1n->setCore( t1 );
    t1n->addChild( b1n );
    endEditCP(t1n);

    cam_trans = t1;

    // light
    
    NodePtr dlight = Node::create();
    DirectionalLightPtr dl = DirectionalLight::create();
    
    beginEditCP(dlight);
    dlight->setCore( dl );
    endEditCP(dlight);
    
    beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);
    endEditCP(dl);

    // root
    root = Node::create();
    GroupPtr gr1 = Group::create();
    beginEditCP(root);
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );
    endEditCP(root);
    
        // Load the file

    NodePtr file = NullFC;
    
    if ( argc > 1 )
        file = SceneFileHandler::the().read(argv[1]);
    
    if ( file == NullFC )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = makeTorus( .5, 2, 16, 16 );
    }
    
    file->updateVolume();

    Vec3f min,max;
    file->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    beginEditCP(dlight);
    dlight->addChild( file );
    endEditCP(dlight);

    std::cerr << "Tree: " << std::endl;
    root->dump();

    // Camera
    PerspectiveCameraPtr cam = PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( deg2rad( 60 ) );
    cam->setNear( 0.1 );
    cam->setFar( 10000 );
    
    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();
    
    // Action
    
    ract = DrawAction::create();

    // tball

    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5f );

    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );
 
    // Win32 Init

    memset(&wndClass, 0, sizeof(wndClass));
    wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = GetModuleHandle(NULL);
    // doesn't compile?!? wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpszClassName = "testWindowWIN32";
    if (!RegisterClass(&wndClass)) 
    {
        return FALSE;
    }

    
    // Create Windows

    win = WIN32Window::create();
    
    // Create a Window
    hwnd = CreateWindow( "testWindowWIN32", "testWindowWIN32",
                    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                    CW_USEDEFAULT, 
                    0, 
                    CW_USEDEFAULT, 
                    0,
                    NULL, 
                    NULL, 
                    GetModuleHandle(NULL), 
                    0 );

    ShowWindow( hwnd, SW_SHOWNORMAL );
    SetActiveWindow( hwnd );
    

    // Viewport
    ViewportPtr vp = Viewport::create();
    beginEditCP(vp);
      vp->setCamera( cam );
      vp->setBackground( bkgnd );
      vp->setRoot( root );
      vp->setSize( 0,0, 1,1 );
    endEditCP(vp);
    beginEditCP(win);
      win->addPort( vp );
    endEditCP(win);


    // main loop 
    while ( GetMessage(&msg, NULL, 0, 0) )
        DispatchMessage(&msg);
    
    return (0);
}

// just compile this under Windows
#endif
