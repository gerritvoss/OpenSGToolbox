/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultCaptionComponentGenerator.h"
#include <OpenSG/Toolbox/OSGStringUtils.h>

#include "OpenSG/UserInterface/OSGLabel.h"
#include "OpenSG/UserInterface/OSGComponent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultCaptionComponentGenerator
A UI Default Tree ComponentGenerator. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultCaptionComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
ComponentPtr DefaultCaptionComponentGenerator::getCaptionComponent(CaptionPtr Parent, const boost::any& Value)
{
    std::string CaptionSegment("");
    try
    {
        CaptionSegment = lexical_cast(Value);
    }
    catch (boost::bad_lexical_cast &)
    {
        std::cout<<"Unable to display segment"<<std::endl;
    }

    LabelPtr TheCaptionSegment = Label::Ptr::dcast(getCaptionSegmentPrototype()->shallowCopy());
    beginEditCP(TheCaptionSegment, Label::TextFieldMask);
        TheCaptionSegment->setText(CaptionSegment);
    endEditCP(TheCaptionSegment, Label::TextFieldMask);

    return TheCaptionSegment;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultCaptionComponentGenerator::DefaultCaptionComponentGenerator(void) :
    Inherited()
{
}

DefaultCaptionComponentGenerator::DefaultCaptionComponentGenerator(const DefaultCaptionComponentGenerator &source) :
    Inherited(source)
{
}

DefaultCaptionComponentGenerator::~DefaultCaptionComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultCaptionComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultCaptionComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultCaptionComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTCAPTIONCOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTCAPTIONCOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTCAPTIONCOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

