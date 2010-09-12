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

#include "OSGComponentMenuItem.h"
#include "OSGUIDrawUtils.h"
#include "OSGInternalWindow.h"
#include "OSGLookAndFeelManager.h"
#include "OSGMenu.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComponentMenuItemBase.cpp file.
// To modify it, please change the .fcd file (OSGComponentMenuItem.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentMenuItem::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ComponentMenuItem::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    if(getComponent() != NULL)
    {
        getComponent()->draw(TheGraphics, getOpacity()*Opacity);
    }
}

Vec2f ComponentMenuItem::getContentRequestedSize(void) const
{
    if(getComponent() != NULL)
    {
        Vec2f ComponentRequestedSize(0.0,0.0);
        if(getComponent() != NULL)
        {
            ComponentRequestedSize = getComponent()->getRequestedSize();
        }

        Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
        getFont()->getBounds(_AcceleratorText, AcceleratorTextTopLeft, AcceleratorTextBottomRight);

        Vec2f RequestedSize((ComponentRequestedSize.x()) + (AcceleratorTextBottomRight.x() - AcceleratorTextTopLeft.x()), osgMax(getPreferredSize().y(), ComponentRequestedSize.y()));

        if(!_AcceleratorText.empty())
        {
            RequestedSize[0] += 50.0f;
        }
        else
        {
            RequestedSize[0] += 25.0f;
        }

        return RequestedSize;
    }
    else
    {
        return Inherited::getContentRequestedSize();
    }
}

void ComponentMenuItem::updateComponentBounds(void)
{
    if(getComponent() != NULL)
    {
        Pnt2f InsideBorderTopLeft, InsideBorderBottomRight;
        getInsideBorderBounds(InsideBorderTopLeft, InsideBorderBottomRight);

        if(getComponent()->getPosition() != InsideBorderTopLeft)
        {
            getComponent()->setPosition(InsideBorderTopLeft);
        }
        Vec2f Size(InsideBorderBottomRight - InsideBorderTopLeft);
        if(getComponent()->getSize() != Size)
        {
            getComponent()->setSize(Size);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComponentMenuItem::ComponentMenuItem(void) :
    Inherited()
{
}

ComponentMenuItem::ComponentMenuItem(const ComponentMenuItem &source) :
    Inherited(source)
{
}

ComponentMenuItem::~ComponentMenuItem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComponentMenuItem::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if((whichField & SizeFieldMask) ||
		(whichField & ComponentFieldMask))
	{
		updateComponentBounds();
	}

    if(whichField & ComponentFieldMask ||
		whichField & AcceleratorKeyFieldMask ||
       whichField & AcceleratorModifiersFieldMask)
    {
        updateAcceleratorText();
    }
}

void ComponentMenuItem::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ComponentMenuItem NI" << std::endl;
}

OSG_END_NAMESPACE
