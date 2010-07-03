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

#include "OSGFieldContainerFieldPathComponentGenerator.h"
#include "OSGFieldContainerTreeModel.h"
#include "OSGNameAttachment.h"
#include "OSGTree.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFieldContainerFieldPathComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGFieldContainerFieldPathComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldContainerFieldPathComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr FieldContainerFieldPathComponentGenerator::getTreeComponent(Tree* const Parent, 
                                                                            const boost::any& Value, 
                                                                            bool IsSelected, 
                                                                            bool Expanded, 
                                                                            bool Leaf, 
                                                                            UInt32 Row, 
                                                                            bool HasFocus)
{
    FieldContainerTreeModel::ContainerFieldIdPair ThePair;
    try
    {
        ThePair = boost::any_cast<FieldContainerTreeModel::ContainerFieldIdPair>(Value);
    }
    catch (boost::bad_any_cast &)
    {
        //Could not convert to FieldContinerFieldPath
        return ComponentTransitPtr(NULL);
    }

    //Get the text for the label
    std::string LabelText("");
    if(ThePair._FieldID == 0)
    {
        if(ThePair._Container != NULL)
        {
            if(ThePair._Container->getType().isDerivedFrom(AttachmentContainer::getClassType()))
            {
                const Char8* name(getName(dynamic_cast<AttachmentContainer*>(ThePair._Container)));
                if(name)
                {
                    LabelText += std::string(name) + " ";
                }
            }
            LabelText += std::string("[") + ThePair._Container->getType().getCName() + "]";
        }
        else
        {
            LabelText += "NULL";
        }
    }
    else
    {
        LabelText = ThePair._Container->getFieldDescription(ThePair._FieldID)->getCName() +
                    std::string(" [") + ThePair._Container->getFieldDescription(ThePair._FieldID)->getFieldType().getContentType().getCName() + "]";
    }


    return getTreeComponentText(Parent, LabelText, IsSelected, Expanded, Leaf, Row, HasFocus);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldContainerFieldPathComponentGenerator::FieldContainerFieldPathComponentGenerator(void) :
    Inherited()
{
}

FieldContainerFieldPathComponentGenerator::FieldContainerFieldPathComponentGenerator(const FieldContainerFieldPathComponentGenerator &source) :
    Inherited(source)
{
}

FieldContainerFieldPathComponentGenerator::~FieldContainerFieldPathComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldContainerFieldPathComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FieldContainerFieldPathComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FieldContainerFieldPathComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
