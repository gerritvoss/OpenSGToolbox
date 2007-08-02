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

#include "OSGScrollbar.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Scrollbar
A UI Scrollbar. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Scrollbar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Scrollbar::drawInternal(const GraphicsPtr Graphics) const
{
    //TODO:Implement
	//Draw Min Button
	//Draw Max Button
}

void  Scrollbar::produceAdjustmentValueChanged(const AdjustmentEvent& e)
{
   for(AdjustmentListenerSetConstItor SetItor(_AdjustmentListeners.begin()) ; SetItor != _AdjustmentListeners.end() ; ++SetItor)
   {
      (*SetItor)->adjustmentValueChanged(e);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Scrollbar::Scrollbar(void) :
    Inherited(),
        _Model(NULL)
{
}

Scrollbar::Scrollbar(const Scrollbar &source) :
    Inherited(source),
        _Model(source._Model)

{
}

Scrollbar::~Scrollbar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Scrollbar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Scrollbar::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Scrollbar NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSCROLLBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCROLLBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCROLLBARFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

