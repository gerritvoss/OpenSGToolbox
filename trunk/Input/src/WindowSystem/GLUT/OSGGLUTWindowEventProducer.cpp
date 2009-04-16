/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGGLUTWindowEventProducer.h"

#ifdef OSG_WITH_GLUT

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGGLUT.h>

#include "WindowSystem/OSGWindowEventProducerFactory.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GLUTWindowEventProducer
GLUTWindowEventProducer Class.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

GLUTWindowEventProducer::GLUTWindowToProducerMap GLUTWindowEventProducer::_GLUTWindowToProducerMap;
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GLUTWindowEventProducer::WindowEventLoopThread(void* args)
{
    WindowEventLoopThreadArguments* Arguments(static_cast<WindowEventLoopThreadArguments*>(args));
    Arguments->_SyncBarrier->addRef();

    int argc(1);
    char **argv = new char*[1];
    (*argv)= "Bla";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    Int32 winid = glutCreateWindow(Arguments->_WindowName.c_str());
    glutPositionWindow(Arguments->_ScreenPosition.x(), Arguments->_ScreenPosition.y());
    glutReshapeWindow(Arguments->_Size.x(), Arguments->_Size.y());

    GLUTWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->setId(winid);
    Arguments->_EventProducer->attachWindow();

    Arguments->_EventProducer->getWindow()->init();

    //Set the current window to this one
    glutSetWindow(GLUTWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->getId());

    Arguments->_SyncBarrier->enter(2);
    Arguments->_SyncBarrier->subRef();

    // GLUT main loop
    glutMainLoop();
    
    //Send the Closed event
    Arguments->_EventProducer->produceWindowClosed();
    
    //Delete my arguments, to avoid memory leak
    delete Arguments;
}

void GLUTWindowEventProducer::draw(void)
{
    glutSetWindow(GLUTWindow::Ptr::dcast(getWindow())->getId());
    glutPostRedisplay();
}

void GLUTWindowEventProducer::update(void)
{
   //Updating
   Time Now(getSystemTime());
   Time ElapsedTime(Now - getLastUpdateTime());
   if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
   {
	   produceUpdate(ElapsedTime);
   }
   beginEditCP(GLUTWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
	   setLastUpdateTime(Now);
   endEditCP(GLUTWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
}

WindowPtr GLUTWindowEventProducer::createWindow(void)
{
    return GLUTWindow::create();
}

void GLUTWindowEventProducer::openWindow(const Pnt2f& ScreenPosition,
                    const Vec2f& Size,
                    const std::string& WindowName)
{
    if(_WindowEventLoopThread == NULL)
    {
        std::string ThreadName = WindowName + " Event Loop";
        _WindowEventLoopThread = dynamic_cast<Thread *>(ThreadManager::the()->getThread(ThreadName.c_str()));
    }
    else
    {
    }

    Barrier* syncBarrier = Barrier::get(NULL);
    syncBarrier->addRef();
    WindowEventLoopThreadArguments* Arguments = new WindowEventLoopThreadArguments( 
                    ScreenPosition,
                    Size,
                    WindowName,
                    GLUTWindow::Ptr::dcast(getWindow()),
                    GLUTWindowEventProducerPtr(this),
                    syncBarrier);
    
    //ChangeList::setReadWriteDefault();
    _WindowEventLoopThread->runFunction(WindowEventLoopThread, 0, Arguments);
    
    //Wait for glut to be fully initialized in the seperate thread
    syncBarrier->enter(2);
    syncBarrier->subRef();
}

void GLUTWindowEventProducer::closeWindow(void)
{
    if(getWindow() != NullFC)
    {
        glutDestroyWindow(GLUTWindow::Ptr::dcast(getWindow())->getId());
    }
}

void GLUTWindowEventProducer::GLUTWindowEventProducerDisplayFunction(void)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutDisplay();
}

void GLUTWindowEventProducer::GLUTWindowEventProducerReshapeFunction(int width,int height)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutReshape(Vec2f(width,height));
}

void GLUTWindowEventProducer::GLUTWindowEventProducerOverlayDisplayFunction(void)
{
   _GLUTWindowToProducerMap[glutGetWindow()];
}

void GLUTWindowEventProducer::GLUTWindowEventProducerKeyboardFunction(unsigned char key, int x,int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutKeyboard(key,Pnt2f(x,y));
}

void GLUTWindowEventProducer::GLUTWindowEventProducerKeyboardUpFunction(unsigned char key, int x,int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutKeyboardUp(key,Pnt2f(x,y));
}

void GLUTWindowEventProducer::GLUTWindowEventProducerMouseFunction(int button, int state, int x, int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutMouse(button,state,Pnt2f(x,y));
}

void GLUTWindowEventProducer::GLUTWindowEventProducerMotionFunction(int x, int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutMotion(Pnt2f(x,y));
}

void GLUTWindowEventProducer::GLUTWindowEventProducerPassiveMotionFunction(int x, int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutPassiveMotion(Pnt2f(x,y));
}

void GLUTWindowEventProducer::GLUTWindowEventProducerVisibilityFunction(int state)
{
   _GLUTWindowToProducerMap[glutGetWindow()];
}

void GLUTWindowEventProducer::GLUTWindowEventProducerEntryFunction(int state)
{
	_GLUTWindowToProducerMap[glutGetWindow()]->glutEntry(state);
}

void GLUTWindowEventProducer::GLUTWindowEventProducerSpecialFunction(int key, int x, int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutSpecial(key,Pnt2f(x,y));
}
void GLUTWindowEventProducer::GLUTWindowEventProducerSpecialUpFunction(int key, int x, int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutSpecialUp(key,Pnt2f(x,y));
}

void GLUTWindowEventProducer::GLUTWindowEventProducerIdleFunction(void)
{
   _GLUTWindowToProducerMap[glutGetWindow()]->glutIdle();
}

void GLUTWindowEventProducer::GLUTWindowEventProducerMenuStatusFunction(int status, int x, int y)
{
   _GLUTWindowToProducerMap[glutGetWindow()];
}

void GLUTWindowEventProducer::initMethod (void)
{
	//Register this WindowEventProducer As the GLUTWindow WindowEventProducer with the factory
	WindowEventProducerFactory::the()->registerProducer(&GLUTWindow::getClassType(), &GLUTWindowEventProducer::getClassType());
}

std::string GLUTWindowEventProducer::getClipboard(void) const
{
	//TODO:Implement
	return std::string("");
}

void GLUTWindowEventProducer::putClipboard(const std::string Value)
{
	//TODO:Implement
}

void GLUTWindowEventProducer::setCursor(void)
{
	//TODO:Implement
}

Pnt2f GLUTWindowEventProducer::getMousePosition(void) const
{
	//TODO:Implement
	return Pnt2f(0,0);
}

KeyEvent::KeyState GLUTWindowEventProducer::getKeyState(KeyEvent::Key TheKey) const
{
	//TODO:Implement
	return KeyEvent::KEY_STATE_UP;
}

Path GLUTWindowEventProducer::saveFileDialog(const std::string& DialogTitle,
                const std::vector<FileDialogFilter>& Filters,
                const Path& InitialFile,
                const Path& InitialDirectory,
                bool PromptForOverwrite
                )
{
    Path Result;
    return Result;
}

std::vector<Path> GLUTWindowEventProducer::openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const Path& InitialDir,
		bool AllowMultiSelect)
{
	//TODO: Implement
	std::vector<Path> Result;
	return Result;
}

Vec2f GLUTWindowEventProducer::getDesktopSize(void) const
{
	//TODO:Implement
    return Vec2f(0,0);
}

void GLUTWindowEventProducer::glutIdle(void)
{
   //Updating
   /*Time Now(getSystemTime());
   Time ElapsedTime(Now - getLastUpdateTime());
   if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
   {
	   produceUpdate(ElapsedTime);
   }
   beginEditCP(GLUTWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
	   setLastUpdateTime(Now);
   endEditCP(GLUTWindowEventProducerPtr(this), LastUpdateTimeFieldMask);*/
}

void GLUTWindowEventProducer::glutMouse(Int32 Button, Int32 State, Pnt2f MousePos)
{
   MouseEvent::MouseButton OSGButton;
   switch(Button)
   {
   case  GLUT_LEFT_BUTTON:
      OSGButton = MouseEvent::BUTTON1;
      break;
   case  GLUT_MIDDLE_BUTTON:
      OSGButton = MouseEvent::BUTTON2;
      break;
   case   GLUT_RIGHT_BUTTON:
      OSGButton = MouseEvent::BUTTON3;
      break;
   default:
      break;
   }

   switch(State)
   {
   case GLUT_UP:
      produceMouseReleased(OSGButton, MousePos);
      //produceMouseClicked(OSGButton, MousePos);
      break;
   case GLUT_DOWN:
      produceMousePressed(OSGButton, MousePos);
      break;
   default:
      break;
   }
}

UInt32 GLUTWindowEventProducer::getKeyModifiers(void) const
{
	//TODO:Implement
	return 0;
}
KeyEvent::Key GLUTWindowEventProducer::determineSpecialKey(UChar8 key)
{
   KeyEvent::Key OSGKey;
   switch(key)
   {
   case GLUT_KEY_F1:
      OSGKey = KeyEvent::KEY_F1;
      break;
   case GLUT_KEY_F2:
      OSGKey = KeyEvent::KEY_F2;
      break;
   case GLUT_KEY_F3:
      OSGKey = KeyEvent::KEY_F3;
      break;
   case GLUT_KEY_F4:
      OSGKey = KeyEvent::KEY_F4;
      break;
   case GLUT_KEY_F5:
      OSGKey = KeyEvent::KEY_F5;
      break;
   case GLUT_KEY_F6:
      OSGKey = KeyEvent::KEY_F6;
      break;
   case GLUT_KEY_F7:
      OSGKey = KeyEvent::KEY_F7;
      break;
   case GLUT_KEY_F8:
      OSGKey = KeyEvent::KEY_F8;
      break;
   case GLUT_KEY_F9:
      OSGKey = KeyEvent::KEY_F9;
      break;
   case GLUT_KEY_F10:
      OSGKey = KeyEvent::KEY_F10;
      break;
   case GLUT_KEY_F11:
      OSGKey = KeyEvent::KEY_F11;
      break;
   case GLUT_KEY_F12:
      OSGKey = KeyEvent::KEY_F12;
      
   case GLUT_KEY_LEFT:
      OSGKey = KeyEvent::KEY_LEFT;
      break;
   case GLUT_KEY_RIGHT:
      OSGKey = KeyEvent::KEY_RIGHT;
      break;
   case GLUT_KEY_UP:
      OSGKey = KeyEvent::KEY_UP;
      break;
   case GLUT_KEY_DOWN:
      OSGKey = KeyEvent::KEY_DOWN;
      break;
      
   case GLUT_KEY_PAGE_UP:
      OSGKey = KeyEvent::KEY_PAGE_UP;
      break;
   case GLUT_KEY_PAGE_DOWN:
      OSGKey = KeyEvent::KEY_PAGE_DOWN;
      break;
   case GLUT_KEY_HOME:
      OSGKey = KeyEvent::KEY_HOME;
      break;
   case GLUT_KEY_END:
      OSGKey = KeyEvent::KEY_END;
      break;
   case GLUT_KEY_INSERT:
      OSGKey = KeyEvent::KEY_INSERT;
      break;
   default:
      OSGKey = KeyEvent::KEY_UNKNOWN;
      break;
   }
   return OSGKey;
}

KeyEvent::Key GLUTWindowEventProducer::determineKey(UChar8 key)
{
   KeyEvent::Key OSGKey;
   switch(key)
   {
   //Alphabet
   case 'a':
   case 'A':
      OSGKey = KeyEvent::KEY_A;
      break;
   case 'b':
   case 'B':
      OSGKey = KeyEvent::KEY_B;
      break;
   case 'c':
   case 'C':
      OSGKey = KeyEvent::KEY_C;
      break;
   case 'd':
   case 'D':
      OSGKey = KeyEvent::KEY_D;
      break;
   case 'e':
   case 'E':
      OSGKey = KeyEvent::KEY_E;
      break;
   case 'f':
   case 'F':
      OSGKey = KeyEvent::KEY_F;
      break;
   case 'g':
   case 'G':
      OSGKey = KeyEvent::KEY_G;
      break;
   case 'h':
   case 'H':
      OSGKey = KeyEvent::KEY_H;
      break;
   case 'i':
   case 'I':
      OSGKey = KeyEvent::KEY_I;
      break;
   case 'j':
   case 'J':
      OSGKey = KeyEvent::KEY_J;
      break;
   case 'k':
   case 'K':
      OSGKey = KeyEvent::KEY_K;
      break;
   case 'l':
   case 'L':
      OSGKey = KeyEvent::KEY_L;
      break;
   case 'm':
   case 'M':
      OSGKey = KeyEvent::KEY_M;
      break;
   case 'n':
   case 'N':
      OSGKey = KeyEvent::KEY_N;
      break;
   case 'o':
   case 'O':
      OSGKey = KeyEvent::KEY_O;
      break;
   case 'p':
   case 'P':
      OSGKey = KeyEvent::KEY_P;
      break;
   case 'q':
   case 'Q':
      OSGKey = KeyEvent::KEY_Q;
      break;
   case 'r':
   case 'R':
      OSGKey = KeyEvent::KEY_R;
      break;
   case 's':
   case 'S':
      OSGKey = KeyEvent::KEY_S;
      break;
   case 't':
   case 'T':
      OSGKey = KeyEvent::KEY_T;
      break;
   case 'u':
   case 'U':
      OSGKey = KeyEvent::KEY_U;
      break;
   case 'v':
   case 'V':
      OSGKey = KeyEvent::KEY_V;
      break;
   case 'w':
   case 'W':
      OSGKey = KeyEvent::KEY_W;
      break;
   case 'x':
   case 'X':
      OSGKey = KeyEvent::KEY_X;
      break;
   case 'y':
   case 'Y':
      OSGKey = KeyEvent::KEY_Y;
      break;
   case 'z':
   case 'Z':
      OSGKey = KeyEvent::KEY_Z;
      break;
   //Numbers
   case '0':
      OSGKey = KeyEvent::KEY_0;
      break;
   case '1':
      OSGKey = KeyEvent::KEY_1;
      break;
   case '2':
      OSGKey = KeyEvent::KEY_2;
      break;
   case '3':
      OSGKey = KeyEvent::KEY_3;
      break;
   case '4':
      OSGKey = KeyEvent::KEY_4;
      break;
   case '5':
      OSGKey = KeyEvent::KEY_5;
      break;
   case '6':
      OSGKey = KeyEvent::KEY_6;
      break;
   case '7':
      OSGKey = KeyEvent::KEY_7;
      break;
   case '8':
      OSGKey = KeyEvent::KEY_8;
      break;
   case '9':
      OSGKey = KeyEvent::KEY_9;
      break;

   //Other
   case '!':
      OSGKey = KeyEvent::KEY_EXCLAMATION_MARK;
      break;
   case '@':
      OSGKey = KeyEvent::KEY_AT;
      break;
   case '#':
      OSGKey = KeyEvent::KEY_NUMBER_SIGN;
      break;
   case '$':
      OSGKey = KeyEvent::KEY_DOLLAR;
      break;
   case '%':
      OSGKey = KeyEvent::KEY_PERCENT;
      break;
   case '^':
      OSGKey = KeyEvent::KEY_CIRCUMFLEX;
      break;
   case '&':
      OSGKey = KeyEvent::KEY_AMPERSAND;
      break;
   case '*':
      OSGKey = KeyEvent::KEY_ASTERISK;
      break;
   case '(':
      OSGKey = KeyEvent::KEY_LEFT_PARENTHESIS;
      break;
   case ')':
      OSGKey = KeyEvent::KEY_RIGHT_PARENTHESIS;
      break;
   case '-':
      OSGKey = KeyEvent::KEY_MINUS;
      break;
   case '=':
      OSGKey = KeyEvent::KEY_EQUALS;
      break;
   case '_':
      OSGKey = KeyEvent::KEY_UNDERSCORE;
      break;
   case '+':
      OSGKey = KeyEvent::KEY_PLUS;
      break;
   case '~':
      OSGKey = KeyEvent::KEY_TILDE;
      break;
   case '`':
      OSGKey = KeyEvent::KEY_BACK_QUOTE;
      break;
   case '   ':
      OSGKey = KeyEvent::KEY_TAB;
      break;
   case ' ':
      OSGKey = KeyEvent::KEY_SPACE;
      break;
   case '[':
      OSGKey = KeyEvent::KEY_OPEN_BRACKET;
      break;
   case ']':
      OSGKey = KeyEvent::KEY_CLOSE_BRACKET;
      break;
   case '\\':
      OSGKey = KeyEvent::KEY_BACK_SLASH;
      break;
   case ';':
      OSGKey = KeyEvent::KEY_SEMICOLON;
      break;
   case '\'':
      OSGKey = KeyEvent::KEY_APOSTROPHE;
      break;
   case ',':
      OSGKey = KeyEvent::KEY_COMMA;
      break;
   case '.':
      OSGKey = KeyEvent::KEY_PERIOD;
      break;
   case '/':
      OSGKey = KeyEvent::KEY_SLASH;
      break;
   case '{':
      OSGKey = KeyEvent::KEY_BRACE_LEFT;
      break;
   case '}':
      OSGKey = KeyEvent::KEY_BRACE_RIGHT;
      break;
   case '|':
      OSGKey = KeyEvent::KEY_PIPE;
      break;
   case ':':
      OSGKey = KeyEvent::KEY_COLON;
      break;
   case '"':
      OSGKey = KeyEvent::KEY_QUOTE;
      break;
   case '<':
      OSGKey = KeyEvent::KEY_LESS;
      break;
   case '>':
      OSGKey = KeyEvent::KEY_GREATER;
      break;
   case '?':
      OSGKey = KeyEvent::KEY_QUESTION_MARK;
      break;

   //Backspace
   case 8:
      OSGKey = KeyEvent::KEY_BACK_SPACE;
      break;
   //Backspace
   case 9:
      OSGKey = KeyEvent::KEY_TAB;
      break;
   //Enter
   case 13:
      OSGKey = KeyEvent::KEY_ENTER;
      break;
   //Escape
   case 27:
      OSGKey = KeyEvent::KEY_ESCAPE;
      break;
   //Delete
   case 127:
      OSGKey = KeyEvent::KEY_DELETE;
      break;
   default:
      OSGKey = KeyEvent::KEY_UNKNOWN;
      break;
   }
   return OSGKey;
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

//Set the Window Position
void GLUTWindowEventProducer::setPosition(Pnt2f Pos)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //Position the Window
   glutPositionWindow(Pos.x(), Pos.y());
}

//Set the Window Position
Pnt2f GLUTWindowEventProducer::getPosition(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //Return the Window's position
   return Pnt2f(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y));
}

//Set the Window size
void GLUTWindowEventProducer::setSize(Vec2us Size)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //Resize the Window
   glutReshapeWindow(Size.x(), Size.y());

   //Resize the OpenGL Viewports
   getWindow()->resize(Size.x(), Size.y());
}

//Get the Window size
Vec2f GLUTWindowEventProducer::getSize(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //Return the Window's Size
   return Vec2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

//Focused
//Set the Window Focus
void GLUTWindowEventProducer::setFocused(bool Focused)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::setFocused(bool Focused): GLUT Does not define a function for setting its focus." << std::endl;
   
}

//Get the Window Focus
bool GLUTWindowEventProducer::getFocused(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getFocused(void): GLUT Does not define a query for Focus." << std::endl;
   
   return false;
}

//Visible / Iconify / Normal
//Set the Window Visible
void GLUTWindowEventProducer::setVisible(bool Visible)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   if(Visible)
   {
      glutShowWindow();
   }
   else
   {
      glutHideWindow();
   }
}

//Get the Window Visible
bool GLUTWindowEventProducer::getVisible(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getVisible(void): GLUT Does not define a query for Visibility." << std::endl;
   
   return false;
}

//Set the Window Iconify
void GLUTWindowEventProducer::setIconify(bool Iconify)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   if(Iconify)
   {
      glutIconifyWindow();
   }
   else
   {
      glutShowWindow();
   }
}

//Get the Window Iconify
bool GLUTWindowEventProducer::getIconify(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getIconify(void): GLUT Does not define a query for Iconify." << std::endl;
   
   return false;
}

//Fullscreen
void GLUTWindowEventProducer::setFullscreen(bool Fullscreen)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   if(Fullscreen)
   {
      glutFullScreen();
   }
   else
   {
      //Reset Position and Size to Initial
      setPosition(Pnt2f(glutGet( GLUT_INIT_WINDOW_X),glutGet( GLUT_INIT_WINDOW_Y)));
      setSize(Vec2us(glutGet( GLUT_INIT_WINDOW_WIDTH),glutGet( GLUT_INIT_WINDOW_HEIGHT)));
   }
}

//Get the Window Fullscreen
bool GLUTWindowEventProducer::getFullscreen(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getFullscreen(void): GLUT Does not define a query for Fullscreen." << std::endl;
   
   return false;
}

void GLUTWindowEventProducer::setTitle(const std::string& TitleText)
{
    //Set the correct GLUT Window
    glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

    //Set the window Title
    glutSetWindowTitle(TitleText.c_str());
}

std::string GLUTWindowEventProducer::getTitle(void)
{
    //TODO:Implement
    return std::string("");
}

void GLUTWindowEventProducer::setRisizable(bool IsResizable)
{
    //TODO:Implement
}

bool GLUTWindowEventProducer::getRisizable(void)
{
    //TODO:Implement
    return true;
}

void GLUTWindowEventProducer::setDrawBorder(bool DrawBorder)
{
    //TODO:Implement
}

bool GLUTWindowEventProducer::getDrawBorder(void)
{
    //TODO:Implement
    return true;
}

bool GLUTWindowEventProducer::attachWindow(void)
{
    if(_GLUTWindowToProducerMap.find(GLUTWindow::Ptr::dcast(getWindow())->getId()) != _GLUTWindowToProducerMap.end())
    {
        return false;
    }

    _GLUTWindowToProducerMap[GLUTWindow::Ptr::dcast(getWindow())->getId()] = GLUTWindowEventProducerPtr(this);

    //Set the correct GLUT Window
    glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

    glutDisplayFunc(GLUTWindowEventProducerDisplayFunction);
    glutReshapeFunc(GLUTWindowEventProducerReshapeFunction);

    //Set the Input Callback Functions
    glutKeyboardFunc(GLUTWindowEventProducerKeyboardFunction);
    glutKeyboardUpFunc(GLUTWindowEventProducerKeyboardUpFunction);
    glutSpecialFunc(GLUTWindowEventProducerSpecialFunction);
    glutSpecialUpFunc(GLUTWindowEventProducerSpecialUpFunction);
    glutMouseFunc(GLUTWindowEventProducerMouseFunction);
    glutMotionFunc(GLUTWindowEventProducerMotionFunction);
    glutPassiveMotionFunc(GLUTWindowEventProducerPassiveMotionFunction);
    glutEntryFunc(GLUTWindowEventProducerEntryFunction);

    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GLUTWindowEventProducer::GLUTWindowEventProducer(void) :
    Inherited()
{
}

GLUTWindowEventProducer::GLUTWindowEventProducer(const GLUTWindowEventProducer &source) :
    Inherited(source)
{
}

GLUTWindowEventProducer::~GLUTWindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

GLUTWindowEventProducer::WindowEventLoopThreadArguments::WindowEventLoopThreadArguments(
                       const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName,
                       GLUTWindowPtr TheWindow,
                       GLUTWindowEventProducerPtr TheEventProducer,
                       Barrier *syncBarrier) :
        _ScreenPosition(ScreenPosition),
        _Size(Size),
        _WindowName(WindowName),
        _Window(TheWindow),
        _EventProducer(TheEventProducer),
        _SyncBarrier(syncBarrier)
{
}

void GLUTWindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GLUTWindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GLUTWindowEventProducer NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGGLUTWINDOWEVENTPRODUCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGLUTWINDOWEVENTPRODUCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGLUTWINDOWEVENTPRODUCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

#endif

