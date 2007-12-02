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

#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "Component/Container/OSGFrame.h"

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

void Slider::drawInternal(const GraphicsPtr TheGraphics) const
{

	//Draw the Major Tick Marks
	if(getDrawMajorTicks())
	{
		for(UInt32 i(0) ; i<getMajorTickPositions().size() ; ++i)
		{
			glPushMatrix();
				glTranslatef(getMajorTickPositions()[i].x(), getMajorTickPositions()[i].y(), 0.0f);
				if(getOrientation() != VERTICAL_ALIGNMENT)
				{
					glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				}

				//Draw the Draw Objects
				for(UInt32 j(0) ; j<getMajorTickDrawObjects().size(); ++j)
				{
					getMajorTickDrawObjects().getValue(j)->draw(TheGraphics);
				}

			glPopMatrix();
		}

	}

	//Draw the Minor Tick Marks
	if(getDrawMinorTicks())
	{
		for(UInt32 i(0) ; i<getMinorTickPositions().size() ; ++i)
		{
			glPushMatrix();
				glTranslatef(getMinorTickPositions()[i].x(), getMinorTickPositions()[i].y(), 0.0f);
				if(getOrientation() != VERTICAL_ALIGNMENT)
				{
					glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				}

				//Draw the Draw Objects
				for(UInt32 j(0) ; j<getMinorTickDrawObjects().size(); ++j)
				{
					getMinorTickDrawObjects().getValue(j)->draw(TheGraphics);
				}

			glPopMatrix();
		}
	}

	
	Inherited::drawInternal(TheGraphics);
}
void Slider::updateLayout(void)
{
	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	
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
	   Vec2s Size(getTrackDrawObject()->getPreferredSize());
	   Pnt2s AlignedPosition;
	   Size[MajorAxis] = getTrackLength();
	   
       AlignedPosition = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), Size, 0.5, 0.5);
	   
	   beginEditCP(getTrackDrawObject(), PositionFieldMask | SizeFieldMask);
	       getTrackDrawObject()->setPosition(AlignedPosition);
	       getTrackDrawObject()->setSize(Size);
	   endEditCP(getTrackDrawObject(), PositionFieldMask | SizeFieldMask);
	}
	
	//Update the MinorTickMarks
	if(getDrawMinorTicks() && _Model != NULL)
	{
		Pnt2s MinorTickTopLeft, MinorTickBottomRight;
		getDrawObjectBounds(getMinorTickDrawObjects(), MinorTickTopLeft, MinorTickBottomRight);
		
	    Vec2f Alignment;

		beginEditCP(SliderPtr(this), MinorTickPositionsFieldMask);
			getMinorTickPositions().clear();

			for(UInt32 i(0) ; i< osgabs<Int32>(getMaximum() - getMinimum())/getMinorTickSpacing() ; ++i)
			{
				if( (i * getMinorTickSpacing())%getMajorTickSpacing() != 0 )
				{
					Alignment[MajorAxis] = static_cast<Real32>(i * getMinorTickSpacing())/static_cast<Real32>(getMaximum() - getMinimum());
					getMinorTickPositions().push_back(
						calculateSliderAlignment(getTrackDrawObject()->getPosition(), getTrackDrawObject()->getSize(), (MinorTickBottomRight - MinorTickTopLeft), Alignment.y(), Alignment.x()));
					getMinorTickPositions().back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToTickOffset();
				}
			}
		
		endEditCP(SliderPtr(this), MinorTickPositionsFieldMask);
	}
	
	//Update the MajorTickMarks
	if(getDrawMajorTicks() && _Model != NULL)
	{
		Pnt2s MajorTickTopLeft, MajorTickBottomRight;
		getDrawObjectBounds(getMajorTickDrawObjects(), MajorTickTopLeft, MajorTickBottomRight);
		
	    Vec2f Alignment;

		beginEditCP(SliderPtr(this), MajorTickPositionsFieldMask);
			getMajorTickPositions().clear();

			for(UInt32 i(0) ; i<= osgabs<Int32>(getMaximum() - getMinimum())/getMajorTickSpacing() ; ++i)
			{
		        Alignment[MajorAxis] = static_cast<Real32>(i * getMajorTickSpacing())/static_cast<Real32>(getMaximum() - getMinimum());
				getMajorTickPositions().push_back(
					calculateSliderAlignment(getTrackDrawObject()->getPosition(), getTrackDrawObject()->getSize(), (MajorTickBottomRight - MajorTickTopLeft), Alignment.y(), Alignment.x()));
				getMajorTickPositions().back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToTickOffset();
			}
		
		endEditCP(SliderPtr(this), MajorTickPositionsFieldMask);
	}

	//Update the Labels
	if(getDrawLabels())
	{
	}
}

void Slider::updateSliderTrack(void)
{
	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	
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
	if(getKnobButton() != NullFC && _Model != NULL)
	{
	   Vec2s Size;
	   Size[MinorAxis] = getKnobButton()->getPreferredSize().x();
	   Size[MajorAxis] = getKnobButton()->getPreferredSize().y();
	   Pnt2s AlignedPosition;
	   //Size[MajorAxis] = getSize()[MajorAxis] - 2;
	   Vec2f Alignment(0.5,0.5);
	   Alignment[MajorAxis] = static_cast<Real32>(getValue() - getMinimum())/static_cast<Real32>(getMaximum() - getMinimum());
	   
       AlignedPosition = calculateSliderAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), getKnobButton()->getPreferredSize(), Alignment.y(), Alignment.x());
	   
	   beginEditCP(getKnobButton(), PositionFieldMask | SizeFieldMask);
	       getKnobButton()->setPosition(AlignedPosition);
	       getKnobButton()->setSize(Size);
	   endEditCP(getKnobButton(), PositionFieldMask | SizeFieldMask);
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

UInt32 Slider::getTrackLength(void) const
{
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        return getSize().y() - 2 * getTrackInset();
    }
    else
    {
        return getSize().x() - 2 * getTrackInset();
    }
}

Int32 Slider::getTrackMin(void) const
{
    return getTrackInset();
}

Int32 Slider::getTrackMax(void) const
{
    return getTrackMin() + getTrackLength();
}

void Slider::setValue(Int32 n)
{
    if(getSnapToTicks())
    {
        //Determine the closest tickmark to the value we are trying to set

		Int32 Div, Mod;

		Div = (n-getMinimum())/getMinorTickSpacing();
		Mod = (n-getMinimum())%getMinorTickSpacing();

		if(Mod <= getMajorTickSpacing()/2)
		{
			_Model->setValue(getMinorTickSpacing() * Div + getMinimum());
		}
		else
		{
			_Model->setValue(getMinorTickSpacing() * (Div + 1) + getMinimum());
		}
    }
    else
    {
	   _Model->setValue(n);
    }
    
}

Pnt2s Slider::calculateSliderAlignment(const Pnt2s& Position1, const Vec2s& Size1, const Vec2s& Size2, const Real32& VAlign, const Real32& HAlign)
{
	Vec2s CorrectedSize2(Size2);

	if(getOrientation() != VERTICAL_ALIGNMENT)
	{
		CorrectedSize2[0] = Size2.y();
		CorrectedSize2[1] = Size2.x();
	}

	if(getInverted())
	{
		if(getOrientation() == VERTICAL_ALIGNMENT)
		{
			return calculateAlignment(Position1, Size1, CorrectedSize2, (1.0-VAlign), HAlign);
		}
		else
		{
			return calculateAlignment(Position1, Size1, CorrectedSize2, VAlign, (1.0 - HAlign));
		}
	}
	else
	{
		return calculateAlignment(Position1, Size1, CorrectedSize2, VAlign, HAlign);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Slider::Slider(void) :
    Inherited(),
		_Model(NULL),
        _BoundedRangeModelChangeListener(SliderPtr(this)),
        _KnobDraggedListener(SliderPtr(this))
{
}

Slider::Slider(const Slider &source) :
    Inherited(source),
		_Model(source._Model),
        _BoundedRangeModelChangeListener(SliderPtr(this)),
        _KnobDraggedListener(SliderPtr(this))
{
    if(getKnobButton() != NullFC)
    {
        beginEditCP(SliderPtr(this), KnobButtonFieldMask);
            setKnobButton(Button::Ptr::dcast(getKnobButton()->shallowCopy()));
        endEditCP(SliderPtr(this), KnobButtonFieldMask);
    }
    if(getTrackDrawObject() != NullFC)
    {
        beginEditCP(SliderPtr(this), TrackDrawObjectFieldMask);
            setTrackDrawObject(UIDrawObjectCanvas::Ptr::dcast(getTrackDrawObject()->shallowCopy()));
        endEditCP(SliderPtr(this), TrackDrawObjectFieldMask);
    }
    if(getMinTrackDrawObject() != NullFC)
    {
        beginEditCP(SliderPtr(this), MinTrackDrawObjectFieldMask);
            setMinTrackDrawObject(UIDrawObjectCanvas::Ptr::dcast(getMinTrackDrawObject()->shallowCopy()));
        endEditCP(SliderPtr(this), MinTrackDrawObjectFieldMask);
    }
    if(getMaxTrackDrawObject() != NullFC)
    {
        beginEditCP(SliderPtr(this), MaxTrackDrawObjectFieldMask);
            setMaxTrackDrawObject(UIDrawObjectCanvas::Ptr::dcast(getMaxTrackDrawObject()->shallowCopy()));
        endEditCP(SliderPtr(this), MaxTrackDrawObjectFieldMask);
    }
}

Slider::~Slider(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Slider::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & KnobButtonFieldMask) ||
       (whichField & TrackDrawObjectFieldMask) ||
       (whichField & MinTrackDrawObjectFieldMask) ||
       (whichField & MaxTrackDrawObjectFieldMask) ||
       (whichField & DrawTrackFieldMask))
    {
        beginEditCP(SliderPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getDrawTrack())
            {
                if(getTrackDrawObject() != NullFC)
                {
                    getChildren().push_back(getTrackDrawObject());
                }
                if(getMinTrackDrawObject() != NullFC)
                {
                    getChildren().push_back(getMinTrackDrawObject());
                }
                if(getMaxTrackDrawObject() != NullFC)
                {
                    getChildren().push_back(getMaxTrackDrawObject());
                }
            }
            if(getKnobButton() != NullFC)
            {
                getChildren().push_back(getKnobButton());
            }
        endEditCP(SliderPtr(this), ChildrenFieldMask);
    }
    
    if((whichField & KnobButtonFieldMask) ||
       (whichField & TrackDrawObjectFieldMask) ||
       (whichField & MinTrackDrawObjectFieldMask) ||
       (whichField & MaxTrackDrawObjectFieldMask) ||
       (whichField & InvertedFieldMask) ||
       (whichField & DrawLabelsFieldMask) ||
       (whichField & DrawTrackFieldMask) ||
       (whichField & OrientationFieldMask))
    {
        updateLayout();
    }

    if(whichField & KnobButtonFieldMask &&
       getKnobButton() != NullFC)
    {
        getKnobButton()->addMouseListener(&_KnobDraggedListener);
    }
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


void Slider::KnobDraggedListener::mouseDragged(const MouseEvent& e)
{
	if(e.getButton() == e.BUTTON1)
	{
		Pnt2s MousePosInComponent = ViewportToComponent(e.getLocation(), _Slider, e.getViewport());
		
        Pnt2s BorderTopLeft, BorderBottomRight;
        _Slider->getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
        
        UInt16 MajorAxis, MinorAxis;
        if(_Slider->getOrientation() == VERTICAL_ALIGNMENT)
        {
            MajorAxis = 1;
        }
        else
        {
            MajorAxis = 0;
        }
        MinorAxis = (MajorAxis+1)%2;

		if(_Slider->getInverted())
		{
			MousePosInComponent[MajorAxis] = _Slider->getTrackMax() - (MousePosInComponent[MajorAxis] - _Slider->getTrackMin());
		}
        
        _Slider->setValue( _Slider->getMinimum() + (_Slider->getMaximum() - _Slider->getMinimum()) * (MousePosInComponent[MajorAxis] - _Slider->getTrackMin())/static_cast<Int32>(_Slider->getTrackLength()) );
	}
}

void Slider::KnobDraggedListener::mousePressed(const MouseEvent& e)
{
    if(e.getButton() == e.BUTTON1 &&
       _Slider->getParentFrame() != NullFC &&
       _Slider->getParentFrame()->getDrawingSurface() != NullFC &&
       _Slider->getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
    {
        _Slider->getParentFrame()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(this);
    }
}

void Slider::KnobDraggedListener::mouseReleased(const MouseEvent& e)
{
    if(e.getButton() == e.BUTTON1 &&
       _Slider->getParentFrame() != NullFC &&
       _Slider->getParentFrame()->getDrawingSurface() != NullFC &&
       _Slider->getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
    {
        _Slider->getParentFrame()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
    }
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

