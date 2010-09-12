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

#include "OSGSlider.h"
#include "OSGUIDrawUtils.h"

#include "OSGWindowEventProducer.h"
#include "OSGUIDrawingSurface.h"
#include "OSGInternalWindow.h"
#include "OSGLabel.h"
#include <sstream>

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSliderBase.cpp file.
// To modify it, please change the .fcd file (OSGSlider.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Slider::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Slider::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{

    //Draw the Major Tick Marks
    if(getDrawMajorTicks())
    {
        for(UInt32 i(0) ; i<getMFMajorTickPositions()->size() ; ++i)
        {
            glPushMatrix();
            glTranslatef(getMajorTickPositions(i).x(), getMajorTickPositions(i).y(), 0.0f);
            if(getOrientation() != VERTICAL_ORIENTATION)
            {
                glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            }

            //Draw the Draw Objects
            for(UInt32 j(0) ; j<getMFMajorTickDrawObjects()->size(); ++j)
            {
                getMajorTickDrawObjects(j)->draw(TheGraphics,getOpacity()*Opacity);
            }

            glPopMatrix();
        }

    }

    //Draw the Minor Tick Marks
    if(getDrawMinorTicks())
    {
        for(UInt32 i(0) ; i<getMFMinorTickPositions()->size() ; ++i)
        {
            glPushMatrix();
            glTranslatef(getMinorTickPositions(i).x(), getMinorTickPositions(i).y(), 0.0f);
            if(getOrientation() != VERTICAL_ORIENTATION)
            {
                glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            }

            //Draw the Draw Objects
            for(UInt32 j(0) ; j<getMFMinorTickDrawObjects()->size(); ++j)
            {
                getMinorTickDrawObjects(j)->draw(TheGraphics, getOpacity()*Opacity);
            }

            glPopMatrix();
        }
    }


    Inherited::drawInternal(TheGraphics,Opacity);
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
    if(getDrawTrack() && getTrackDrawObject() != NULL)
    {
        Pnt2f BorderTopLeft, BorderBottomRight;
        getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

        Vec2f Size(getTrackDrawObject()->getPreferredSize());
        Pnt2f AlignedPosition;
        Size[MajorAxis] = getTrackLength();

        if(getOrientation() == VERTICAL_ORIENTATION)
        {
            AlignedPosition = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), Size, 0.5, getAlignment());
        }
        else
        {
            AlignedPosition = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), Size, getAlignment(), 0.5);
        }

        if(getTrackDrawObject()->getPosition() != AlignedPosition)
        {
            getTrackDrawObject()->setPosition(AlignedPosition);
        }
        if(getTrackDrawObject()->getSize() != Size)
        {
            getTrackDrawObject()->setSize(Size);
        }
    }

    //Update the MinorTickMarks
    if(getDrawMinorTicks() && getRangeModel() != NULL)
    {
        Pnt2f MinorTickTopLeft, MinorTickBottomRight;
        getDrawObjectBounds(*editMFMinorTickDrawObjects(), MinorTickTopLeft, MinorTickBottomRight);

        Vec2f Alignment;

        Real32 MaxLength(0.0);
        for(UInt32 i(0) ; i<getMFMinorTickDrawObjects()->size() ; ++i)
        {
            Pnt2f DrawObjectTopLeft, DrawObjectBottomRight;
            getMinorTickDrawObjects(i)->getBounds(DrawObjectTopLeft, DrawObjectBottomRight);
            MaxLength = osgMax(MaxLength, DrawObjectBottomRight.x()-DrawObjectTopLeft.x());
        }
        editMFMinorTickPositions()->clear();

        for(UInt32 i(0) ; i< osgAbs<Int32>(getMaximum() - getMinimum())/getMinorTickSpacing() ; ++i)
        {
            if( (i * getMinorTickSpacing())%getMajorTickSpacing() != 0 )
            {
                Alignment[MajorAxis] = static_cast<Real32>(i * getMinorTickSpacing())/static_cast<Real32>(getMaximum() - getMinimum());
                editMFMinorTickPositions()->push_back(
                                                  calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), (MinorTickBottomRight - MinorTickTopLeft), Alignment.y(), Alignment.x()));
                if(getTicksOnRightBottom())
                {
                    editMFMinorTickPositions()->back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToTickOffset();
                }
                else
                {
                    editMFMinorTickPositions()->back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] - getTrackToTickOffset() - MaxLength;
                }
            }
        }

    }

    //Update the MajorTickMarks
    if(getDrawMajorTicks() && getRangeModel() != NULL)
    {
        Pnt2f MajorTickTopLeft, MajorTickBottomRight;
        getDrawObjectBounds(*editMFMajorTickDrawObjects(), MajorTickTopLeft, MajorTickBottomRight);

        Vec2f Alignment;

        Real32 MaxLength(0.0);
        for(UInt32 i(0) ; i<getMFMajorTickDrawObjects()->size() ; ++i)
        {
            Pnt2f DrawObjectTopLeft, DrawObjectBottomRight;
            getMajorTickDrawObjects(i)->getBounds(DrawObjectTopLeft, DrawObjectBottomRight);
            MaxLength = osgMax(MaxLength, DrawObjectBottomRight.x()-DrawObjectTopLeft.x());
        }
        editMFMajorTickPositions()->clear();

        for(UInt32 i(0) ; i<= osgAbs<Int32>(getMaximum() - getMinimum())/getMajorTickSpacing() ; ++i)
        {
            Alignment[MajorAxis] = static_cast<Real32>(i * getMajorTickSpacing())/static_cast<Real32>(getMaximum() - getMinimum());
            editMFMajorTickPositions()->push_back(
                                              calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), (MajorTickBottomRight - MajorTickTopLeft), Alignment.y(), Alignment.x()));
            if(getTicksOnRightBottom())
            {
                editMFMajorTickPositions()->back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToTickOffset();
            }
            else
            {
                editMFMajorTickPositions()->back()[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] - getTrackToTickOffset() - MaxLength;
            }
        }

    }

    //Update the Labels
    if(getDrawLabels() && getRangeModel() != NULL)
    {
        Vec2f Alignment;
        Pnt2f Pos;
        FieldContainerMap::const_iterator Itor;
        for(Itor = getLabelMap().begin() ; Itor != getLabelMap().end() ; ++Itor)
        {
            Alignment[MajorAxis] = static_cast<Real32>((*Itor).first - getMinimum())/static_cast<Real32>(getMaximum() - getMinimum());
            Pos = calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), dynamic_pointer_cast<Component>((*Itor).second)->getPreferredSize(), Alignment.y(), Alignment.x());
            if(getTicksOnRightBottom())
            {
                Pos[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] + getTrackDrawObject()->getSize()[MinorAxis] + getTrackToLabelOffset();
            }
            else
            {
                Pos[MinorAxis] = getTrackDrawObject()->getPosition()[MinorAxis] - getTrackToLabelOffset() - dynamic_pointer_cast<Component>((*Itor).second)->getPreferredSize()[MinorAxis];
            }

            if(dynamic_pointer_cast<Component>((*Itor).second)->getPosition() != Pos)
            {
                dynamic_pointer_cast<Component>((*Itor).second)->setPosition(Pos);
            }
            if(dynamic_pointer_cast<Component>((*Itor).second)->getSize() != dynamic_pointer_cast<Component>((*Itor).second)->getPreferredSize())
            {
                dynamic_pointer_cast<Component>((*Itor).second)->setSize(dynamic_pointer_cast<Component>((*Itor).second)->getPreferredSize());
            }
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

    //Update the Knob position
    if(getKnobButton() != NULL && getRangeModel() != NULL)
    {
        Vec2f Size;
        Size[MinorAxis] = getKnobButton()->getPreferredSize().x();
        Size[MajorAxis] = getKnobButton()->getPreferredSize().y();
        Pnt2f AlignedPosition;
        //Size[MajorAxis] = getSize()[MajorAxis] - 2;
        Vec2f Alignment(0.5,0.5);
        Alignment[MajorAxis] = static_cast<Real32>(getValue() - getMinimum())/static_cast<Real32>(getMaximum() - getMinimum());

        AlignedPosition = calculateSliderAlignment(getSliderTrackTopLeft(), getSliderTrackSize(), getKnobButton()->getPreferredSize(), Alignment.y(), Alignment.x());

        if(getKnobButton()->getPosition() != AlignedPosition)
        {
            getKnobButton()->setPosition(AlignedPosition);
        }
        if(getKnobButton()->getSize() != Size)
        {
            getKnobButton()->setSize(Size);
        }
    }

}

Pnt2f Slider::getSliderTrackTopLeft(void) const
{
    Pnt2f BorderTopLeft, BorderBottomRight;
    getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

    Pnt2f Pos;

    if(getOrientation() == VERTICAL_ORIENTATION)
    {
        Pos = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), Vec2f(0,0), 0.0, getAlignment());
        Pos[1] += getTrackInset();
    }
    else
    {
        Pos = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), Vec2f(0,0), getAlignment(), 0.0);
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
        LabelRefPtr NewLabel;
        NewLabel = dynamic_pointer_cast<Label>(getLabelPrototype()->shallowCopy());

        std::stringstream TempSStream;
        TempSStream << i;

        NewLabel->setText(TempSStream.str());

        NewMap[i] = NewLabel;
    }

    return NewMap;
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
            getRangeModel()->setValue(getMinorTickSpacing() * Div + getMinimum());
        }
        else
        {
            getRangeModel()->setValue(getMinorTickSpacing() * (Div + 1) + getMinimum());
        }
    }
    else
    {
        getRangeModel()->setValue(n);
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

void Slider::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _RangeModelStateChangedConnection.disconnect();
    _KnobDragMouseDraggedConnection.disconnect();
    _KnobMousePressedConnection.disconnect();
    _KnobDragMouseReleasedConnection.disconnect();
    _KnobDragkeyTypedConnection.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Slider::onCreate(const Slider * Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL)
    {
        FieldContainerUnrecPtr TheFC(NULL);

        if(Id->getKnobButton() != NULL)
        {
            TheFC = Id->getKnobButton()->shallowCopy();
            setKnobButton(dynamic_pointer_cast<Button>(TheFC));
        }
        if(Id->getTrackDrawObject() != NULL)
        {
            TheFC = Id->getTrackDrawObject()->shallowCopy();
            setTrackDrawObject(dynamic_pointer_cast<UIDrawObjectCanvas>(TheFC));
        }
        if(Id->getMinTrackDrawObject() != NULL)
        {
            TheFC = Id->getMinTrackDrawObject()->shallowCopy();
            setMinTrackDrawObject(dynamic_pointer_cast<UIDrawObjectCanvas>(TheFC));
        }
        if(Id->getMaxTrackDrawObject() != NULL)
        {
            TheFC = Id->getMaxTrackDrawObject()->shallowCopy();
            setMaxTrackDrawObject(dynamic_pointer_cast<UIDrawObjectCanvas>(TheFC));
        }
        setLabelPrototype(Id->getLabelPrototype());
    }
}

void Slider::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

Slider::Slider(void) :
    Inherited(),
    _UsingDefaultLabels(true)
{
}

Slider::Slider(const Slider &source) :
    Inherited(source),
    _UsingDefaultLabels(source._UsingDefaultLabels)
{
}

Slider::~Slider(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Slider::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & LabelMapFieldMask))
    {
        _UsingDefaultLabels = (getLabelMap().size() == 0);
    }

    if( ((whichField & DrawLabelsFieldMask) ||
         (whichField & LabelPrototypeFieldMask) ||
         (whichField & MajorTickSpacingFieldMask))&&
        getDrawLabels() &&
        getRangeModel() != NULL &&
        _UsingDefaultLabels)
    {
        setLabelMap(createStandardLabels(getMajorTickSpacing()));
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
        clearChildren();
        if(getDrawTrack())
        {
            if(getTrackDrawObject() != NULL)
            {
                pushToChildren(getTrackDrawObject());
            }
            if(getMinTrackDrawObject() != NULL)
            {
                pushToChildren(getMinTrackDrawObject());
            }
            if(getMaxTrackDrawObject() != NULL)
            {
                pushToChildren(getMaxTrackDrawObject());
            }
        }
        if(getKnobButton() != NULL)
        {
            pushToChildren(getKnobButton());
        }

        if(getDrawLabels())
        {
            FieldContainerMap::const_iterator Itor;
            for(Itor = getLabelMap().begin() ; Itor != getLabelMap().end() ; ++Itor)
            {
                pushToChildren(dynamic_pointer_cast<Component>((*Itor).second));
            }
        }
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
       (whichField & LabelPrototypeFieldMask) ||
       (whichField & AlignmentFieldMask) ||
       (whichField & TicksOnRightBottomFieldMask))
    {
        updateLayout();
    }

    if(whichField & KnobButtonFieldMask)
    {
        _KnobMousePressedConnection.disconnect();
        if(getKnobButton() != NULL)
        {
            _KnobMousePressedConnection = getKnobButton()->connectMousePressed(boost::bind(&Slider::handleKnobMousePressed, this, _1));
        }
    }
    if(whichField & RangeModelFieldMask)
    {
        _RangeModelStateChangedConnection.disconnect();
        if(getRangeModel() != NULL)
        {
            _RangeModelStateChangedConnection = getRangeModel()->connectStateChanged(boost::bind(&Slider::handleRangeModelStateChanged, this, _1));
            if( getDrawLabels() &&
                _UsingDefaultLabels)
            {
                setLabelMap(createStandardLabels(getMajorTickSpacing()));
                _UsingDefaultLabels = true;
            }
        }
    }
}

void Slider::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Slider NI" << std::endl;
}

void Slider::handleRangeModelStateChanged(ChangeEventDetails* const e)
{
    updateLayout();
}

void Slider::handleKnobDragMouseDragged(MouseEventDetails* const e)
{
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), this, e->getViewport());
		
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

		if(getInverted())
		{
			MousePosInComponent[MajorAxis] = getTrackMax() - (MousePosInComponent[MajorAxis] - getTrackMin());
		}
        
        setValue( getMinimum() + (getMaximum() - getMinimum()) * (MousePosInComponent[MajorAxis] - getTrackMin())/static_cast<Int32>(getTrackLength()) );
	}
}

void Slider::handleKnobMousePressed(MouseEventDetails* const e)
{
    if(e->getButton() == MouseEventDetails::BUTTON1 &&
		getEnabled() &&
       getParentWindow() != NULL &&
       getParentWindow()->getParentDrawingSurface() != NULL &&
       getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
		_InitialValue = getValue();
        _KnobMousePressedConnection.disconnect();
        _KnobDragMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&Slider::handleKnobDragMouseDragged, this, _1));
        _KnobDragMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&Slider::handleKnobDragMouseReleased, this, _1));
        _KnobDragkeyTypedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyTyped(boost::bind(&Slider::handleKnobDragKeyTyped, this, _1));
		getRangeModel()->setValueIsAdjusting(true);
    }
}

void Slider::handleKnobDragMouseReleased(MouseEventDetails* const e)
{
    if(e->getButton() == MouseEventDetails::BUTTON1)
    {
        _KnobDragMouseDraggedConnection.disconnect();
        _KnobMousePressedConnection = getKnobButton()->connectMousePressed(boost::bind(&Slider::handleKnobMousePressed, this, _1));
        _KnobDragMouseReleasedConnection.disconnect();
        _KnobDragkeyTypedConnection.disconnect();
        getRangeModel()->setValueIsAdjusting(false);
    }
}

void Slider::handleKnobDragKeyTyped(KeyEventDetails* const e)
{
	if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
	{
		setValue(_InitialValue);
        _KnobDragMouseDraggedConnection.disconnect();
        _KnobMousePressedConnection = getKnobButton()->connectMousePressed(boost::bind(&Slider::handleKnobMousePressed, this, _1));
        _KnobDragMouseReleasedConnection.disconnect();
        _KnobDragkeyTypedConnection.disconnect();
        getRangeModel()->setValueIsAdjusting(false);
	}
}

OSG_END_NAMESPACE
