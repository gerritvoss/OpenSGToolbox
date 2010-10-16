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

#include "OSGSpinnerNumberEditor.h"
#include <boost/lexical_cast.hpp>
#include "OSGSpinner.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSpinnerNumberEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGSpinnerNumberEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpinnerNumberEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpinnerNumberEditor::commitEdit(void)
{
    try
    {
        Real64 result = boost::lexical_cast<Real64>(getTextField()->getText());

        getSpinner()->getModel()->setValue(getTextField()->getText());
    }
    catch(std::exception &)
    {
        //Reset to the old value
        std::string NewValue;
        try
        {
            getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
        }
        catch(boost::bad_any_cast &)
        {
            getTextField()->setText("0.0");
        }
    }
}

void SpinnerNumberEditor::handleModelStateChanged(ChangeEventDetails* const e)
{
    std::string Text(getSpinner()->getModel()->getValueAsString());
    if(!Text.empty())
    {
        getTextField()->setText(Text);
    }
    else
    {
        getTextField()->setText("0");
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SpinnerNumberEditor::SpinnerNumberEditor(void) :
    Inherited()
{
}

SpinnerNumberEditor::SpinnerNumberEditor(const SpinnerNumberEditor &source) :
    Inherited(source)
{
}

SpinnerNumberEditor::~SpinnerNumberEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SpinnerNumberEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SpinnerNumberEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SpinnerNumberEditor NI" << std::endl;
}

OSG_END_NAMESPACE
