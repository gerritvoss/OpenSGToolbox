/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGXMLLookAndFeel.h"
#include <boost/filesystem/operations.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::XMLLookAndFeel
UI XML LookAndFeel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void XMLLookAndFeel::initMethod (void)
{
}

XMLLookAndFeelPtr XMLLookAndFeel::create(const Path& LoadFile)
{
    XMLLookAndFeelPtr Result = NullFC;
    if(boost::filesystem::exists(LoadFile))
    {
        FCFileType::FCPtrStore Containers;
	    Containers = FCFileHandler::the()->read(LoadFile);

        FCFileType::FCPtrStore::iterator ContainerItor;
        for(ContainerItor = Containers.begin(); ContainerItor != Containers.end(); ++ContainerItor)
        {
            if((*ContainerItor)->getType() == XMLLookAndFeel::getClassType())
            {
                Result = XMLLookAndFeel::Ptr::dcast((*ContainerItor));
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
    if(getBaseLookAndFeel() != NullFC)
    {
        getBaseLookAndFeel()->init();
    }

    //Setup my prototypes
    initPrototypes();
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

void XMLLookAndFeel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void XMLLookAndFeel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump XMLLookAndFeel NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGXMLLOOKANDFEELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGXMLLOOKANDFEELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGXMLLOOKANDFEELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

