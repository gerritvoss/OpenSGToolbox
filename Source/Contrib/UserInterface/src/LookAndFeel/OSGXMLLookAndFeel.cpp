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

#include "OSGXMLLookAndFeel.h"
#include <boost/filesystem/operations.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGXMLLookAndFeelBase.cpp file.
// To modify it, please change the .fcd file (OSGXMLLookAndFeel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void XMLLookAndFeel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

XMLLookAndFeelUnrecPtr XMLLookAndFeel::create(const BoostPath& LoadFile)
{
    XMLLookAndFeelUnrecPtr Result = NULL;
    if(boost::filesystem::exists(LoadFile))
    {
        FCFileType::FCPtrStore Containers;
	    Containers = FCFileHandler::the()->read(LoadFile);

        FCFileType::FCPtrStore::iterator ContainerItor;
        for(ContainerItor = Containers.begin(); ContainerItor != Containers.end(); ++ContainerItor)
        {
            if((*ContainerItor)->getType() == XMLLookAndFeel::getClassType())
            {
                Result = dynamic_pointer_cast<XMLLookAndFeel>(*ContainerItor);
                break;
            }
        }
    }

    return Result;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void XMLLookAndFeel::init(void)
{
    //Get All of the prototypes of the Base Look and feel
    if(getBaseLookAndFeel() != NULL)
    {
        getBaseLookAndFeel()->init();
    }

    //Setup my prototypes
    initPrototypes();

    
    //Setup my undefined prototypes
    initUndefinedPrototypes();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

XMLLookAndFeel::XMLLookAndFeel(void) :
    Inherited()
{
}

XMLLookAndFeel::XMLLookAndFeel(const XMLLookAndFeel &source) :
    Inherited(source)
{
}

XMLLookAndFeel::~XMLLookAndFeel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void XMLLookAndFeel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void XMLLookAndFeel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump XMLLookAndFeel NI" << std::endl;
}

OSG_END_NAMESPACE
