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
#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Text/OSGLabel.h"
#include <sstream>

#include <boost/bind.hpp>

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

EventConnection Slider::addChangeListener(ChangeListenerPtr l)
{
	return _Model->addChangeListener(l);
}

void Slider::drawInternal(const GraphicsPtr TheGraphics) const
{

	//Draw the Major Tick Marks
	if(getDrawMajorTicks())
	{
		for(UInt32 i(0) ; i<getMajorTickPositions().size() ; ++i)
		{
			glPushMatrix();
				glTranslatef(getMajorTickPositions()[i].x(), getMajorTickPositions()[i].y(), 0.0f);
				if(getOrientation() != VERTICAL_ORIENTATION)
				{
					glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				}

				//Draw the Draw Objects
				for(UInt32 j(0) ; j<getMajorTickDrawObjects().size(); ++j)
				{
					getMajorTickDrawObjects()[j]->draw(TheGraphics);
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
				if(getOrientation() != VERTICAL_ORIENTATION)
				{
					glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				}

				//Draw the Draw Objects
				for(UInt32 j(0) ; j<getMinorTickDrawObjects().size(); ++j)
				{
					getMinorTickDrawObjects()[j]->draw(TheGraphics);
				}

			glPopMatrix();
		}
	}

	
	Inherited::drawInternal(TheGraphics);
}

void Slider::updateLayout(void)
{
	
    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == VERTICAL_ORIENTATION)
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
		Pnt2f BorderTopLeft, BorderBottomRight;
		getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

	   Vec2f Size(getTrackDrawObject()->getPreferredSize());
	   Pnt2f AlignedPosition;
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
		Pnt2f MinorTickTopLeft, MinorTickBottomRight;
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
						calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), (MinorTickBottomRight - MinorTickTopLeft), Alignment.y(), Alignment.x()));
					getMinorTickPositions().back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToTickOffset();
				}
			}
		
		endEditCP(SliderPtr(this), MinorTickPositionsFieldMask);
	}
	
	//Update the MajorTickMarks
	if(getDrawMajorTicks() && _Model != NULL)
	{
		Pnt2f MajorTickTopLeft, MajorTickBottomRight;
		getDrawObjectBounds(getMajorTickDrawObjects(), MajorTickTopLeft, MajorTickBottomRight);
		
	    Vec2f Alignment;

		beginEditCP(SliderPtr(this), MajorTickPositionsFieldMask);
			getMajorTickPositions().clear();

			for(UInt32 i(0) ; i<= osgabs<Int32>(getMaximum() - getMinimum())/getMajorTickSpacing() ; ++i)
			{
		        Alignment[MajorAxis] = static_cast<Real32>(i * getMajorTickSpacing())/static_cast<Real32>(getMaximum() - getMinimum());
				getMajorTickPositions().push_back(
					calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), (MajorTickBottomRight - MajorTickTopLeft), Alignment.y(), Alignment.x()));
				getMajorTickPositions().back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToTickOffset();
			}
		
		endEditCP(SliderPtr(this), MajorTickPositionsFieldMask);
	}

	//Update the Labels
	if(getDrawLabels() && _Model != NULL)
	{
		Vec2f Alignment;
		Pnt2f Pos;
		FieldContainerMap::iterator Itor;
		for(Itor = getLabelMap().begin() ; Itor != getLabelMap().end() ; ++Itor)
		{
			Alignment[MajorAxis] = static_cast<Real32>((*Itor).first - getMinimum())/static_cast<Real32>(getMaximum() - getMinimum());
			Pos = calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), Component::Ptr::dcast((*Itor).second)->getPreferredSize(), Alignment.y(), Alignment.x());
			Pos[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToLabelOffset();

			beginEditCP(Component::Ptr::dcast((*Itor).second), PositionFieldMask | SizeFieldMask);
				Component::Ptr::dcast((*Itor).second)->setPosition(Pos);
				Component::Ptr::dcast((*Itor).second)->setSize(Component::Ptr::dcast((*Itor).second)->getPreferredSize());
			endEditCP(Component::Ptr::dcast((*Itor).second), PositionFieldMask | SizeFieldMask);
		}
	}
}

void Slider::updateSliderTrack(void)
{
	Pnt2f BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	
    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == VERTICAL_ORIENTATION)
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
	   Vec2f Size;
	   Size[MinorAxis] = getKnobButton()->getPreferredSize().x();
	   Size[MajorAxis] = getKnobButton()->getPreferredSize().y();
	   Pnt2f AlignedPosition;
	   //Size[MajorAxis] = getSize()[MajorAxis] - 2;
	   Vec2f Alignment(0.5,0.5);
	   Alignment[MajorAxis] = static_cast<Real32>(getValue() - getMinimum())/static_cast<Real32>(getMaximum() - getMinimum());
	   
       AlignedPosition = calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), getKnobButton()->getPreferredSize(), Alignment.y(), Alignment.x());
	   
	   beginEditCP(getKnobButton(), PositionFieldMask | SizeFieldMask);
	       getKnobButton()->setPosition(AlignedPosition);
	       getKnobButton()->setSize(Size);
	   endEditCP(getKnobButton(), PositionFieldMask | SizeFieldMask);
	}

}

Pnt2f Slider::getSliderTrackTopLeft(void) const
{
	Pnt2f BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

	Pnt2f Pos;
	
    if(getOrientation() == VERTICAL_ORIENTATION)
    {
		Pos = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), Vec2f(0,0), 0.0, 0.5);
		Pos[1] += getTrackInset();
    }
    else
    {
		Pos = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), Vec2f(0,0), 0.5, 0.0);
		Pos[0] += getTrackInset();
    }

	return Pos;
}

Vec2f Slider::getSliderTrackSize(void) const
{
    if(getOrientation() == VERTICAL_ORIENTATION)
    {
		return Vec2f(0, getTrackLength());
    }
    else
    {
		return Vec2f(getTrackLength(), 0);
    }
}

FieldContainerMap Slider::createStandardLabels(UInt32 increment, Int32 start)
{
	FieldContainerMap NewMap;
	for(Int32 i(start) ; i<=getMaximum() ; i += increment)
	{
		LabelPtr NewLabel;
		NewLabel = Label::Ptr::dcast(getLabelPrototype()->shallowCopy());

		std::stringstream TempSStream;
		TempSStream << i;

		beginEditCP(NewLabel, Label::TextFieldMask);
			NewLabel->setText(TempSStream.str());
		endEditCP(NewLabel, Label::TextFieldMask);

		NewMap[i] = NewLabel;
	}

	return NewMap;
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
		
		if( getDrawLabels() &&
			_UsingDefaultLabels)
		{
			beginEditCP(SliderPtr(this), LabelMapFieldMask);
				setLabelMap(createStandardLabels(getMajorTickSpacing()));
			endEditCP(SliderPtr(this), LabelMapFieldMask);
			_UsingDefaultLabels = true;
		}
    }
}

UInt32 Slider::getTrackLength(void) const
{
    if(getOrientation() == VERTICAL_ORIENTATION)
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

Pnt2f Slider::calculateSliderAlignment(const Pnt2f& Position1, const Vec2f& Size1, const Vec2f& Size2, const Real32& VAlign, const Real32& HAlign)
{
	Vec2f CorrectedSize2(Size2);

	if(getOrientation() != VERTICAL_ORIENTATION)
	{
		CorrectedSize2[0] = Size2.y();
		CorrectedSize2[1] = Size2.x();
	}

	Real32 CorrectedVAlign(VAlign),
		   CorrectedHAlign(HAlign);

	if(getInverted())
	{
		if(getOrientation() == VERTICAL_ORIENTATION)
		{
			CorrectedVAlign = (1.0-VAlign);
		}
		else
		{
			CorrectedHAlign = (1.0-HAlign);
		}
	}
	
	Pnt2f AlignedPosition;

	AlignedPosition[0] = Position1[0]-CorrectedSize2[0]/2+CorrectedHAlign*(Size1[0]);
	AlignedPosition[1] = Position1[1]-CorrectedSize2[1]/2+CorrectedVAlign*(Size1[1]);
	
	return AlignedPosition;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Slider::Slider(void) :
    Inherited(),
		_Model(NULL),
        _BoundedRangeModelChangeListener(SliderPtr(this)),
        _KnobDraggedListener(SliderPtr(this)),
		_UsingDefaultLabels(true)
{
}

Slider::Slider(const Slider &source) :
    Inherited(source),
		_Model(source._Model),
        _BoundedRangeModelChangeListener(SliderPtr(this)),
        _KnobDraggedListener(SliderPtr(this)),
		_UsingDefaultLabels(source._UsingDefaultLabels)
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
	if((whichField & LabelMapFieldMask))
	{
		_UsingDefaultLabels = (getLabelMap().size() == 0);
	}

	if( ((whichField & DrawLabelsFieldMask) ||
	     (whichField & LabelPrototypeFieldMask) ||
	     (whichField & MajorTickSpacingFieldMask))&&
		 getDrawLabels() &&
		 _Model != NULL &&
		 _UsingDefaultLabels)
	{
		beginEditCP(SliderPtr(this), LabelMapFieldMask);
			setLabelMap(createStandardLabels(getMajorTickSpacing()));
		endEditCP(SliderPtr(this), LabelMapFieldMask);
		_UsingDefaultLabels = true;
	}

    if((whichField & KnobButtonFieldMask) ||
       (whichField & TrackDrawObjectFieldMask) ||
       (whichField & MinTrackDrawObjectFieldMask) ||
       (whichField & MaxTrackDrawObjectFieldMask) ||
       (whichField & DrawTrackFieldMask) ||
       (whichField & DrawLabelsFieldMask) ||
       (whichField & LabelMapFieldMask) ||
       (whichField & LabelPrototypeFieldMask))
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
			
            if(getDrawLabels())
            {
				FieldContainerMap::iterator Itor;
				for(Itor = getLabelMap().begin() ; Itor != getLabelMap().end() ; ++Itor)
				{
					getChildren().push_back(Component::Ptr::dcast((*Itor).second));
				}
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
       (whichField & OrientationFieldMask) ||
       (whichField & MinorTickSpacingFieldMask) ||
       (whichField & MajorTickSpacingFieldMask) ||
       (whichField & LabelMapFieldMask) ||
       (whichField & LabelPrototypeFieldMask))
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
		Pnt2f MousePosInComponent = ViewportToComponent(e.getLocation(), _Slider, e.getViewport());
		
        Pnt2f BorderTopLeft, BorderBottomRight;
        _Slider->getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
        
        UInt16 MajorAxis, MinorAxis;
        if(_Slider->getOrientation() == VERTICAL_ORIENTATION)
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
		_Slider->getEnabled() &&
       _Slider->getParentWindow() != NullFC &&
       _Slider->getParentWindow()->getDrawingSurface() != NullFC &&
       _Slider->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_InitialValue = _Slider->getValue();
        _Slider->getKnobButton()->removeMouseListener(this);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(this);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(this);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(this);
		_Slider->_Model->setValueIsAdjusting(true);
    }
}

void Slider::KnobDraggedListener::mouseReleased(const MouseEvent& e)
{
    if(e.getButton() == e.BUTTON1 &&
       _Slider->getParentWindow() != NullFC &&
       _Slider->getParentWindow()->getDrawingSurface() != NullFC &&
       _Slider->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
        _Slider->getKnobButton()->addMouseListener(this);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
		_Slider->_Model->setValueIsAdjusting(false);
    }
}

void Slider::KnobDraggedListener::keyTyped(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE)
	{
		_Slider->setValue(_InitialValue);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
        _Slider->getKnobButton()->addMouseListener(this);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
        _Slider->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
		_Slider->_Model->setValueIsAdjusting(false);
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

