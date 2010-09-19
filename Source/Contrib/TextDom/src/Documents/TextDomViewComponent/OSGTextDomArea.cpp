/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
 *                                                                           *
\*------------------------- --------------------------------------------------*/
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

#include <cstdlib>
#include <cstdio>

#define OSG_COMPILECONTRIBTEXTDOMLIB

#include <OSGConfig.h>

#include "OSGTextFileHandler.h"
#include "OSGTextDomArea.h"
#include "OSGUIDrawingSurface.h"
#include "OSGUIDrawUtils.h"
#include "OSGWindowEventProducer.h"
#include "OSGInternalWindow.h"
#include "OSGLookAndFeelManager.h"
#include "OSGStringUtils.h"
#include "OSGScrollBar.h"
#include "OSGUIViewport.h"
#include "OSGSearchWindow.h"
#include "OSGAdvancedTextDomArea.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextDomAreaBase.cpp file.
// To modify it, please change the .fcd file (OSGTextDomArea.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextDomArea::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

EventConnection TextDomArea::addDocumentModelChangedListener(DocumentModelChangedListenerPtr Listener)
{
   _DocumentModelChangedListeners.insert(Listener);
   return EventConnection(
       boost::bind(&TextDomArea::isDocumentModelChangedListenerAttached, this, Listener),
       boost::bind(&TextDomArea::removeDocumentModelChangedListener, this, Listener));
   
}

bool TextDomArea::isDocumentModelChangedListenerAttached(DocumentModelChangedListenerPtr Listener) const
{
    return _DocumentModelChangedListeners.find(Listener) != _DocumentModelChangedListeners.end();
}

void TextDomArea::removeDocumentModelChangedListener(DocumentModelChangedListenerPtr Listener)
{
   DocumentModelChangedListenerSetItor EraseIter(_DocumentModelChangedListeners.find(Listener));
   if(EraseIter != _DocumentModelChangedListeners.end())
   {
      _DocumentModelChangedListeners.erase(EraseIter);
   }
}


void TextDomArea::produceDocumentModelChanged(const DocumentModelChangedEventP e)
{
	DocumentModelChangedListenerSet Listeners(_DocumentModelChangedListeners);
    for(DocumentModelChangedListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->changedUpdate(e);
    }
    _Producer.produceEvent(DocumentModelChangedMethodId,e);
}

void TextDomArea::loadFile(BoostPath pathOfFile)
{
	PlainDocumentRefPtr temp=dynamic_pointer_cast<PlainDocument>(TextFileHandler::the()->forceRead(pathOfFile));
	if(temp)
	{
		setDocumentModel(temp);
		handleDocumentModelChanged();
	}
}

void TextDomArea::saveFile(BoostPath pathOfFile)
{
	TextFileHandler::the()->forceWrite(getDocumentModel(),pathOfFile);
}
void TextDomArea::drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
	if(Manager)
	{
		drawHighlightBG(Graphics,Opacity);
		drawLineHighlight(Graphics,Opacity);
		drawBraceHighlight(Graphics,Opacity);
	}
	
	// ask manager to draw visible views
	
	if(Manager && Manager->getMFVisibleViews()->size()>0)	// draw the view by calling the view's draw function
	{
		
		for(UInt32 i=0;i<Manager->getMFVisibleViews()->size();i++)
		{
			Manager->getVisibleViews(i)->drawView(Graphics,Opacity);
		}
	}
	
	/*if(Manager)
	{
		Manager->drawGutter(Graphics,Opacity);
	}*/

	if(Manager && _CaretUpdateListener.DrawCaret())
		drawTheCaret(Graphics,Opacity);
}

void TextDomArea::drawHighlightBG(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
	if(Manager->getRootElement())
	{
		// draw the lines inbetweeen
		if(Manager->getHSL() != Manager->getHEL() ||  Manager->getHSI() != Manager->getHEI() )
		{
			if(Manager->isStartLocationBeforeEndLocation())
			{
				drawHighlightBGInternal(Graphics,Opacity,Manager->getHSL(),Manager->getHSI(),Manager->getHEL(),Manager->getHEI());
			}
			else
			{
				drawHighlightBGInternal(Graphics,Opacity,Manager->getHEL(),Manager->getHEI(),Manager->getHSL(),Manager->getHSI());
			}
		}
	}
}
void TextDomArea::drawHighlightBGInternal(const GraphicsWeakPtr Graphics, Real32 Opacity,UInt32 lesserLine,UInt32 lesserIndex,UInt32 greaterLine,UInt32 greaterIndex) const
{
	for(UInt32 i=lesserLine+1;i<greaterLine;i++)
	{
		PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(Manager->getRootElement()->getElement(i));
		
		if(theElement)
		{
			Pnt2f topLeft,bottomRight;
			getFont()->getBounds(theElement->getText(),topLeft,bottomRight);

			Graphics->drawRect(Pnt2f(Manager->getGutterSpace() + Manager->getGutterSeparation(),i*Manager->getHeightOfLine()),Pnt2f(Manager->getGutterSpace() + Manager->getGutterSeparation()+ bottomRight.x(),(i+1)*Manager->getHeightOfLine()),Color4f(0.7,0.7,0.95,1),Opacity);
		}
	}

	if(lesserLine== greaterLine)
	{
		Graphics->drawRect(Manager->getXYPosition(lesserLine,lesserIndex,true),Manager->getXYPosition(greaterLine,greaterIndex,false),Color4f(0.7,0.7,0.95,1),Opacity);
	}
	else
	{
		// draw the first line
		Graphics->drawRect(Manager->getXYPosition(lesserLine,lesserIndex,true),Manager->getEndXYPosition(lesserLine),Color4f(0.7,0.7,0.95,1),Opacity);

		// draw the last line
		Graphics->drawRect(Manager->getStartXYPosition(greaterLine),Manager->getXYPosition(greaterLine,greaterIndex,false),Color4f(0.7,0.7,0.95,1),Opacity);
	}

}


void TextDomArea::drawLineHighlight(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
	Graphics->drawRect(Pnt2f(0,Manager->getCaretYPosition()),Pnt2f(Manager->getPreferredWidth(),Manager->getCaretYPosition()+Manager->getHeightOfLine()),Color4f(0.7,0.7,0.7,0.5),Opacity);
}

void TextDomArea::drawBraceHighlight(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
	if(Manager->getBracesHighlightFlag())
	{
		if(Manager->getStartingBraceLine() != -1 && Manager->getStartingBraceIndex() != -1)
		{
			Pnt2f thePosition = Manager->getXYPosition(Manager->getStartingBraceLine(),Manager->getStartingBraceIndex(),true);
			Graphics->drawRect(thePosition,Pnt2f(thePosition.x()+5,thePosition.y()+Manager->getHeightOfLine()),Color4f(0.7,0.7,0.0,1.0),Opacity);
		}
		if(Manager->getEndingBraceLine() != -1 && Manager->getEndingBraceIndex() != -1)
		{
			if(Manager->getEndingBraceLine()<Manager->getRootElement()->getElementCount())
			{
				PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(Manager->getRootElement()->getElement(Manager->getEndingBraceLine()));
				if(Manager->getEndingBraceIndex() < temp->getTextLength())
				{
					Pnt2f thePosition = Manager->getXYPosition(Manager->getEndingBraceLine(),Manager->getEndingBraceIndex(),true);
					Graphics->drawRect(thePosition,Pnt2f(thePosition.x()+5,thePosition.y()+Manager->getHeightOfLine()),Color4f(0.7,0.7,0.0,1.0),Opacity);
				}
			}
		}
	}
}


void TextDomArea::drawTheCaret(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
	Graphics->drawRect(Pnt2f(Manager->getCaretXPosition(),Manager->getCaretYPosition()),Pnt2f(Manager->getCaretXPosition()+2,Manager->getCaretYPosition()+Manager->getHeightOfLine()),Color4f(0,0,0,1),Opacity);
}


TextDomArea::DocumentModifiedListener::DocumentModifiedListener(TextDomAreaRefPtr TheTextDomArea)
{
	_TextDomArea = TheTextDomArea;
}

void TextDomArea::DocumentModifiedListener::changedUpdate(const DocumentEventUnrecPtr e)
{
	_TextDomArea->changedUpdate(e);
}

void TextDomArea::DocumentModifiedListener::insertUpdate(const DocumentEventUnrecPtr e)
{
	_TextDomArea->insertUpdate(e);
}

void TextDomArea::DocumentModifiedListener::removeUpdate(const DocumentEventUnrecPtr e)
{
	_TextDomArea->removeUpdate(e);
}

void TextDomArea::changedUpdate(const DocumentEventUnrecPtr e)
{
	//std::cout<<"Detecting a change in the Document"<<std::endl;
	//Manager->populateCache();
	//Manager->updateViews();
}

void TextDomArea::insertUpdate(const DocumentEventUnrecPtr e)
{
	//std::cout<<"Detecting an insert	into the Document"<<std::endl;
	//Manager->populateCache();
	//Manager->updateViews();
}

void TextDomArea::removeUpdate(const DocumentEventUnrecPtr e)
{
	SWARNING << "Deleted an element"<<std::endl;
	Manager->updateViews();
	Manager->updateSize();
	updatePreferredSize();
	//std::cout<<"Detecting a remove in the Document"<<std::endl;
	//Manager->populateCache();
	//Manager->updateViews();
}

void TextDomArea::mouseDragged(const MouseEventUnrecPtr e)
{
   if(_IsMousePressed && e->getButton() == e->BUTTON1)
	{
		Manager->calculateCaretPosition(DrawingSurfaceToComponent(e->getLocation(), TextDomAreaRefPtr(this)) , true);	
	}
}

void TextDomArea::keyTyped(const KeyEventUnrecPtr e)
{
	TextWithProps temp;
	_CurrentCaretBlinkElps=0;
	_CaretUpdateListener.setDrawCaret(true);

	if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
	    if(this->getParentWindow() != NULL && this->getParentWindow()->getDrawingSurface()!=NULL&& this->getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
	    {
            disconnect();
        }
    }
	else if(e->getKey() == KeyEvent::KEY_UP)
    {
	    Manager->moveTheCaret(UP,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));
		Manager->printDebugInformation();
    }
	else if(e->getKey() == KeyEvent::KEY_DOWN)
    {
	    Manager->moveTheCaret(DOWN,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));
		Manager->printDebugInformation();
    }
	else if(e->getKey() == KeyEvent::KEY_LEFT)
    {
		Manager->moveTheCaret(LEFT,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));
		Manager->printDebugInformation();
    }
	else if(e->getKey() == KeyEvent::KEY_RIGHT)
    {
	    Manager->moveTheCaret(RIGHT,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));
		Manager->printDebugInformation();
    }
	else if(e->getKey() == KeyEvent::KEY_PAGE_UP)
    {
	    Manager->moveTheCaret(PAGEUP,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));
	}
	else if(e->getKey() == KeyEvent::KEY_PAGE_DOWN)
    {
	    Manager->moveTheCaret(PAGEDOWN,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));
	}
	else if(e->getKey() == KeyEvent::KEY_BACK_SPACE)
	{
		if(Manager->isSomethingSelected())
		{
			Manager->deleteSelected();
		}
		else
		{
			if(Manager->getCaretLine()!=0 || Manager->getCaretIndex()!=0)
			{
				/*if(Manager->getCaretIndex())
				{
					Manager->moveTheCaret(LEFT,false);
					getDocumentModel()->deleteCharacter(Manager->getCaretLine(),Manager->getCaretIndex());
				}
				else
				{*/
					Manager->moveTheCaret(LEFT,false,false);
					getDocumentModel()->deleteCharacter(Manager->getCaretLine(),Manager->getCaretIndex());
				//}
			}
		}
	}
	else if(e->getKey() == KeyEvent::KEY_DELETE)
	{
		if(Manager->isSomethingSelected())
		{
			Manager->deleteSelected();
		}
		else
		{
			if(!Manager->isLastCharacterOfDocument())
			{
				getDocumentModel()->deleteCharacter(Manager->getCaretLine(),Manager->getCaretIndex());
			} 
		}
	}
	else if(e->getKey() == KeyEvent::KEY_ENTER)
	{
		if(Manager->isSomethingSelected())
		{
			Manager->deleteSelected();
		}
		UInt32 numberOfLeadingSpaces = Manager->getNumberOfLeadingSpaces(Manager->getCaretLine());
		getDocumentModel()->insertCharacter(Manager->getCaretIndex(),Manager->getCaretLine(),'\r',temp);
		getDocumentModel()->insertCharacter(Manager->getCaretIndex()+1,Manager->getCaretLine(),'\n',temp);

		Int32 i,count;
		for(i = Manager->getCaretIndex()+2,count=0;count<numberOfLeadingSpaces;count++,i++)
			getDocumentModel()->insertCharacter(count,Manager->getCaretLine()+1,' ',temp);

		Manager->updateViews();
		Manager->updateSize();
		updatePreferredSize();

		Manager->moveTheCaret(HOMEOFNEXTLINE,false,false);



		for(count=0;count<numberOfLeadingSpaces;count++)
			Manager->moveTheCaret(RIGHT,false,false);

	}
	else if(e->getKey() == KeyEvent::KEY_HOME)
	{
		Manager->moveTheCaret(HOME,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));

	}
	else if(e->getKey() == KeyEvent::KEY_END)
	{
		Manager->moveTheCaret(END,(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT),(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL));

	}
	else if(e->getKey() == KeyEvent::KEY_TAB)
	{
			Manager->tabHandler(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT);
	}
	else
	{
		if(isPrintableChar(e->getKeyChar()) || e->getKey() == KeyEvent::KEY_SPACE)
		{
			if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
			{

				if(e->getKey() == KeyEvent::KEY_A)
					Manager->selectAll();

				if(e->getKey() == KeyEvent::KEY_C)
				{






					getParentWindow()->getDrawingSurface()->getEventProducer()->putClipboard("hellooo");
				}
				if(e->getKeyChar() == KeyEvent::KEY_V)
				{
					std::cout<<getParentWindow()->getDrawingSurface()->getEventProducer()->getClipboard();
				}
			}
			else
			{
				if(Manager->isSomethingSelected())Manager->deleteSelected();
				if(Manager->isStartingBraces(e->getKeyChar()))
				{
					Manager->removeBracesHighlightIndices();
					Manager->setStartingBraces(e->getKeyChar(),Manager->getCaretIndex(),Manager->getCaretLine());
				}
				else if(Manager->isEndingBraces(e->getKeyChar()))
				{
					Manager->removeBracesHighlightIndices();
					Manager->setEndingBraces(e->getKeyChar(),Manager->getCaretIndex(),Manager->getCaretLine());
				}
				getDocumentModel()->insertCharacter(Manager->getCaretIndex(),Manager->getCaretLine(),e->getKeyChar(),temp);
				Manager->moveTheCaret(RIGHT,false,false);
				Manager->DoIfLineLongerThanPreferredSize();
			}
		}
	}
}


void TextDomArea::setupCursor(void)
{
    UInt32 Cursor;
    if(getEnabled())
    {
        Cursor = WindowEventProducer::CURSOR_I_BEAM;
    }
    else
    {
        Cursor = WindowEventProducer::CURSOR_POINTER;
    }
    if(Cursor != getCursor())
    {
        setCursor(Cursor);
    }
}

Vec2f TextDomArea::getPreferredScrollableViewportSize(void)
{
	return Manager->getContentRequestedSize();
}

void TextDomArea::disconnect(void)
{
  /*  this->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
    this->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
    this->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);*/
}

void TextDomArea::focusGained(const FocusEventUnrecPtr e)
{
	if( getParentWindow() != NULL &&
		getParentWindow()->getDrawingSurface() != NULL &&
		getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
    {
		getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_CaretUpdateListener);
	}
	Inherited::focusGained(e);
}

void TextDomArea::focusLost(const FocusEventUnrecPtr e)
{
	if( getParentWindow() != NULL &&
		getParentWindow()->getDrawingSurface() != NULL &&
		getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
    {
        _CaretUpdateListener.disconnect();
	}
	Inherited::focusLost(e);
}
/*
UInt32 TextDomArea::numVisibleLines(void) const
{
	
    Pnt2f ClipTopLeft, ClipBottomRight;
	getClipBounds(ClipTopLeft, ClipBottomRight);
    
    Pnt2f TopLeft, BottomRight;
	getFont()->getBounds("A", TopLeft, BottomRight);

    return static_cast<Int32>(ClipBottomRight.y() - ClipTopLeft.y())/static_cast<Int32>(BottomRight.y() - TopLeft.y());
}
*/


void TextDomArea::mouseClicked(const MouseEventUnrecPtr e)
{

	Manager->calculateCaretPosition(DrawingSurfaceToComponent(e->getLocation(), TextDomAreaRefPtr(this)),false);

	//setCaretPosition(Position);

	if(e->getButton() == e->BUTTON1)
	{
		if(e->getClickCount() == 2)
		{
			Manager->doubleClickHandler();
		}
	}

	Inherited::mouseClicked(e);

}

void TextDomArea::mouseReleased(const MouseEventUnrecPtr e)
{
	_IsMousePressed = false;
	Inherited::mouseReleased(e);
}
void TextDomArea::mousePressed(const MouseEventUnrecPtr e)
{
	_IsMousePressed = true;
	if(e->getButton() == e->BUTTON1)
	{
		//set caret position to proper place
		Manager->calculateCaretPosition(DrawingSurfaceToComponent(e->getLocation(), TextDomAreaRefPtr(this)),false);
	}

	Inherited::mousePressed(e);
}


bool TextDomArea::CaretUpdateListener::DrawCaret(void) const
{
	return _DrawCaret;
}

void TextDomArea::CaretUpdateListener::setDrawCaret(bool val)
{
	_DrawCaret = val;
}


void TextDomArea::CaretUpdateListener::update(const UpdateEventUnrecPtr e)
{
   _TextDomArea->_CurrentCaretBlinkElps += e->getElapsedTime();
   if(_TextDomArea->_CurrentCaretBlinkElps > LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
   {
       Int32 Div = _TextDomArea->_CurrentCaretBlinkElps/LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
	   _TextDomArea->_CurrentCaretBlinkElps -= static_cast<OSG::Time>(Div)*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
	   _DrawCaret = !_DrawCaret;
   }
	
}

void TextDomArea::CaretUpdateListener::disconnect(void)
{
    _TextDomArea->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
}

void TextDomArea::createDefaultFont(void)
{
	_Font = UIFont::create();
    _Font->setFamily("SANS");
    _Font->setGap(3);
    _Font->setGlyphPixelSize(46);
    _Font->setSize(12);
    _Font->setTextureWidth(0);
    _Font->setStyle(TextFace::STYLE_PLAIN);
	
}

void TextDomArea::createDefaultLayer(void)
{
	tempBackground = ColorLayer::create();
    this->setBackgrounds(tempBackground);
    tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
}


void TextDomArea::updatePreferredSize(void)
{
	setPreferredSize(getRequestedSize());
	//setMinSize(Manager->getContentRequestedSize());
	///setMaxSize(Manager->getContentRequestedSize());
	produceDocumentModelChanged(NULL);
}

Int32 TextDomArea::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
/*    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    
    return direction * (VisibleRectBottomRight[MajorAxis] - VisibleRectTopLeft[MajorAxis]);
	*/
	return 1;
}
/*
bool TextDomArea::getScrollableTracksViewportHeight(void)
{
    return true;
}

bool TextDomArea::getScrollableTracksViewportWidth(void)
{
    return true;
}


bool TextDomArea::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool TextDomArea::getScrollableWidthMinTracksViewport(void)
{
    return true;
}
*/
Int32 TextDomArea::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
	return 15;
    /*if(getFont() != NULL)
    {
        UInt16 MajorAxis;
        if(orientation == ScrollBar::VERTICAL_ORIENTATION)
        {
            MajorAxis = 1;
        }
        else
        {
            MajorAxis = 0;
        }
        Pnt2f TopLeft, BottomRight;
		getFont()->getBounds("A", TopLeft, BottomRight);
        return BottomRight[MajorAxis] - TopLeft[MajorAxis] + getLineSpacing();
    }
    else
    {
        return Inherited::getScrollableUnitIncrement(VisibleRectTopLeft, VisibleRectBottomRight, orientation, direction);
    }
    */
}

Vec2f TextDomArea::getContentRequestedSize(void) const
{
	if(Manager)
	{
		return Manager->getContentRequestedSize();
	}
	else
	{
		return getSize();//getPreferredSize();
	}
}

void TextDomArea::handleDocumentModelChanged(void)
{
	setPosition(Pnt2f(0,0));
	SLOG<<"DocumentModel changed"<<std::endl;
	if(Manager == NULL)
	{
		Manager = FixedHeightLayoutManager::create();
		Manager->setTextDomArea(this);
		Manager->calculateLineHeight();
	}
	Manager->initializeRootElement();
	Manager->calculatePreferredSize();
	if(getDocumentModel())getDocumentModel()->addDocumentListener(&_DocumentModifiedListener);
	Manager->setHighlight(0,0,0,0);
	Manager->populateCache();
	updatePreferredSize();
	Manager->updateViews();
}


TextDomArea::CaretUpdateListener::CaretUpdateListener(TextDomAreaRefPtr TheTextDomArea):_DrawCaret(true)
{
	_TextDomArea=TheTextDomArea;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextDomArea::TextDomArea(void) :
	_DocumentModifiedListener(this),
	Manager(NULL),
	_CurrentCaretBlinkElps(0.0),
	_CaretUpdateListener(this),
	_Font(NULL),
    Inherited()
{
	createDefaultFont();
	createDefaultLayer();
	setupCursor();
}

TextDomArea::TextDomArea(const TextDomArea &source) :
	_DocumentModifiedListener(this),
	_CurrentCaretBlinkElps(0.0),
    _CaretUpdateListener(this),
	Inherited(source)
{
	Manager = source.Manager;
	_Font = source._Font;
	setupCursor();
}

TextDomArea::~TextDomArea(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextDomArea::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
	if(whichField & TextDomArea::DocumentModelFieldMask)
	{
		handleDocumentModelChanged();
	
	}
	else if(whichField & TextDomArea::ClipBoundsFieldMask)
	{
		//std::cout<<"CBC"<<std::endl;
		if(Manager)Manager->updateViews();
	}
	else if(whichField & TextDomArea::FontFieldMask)
	{
		if(Manager)
		{
			Manager->calculateLineHeight();
			Manager->populateCache();
			Manager->updateViews();
			updatePreferredSize();
		}
	}
}

void TextDomArea::dump(      UInt32,
                         const BitVector ) const
{
    SLOG << "Dump TextDomArea NI" << std::endl;

}

OSG_END_NAMESPACE
