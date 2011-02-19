/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
 *          David Kabala (djkabala@gmail.com)                                *
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
#include "OSGGlyphView.h"
#include "OSGColorLayer.h"
#include "OSGPlainDocumentLeafElement.h"
#include "OSGFixedHeightLayoutManager.h"
#include "OSGInsertCharacterCommand.h"
#include "OSGDeleteSelectedCommand.h"
#include "OSGDeleteCharacterCommand.h"
#include "OSGSetTextCommand.h"
#include "OSGInsertStringCommand.h"
#include "OSGPlainDocument.h"
#include "OSGTextDomUtils.h"
#include <boost/xpressive/xpressive.hpp>
#include "cctype" 


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

void TextDomArea::loadFile(const BoostPath& pathOfFile)
{
    PlainDocumentRefPtr temp=dynamic_pointer_cast<PlainDocument>(TextFileHandler::the()->forceRead(pathOfFile));
    if(temp)
    {
        setDocumentModel(temp);
        handleDocumentModelChanged();
    }
}

void TextDomArea::clear(void) 
{
    getLayoutManager()->selectAll();
    deleteSelectedUsingCommandManager();
}

void TextDomArea::write(const std::string& txt) 
{
    insertStringUsingCommandManager(getDocumentModel()->getEndPosition(),txt);
}

void TextDomArea::drawInternal(Graphics * const TheGraphics, Real32 Opacity) const
{
    if(getLayoutManager())
    {
        drawHighlightBG(TheGraphics,Opacity);
        drawBookmarkHighlight(TheGraphics,Opacity);
        drawLineHighlight(TheGraphics,Opacity);
        drawBraceHighlight(TheGraphics,Opacity);
    }

    // ask manager to draw visible views

    if(getLayoutManager() && getLayoutManager()->getMFVisibleViews()->size()>0)	// draw the view by calling the view's draw function
    {

        for(UInt32 i=0;i<getLayoutManager()->getMFVisibleViews()->size();i++)
        {
            getLayoutManager()->getVisibleViews(i)->drawView(TheGraphics,Opacity);
        }
    }

    if(getLayoutManager() && _DrawCaret)
    {
        drawTheCaret(TheGraphics,Opacity);
    }
}

void TextDomArea::drawHighlightBG(Graphics * const TheGraphics, Real32 Opacity) const
{
    if(getLayoutManager()->getRootElement())
    {
        if(getLayoutManager()->getHSL() != getLayoutManager()->getHEL() ||
           getLayoutManager()->getHSI() != getLayoutManager()->getHEI() )
        {
            if(getLayoutManager()->isStartLocationBeforeEndLocation())
            {
                drawHighlightBGInternal(TheGraphics,
                                        Opacity,
                                        getLayoutManager()->getHSL(),
                                        getLayoutManager()->getHSI(),
                                        getLayoutManager()->getHEL(),
                                        getLayoutManager()->getHEI());
            }
            else
            {
                drawHighlightBGInternal(TheGraphics,
                                        Opacity,
                                        getLayoutManager()->getHEL(),
                                        getLayoutManager()->getHEI(),
                                        getLayoutManager()->getHSL(),
                                        getLayoutManager()->getHSI());
            }
        }
    }
}
void TextDomArea::drawHighlightBGInternal(Graphics * const TheGraphics,
                                          Real32 Opacity,
                                          UInt32 lesserLine,
                                          UInt32 lesserIndex,
                                          UInt32 greaterLine,
                                          UInt32 greaterIndex) const
{
    for(UInt32 i=lesserLine+1;i<greaterLine;i++)
    {
        PlainDocumentLeafElementRefPtr theElement = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(i));

        if(theElement)
        {
            Pnt2f topLeft,bottomRight;
            getFont()->getBounds(theElement->getText(),topLeft,bottomRight);

            TheGraphics->drawRect(Pnt2f(getLayoutManager()->getGutterSpace() + getLayoutManager()->getGutterSeparation(),i*getLayoutManager()->getHeightOfLine()),Pnt2f(getLayoutManager()->getGutterSpace() + getLayoutManager()->getGutterSeparation()+ bottomRight.x(),(i+1)*getLayoutManager()->getHeightOfLine()),Color4f(0.7,0.7,0.95,1),Opacity);
        }
    }

    if(lesserLine== greaterLine)
    {
        TheGraphics->drawRect(getLayoutManager()->getXYPosition(lesserLine,lesserIndex,true),getLayoutManager()->getXYPosition(greaterLine,greaterIndex,false),Color4f(0.7,0.7,0.95,1),Opacity);
    }
    else
    {
        // draw the first line
        TheGraphics->drawRect(getLayoutManager()->getXYPosition(lesserLine,lesserIndex,true),getLayoutManager()->getEndXYPosition(lesserLine),Color4f(0.7,0.7,0.95,1),Opacity);

        // draw the last line
        TheGraphics->drawRect(getLayoutManager()->getStartXYPosition(greaterLine),getLayoutManager()->getXYPosition(greaterLine,greaterIndex,false),Color4f(0.7,0.7,0.95,1),Opacity);
    }

}


void TextDomArea::drawLineHighlight(Graphics * const TheGraphics, Real32 Opacity) const
{
    TheGraphics->drawRect(Pnt2f(0,getLayoutManager()->getCaretYPosition()),Pnt2f(getLayoutManager()->getPreferredWidth(),getLayoutManager()->getCaretYPosition()+getLayoutManager()->getHeightOfLine()),Color4f(0.7,0.7,0.7,0.5),Opacity);
}

void TextDomArea::drawBookmarkHighlight(Graphics * const TheGraphics, Real32 Opacity) const
{
    for(UInt32 i=0;i<getMFBookmarkedLines()->size();i++)
        TheGraphics->drawRect(Pnt2f(0,getLayoutManager()->getHeightOfLine()*getBookmarkedLines(i)),Pnt2f(getLayoutManager()->getPreferredWidth(),getLayoutManager()->getHeightOfLine()*(getBookmarkedLines(i)+1)),Color4f(0.7,0.7,1.0,0.5),Opacity);
}


void TextDomArea::drawBraceHighlight(Graphics * const TheGraphics, Real32 Opacity) const
{
    if(getLayoutManager()->getBracesHighlightFlag())
    {
        if(getLayoutManager()->getStartingBraceLine() != -1 && getLayoutManager()->getStartingBraceIndex() != -1)
        {
            Pnt2f thePosition = getLayoutManager()->getXYPosition(getLayoutManager()->getStartingBraceLine(),getLayoutManager()->getStartingBraceIndex(),true);
            TheGraphics->drawRect(thePosition,Pnt2f(thePosition.x()+5,thePosition.y()+getLayoutManager()->getHeightOfLine()),Color4f(0.7,0.7,0.0,1.0),Opacity);
        }
        if(getLayoutManager()->getEndingBraceLine() != -1 && getLayoutManager()->getEndingBraceIndex() != -1)
        {
            if(getLayoutManager()->getEndingBraceLine()<getLayoutManager()->getRootElement()->getElementCount())
            {
                PlainDocumentLeafElementRefPtr temp = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(getLayoutManager()->getEndingBraceLine()));
                if(getLayoutManager()->getEndingBraceIndex() < temp->getTextLength())
                {
                    Pnt2f thePosition = getLayoutManager()->getXYPosition(getLayoutManager()->getEndingBraceLine(),getLayoutManager()->getEndingBraceIndex(),true);
                    TheGraphics->drawRect(thePosition,Pnt2f(thePosition.x()+5,thePosition.y()+getLayoutManager()->getHeightOfLine()),Color4f(0.7,0.7,0.0,1.0),Opacity);
                }
            }
        }
    }
}

void TextDomArea::drawTheCaret(Graphics * const TheGraphics, Real32 Opacity) const
{
    TheGraphics->drawRect(Pnt2f(getLayoutManager()->getCaretXPosition(),
                                getLayoutManager()->getCaretYPosition()),
                          Pnt2f(getLayoutManager()->getCaretXPosition()+2,
                                getLayoutManager()->getCaretYPosition()+getLayoutManager()->getHeightOfLine()),
                          Color4f(0,0,0,1),
                          Opacity);
}


std::string TextDomArea::initialSearchStringModification(const std::string& stringToBeLookedFor,
                                                         bool isUseRegExChecked)
{
    std::string specialcharacters(".|*?+(){}[]^$\\");
    std::string Result("");
    if(!isUseRegExChecked)
    {
        size_t found;
        for(UInt32 i=0;i<stringToBeLookedFor.length();i++)
        {
            found=specialcharacters.find(stringToBeLookedFor[i]);
            if (found!=std::string::npos)
            {
                Result+="\\"+stringToBeLookedFor[i];
            }
            else
            {
                Result+=stringToBeLookedFor[i];
            }
        }
    }
    return Result;
}

void TextDomArea::regexCompiling(const std::string& stringToBeLookedFor,
                                 boost::xpressive::sregex& rex,
                                 bool isCaseChecked,
                                 bool isWholeWordChecked)
{
    if(isCaseChecked)
    {
        if(isWholeWordChecked)
        {
            rex = boost::xpressive::sregex::compile("\\b"+stringToBeLookedFor+"\\b");
        }
        else
        {
            rex = boost::xpressive::sregex::compile(stringToBeLookedFor);
        }
    }
    else
    {
        if(isWholeWordChecked)
        {
            rex = boost::xpressive::sregex::compile("\\b"+stringToBeLookedFor+"\\b", boost::xpressive::regex_constants::icase);
        }
        else
        {
            rex = boost::xpressive::sregex::compile(stringToBeLookedFor, boost::xpressive::regex_constants::icase);
        }
    }
}

void TextDomArea::bookmarkAllUsingRegEx(const std::string& stringToBeLookedFor,
                                        bool isCaseChecked,
                                        bool isWholeWordChecked,
                                        bool isUseRegExChecked)
{
    boost::xpressive::sregex rex;

    std::string ConvertedSearchString(initialSearchStringModification(stringToBeLookedFor,isUseRegExChecked));

    regexCompiling(ConvertedSearchString,rex,isCaseChecked,isWholeWordChecked);

    for(UInt32 i=0;i<getLayoutManager()->getRootElement()->getElementCount();i++)
    {
        PlainDocumentLeafElementRefPtr theElement = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(i));
        std::string stringToBeSearchedIn = theElement->getText();

        boost::xpressive::smatch what;

        if( boost::xpressive::regex_search( stringToBeSearchedIn, what, rex ) )
        {
            editMFBookmarkedLines()->push_back(i);   
        }
    }
}

void  TextDomArea::replaceAllUsingRegEx(const std::string& theSearchText,
                                        const std::string& theReplaceText,
                                        bool isCaseChecked,
                                        bool isWholeWordChecked,
                                        bool isUseRegExChecked)
{
    if(getEditable() && getEnabled())
    {
        boost::xpressive::sregex rex;

        std::string ConvertedSearchString(initialSearchStringModification(theSearchText,isUseRegExChecked));

        regexCompiling(ConvertedSearchString,rex,isCaseChecked,isWholeWordChecked);

        for(UInt32 i=0;i<getLayoutManager()->getRootElement()->getElementCount();i++)
        {
            PlainDocumentLeafElementRefPtr theElement = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(i));
            std::string stringToBeSearchedIn = theElement->getText();

            boost::xpressive::smatch what;

            if( boost::xpressive::regex_search( stringToBeSearchedIn, what, rex ) )
            {
                std::string str = regex_replace( stringToBeSearchedIn, rex, theReplaceText );
                setTextUsingCommandManager(theElement,str);
            }
        }
    }
}

void TextDomArea::setText(const std::string& txt)
{
    getLayoutManager()->selectAll();
    deleteSelectedUsingCommandManager();
    handlePastingAString(txt);
}

bool TextDomArea::searchForStringInDocumentUsingRegEx(const std::string& stringToBeLookedFor,
                                                      bool isCaseChecked,
                                                      bool isWholeWordChecked,
                                                      bool searchUp,
                                                      bool wrapAround,
                                                      bool isUseRegExChecked)
{
    boost::xpressive::sregex rex;

    std::string ConvertedSearchString(initialSearchStringModification(stringToBeLookedFor,isUseRegExChecked));

    regexCompiling(ConvertedSearchString,rex,isCaseChecked,isWholeWordChecked);

    Int32 i=getLayoutManager()->getCaretLine();
    UInt32 count=0;
    UInt32 totalElements = getLayoutManager()->getRootElement()->getElementCount();

    for(;;count++)
    {
        // conditions to exit on...
        if(!wrapAround)
        {
            if(!searchUp)
            {
                if(i>=totalElements)break;
            }
            else
            {
                if(i<0)break;
            }
        }
        else
        {
            if(count>=totalElements)break;
        }

        PlainDocumentLeafElementRefPtr theElement = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(i));
        std::string stringToBeSearchedIn = theElement->getText();

        if(i==getLayoutManager()->getCaretLine()) stringToBeSearchedIn = stringToBeSearchedIn.substr(getLayoutManager()->getCaretIndex());

        boost::xpressive::smatch what;

        if( boost::xpressive::regex_search( stringToBeSearchedIn, what, rex ) )
        {
            UInt32 temphsi = what.position();
            if(i==getLayoutManager()->getCaretLine())temphsi+=getLayoutManager()->getCaretIndex();
            getLayoutManager()->setHSI(temphsi);
            getLayoutManager()->setHSL(i);
            getLayoutManager()->setHEL(i);
            getLayoutManager()->setHEI(temphsi+ what.length());
            getLayoutManager()->setCaretLine(i);
            getLayoutManager()->setCaretIndex(temphsi+ what.length() );
            getLayoutManager()->recalculateCaretPositions();
            getLayoutManager()->checkCaretVisibility();

            return true;
        }

        // incrementing values 
        if(!wrapAround)
        {
            if(!searchUp)
            {
                ++i;
            }
            else
            {
                --i;
            }
        }
        else
        {
            if(!searchUp)
            {
                i=(i+1)%totalElements;
            }
            else
            {
                --i;
                if(i<0)
                {
                    i=totalElements-1;
                }
            }
        }
    }
    return false;
}

void TextDomArea::keyTyped(KeyEventDetails* const details)
{

    if(!(details->getModifiers() &
         ( KeyEventDetails::KEY_MODIFIER_ALT |
           KeyEventDetails::KEY_MODIFIER_CONTROL |
           KeyEventDetails::KEY_MODIFIER_META )))
    {
        DocumentElementAttribute temp;
        _CurrentCaretBlinkElps=0.0f;

        getLayoutManager()->removeBracesHighlightIndices();

        switch(details->getKey())
        {
            case KeyEventDetails::KEY_UP:
                getLayoutManager()->moveTheCaret(UP,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_DOWN:
                getLayoutManager()->moveTheCaret(DOWN,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_LEFT:
                getLayoutManager()->moveTheCaret(LEFT,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_RIGHT:
                getLayoutManager()->moveTheCaret(RIGHT,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_PAGE_UP:
                getLayoutManager()->moveTheCaret(PAGEUP,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_PAGE_DOWN:
                getLayoutManager()->moveTheCaret(PAGEDOWN,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_BACK_SPACE:
                if(getEditable() && getEnabled())
                {
                    if(getLayoutManager()->isSomethingSelected())
                    {
                        deleteSelectedUsingCommandManager();//getLayoutManager()->deleteSelected();
                    }
                    else
                    {
                        if(getLayoutManager()->getCaretLine()!=0 || getLayoutManager()->getCaretIndex()!=0)
                        {
                            getLayoutManager()->moveTheCaret(LEFT,false,false);
                            deleteCharacterUsingCommandManager();//getDocumentModel()->deleteCharacter(getLayoutManager()->getCaretLine(),getLayoutManager()->getCaretIndex());
                        }
                    }
                    highlightIfNextCharacterIsABrace();
                }
                break;
            case KeyEventDetails::KEY_DELETE:
                if(getEditable() && getEnabled())
                {
                    if(getLayoutManager()->isSomethingSelected())
                    {
                        deleteSelectedUsingCommandManager();//getLayoutManager()->deleteSelected();
                    }
                    else
                    {
                        deleteCharacterUsingCommandManager();//getDocumentModel()->deleteCharacter(getLayoutManager()->getCaretLine(),getLayoutManager()->getCaretIndex());
                    }
                    highlightIfNextCharacterIsABrace();
                }
                break;
            case KeyEventDetails::KEY_ENTER:
                if(getEditable() && getEnabled())
                {
                    if(getLayoutManager()->isSomethingSelected())
                    {
                        deleteSelectedUsingCommandManager();//getLayoutManager()->deleteSelected();
                    }
                    insertCharacterUsingCommandManager('\n',-1,-1);
                    highlightIfNextCharacterIsABrace();
                }
                break;
            case KeyEventDetails::KEY_HOME:
                getLayoutManager()->moveTheCaret(HOME,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_END:
                getLayoutManager()->moveTheCaret(END,(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT),(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND));
                highlightIfNextCharacterIsABrace();
                break;
            case KeyEventDetails::KEY_TAB:
                if(getEditable() && getEnabled())
                {
                    tabHandler(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT);
                    highlightIfNextCharacterIsABrace();
                }
                break;
            default:
                if(isPrintableChar(details->getKeyChar()) ||
                   details->getKey() == KeyEventDetails::KEY_SPACE)
                {
                    if(getEditable() && getEnabled())
                    {
                        if(getLayoutManager()->isSomethingSelected())
                        {
                            deleteSelectedUsingCommandManager();//getLayoutManager()->deleteSelected();
                        }

                        if(isStartingBraceForEncoding(details->getKeyChar()))
                        {
                            getLayoutManager()->setStartingBraces(details->getKeyChar(),getLayoutManager()->getCaretIndex(),getLayoutManager()->getCaretLine(),true);
                        }
                        else if(isEndingBraceForEncoding(details->getKeyChar()))
                        {
                            getLayoutManager()->setEndingBraces(details->getKeyChar(),getLayoutManager()->getCaretIndex(),getLayoutManager()->getCaretLine());
                        }

                        insertCharacterUsingCommandManager(details->getKeyChar(),-1,-1);

                        /*getDocumentModel()->insertCharacter(getLayoutManager()->getCaretIndex(),getLayoutManager()->getCaretLine(),details->getKeyChar(),temp);
                          getLayoutManager()->moveTheCaret(RIGHT,false,false);
                          getLayoutManager()->DoIfLineLongerThanPreferredSize();*/
                    }
                }
                break;
        }
        getLayoutManager()->DoIfLineLongerThanPreferredSize();
    }
    else if(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        switch(details->getKey())
        {

            case KeyEventDetails::KEY_A:
                getLayoutManager()->selectAll();
                break;
            case KeyEventDetails::KEY_C:
                {
                    std::string stringToTheClipboard = getHighlightedString();
                    getParentWindow()->getParentDrawingSurface()->getEventProducer()->putClipboard(stringToTheClipboard);
                    break;
                }
            case KeyEventDetails::KEY_V:
                {
                    if(getEditable() && getEnabled())
                    {
                        std::string theClipboard = getParentWindow()->getParentDrawingSurface()->getEventProducer()->getClipboard();
                        handlePastingAString(theClipboard);
                    }
                    break;
                }
            case KeyEventDetails::KEY_Z:
                if(getEditable() && getEnabled())
                {
                    if(_TheUndoManager->canUndo())
                    {
                        _TheUndoManager->undo();
                    }
                }
                break;
            case KeyEventDetails::KEY_Y:
                if(getEditable() && getEnabled())
                {
                    if(_TheUndoManager->canRedo())
                    {
                        _TheUndoManager->redo();
                    }
                }
                break;
        }
    }
}

void TextDomArea::highlightIfNextCharacterIsABrace(void)
{

    std::string nextCharacterInString = getDocumentModel()->getText(getLayoutManager()->CaretLineAndIndexToCaretOffsetInDOM(getLayoutManager()->getCaretLine(),getLayoutManager()->getCaretIndex()),1);

    char nextCharacter = nextCharacterInString[0];

    if(isStartingBraceForEncoding(nextCharacter))
    {
        getLayoutManager()->setStartingBraces(nextCharacter,getLayoutManager()->getCaretIndex(),getLayoutManager()->getCaretLine(),false);
    }
    else if(isEndingBraceForEncoding(nextCharacter))
    {
        getLayoutManager()->setEndingBraces(nextCharacter,getLayoutManager()->getCaretIndex(),getLayoutManager()->getCaretLine());
    }

}

void TextDomArea::tabHandler(bool isShiftPressed)
{
    UInt32 lesserLine,greaterLine,lesserIndex;
    DocumentElementAttribute temp;
    UInt32 oldHSI = getLayoutManager()->getHSI();
    UInt32 oldHSL = getLayoutManager()->getHSL();
    UInt32 oldHEI = getLayoutManager()->getHEI();
    UInt32 oldHEL = getLayoutManager()->getHEL();

    PlainDocumentLeafElementRefPtr theElement;
    if(getLayoutManager()->getHSL() <= getLayoutManager()->getHEL())
    {
        lesserLine = getLayoutManager()->getHSL();
        lesserIndex = getLayoutManager()->getHSI();
        greaterLine = getLayoutManager()->getHEL();
    }
    else
    {
        lesserLine = getLayoutManager()->getHEL();
        lesserIndex = getLayoutManager()->getHEI();
        greaterLine = getLayoutManager()->getHSL();
    }

    UInt32 count=0;
    if(getLayoutManager()->isSomethingSelected())
    {
        if(!isShiftPressed)
        {
            for(UInt32 caretLine = lesserLine;caretLine<=greaterLine;caretLine++)
            {
                for(UInt32 i=0;i<getTabSize();i++)
                {
                    //getDocumentModel()->insertCharacter(0,caretLine,' ',temp);
                    insertCharacterUsingCommandManager(' ',caretLine,0);
                }
                //getLayoutManager()->DoIfLineLongerThanPreferredSize();
            }

        }
        else
        {
            for(UInt32 caretLine = lesserLine;caretLine<=greaterLine;caretLine++)
            {
                theElement = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(caretLine));
                std::string theString = theElement->getText();
                Int32 i;
                for(i=0;i<theElement->getTextLength()-2,i<getTabSize();i++)
                {
                    if(theString[i]!=' ')break;
                    if(caretLine == getLayoutManager()->getCaretLine())getLayoutManager()->moveTheCaret(LEFT,false,false);
                    if(caretLine == lesserLine)count--;
                }
                theString = theString.substr(i);
                setTextUsingCommandManager(theElement,theString);
                //theElement->setText(theString);

            }
            getLayoutManager()->setHSI(0);
            getLayoutManager()->setHSL(lesserLine);
            getLayoutManager()->setHEI(0);
            getLayoutManager()->setHEL(greaterLine);
        }
    }
    else
    {
        if(!isShiftPressed)
        {
            for(UInt32 i=0;i<getTabSize();i++)
            {
                //getDocumentModel()->insertCharacter(getLayoutManager()->getCaretIndex(),getLayoutManager()->getCaretLine(),' ',temp);
                insertCharacterUsingCommandManager(' ',-1,-1);
                //getLayoutManager()->moveTheCaret(RIGHT,false,false);
            }
            //getLayoutManager()->DoIfLineLongerThanPreferredSize();	
        }
        else
        {
            theElement = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(getLayoutManager()->getCaretLine()));
            std::string theString = theElement->getText();
            Int32 i,count=0;
            Int32 initIndex = getLayoutManager()->getCaretIndex();
            for(i=getLayoutManager()->getCaretIndex()-1;i>=0,count<getTabSize();i--,count++)
            {
                if(i<0 || theString[i]!=' ')break;
                getLayoutManager()->moveTheCaret(LEFT,false,false);
            }
            theString = theString.substr(0,getLayoutManager()->getCaretIndex())+theString.substr(initIndex);
            setTextUsingCommandManager(theElement,theString);
            //theElement->setText(theString);
        }
    }
}


void TextDomArea::handlePastingAString(const std::string& theClipboard)
{

    DocumentElementAttribute temp;
    if(getLayoutManager()->isSomethingSelected())
    {
        deleteSelectedUsingCommandManager();//getLayoutManager()->deleteSelected();
    }

    //getDocumentModel()->insertString(getCaretPosition(),theClipboard,temp);/// need to deal with this......
    insertStringUsingCommandManager(getLayoutManager()->CaretLineAndIndexToCaretOffsetInDOM(getLayoutManager()->getCaretLine(),getLayoutManager()->getCaretIndex()),theClipboard);

    getLayoutManager()->updateViews();
    getLayoutManager()->updateSize();
    updatePreferredSize();
}

void TextDomArea::insertCharacterUsingCommandManager(char theCharacter,UInt32 line,UInt32 index)
{
    CommandPtr theCommand = InsertCharacterCommand::create(getLayoutManager(),dynamic_cast<PlainDocument*>(getDocumentModel()),theCharacter,line,index);
    _TheCommandManager->executeCommand(theCommand);
}

void TextDomArea::insertStringUsingCommandManager(UInt32 caretPosition,std::string theString)
{
    CommandPtr theCommand = InsertStringCommand::create(getLayoutManager(),dynamic_cast<PlainDocument*>(getDocumentModel()),caretPosition,theString);
    _TheCommandManager->executeCommand(theCommand);
}

void TextDomArea::deleteCharacterUsingCommandManager()
{
    CommandPtr theCommand = DeleteCharacterCommand::create(getLayoutManager(),dynamic_cast<PlainDocument*>(getDocumentModel()));
    _TheCommandManager->executeCommand(theCommand);
}

void TextDomArea::deleteSelectedUsingCommandManager(void)
{
    CommandPtr theCommand = DeleteSelectedCommand::create(getLayoutManager(),this);
    _TheCommandManager->executeCommand(theCommand);
}

void TextDomArea::setTextUsingCommandManager(PlainDocumentLeafElement* theElement,std::string theString)
{
    CommandPtr theCommand = SetTextCommand::create(theElement,theString);
    _TheCommandManager->executeCommand(theCommand);
}

TextDomAreaTransitPtr TextDomArea::createDuplicate(void)
{
    TextDomAreaRefPtr newPtr = TextDomArea::create();
    newPtr->setWrapStyleWord(this->getWrapStyleWord());
    newPtr->setPreferredSize(this->getPreferredSize());
    newPtr->setMinSize(this->getMinSize());
    newPtr->setFont(this->getFont());
    newPtr->setDocumentModel(this->getDocumentModel());
    newPtr->handleDocumentModelChanged();
    newPtr->setEditable(this->getEditable());
    newPtr->setEnabled(this->getEnabled());
    return TextDomAreaTransitPtr(newPtr);
}

std::string TextDomArea::getHighlightedString(void) const
{
    if(getLayoutManager()->getHSL() != getLayoutManager()->getHEL() ||
       getLayoutManager()->getHSI() != getLayoutManager()->getHEI() )
    {
        if(getLayoutManager()->isStartLocationBeforeEndLocation())
        {
            return(getHighlightedStringInternal(getLayoutManager()->getHSL(),
                                                getLayoutManager()->getHSI(),
                                                getLayoutManager()->getHEL(),
                                                getLayoutManager()->getHEI()));
        }
        else
        {
            return(getHighlightedStringInternal(getLayoutManager()->getHEL(),
                                                getLayoutManager()->getHEI(),
                                                getLayoutManager()->getHSL(),
                                                getLayoutManager()->getHSI()));
        }
    }
    else 
    {
        return "";
    }
}

std::string TextDomArea::getHighlightedStringInternal(UInt32 lesserLine,
                                                      UInt32 lesserIndex,
                                                      UInt32 greaterLine,
                                                      UInt32 greaterIndex) const
{
    std::string firstLine="";
    std::string lastLine="";
    std::string intermediateLines="";
    PlainDocumentLeafElementRefPtr temp1 = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(lesserLine));
    std::string temp2 = temp1->getText();
    if(lesserLine== greaterLine)
    {
        return temp2.substr(lesserIndex,greaterIndex-lesserIndex);
    }
    else
    {
        // get the first line 
        firstLine = temp2.substr(lesserIndex);

        // get the last line
        temp1 = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(greaterLine));
        temp2 = temp1->getText();
        lastLine = temp2.substr(0,greaterIndex);
    }

    for(UInt32 i=lesserLine+1;i<greaterLine;i++)
    {
        PlainDocumentLeafElementRefPtr theElement = dynamic_cast<PlainDocumentLeafElement*>(getLayoutManager()->getRootElement()->getElement(i));
        intermediateLines+=theElement->getText();
    }

    return firstLine + intermediateLines + lastLine;
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
    return getLayoutManager()->getContentRequestedSize();
}

void TextDomArea::focusGained(FocusEventDetails* const details)
{
    _CaretUpdateConnection.disconnect();
    _CaretUpdateConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&TextDomArea::handleCaretUpdate, this, _1));

    Inherited::focusGained(details);
}

void TextDomArea::focusLost(FocusEventDetails* const details)
{
    _CaretUpdateConnection.disconnect();

    Inherited::focusLost(details);
}


void TextDomArea::mouseClicked(MouseEventDetails* const details)
{

    getLayoutManager()->calculateCaretPosition(DrawingSurfaceToComponent(details->getLocation(), TextDomAreaRefPtr(this)),false);

    if(details->getButton() == details->BUTTON1)
    {
        if(details->getClickCount() >= 2)
        {
            getLayoutManager()->doubleClickHandler();
        }
    }

    Inherited::mouseClicked(details);

}

void TextDomArea::mouseReleased(MouseEventDetails* const details)
{
    _IsMousePressed = false;
    Inherited::mouseReleased(details);
}

void TextDomArea::mousePressed(MouseEventDetails* const details)
{
    _IsMousePressed = true;
    if(details->getButton() == details->BUTTON1)
    {
        //set caret position to proper place
        getLayoutManager()->calculateCaretPosition(DrawingSurfaceToComponent(details->getLocation(), TextDomAreaRefPtr(this)),false);
    }

    Inherited::mousePressed(details);
}

void TextDomArea::handleCaretUpdate(UpdateEventDetails* const details)
{
    _CurrentCaretBlinkElps += details->getElapsedTime();
    if(_CurrentCaretBlinkElps > LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
    {
        Int32 Div = _CurrentCaretBlinkElps/LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
        _CurrentCaretBlinkElps -= static_cast<OSG::Time>(Div)*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
    }
    _DrawCaret = (getEnabled() &&
                  getEditable() &&
                  getFocused() &&
                  _CurrentCaretBlinkElps <= 0.5*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate());
}

void TextDomArea::createDefaultLayer(void)
{
    ColorLayerRecPtr EditableBackground = ColorLayer::create();
    EditableBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
    setBackgrounds(EditableBackground);

    ColorLayerRecPtr UneditableBackground = ColorLayer::create();
    UneditableBackground->setColor(Color4f(0.5, 0.5, 0.5, 1.0));

    setDisabledBackground(UneditableBackground);
}

Layer* TextDomArea::getDrawnBackground(void) const
{
    if(getEditable())
    {
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedBackground();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverBackground();
            }
            else
            {
                return getBackground();
            }
        }
        else
        {
            return getDisabledBackground();
        }
    }
    else
    {
        return getDisabledBackground();
    }
}

Layer* TextDomArea::getDrawnForeground(void) const
{
    if(getEditable())
    {
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedForeground();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverForeground();
            }
            else
            {
                return getForeground();
            }
        }
        else
        {
            return getDisabledForeground();
        }
    }
    else
    {
        return getDisabledForeground();
    }
}

Border* TextDomArea::getDrawnBorder(void) const
{
    if(getEditable())
    {
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedBorder();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverBorder();
            }
            else
            {
                return getBorder();
            }
        }
        else
        {
            return getDisabledBorder();
        }
    }
    else
    {
        return getDisabledBorder();
    }
}

void TextDomArea::updatePreferredSize(void)
{
    setPreferredSize(getRequestedSize());
}

Int32 TextDomArea::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft,
                                               const Pnt2f& VisibleRectBottomRight,
                                               const UInt32& orientation,
                                               const Int32& direction)
{
    return Inherited::getScrollableBlockIncrement(VisibleRectTopLeft,
                                                  VisibleRectBottomRight,
                                                  orientation,
                                                  direction);
}

bool TextDomArea::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool TextDomArea::getScrollableTracksViewportWidth(void)
{
    return false;
}

bool TextDomArea::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool TextDomArea::getScrollableWidthMinTracksViewport(void)
{
    return true;
}

Int32 TextDomArea::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft,
                                              const Pnt2f& VisibleRectBottomRight,
                                              const UInt32& orientation,
                                              const Int32& direction)
{
    return getLineHeight(0);
}

Vec2f TextDomArea::getContentRequestedSize(void) const
{
    //getTheManager()->calculatePreferredSize();

    if(getLayoutManager())
    {
        return getLayoutManager()->getContentRequestedSize();
    }
    else
    {
        return getSize();
    }
}

void TextDomArea::handleDocumentModelChanged(void)
{
    setPosition(Pnt2f(0,0));
    getLayoutManager()->initializeRootElement();
    getLayoutManager()->calculatePreferredSize();

    _DocumentChangedConnection.disconnect();
    _DocumentInsertConnection.disconnect();
    _DocumentRemoveConnection.disconnect();

    _DocumentChangedConnection = getDocumentModel()->connectChanged(boost::bind(&TextDomArea::handleDocumentChanged, this, _1));
    _DocumentInsertConnection = getDocumentModel()->connectInsert(boost::bind(&TextDomArea::handleDocumentInsert, this, _1));
    _DocumentRemoveConnection = getDocumentModel()->connectRemove(boost::bind(&TextDomArea::handleDocumentRemove, this, _1));


    getLayoutManager()->setHighlight(0,0,0,0);
    getLayoutManager()->populateCache();
    updatePreferredSize();
    getLayoutManager()->updateViews();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void TextDomArea::onCreate(const TextDomArea *source)
{
	if(source == NULL) return;

	FixedHeightLayoutManagerRefPtr Manager= FixedHeightLayoutManager::create();
	setLayoutManager(Manager);
	getLayoutManager()->calculateLineHeight();
	createDefaultDocument();
		
}

void TextDomArea::createDefaultDocument(void)
{
	DocumentElementAttribute Props;
	PlainDocumentRefPtr temp=PlainDocument::create();
	temp->addTextAsNewElementToDocument(" \r\n",Props,true);
	setDocumentModel(temp);
	handleDocumentModelChanged();
}

void TextDomArea::resolveLinks(void)
{
    Inherited::resolveLinks();

    _DocumentChangedConnection.disconnect();
    _DocumentInsertConnection.disconnect();
    _DocumentRemoveConnection.disconnect();
    _CaretUpdateConnection.disconnect();
}

void TextDomArea::handleDocumentChanged(DocumentEventDetails* const details)
{
	getLayoutManager()->updateViews();
	getLayoutManager()->updateSize();
	getLayoutManager()->calculatePreferredSize();
	updatePreferredSize();
}

void TextDomArea::handleDocumentInsert(DocumentEventDetails* const details)
{
	getLayoutManager()->updateViews();
	getLayoutManager()->updateSize();
	getLayoutManager()->calculatePreferredSize();
	updatePreferredSize();
}

void TextDomArea::handleDocumentRemove(DocumentEventDetails* const details)
{
	getLayoutManager()->updateViews();
	getLayoutManager()->updateSize();
	getLayoutManager()->calculatePreferredSize();
	updatePreferredSize();
}

void TextDomArea::mouseDragged(MouseEventDetails* const details)
{
    if(_IsMousePressed && details->getButton() == MouseEventDetails::BUTTON1)
	{
		getLayoutManager()->calculateCaretPosition(DrawingSurfaceToComponent(details->getLocation(), TextDomAreaRefPtr(this)) , true);	
	}
}

/*----------------------- constructors & destructors ----------------------*/

TextDomArea::TextDomArea(void) :
    Inherited(),
	_CurrentCaretBlinkElps(0.0),
    _DrawCaret(false)
{
	createDefaultLayer();
	setupCursor();
	_TheUndoManager = UndoManager::create();
	_TheCommandManager = CommandManager::create(_TheUndoManager);
}



TextDomArea::TextDomArea(const TextDomArea &source) :
	Inherited(source),
	_CurrentCaretBlinkElps(0.0),
    _DrawCaret(false),
    _TheUndoManager(source._TheUndoManager),
    _TheCommandManager(source._TheCommandManager)
{
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

	if(whichField & TextDomArea::ClipBoundsFieldMask)
	{
		if(getLayoutManager())getLayoutManager()->updateViews();
	}

	if(whichField & TextDomArea::FontFieldMask)
	{
		if(getLayoutManager())
		{
			getLayoutManager()->calculateLineHeight();
			getLayoutManager()->populateCache();
			getLayoutManager()->updateViews();
			updatePreferredSize();
		}
	}

    if((whichField & EnabledFieldMask) || (whichField & EditableFieldMask))
    {
        setupCursor();
    }
}

void TextDomArea::dump(      UInt32,
                         const BitVector ) const
{
    SLOG << "Dump TextDomArea NI" << std::endl;

}

OSG_END_NAMESPACE
