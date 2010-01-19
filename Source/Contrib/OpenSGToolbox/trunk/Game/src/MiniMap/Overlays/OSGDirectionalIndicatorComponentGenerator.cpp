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

#include "OSGDirectionalIndicatorComponentGenerator.h"
#include "MiniMap/Indicators/OSGMiniMapIndicator.h"
#include "MiniMap/OSGMiniMap.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DirectionalIndicatorComponentGenerator
A DirectionalIndicator ComponentGenerator. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DirectionalIndicatorComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


ComponentPtr DirectionalIndicatorComponentGenerator::getComponent(ComponentPtr Parent, const boost::any &Value, Int32 PrimaryAxisIndex, Int32 SecondaryAxisIndex, bool IsSelected, bool HasFocus)
{
    MiniMapPtr UsedParent;
    MiniMapIndicatorPtr Indicator;

    //Parent
    if(Parent->getType().isDerivedFrom(MiniMap::getClassType()))
    {
		 UsedParent = MiniMapPtr::dcast(Parent);
	}
	else
	{
        UsedParent = NullFC;
	}

    //Indicator
    try
    {
        Indicator = boost::any_cast<MiniMapIndicatorPtr>(Value);
    }
    catch(boost::bad_any_cast&)
    {
        Indicator = NullFC;
    }

    return getDirectionalComponent(UsedParent, Indicator, Vec3f(0.0f,0.0f,0.0f), IsSelected);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DirectionalIndicatorComponentGenerator::DirectionalIndicatorComponentGenerator(void) :
    Inherited()
{
}

DirectionalIndicatorComponentGenerator::DirectionalIndicatorComponentGenerator(const DirectionalIndicatorComponentGenerator &source) :
    Inherited(source)
{
}

DirectionalIndicatorComponentGenerator::~DirectionalIndicatorComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DirectionalIndicatorComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DirectionalIndicatorComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DirectionalIndicatorComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDIRECTIONALINDICATORCOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDIRECTIONALINDICATORCOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDIRECTIONALINDICATORCOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

