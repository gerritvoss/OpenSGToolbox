/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGProgressBar.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "Util/OSGUIDrawUtils.h"
#include <sstream>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ProgressBar
A UI Spinner. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProgressBar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Color4f ProgressBar::getDrawnTextColor(void) const
{
    if(getEnabled())
    {
        if(getFocused())
        {
            return getFocusedTextColor();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverTextColor();
        }
        else
        {
            return getTextColor();
        }
    }
    else
    {
        return getDisabledTextColor();
    }
}

UIDrawObjectCanvasPtr ProgressBar::getDrawnDrawObject(void) const
{
    if(getEnabled())
    {
        if(getFocused())
        {
            return getFocusedDrawObject();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverDrawObject();
        }
        else
        {
            return getDrawObject();
        }
    }
    else
    {
        return getDisabledDrawObject();
    }
}

void ProgressBar::drawInternal(const GraphicsPtr Graphics) const
{

	//Draw The ProgressBar
    UIDrawObjectCanvasPtr DrawObject(getDrawnDrawObject());
    if(DrawObject != NullFC)
    {
		beginEditCP(DrawObject , SizeFieldMask | PositionFieldMask);
            DrawObject->setPosition(_ProgressBarPosition);
            DrawObject->setSize(_ProgressBarSize);
		endEditCP(DrawObject , SizeFieldMask | PositionFieldMask);
        DrawObject->draw(Graphics);
    }
	
	//Draw The Progress String
	if(getEnableProgressString() && getFont() != NullFC)
	{
		Pnt2f TopLeft, BottomRight;
		getInsideBorderBounds(TopLeft, BottomRight);

		//Draw the progress String
		std::string StringToDraw;
		if(getProgressString().compare("") == 0)
		{
            if(!getIndeterminate())
            {
			    UInt32 Percent(static_cast<Int32>( osgfloor(getPercentComplete() * 100.0f) ));

			    std::stringstream TempSStream;
			    TempSStream << Percent;

			    StringToDraw = TempSStream.str() + std::string("%");
            }
		}
		else
		{
			StringToDraw = getProgressString();
		}

		//Calculate Alignment
		Pnt2f AlignedPosition;
		Pnt2f TextTopLeft, TextBottomRight;
		getFont()->getBounds(StringToDraw, TextTopLeft, TextBottomRight);

		AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),getVerticalAlignment(), getHorizontalAlignment());

		//Draw the Text
		Graphics->drawText(AlignedPosition, StringToDraw, getFont(), getDrawnTextColor(), getOpacity());
	}
}

void ProgressBar::setupProgressBar(void)
{

    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);
   
	if(getIndeterminate())
	{
		Real32 Pos;
		if(_IndeterminateBarPosition > 1.0)
		{
			Pos = 2.0 - _IndeterminateBarPosition;
		}
		else
		{
			Pos = _IndeterminateBarPosition;
		}
			switch(getOrientation())
			{
			case ProgressBar::HORIZONTAL_ORIENTATION:
                _ProgressBarPosition.setValues((BottomRight.x() - TopLeft.x())*Pos*(1.0-getIndeterminateBarSize()), TopLeft.y());
                _ProgressBarSize.setValues( (BottomRight.x() - TopLeft.x())*getIndeterminateBarSize(),BottomRight.y() - TopLeft.y());
				break;
			case ProgressBar::VERTICAL_ORIENTATION:
			default:
                _ProgressBarPosition.setValues( Pos*(BottomRight.x() - TopLeft.x())*(1.0-getIndeterminateBarSize()), TopLeft.y());
                _ProgressBarSize.setValues( TopLeft.x(), Pos*(BottomRight.y() - TopLeft.y())*(1.0-getIndeterminateBarSize()));
				break;
			}
	}
	else
	{
		if(_Model == NULL) {return;}

		Real32 Percent(getPercentComplete());

        _ProgressBarPosition = TopLeft;
		switch(getOrientation())
		{
		case ProgressBar::HORIZONTAL_ORIENTATION:
            _ProgressBarSize.setValues( (BottomRight.x() - TopLeft.x())*Percent,BottomRight.y() - TopLeft.y());
			break;
		case ProgressBar::VERTICAL_ORIENTATION:
		default:
            _ProgressBarSize.setValues( BottomRight.x() - TopLeft.x(),(BottomRight.y() - TopLeft.y())*Percent);
			break;
		}
	}
}

void ProgressBar::setupIndeterminateProgressBar(const Time& Elps)
{
	_IndeterminateBarPosition += Elps * getIndeterminateBarMoveRate();
	if(_IndeterminateBarPosition > 2.0)
	{
		_IndeterminateBarPosition -= 2.0f*osgfloor(_IndeterminateBarPosition/2.0f);
	}
	setupProgressBar();
}

void ProgressBar::startIndeterminate(void)
{
    beginEditCP(ProgressBarPtr(this), IndeterminateFieldMask);
        setIndeterminate(true);
    endEditCP(ProgressBarPtr(this), IndeterminateFieldMask);
    _IndeterminateBarPosition = 0;
	if(getParentWindow() != NullFC &&
		getParentWindow()->getDrawingSurface() != NullFC &&
		getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
        getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_IndeterminateUpdateListener);
	}
}

void ProgressBar::endIndeterminate(void)
{
    beginEditCP(ProgressBarPtr(this), IndeterminateFieldMask);
        setIndeterminate(false);
    endEditCP(ProgressBarPtr(this), IndeterminateFieldMask);
	if(getParentWindow() != NullFC &&
		getParentWindow()->getDrawingSurface() != NullFC &&
		getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
        getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&_IndeterminateUpdateListener);
	}
    setupProgressBar();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ProgressBar::ProgressBar(void) :
    Inherited(),
	_Model(NULL),
	_ModelChangeListener(ProgressBarPtr(this)),
	_IndeterminateUpdateListener(ProgressBarPtr(this)),
    _IndeterminateBarPosition(0)
{
}

ProgressBar::ProgressBar(const ProgressBar &source) :
    Inherited(source),
	_Model(NULL),
	_ModelChangeListener(ProgressBarPtr(this)),
	_IndeterminateUpdateListener(ProgressBarPtr(this)),
    _IndeterminateBarPosition(0),
    _ProgressBarPosition(source._ProgressBarPosition),
    _ProgressBarSize(source._ProgressBarSize)
{
}

ProgressBar::~ProgressBar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ProgressBar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & SizeFieldMask))
    {
        setupProgressBar();
    }
}

void ProgressBar::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ProgressBar NI" << std::endl;
}


void ProgressBar::ModelChangeListener::stateChanged(const ChangeEvent& e)
{
	_ProgressBar->setupProgressBar();
}

void ProgressBar::IndeterminateUpdateListener::update(const UpdateEvent& e)
{
	_ProgressBar->setupIndeterminateProgressBar(e.getElapsedTime());
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
    static Char8 cvsid_hpp       [] = OSGPROGRESSBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPROGRESSBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPROGRESSBARFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

