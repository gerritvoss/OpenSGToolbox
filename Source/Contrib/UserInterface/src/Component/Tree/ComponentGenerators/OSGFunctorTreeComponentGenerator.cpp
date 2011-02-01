/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#include "OSGConfig.h"

#include "OSGFunctorTreeComponentGenerator.h"
#include "OSGComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFunctorTreeComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGFunctorTreeComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FunctorTreeComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr FunctorTreeComponentGenerator::getTreeComponent(Tree* const Parent,
                                                                    const boost::any& Value,
                                                                    bool IsSelected,
                                                                    bool Expanded,
                                                                    bool Leaf,
                                                                    UInt32 Row,
                                                                    bool HasFocus)
{
    if(!_GenerateFunctor.empty())
    {
        return _GenerateFunctor(Parent,
                                Value,
                                IsSelected,
                                Expanded,
                                Leaf,
                                Row,
                                HasFocus);
    }
    else
    {
        SFATAL << "Cannot generate component because the generate functor has not been defined." << std::endl;
        return ComponentTransitPtr(NULL);
    }
}

ComponentTransitPtr FunctorTreeComponentGenerator::getTreeExpandedComponent(Tree* const Parent,
                                                                            const boost::any& Value,
                                                                            bool IsSelected,
                                                                            bool Expanded,
                                                                            bool Leaf,
                                                                            UInt32 Row,
                                                                            bool HasFocus)
{
    if(!_ExpandGenerateFunctor.empty())
    {
        return _ExpandGenerateFunctor(Parent,
                                Value,
                                IsSelected,
                                Expanded,
                                Leaf,
                                Row,
                                HasFocus);
    }
    else
    {
        SFATAL << "Cannot generate expand component because the generate functor has not been defined." << std::endl;
        return ComponentTransitPtr(NULL);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FunctorTreeComponentGenerator::FunctorTreeComponentGenerator(void) :
    Inherited()
{
}

FunctorTreeComponentGenerator::FunctorTreeComponentGenerator(const FunctorTreeComponentGenerator &source) :
    Inherited(source)
{
}

FunctorTreeComponentGenerator::~FunctorTreeComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FunctorTreeComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FunctorTreeComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FunctorTreeComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
