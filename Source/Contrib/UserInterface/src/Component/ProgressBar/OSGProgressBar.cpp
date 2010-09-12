/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <OSGConfig.h>

#include "OSGProgressBar.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGUIDrawUtils.h"
#include <sstream>

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGProgressBarBase.cpp file.
// To modify it, please change the .fcd file (OSGProgressBar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProgressBar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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

UIDrawObjectCanvas* ProgressBar::getDrawnDrawObject(void) const
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

void ProgressBar::drawInternal(Graphics* const Graphics, Real32 Opacity) const
{

	//Draw The ProgressBar
    UIDrawObjectCanvasRefPtr DrawObject(getDrawnDrawObject());
    if(DrawObject != NULL)
    {
        if(DrawObject->getPosition() != _ProgressBarPosition)
        {
            DrawObject->setPosition(_ProgressBarPosition);
        }
        if(DrawObject->getSize() != _ProgressBarSize)
        {
            DrawObject->setSize(_ProgressBarSize);
        }
        DrawObject->draw(Graphics,getOpacity()*Opacity);
    }
	
	//Draw The Progress String
	if(getEnableProgressString() && getFont() != NULL)
	{
		Pnt2f TopLeft, BottomRight;
		getInsideBorderBounds(TopLeft, BottomRight);

		//Draw the progress String
		std::string StringToDraw;
		if(getProgressString().compare("") == 0)
		{
            if(!getIndeterminate())
            {
			    UInt32 Percent(static_cast<Int32>( osgFloor(getPercentComplete() * 100.0f) ));

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

		AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),getAlignment().y(), getAlignment().x());

		//Draw the Text
		Graphics->drawText(AlignedPosition, StringToDraw, getFont(), getDrawnTextColor(), getOpacity()*Opacity);
	}
}

void ProgressBar::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _ProgressStateChangedConnection.disconnect();
    _ProgressUpdateConnection.disconnect();

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
		if(getRangeModel() == NULL) {return;}

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
		_IndeterminateBarPosition -= 2.0f*osgFloor(_IndeterminateBarPosition/2.0f);
	}
	setupProgressBar();
}

void ProgressBar::startIndeterminate(void)
{
    _ProgressUpdateConnection.disconnect();
    setIndeterminate(true);
    _IndeterminateBarPosition = 0;
	if(getParentWindow() != NULL &&
		getParentWindow()->getParentDrawingSurface() != NULL &&
		getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
	{
        _ProgressUpdateConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&ProgressBar::handleProgressUpdate, this, _1));
	}
}

void ProgressBar::endIndeterminate(void)
{
    setIndeterminate(false);
    _ProgressUpdateConnection.disconnect();
    setupProgressBar();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ProgressBar::ProgressBar(void) :
    Inherited(),
    _IndeterminateBarPosition(0)
{
}

ProgressBar::ProgressBar(const ProgressBar &source) :
    Inherited(source),
    _IndeterminateBarPosition(0),
    _ProgressBarPosition(source._ProgressBarPosition),
    _ProgressBarSize(source._ProgressBarSize)
{
}

ProgressBar::~ProgressBar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ProgressBar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & SizeFieldMask))
    {
        setupProgressBar();
    }
    if(whichField & RangeModelFieldMask)
    {
        _ProgressStateChangedConnection.disconnect();
        if(getRangeModel() != NULL)
        {
            _ProgressStateChangedConnection = getRangeModel()->connectStateChanged(boost::bind(&ProgressBar::handleProgressStateChanged, this, _1));
        }
    }
}

void ProgressBar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ProgressBar NI" << std::endl;
}

void ProgressBar::handleProgressStateChanged(ChangeEventDetails* const e)
{
	setupProgressBar();
}

void ProgressBar::handleProgressUpdate(UpdateEventDetails* const e)
{
	setupIndeterminateProgressBar(e->getElapsedTime());
}

OSG_END_NAMESPACE
