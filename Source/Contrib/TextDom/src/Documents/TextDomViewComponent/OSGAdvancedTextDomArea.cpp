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
#include "OSGDocument.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGGlyphView.h"

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

std::string AdvancedTextDomArea::getText(void)
{
	if(getTheTextDomArea())
	{
		return getTheTextDomArea()->getText();
	}
	else return "";
}

void AdvancedTextDomArea::clear(void) 
{
	if(getTheTextDomArea())
	{
		getTheTextDomArea()->clear();
	}
}

void AdvancedTextDomArea::write(std::string txt) 
{
	if(getTheTextDomArea())
	{
		getTheTextDomArea()->write(txt);
	}
}

void AdvancedTextDomArea::loadFile(const BoostPath& path)
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
    //_TheTextDomArea->setPreferredSize(Vec2f(600, 400));
    //_TheTextDomArea->setMinSize(Vec2f(600,400));
	_TheTextDomArea->setFont(_Font);

	setPreferredSize(_TheTextDomArea->getRequestedSize());

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

void AdvancedTextDomArea::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideInsetsBounds(TopLeft, BottomRight);

	if(getMFChildren()->size() > 0)
	{
		Vec2f GutterSize(getGutterWidth(), 0.0f);
		getChildren(0)->setPosition(TopLeft + GutterSize);
		getChildren(0)->setSize(getChildren(0)->getRequestedSize());
		if(getSize() != getRequestedSize()) /////// isnt it getPreferredSize
		{
			setPreferredSize(getRequestedSize());
		}
	}
}

void AdvancedTextDomArea::drawGutter(Graphics * const TheGraphics, Real32 Opacity) const
{
	if(getMFChildren()->size())
	{
		TextDomAreaRefPtr textDomArea = dynamic_cast<TextDomArea*>(getChildren(0));

		Pnt2f ClipTopLeft,ClipBottomRight;
		getClipBounds(ClipTopLeft,ClipBottomRight);
        ClipBottomRight.setValues(ClipTopLeft.x() + getGutterWidth(),ClipBottomRight.y());

        //Setup clipping
        Vec4d LeftPlaneEquation(1.0,0.0,0.0,-ClipTopLeft.x()+ TheGraphics->getClipPlaneOffset()),
              RightPlaneEquation(-1.0,0.0,0.0,ClipBottomRight.x() + TheGraphics->getClipPlaneOffset()),
              TopPlaneEquation(0.0,1.0,0.0,-ClipTopLeft.y() + TheGraphics->getClipPlaneOffset()),
              BottomPlaneEquation(0.0,-1.0,0.0,ClipBottomRight.y() + TheGraphics->getClipPlaneOffset());

        //glClipPlane
        //Clip with the Intersection of this components RenderingSurface bounds
        //and its parents RenderingSurface bounds
        if(ClipBottomRight.x()-ClipTopLeft.x() <= 0 || ClipBottomRight.y()-ClipTopLeft.y()<= 0)
        {
            return;
        }

        if(!glIsEnabled(GL_CLIP_PLANE0)) { glEnable(GL_CLIP_PLANE0); }
        if(!glIsEnabled(GL_CLIP_PLANE1)) { glEnable(GL_CLIP_PLANE1); }
        if(!glIsEnabled(GL_CLIP_PLANE2)) { glEnable(GL_CLIP_PLANE2); }
        if(!glIsEnabled(GL_CLIP_PLANE3)) { glEnable(GL_CLIP_PLANE3); }

        //Clip Plane Equations
        //Clip Planes get transformed by the ModelViewMatrix when set
        //So we can rely on the fact that our current coordinate space
        //is relative to the this components position

        glClipPlane(GL_CLIP_PLANE0,LeftPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE1,RightPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE2,TopPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE3,BottomPlaneEquation.getValues());

		TheGraphics->drawRect(ClipTopLeft,
                              ClipBottomRight,
                              getGutterColor(),
                              Opacity);

		UInt32 topVisibleLine = textDomArea->getTopmostVisibleLineNumber();
		UInt32 bottomVisibleLine = topVisibleLine + textDomArea->getLinesToBeDisplayed();

		for(UInt32 i(topVisibleLine) ; i<bottomVisibleLine ; ++i)
		{
            TheGraphics->drawText(Pnt2f(ClipTopLeft.x(),i* textDomArea->getHeightOfLine()),
                                  boost::lexical_cast<std::string>(i+1),
                                  textDomArea->getFont(),
                                  getGutterTextColor(),
                                  Opacity);
		}
		
	}
}

Vec2f AdvancedTextDomArea::getPreferredScrollableViewportSize(void)
{
	if(getMFChildren()->size() > 0)
	{
		return getChildren(0)->getPreferredScrollableViewportSize();
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


bool AdvancedTextDomArea::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool AdvancedTextDomArea::getScrollableTracksViewportWidth(void)
{
    return false;
}


bool AdvancedTextDomArea::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool AdvancedTextDomArea::getScrollableWidthMinTracksViewport(void)
{
    return true;
}

void AdvancedTextDomArea::drawInternal(Graphics * const TheGraphics, Real32 Opacity) const
{
	Inherited::drawInternal(TheGraphics,Opacity);
	drawGutter(TheGraphics,Opacity);
}

void AdvancedTextDomArea::setTheTextDomArea(TextDomArea* const duplicatedTextDom)
{
	_TheTextDomArea = duplicatedTextDom;
}

TextDomArea* AdvancedTextDomArea::getTheTextDomArea(void)
{
	return _TheTextDomArea;
}


AdvancedTextDomAreaTransitPtr AdvancedTextDomArea::createDuplicate()
{
	AdvancedTextDomAreaRefPtr newPtr = AdvancedTextDomArea::create();
	newPtr->setPreferredSize(Vec2f(400,400));
	TextDomAreaRefPtr duplicatedTextDom = dynamic_cast<TextDomArea*>(getChildren(0))->createDuplicate();
	newPtr->setTheTextDomArea(duplicatedTextDom);
	newPtr->clearChildren();
	newPtr->pushToChildren(duplicatedTextDom);
	newPtr->setPreferredSize(duplicatedTextDom->getRequestedSize());
	return AdvancedTextDomAreaTransitPtr(newPtr);
}

//void AdvancedTextDomArea::changedUpdate(const DocumentModelChangedEventUnrecPtr e)
//{
//	if(getMFChildren()->size()>0)
//		setPreferredSize(dynamic_cast<TextDomArea*>(getChildren(0))->getPreferredSize());
//}



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void AdvancedTextDomArea::resolveLinks(void)
{
    Inherited::resolveLinks();

    _TheTextDomArea = NULL;
    _Font = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

AdvancedTextDomArea::AdvancedTextDomArea(void) :
    Inherited()
{
}

AdvancedTextDomArea::AdvancedTextDomArea(const AdvancedTextDomArea &source) :
    Inherited(source)
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
