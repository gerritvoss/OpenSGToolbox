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

#include "OSGLuaIntrospectionComponentGenerator.h"
#include "OSGTree.h"
#include "OSGLuaUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaIntrospectionComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaIntrospectionComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaIntrospectionComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
ComponentTransitPtr LuaIntrospectionComponentGenerator::getTreeComponent(Tree* const Parent, 
                                                                         const boost::any& Value, 
                                                                         bool IsSelected, 
                                                                         bool Expanded, 
                                                                         bool Leaf, 
                                                                         UInt32 Row, 
                                                                         bool HasFocus)
{
    std::string LabelText;
    try
    {
        const lua_details::FieldStack& vecPath(boost::any_cast<lua_details::FieldStack >(Value));
        if(vecPath.size() > 0)
        {
            //Get the text for the label
            LabelText = vecPath.back().key.value +  "   " + vecPath.back().val.value + "   [" + vecPath.back().val.type_name + "]";
        }
    }
    catch (boost::bad_any_cast &)
    {
        //Could not convert to string
        return ComponentTransitPtr(NULL);
    }

    return getTreeComponentText(Parent, LabelText, IsSelected, Expanded, Leaf, Row, HasFocus);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaIntrospectionComponentGenerator::LuaIntrospectionComponentGenerator(void) :
    Inherited()
{
}

LuaIntrospectionComponentGenerator::LuaIntrospectionComponentGenerator(const LuaIntrospectionComponentGenerator &source) :
    Inherited(source)
{
}

LuaIntrospectionComponentGenerator::~LuaIntrospectionComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LuaIntrospectionComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LuaIntrospectionComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaIntrospectionComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
