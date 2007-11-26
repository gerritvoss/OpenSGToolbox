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

#include "OSGSlider.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Slider
A UI Spinner. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Slider::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Slider::updateLayout(void)
{
    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

	updateSliderTrack();

	
	//Update the Track
	if(getDrawTrack() && getTrackDrawObject() != NullFC)
	{
	}
	
	//Update the MinTickMarks
	if(getDrawMinorTicks())
	{
	}
	
	//Update the MaxTickMarks
	if(getDrawMajorTicks())
	{
	}

	//Update the Labels
	if(getDrawLabels())
	{
	}
}

void Slider::updateSliderTrack(void)
{
    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

	//Update the Min Track
	if(getDrawTrack() && getMinTrackDrawObject() != NullFC)
	{
	}

	//Update the Max Track
	if(getDrawTrack() && getMaxTrackDrawObject() != NullFC)
	{
	}

	//Update the Knob position
	if(getDrawTrack() && getKnobButton() != NullFC)
	{
	}

}

FieldContainerMap Slider::createStandardLabels(UInt32 increment)
{
	//TODO: Implement
	return FieldContainerMap();
}

FieldContainerMap Slider::createStandardLabels(UInt32 increment, Int32 start)
{
	//TODO: Implement
	return FieldContainerMap();
}

void Slider::setModel(BoundedRangeModel* Model)
{
    if(_Model != NULL)
    {
        _Model->removeChangeListener(&_BoundedRangeModelChangeListener);
    }
    _Model = Model;
    if(_Model != NULL)
    {
        _Model->addChangeListener(&_BoundedRangeModelChangeListener);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Slider::Slider(void) :
    Inherited(),
        _BoundedRangeModelChangeListener(SliderPtr(this))
{
}

Slider::Slider(const Slider &source) :
    Inherited(source),
        _BoundedRangeModelChangeListener(SliderPtr(this))
{
}

Slider::~Slider(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Slider::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Slider::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Slider NI" << std::endl;
}

void Slider::BoundedRangeModelChangeListener::stateChanged(const ChangeEvent& e)
{
    _Slider->updateLayout();
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
    static Char8 cvsid_hpp       [] = OSGSLIDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSLIDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSLIDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

