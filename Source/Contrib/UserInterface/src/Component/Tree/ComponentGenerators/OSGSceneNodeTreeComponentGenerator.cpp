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

#include "OSGSceneNodeTreeComponentGenerator.h"
#include "OSGFieldContainerTreeModel.h"
#include "OSGNameAttachment.h"
#include "OSGTree.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneNodeTreeComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneNodeTreeComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneNodeTreeComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr SceneNodeTreeComponentGenerator::getTreeComponent(Tree* const Parent, 
                                                                            const boost::any& Value, 
                                                                            bool IsSelected, 
                                                                            bool Expanded, 
                                                                            bool Leaf, 
                                                                            UInt32 Row, 
                                                                            bool HasFocus)
{
    NodeUnrecPtr TheNode;
    try
    {
        TheNode = boost::any_cast<NodeUnrecPtr>(Value);
    }
    catch (boost::bad_any_cast &)
    {
        //Could not convert to FieldContinerFieldPath
        return ComponentTransitPtr(NULL);
    }

    //Get the text for the label
    std::string LabelText("");
    if(TheNode != NULL)
    {
        const Char8* name(getName(TheNode));
        if(name)
        {
            LabelText += std::string(name) + " ";
        }
        if(TheNode->getCore() != NULL)
        {
            LabelText += std::string("[") + TheNode->getCore()->getType().getCName() + "]";
        }
        else
        {
            LabelText += "[NULL core]";
        }
    }
    else
    {
        LabelText += "NULL";
    }

    ComponentRecPtr GenComp = getTreeComponentText(Parent, LabelText, IsSelected, Expanded, Leaf, Row, HasFocus);
    if(TheNode != NULL &&
       !(TheNode->getTravMask() & getTravMask()))
    {
        GenComp->setEnabled(false);
    }

    return ComponentTransitPtr(GenComp);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneNodeTreeComponentGenerator::SceneNodeTreeComponentGenerator(void) :
    Inherited()
{
}

SceneNodeTreeComponentGenerator::SceneNodeTreeComponentGenerator(const SceneNodeTreeComponentGenerator &source) :
    Inherited(source)
{
}

SceneNodeTreeComponentGenerator::~SceneNodeTreeComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneNodeTreeComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneNodeTreeComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneNodeTreeComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
