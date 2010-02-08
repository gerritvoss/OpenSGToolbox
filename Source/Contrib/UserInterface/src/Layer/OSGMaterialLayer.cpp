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

#include <OpenSG/OSGConfig.h>

#include "OSGMaterialLayer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MaterialLayer
UI Material Background. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaterialLayer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MaterialLayer::draw(const GraphicsPtr TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const
{
	TheGraphics->drawQuad(TopLeft, Pnt2f(BottomRight.x(), TopLeft.y()), BottomRight, Pnt2f(TopLeft.x(), BottomRight.y()), Vec2f(0.0, 0.0), Vec2f(1.0, 0.0), Vec2f(1.0, 1.0), Vec2f(0.0, 1.0), getMaterial(), Opacity);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MaterialLayer::MaterialLayer(void) :
    Inherited()
{
}

MaterialLayer::MaterialLayer(const MaterialLayer &source) :
    Inherited(source)
{
}

MaterialLayer::~MaterialLayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MaterialLayer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MaterialLayer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MaterialLayer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGMATERIALLAYERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMATERIALLAYERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMATERIALLAYERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

