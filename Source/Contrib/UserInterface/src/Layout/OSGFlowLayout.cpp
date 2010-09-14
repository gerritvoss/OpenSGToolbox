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

#include "OSGFlowLayout.h"
#include "OSGUIDrawUtils.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFlowLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGFlowLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FlowLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


Vec2f FlowLayout::getAppropriateComponentSize(Component* const TheComponent)
{
    Vec2f ComponentSize(0.0f,0.0f);
    if(TheComponent != NULL)
    {
        ComponentSize = TheComponent->getPreferredSize();
        if(ComponentSize.x() < TheComponent->getMinSize().x())
        {
            ComponentSize[0] = TheComponent->getMinSize()[0];
        }
        if(ComponentSize.y() < TheComponent->getMinSize().y())
        {
            ComponentSize[1] = TheComponent->getMinSize()[1];
        }
    }
    return ComponentSize;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FlowLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    /*!
      totalMajorAxis will hold the width of its container, and cumMajorAxis
      will hold the width of all of the buttons. That way it will always know
      when to move to the next line. In addition, maxMinorAxis keeps track of
      the largest height so it knows how far down to move the next row. Also,
      oneInRow is used to make sure that it places at least one component in
      every row.
      */
    UInt32 AxisIndex(0);
    if(getOrientation() != HORIZONTAL_ORIENTATION ) AxisIndex = 1;
    Vec2f gap(getHorizontalGap(), getVerticalGap());
    UInt32 numGaps(0);
    /*!
      When finding the cumMinor Axis, the gap is included, because there is
      no count for how many stacks there are. When finding cumMajor, the
      gap isn't included because the total distance relies on how many
      components there are in that row/column.
      */

    Pnt2f borderTopLeft, borderBottomRight;
    dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
    Vec2f borderSize(borderBottomRight-borderTopLeft);
    Real64 totalMajorAxis(borderSize[AxisIndex]);
    Real32 cumMajorAxis(0);
    Real32 maxMinorAxis(0);
    Real32 cumMinorAxis(0);
    Real32 prevComponent(0);
    Real64 offsetMajorAxis(0);
    Real64 offsetMinorAxis(0);
    Real64 offsetX(borderTopLeft.x());
    Real64 offsetY(borderTopLeft.y());
    bool firstOne = true;

    Vec2f Size;
    for(UInt32 i=0 ; i<Components->size(); ++i)
    {
        // set the component to its preferred size
        Size = getAppropriateComponentSize((*Components)[i]);
        if((*Components)[i]->getSize() != Size)
        {
            (*Components)[i]->setSize(Size);
        }

        // if there is only one so far, then it can't draw it using cumMajorAxis
        // because it hasn't been set yet
        if (firstOne) // this one might draw it
        {
            firstOne = false;
            // if this is the last component or it is already too big for the
            // container, draw it centered on its line
            if (i == Components->size() || (*Components)[i]->getSize()[AxisIndex] >= totalMajorAxis)
            {
                // find how far to translate to make it properly aligned
                offsetMajorAxis = getMajorAxisAlignment()*(totalMajorAxis - (*Components)[i]->getSize()[AxisIndex]);

                if (AxisIndex)
                {
                    offsetY+= offsetMajorAxis;
                }
                else
                {
                    offsetX += offsetMajorAxis;
                }

                if((*Components)[i]->getPosition().x() != offsetX ||
                    (*Components)[i]->getPosition().y() != offsetY)
                {
                    (*Components)[i]->setPosition(Pnt2f(offsetX, offsetY));
                }

                // get to the next row
                if (AxisIndex)
                {
                    offsetX += (*Components)[i]->getSize()[(AxisIndex+1)%2]+gap[(AxisIndex+1)%2];
                    offsetY += -offsetMajorAxis;
                }
                else
                {
                    offsetX += -offsetMajorAxis;
                    offsetY += (*Components)[i]->getSize()[(AxisIndex+1)%2]+gap[(AxisIndex+1)%2];
                }
                // update cumMinorAxis, other values should still be at 0
                cumMinorAxis += (*Components)[i]->getSize()[(AxisIndex+1)%2];
                if(i < Components->size()-1)
                {
                    cumMinorAxis += gap[(AxisIndex+1)%2];
                }
                // update prevComponent
                prevComponent++;
                // next component is still just like the first one
                firstOne = true;
            }
            else
            {
                // update the maxMinorAxis
                maxMinorAxis = (*Components)[i]->getSize()[(AxisIndex+1)%2];
                // update cumMajorAxis
                cumMajorAxis += (*Components)[i]->getSize()[AxisIndex];
            }
        }
        else if (cumMajorAxis + (*Components)[i]->getSize()[AxisIndex] + gap[AxisIndex]*(i-prevComponent) > totalMajorAxis) // this one draws up to i
        {
            // The numGaps is one less than the number of components being drawn, but it
            // is actually translates once for each component, so it must be compensated
            // when returning to the next row.
            numGaps = i-prevComponent-1;

            // find how far to translate to make it properly aligned
            offsetMajorAxis = getMajorAxisAlignment()*(totalMajorAxis - (cumMajorAxis+numGaps*gap[AxisIndex]));


            if (AxisIndex){
                offsetY += offsetMajorAxis;
            }
            else
            {
                offsetX += offsetMajorAxis;
            }
            for (int j = prevComponent; j < i; j++)
            {
                // find how far to translate to make this button properly aligned
                offsetMinorAxis = (maxMinorAxis-(*Components)[j]->getSize()[(AxisIndex+1)%2])*getComponentAlignment();

                // translate to make it properly aligned
                if (AxisIndex)
                {	
                    offsetX += offsetMinorAxis;
                }
                else
                {
                    offsetY += offsetMinorAxis;
                }

                if((*Components)[j]->getPosition().x() != offsetX ||
                    (*Components)[j]->getPosition().y() != offsetY)
                {
                    (*Components)[j]->setPosition(Pnt2f(offsetX, offsetY));
                }

                // translate to next button
                if (AxisIndex)
                {
                    offsetX+=-(Real64)offsetMinorAxis;
                    offsetY+= (*Components)[j]->getSize()[AxisIndex] + gap[AxisIndex];
                }
                else
                {
                    offsetX+=(*Components)[j]->getSize()[AxisIndex] + gap[AxisIndex];
                    offsetY+= -offsetMinorAxis;
                }
            }
            // translate to the next row
            if (AxisIndex)
            {
                offsetX += maxMinorAxis+gap[(AxisIndex+1)%2];
                offsetY += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
            }
            else
            {
                offsetX += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
                offsetY += maxMinorAxis+gap[(AxisIndex+1)%2];
            }

            cumMinorAxis += maxMinorAxis + gap[(AxisIndex+1)%2];
            maxMinorAxis = (*Components)[i]->getSize()[(AxisIndex+1)%2];
            prevComponent = i;
            cumMajorAxis = (*Components)[i]->getSize()[AxisIndex];
        }
        else
        {
            // update the maxMinorAxis
            if ((*Components)[i]->getSize()[(AxisIndex+1)%2] > maxMinorAxis)
                maxMinorAxis = (*Components)[i]->getSize()[(AxisIndex+1)%2];
            // update cumMajorAxis
            cumMajorAxis += (*Components)[i]->getSize()[AxisIndex];
        }
        if (i+1 == Components->size() && !firstOne) // if on the last one, draw the last buttons
        {
            numGaps = i-prevComponent;

            // find how far to translate to make it properly aligned
            offsetMajorAxis = getMajorAxisAlignment()*(totalMajorAxis - (cumMajorAxis+numGaps*gap[AxisIndex]));

            if (AxisIndex)
            {
                offsetY += offsetMajorAxis;
            }
            else
            {			
                offsetX += offsetMajorAxis;
            }
            for (int j = prevComponent; j < i+1; j++)
            {
                // find how far to translate to make this button properly aligned
                offsetMinorAxis = (maxMinorAxis-(*Components)[j]->getSize()[(AxisIndex+1)%2])*getComponentAlignment();

                // translate to make it properly aligned
                if (AxisIndex)
                {
                    offsetX += offsetMinorAxis;
                }
                else
                {
                    offsetY += offsetMinorAxis;
                }
                if((*Components)[j]->getPosition().x() != offsetX ||
                    (*Components)[j]->getPosition().y() != offsetY)
                {
                    (*Components)[j]->setPosition(Pnt2f(offsetX, offsetY));
                }

                if (AxisIndex)
                {
                    offsetX += -(Real64)offsetMinorAxis;
                    offsetY += (*Components)[j]->getSize()[AxisIndex] + gap[AxisIndex];
                }
                else
                {
                    offsetX += (*Components)[j]->getSize()[AxisIndex] + gap[AxisIndex];
                    offsetY+= -(Real64)offsetMinorAxis;
                }
            }
            // translate to the next row
            if (AxisIndex)
            {
                offsetX += maxMinorAxis+gap[(AxisIndex+1)%2];
                offsetY += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
            }
            else
            {
                offsetX += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
                offsetY += maxMinorAxis+gap[(AxisIndex+1)%2];
            }
            cumMinorAxis += maxMinorAxis;
        }
    }
    //Minor Axis Alignment
    Real32 displacement(borderSize[(AxisIndex+1)%2]-cumMinorAxis);
    Pnt2f offset;
    displacement *= getMinorAxisAlignment(); 
    for (UInt32 i = 0; i < Components->size(); ++i)
    {
        offset = (*Components)[i]->getPosition();
        offset[(AxisIndex+1)%2] += displacement;
        if((*Components)[i]->getPosition() != offset)
        {
            (*Components)[i]->setPosition(offset);
        }
    }
}

Vec2f FlowLayout::layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const
{
    Real32 MinorAxisMax(0.0f);
    Real32 MajorAxisSum(0.0f);

    UInt32 MajorAxisIndex(0);
    if(getOrientation() != HORIZONTAL_ORIENTATION ) MajorAxisIndex = 1;

    UInt32 MinorAxisIndex((MajorAxisIndex+1)%2);

    Vec2f ComponentSize;
    for(UInt32 i(0) ; i<Components->size() ; ++i)
    {
        ComponentSize = getComponentSize((*Components)[i],TheSizeType);
        if(ComponentSize[MinorAxisIndex] > MinorAxisMax)
        {
            MinorAxisMax = ComponentSize[MinorAxisIndex];
        }
        MajorAxisSum += ComponentSize[MajorAxisIndex];
    }

    Vec2f Result;
    Result[MajorAxisIndex] = MajorAxisSum;
    Result[MinorAxisIndex] = MinorAxisMax;
    return Result;
}

Vec2f FlowLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f FlowLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f FlowLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f FlowLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FlowLayout::FlowLayout(void) :
    Inherited()
{
}

FlowLayout::FlowLayout(const FlowLayout &source) :
    Inherited(source)
{
}

FlowLayout::~FlowLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FlowLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ( OrientationFieldMask | 
                      HorizontalGapFieldMask | 
                      VerticalGapFieldMask | 
                      MajorAxisAlignmentFieldMask | 
                      MinorAxisAlignmentFieldMask | 
                      ComponentAlignmentFieldMask))
    {
        updateParentContainers();
    }
}

void FlowLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FlowLayout NI" << std::endl;
}

OSG_END_NAMESPACE
