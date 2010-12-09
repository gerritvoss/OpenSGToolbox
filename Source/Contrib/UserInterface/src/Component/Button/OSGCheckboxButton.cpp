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

#include "OSGCheckboxButton.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCheckboxButtonBase.cpp file.
// To modify it, please change the .fcd file (OSGCheckboxButton.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CheckboxButton::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UIDrawObjectCanvas* CheckboxButton::getDrawnDrawObject(void) const
{
    if(getEnabled())
    {
        if(getActive())
        {
            if(getSelected())
            {
                return getActiveCheckboxDrawObject();
            }
            else
            {
                return getActiveSelectedCheckboxDrawObject();
            }
        }
        else if(_MouseInComponentLastMouse)
        {
            if(getSelected())
            {
                return getRolloverSelectedCheckboxDrawObject();
            }
            else
            {
                return getRolloverCheckboxDrawObject();
            }
        }
        else
        {
            if(getSelected())
            {
                return getSelectedCheckboxDrawObject();
            }
            else
            {
                return getCheckboxDrawObject();
            }
        }
    }
    else
    {
        if(getSelected())
        {
            return getDisabledSelectedCheckboxDrawObject();
        }
        else
        {
            return getDisabledCheckboxDrawObject();
        }
    }
}

UIDrawObjectCanvas* CheckboxButton::getBaseDrawObject(void) const
{
	return getCheckboxDrawObject();          
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CheckboxButton::CheckboxButton(void) :
    Inherited()
{
}

CheckboxButton::CheckboxButton(const CheckboxButton &source) :
    Inherited(source)
{
}

CheckboxButton::~CheckboxButton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CheckboxButton::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & CheckboxDrawObjectFieldMask &&
		getCheckboxDrawObject() != NULL)
	{
        getCheckboxDrawObject()->setSize(getCheckboxDrawObject()->getPreferredSize());
	}
	
	if(whichField & SelectedCheckboxDrawObjectFieldMask &&
		getSelectedCheckboxDrawObject() != NULL)
	{
        getSelectedCheckboxDrawObject()->setSize(getSelectedCheckboxDrawObject()->getPreferredSize());
	}
	
	if(whichField & ActiveCheckboxDrawObjectFieldMask &&
		getActiveCheckboxDrawObject() != NULL)
	{
        getActiveCheckboxDrawObject()->setSize(getActiveCheckboxDrawObject()->getPreferredSize());
	}
	
	if(whichField & ActiveSelectedCheckboxDrawObjectFieldMask &&
		getActiveSelectedCheckboxDrawObject() != NULL)
	{
        getActiveSelectedCheckboxDrawObject()->setSize(getActiveSelectedCheckboxDrawObject()->getPreferredSize());
	}
	
	if(whichField & RolloverCheckboxDrawObjectFieldMask &&
		getRolloverCheckboxDrawObject() != NULL)
	{
        getRolloverCheckboxDrawObject()->setSize(getRolloverCheckboxDrawObject()->getPreferredSize());
	}
	
	if(whichField & RolloverSelectedCheckboxDrawObjectFieldMask &&
		getRolloverSelectedCheckboxDrawObject() != NULL)
	{
        getRolloverSelectedCheckboxDrawObject()->setSize(getRolloverSelectedCheckboxDrawObject()->getPreferredSize());
	}
	
	if(whichField & DisabledCheckboxDrawObjectFieldMask &&
		getDisabledCheckboxDrawObject() != NULL)
	{
        getDisabledCheckboxDrawObject()->setSize(getDisabledCheckboxDrawObject()->getPreferredSize());
	}
	
	if(whichField & DisabledSelectedCheckboxDrawObjectFieldMask &&
		getDisabledSelectedCheckboxDrawObject() != NULL)
	{
        getDisabledSelectedCheckboxDrawObject()->setSize(getDisabledSelectedCheckboxDrawObject()->getPreferredSize());
	}
	
}

void CheckboxButton::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CheckboxButton NI" << std::endl;
}

OSG_END_NAMESPACE
