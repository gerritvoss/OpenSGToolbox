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

#include "OSGAbstractColorChooserPanel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractColorChooserPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractColorChooserPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractColorChooserPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ColorChooser* AbstractColorChooserPanel::getParentChooser(void) const
{
    return getInternalParentChooser();
}

Color4f AbstractColorChooserPanel::getColorFromModel(void) const
{
    if(getParentChooser() != NULL && getParentChooser()->getSelectionModel() != NULL)
    {
        return getParentChooser()->getSelectionModel()->getSelectedColor();
    }
    else
    {
        return Color4f();
    }
}

ColorSelectionModel* AbstractColorChooserPanel::getColorSelectionModel(void)
{
    if(getParentChooser() != NULL)
    {
        return getParentChooser()->getSelectionModel();
    }
    else
    {
        return NULL;
    }
}

void AbstractColorChooserPanel::installChooserPanel(ColorChooser* const enclosingChooser)
{
    buildChooser();
}

void AbstractColorChooserPanel::uninstallChooserPanel(ColorChooser* const enclosingChooser)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractColorChooserPanel::AbstractColorChooserPanel(void) :
    Inherited()
{
}

AbstractColorChooserPanel::AbstractColorChooserPanel(const AbstractColorChooserPanel &source) :
    Inherited(source)
{
}

AbstractColorChooserPanel::~AbstractColorChooserPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractColorChooserPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractColorChooserPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractColorChooserPanel NI" << std::endl;
}

OSG_END_NAMESPACE
