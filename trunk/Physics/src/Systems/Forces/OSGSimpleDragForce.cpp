/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGSimpleDragForce.h"
#include "Physics/Objects/Attributes/OSGLinearPositionalAttribute.h"
#include "Physics/Objects/Attributes/OSGDragGeometricAttribute.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SimpleDragForce

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SimpleDragForce::initMethod (void)
{
}

 bool SimpleDragForce::updateForce(osg::AttachmentMap& Attributes, osg::Vec3f& Force, osg::Vec3f& Torque)
{
    AttachmentMap::iterator fcPos = Attributes.find( 
          osg::LinearPositionalAttribute::getClassType().getGroupId() << 16 );
    AttachmentMap::iterator fcDrag = Attributes.find( 
          osg::DragGeometricAttribute::getClassType().getGroupId() << 16 );
    //Check for all of the Requirements
    
    if(getFluid() == NullFC )
    {
       SWARNING << "SimpleDragForce: No Fluid Defined."  << std::endl;
       Force.setValue(Vec3f(0.0f,0.0f,0.0f));
       Torque.setValue(Vec3f(0.0f,0.0f,0.0f));
       return false;
    }
    if(fcPos == Attributes.end() )
    {
       SWARNING << "SimpleDragForce: No Linear Positional Attribute Defined."  << std::endl;
       Force.setValue(Vec3f(0.0f,0.0f,0.0f));
       Torque.setValue(Vec3f(0.0f,0.0f,0.0f));
       return false;
    }
    if(fcDrag == Attributes.end() )
    {
       SWARNING << "SimpleDragForce: No Drag Attribute Defined."  << std::endl;
       Force.setValue(Vec3f(0.0f,0.0f,0.0f));
       Torque.setValue(Vec3f(0.0f,0.0f,0.0f));
       return false;
    }
    
    LinearPositionalAttributePtr PosAttribute = osg::LinearPositionalAttribute::Ptr::dcast( (*fcPos).second );
    DragGeometricAttributePtr DragAttribute = osg::DragGeometricAttribute::Ptr::dcast( (*fcDrag).second );

    //Calculate the force
    Force = getFluid()->getViscosity() * DragAttribute->getGeometricDragFactor() * -PosAttribute->getVelocity();
    
    //Torque
    Torque.setValue(Vec3f(0.0f,0.0f,0.0f));
    
    return false;
 }

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SimpleDragForce::SimpleDragForce(void) :
    Inherited()
{
}

SimpleDragForce::SimpleDragForce(const SimpleDragForce &source) :
    Inherited(source)
{
}

SimpleDragForce::~SimpleDragForce(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SimpleDragForce::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SimpleDragForce::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SimpleDragForce NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGSIMPLEDRAGFORCEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSIMPLEDRAGFORCEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSIMPLEDRAGFORCEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

