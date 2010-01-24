/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGConditionalParticleAffector.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGConditionalParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGConditionalParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ConditionalParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool ConditionalParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
    bool returnStatus(false), runAffectors(false);

    UInt8 Operator(getConditionalOperator());
    switch(getConditionalOperator())
    {
        case 1: // equals
            if(System->getAttribute(ParticleIndex,getConditionalAttribute()) == getConditionalValue()) 
                runAffectors = true;
            break;

        case 2: // not equal
            if(System->getAttribute(ParticleIndex,getConditionalAttribute()) != getConditionalValue()) 
                runAffectors = true;
            break;

        case 3: // less than
            if(System->getAttribute(ParticleIndex,getConditionalAttribute()) < getConditionalValue()) 
                runAffectors = true;
            break;

        case 4: // greater than
            if(System->getAttribute(ParticleIndex,getConditionalAttribute()) > getConditionalValue()) 
                runAffectors = true;
            break;

        case 5: // less than or equal
            if(System->getAttribute(ParticleIndex,getConditionalAttribute()) <= getConditionalValue()) 
                runAffectors = true;
            break;

        case 6: // greater than or equal
            if(System->getAttribute(ParticleIndex,getConditionalAttribute()) >= getConditionalValue()) 
                runAffectors = true;
            break;

        default: // error
            returnStatus = false;
            runAffectors = false;
            break;
    }

    if(runAffectors)
    {
        for(unsigned int i(0); i < getMFAffectors()->size();i++)
        {
            if(getAffectors(i)->affect(System,ParticleIndex,elps))
                returnStatus = true;
        }
    }

    return returnStatus;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ConditionalParticleAffector::ConditionalParticleAffector(void) :
    Inherited()
{
}

ConditionalParticleAffector::ConditionalParticleAffector(const ConditionalParticleAffector &source) :
    Inherited(source)
{
}

ConditionalParticleAffector::~ConditionalParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ConditionalParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ConditionalParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ConditionalParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
