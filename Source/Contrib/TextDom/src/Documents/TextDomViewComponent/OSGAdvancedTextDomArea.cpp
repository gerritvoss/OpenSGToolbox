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

#include <cstdlib>
#include <cstdio>

#define OSG_COMPILECONTRIBTEXTDOMLIB

#include <OSGConfig.h>

#include "OSGAdvancedTextDomArea.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGBorderLayout.h"
#include "OSGFlowLayout.h"
#include "OSGTextDomArea.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h";
#include "OSGSplitPanel.h"
#include "OSGUIFont.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAdvancedTextDomAreaBase.cpp file.
// To modify it, please change the .fcd file (OSGAdvancedTextDomArea.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AdvancedTextDomArea::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


void AdvancedTextDomArea::loadFile(BoostPath path)
{
		// Create a TextDomArea component
		_TheTextDomArea = OSG::TextDomArea::create();
		_TheTextDomArea->setWrapStyleWord(false);
        _TheTextDomArea->setPreferredSize(Vec2f(600, 400));
        _TheTextDomArea->setMinSize(Vec2f(600,400));
		_TheTextDomArea->setFont(_Font);
		_TheTextDomArea->loadFile(path);
		clearChildren();
		pushToChildren(_TheTextDomArea);
		setPreferredSize(_TheTextDomArea->getContentRequestedSize());
		_TheTextDomArea->addDocumentModelChangedListener(&_PreferredSizeChangedListener);
}

void AdvancedTextDomArea::onCreate(const AdvancedTextDomArea *source)
{
	//Create and add the TextDomArea
	if(source == NULL) return;
		
	_Font = UIFont::create();
	_Font->setFamily("SANS");
	_Font->setGap(3);
	_Font->setGlyphPixelSize(46);
	_Font->setSize(15);
	_Font->setTextureWidth(0);
	_Font->setStyle(TextFace::STYLE_PLAIN);

	// Create a TextDomArea component
	_TheTextDomArea = OSG::TextDomArea::create();
	_TheTextDomArea->setWrapStyleWord(false);
    _TheTextDomArea->setPreferredSize(Vec2f(600, 400));
    _TheTextDomArea->setMinSize(Vec2f(600,400));
	_TheTextDomArea->setFont(_Font);
	_TheTextDomArea->loadFile(BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TextDom\\Data\\SampleText3.txt"));

	setPreferredSize(_TheTextDomArea->getContentRequestedSize());

	_TheTextDomArea->addDocumentModelChangedListener(&_PreferredSizeChangedListener);

	pushToChildren(_TheTextDomArea);
	
	
}

std::string AdvancedTextDomArea::getHighlightedString(void)
{
	if(getMFChildren()->size() > 0)
	{
		return dynamic_cast<TextDomArea*>(getChildren(0))->getHighlightedString();
	}
	else 
	{
		return "";
	}
}

void AdvancedTextDomArea::updateLayout()
{
    Pnt2f TopLeft, BottomRight;
    getInsideInsetsBounds(TopLeft, BottomRight);

	if(getMFChildren()->size() > 0)
	{
		Vec2f GutterSize(getGutterWidth(), 0.0f);
		getChildren(0)->setPosition(TopLeft + GutterSize);
		getChildren(0)->setSize(BottomRight - TopLeft - GutterSize);
	}
}

void AdvancedTextDomArea::drawGutter(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
	if(getMFChildren()->size())
	{
		TextDomAreaRefPtr textDomArea = dynamic_cast<TextDomArea*>(getChildren(0));

		Pnt2f topLeft,bottomRight;
		getClipBounds(topLeft,bottomRight);
		
		Graphics->drawRect(topLeft,Pnt2f(topLeft.x()+getGutterWidth(),bottomRight.y()),Color4f(1,1,0,1),Opacity);

		UInt32 topMostVisibleLine = textDomArea->getTopmostVisibleLineNumber();
		UInt32 linesToBeDisplayed = textDomArea->getLinesToBeDisplayed();

		std::ostringstream o;
		for(UInt32 i=topMostVisibleLine ; i<topMostVisibleLine + linesToBeDisplayed;i++)
		{
			o<<(i+1);
			Graphics->drawText(Pnt2f(topLeft.x(),i* textDomArea->getHeightOfLine()),o.str(),textDomArea->getFont(),Color4f(0.2,0.2,0.2,1.0),Opacity);
			o.str("");
			o.clear();
		}
		
	}
}

Vec2f AdvancedTextDomArea::getPreferredScrollableViewportSize(void)
{
	if(getMFChildren()->size() > 0)
	{
		getChildren(0)->getPreferredScrollableViewportSize();
	}
	return getPreferredSize();
}

Int32 AdvancedTextDomArea::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
	if(getMFChildren()->size() > 0)
	{
		return getChildren(0)->getScrollableUnitIncrement(VisibleRectTopLeft,VisibleRectBottomRight,orientation,direction);
	}
	else 
	{
		return 15;
	}
}

Vec2f AdvancedTextDomArea::getContentRequestedSize(void) const
{
	if(getMFChildren()->size()>0)
	{
		getChildren(0)->getRequestedSize();
	}
	else
	{ 
		return Inherited::getContentRequestedSize();
	}
}

void AdvancedTextDomArea::drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
	Inherited::drawInternal(Graphics,Opacity);
	drawGutter(Graphics,Opacity);
}

void AdvancedTextDomArea::setTheTextDomArea(TextDomAreaRefPtr duplicatedTextDom)
{
	this->_TheTextDomArea = duplicatedTextDom;
	duplicatedTextDom->addDocumentModelChangedListener(&_PreferredSizeChangedListener);
}

AdvancedTextDomAreaRefPtr AdvancedTextDomArea::makeADuplicate()
{
	AdvancedTextDomAreaRefPtr newPtr = AdvancedTextDomArea::create();
	newPtr->setPreferredSize(Vec2f(400,400));
	TextDomAreaRefPtr duplicatedTextDom = dynamic_cast<TextDomArea*>(getChildren(0))->getDuplicatedTextDomArea();
	newPtr->setTheTextDomArea(duplicatedTextDom);
	newPtr->clearChildren();
	newPtr->pushToChildren(duplicatedTextDom);
	newPtr->setPreferredSize(duplicatedTextDom->getContentRequestedSize());
	return newPtr;
}

void AdvancedTextDomArea::PreferredSizeChangedListener::changedUpdate(const DocumentModelChangedEventUnrecPtr e)
{
	_AdvancedTextDomArea->changedUpdate(e);
}

AdvancedTextDomArea::PreferredSizeChangedListener::PreferredSizeChangedListener(AdvancedTextDomAreaRefPtr _TheAdvancedTextDomArea)
{
	_AdvancedTextDomArea = _TheAdvancedTextDomArea;
}

void AdvancedTextDomArea::changedUpdate(const DocumentModelChangedEventUnrecPtr e)
{
	std::cout<<"child has been updated.";
	if(getMFChildren()->size()>0)
		setPreferredSize(dynamic_cast<TextDomArea*>(getChildren(0))->getPreferredSize());
}



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AdvancedTextDomArea::AdvancedTextDomArea(void) :
    Inherited(),
	_PreferredSizeChangedListener(this)
{
}

AdvancedTextDomArea::AdvancedTextDomArea(const AdvancedTextDomArea &source) :
    Inherited(source),
	_PreferredSizeChangedListener(this)
{
}

AdvancedTextDomArea::~AdvancedTextDomArea(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AdvancedTextDomArea::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{

	
    Inherited::changed(whichField, origin, details);
	
}

void AdvancedTextDomArea::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AdvancedTextDomArea NI" << std::endl;
}

OSG_END_NAMESPACE
