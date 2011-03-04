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
#include "OSGSpringLayoutConstraints.h"
#include "OSGSplitPanel.h"
#include "OSGUIFont.h"
#include "OSGDocument.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGGlyphView.h"
#include "OSGScrollPanel.h"

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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string AdvancedTextDomArea::getText(void) const
{
	if(getTextArea())
	{
		return getTextArea()->getText();
	}
	else return "";
}

void AdvancedTextDomArea::clear(void) 
{
	if(getTextArea())
	{
		getTextArea()->clear();
	}
}

void AdvancedTextDomArea::write(const std::string& txt) 
{
	if(getTextArea())
	{
		getTextArea()->write(txt);
	}
}

void AdvancedTextDomArea::loadFile(const BoostPath& path)
{
	// Create a TextDomArea component
	TextDomAreaRecPtr NewTextDomArea = TextDomArea::create();
	NewTextDomArea->setWrapStyleWord(false);
	NewTextDomArea->setFont(getTextArea()->getFont());
	NewTextDomArea->loadFile(path);

    setTextDomArea(NewTextDomArea);
}


std::string AdvancedTextDomArea::getHighlightedString(void) const
{
	if(getTextArea())
	{
		return getTextArea()->getHighlightedString();
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

    Vec2f GutterWidthSize(getGutterWidth(), 0.0f);
    Vec2f GutterSize(getGutterWidth(), BottomRight.y() - TopLeft.y());

    //Set the Position and size of the Gutter
    getGutter()->setPosition(TopLeft);
    getGutter()->setSize(GutterSize);

    //Set the Position and size of the TextArea
    _ScrollPanel->setPosition(TopLeft + GutterWidthSize);
    _ScrollPanel->setSize(BottomRight - TopLeft - GutterWidthSize);
}
 
Vec2f AdvancedTextDomArea::getContentRequestedSize(void) const
{
	if(getTextArea())
	{
		getTextArea()->getRequestedSize() + Vec2f(getGutterWidth(),0.0f);
	}
	else
	{ 
		return Inherited::getContentRequestedSize();
	}
}

AdvancedTextDomAreaTransitPtr AdvancedTextDomArea::createDuplicate(void) const
{
	AdvancedTextDomAreaRefPtr newPtr = AdvancedTextDomArea::create();
	TextDomAreaRefPtr duplicatedTextDom = getTextArea()->createDuplicate();
	newPtr->setTextDomArea(duplicatedTextDom);
	return AdvancedTextDomAreaTransitPtr(newPtr);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void AdvancedTextDomArea::onCreate(const AdvancedTextDomArea *source)
{
	Inherited::onCreate(source);

	//Create and add the TextDomArea
    if(GlobalSystemState != Startup)
    {
        UIFontRecPtr TheFont = UIFont::create();
        TheFont->setFamily("SANS");
        TheFont->setGap(3);
        TheFont->setSize(15);
        TheFont->setGlyphPixelSize(TheFont->getSize());
        TheFont->setStyle(TextFace::STYLE_PLAIN);

        // Create a TextDomArea component
        TextDomAreaRecPtr NewTextArea = TextDomArea::create();
        NewTextArea->setWrapStyleWord(false);
        NewTextArea->setFont(TheFont);
        setTextArea(NewTextArea);

        _ScrollPanel = ScrollPanel::create();
	    _ScrollPanel->setViewComponent(getTextArea());

        //Create the gutter
        TextAreaGutterRecPtr NewTextAreaGutter = TextAreaGutter::create();
        NewTextAreaGutter->setPreferredSize(Vec2f(35.0f,1.0f));
        NewTextAreaGutter->setFont(TheFont);
        NewTextAreaGutter->setAlignment(Vec2f(1.0f,0.5f));
        NewTextAreaGutter->setInset(Vec4f(5.0f,5.0f,0.0f,0.0f));
        setGutter(NewTextAreaGutter);
    }
}

void AdvancedTextDomArea::resolveLinks(void)
{
    Inherited::resolveLinks();
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

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & TextAreaFieldMask ||
       whichField & GutterFieldMask)
    {
        clearChildren();
        pushToChildren(_ScrollPanel);
        pushToChildren(getGutter());

	    _ScrollPanel->setViewComponent(getTextArea());
        getGutter()->setTrackedArea(getTextArea());
    }
}

void AdvancedTextDomArea::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AdvancedTextDomArea NI" << std::endl;
}

OSG_END_NAMESPACE
