/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class DiscUIDrawObject!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &DiscUIDrawObjectBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 DiscUIDrawObjectBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
DiscUIDrawObjectPtr DiscUIDrawObjectBase::create(void) 
{
    DiscUIDrawObjectPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = DiscUIDrawObjectPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
DiscUIDrawObjectPtr DiscUIDrawObjectBase::createEmpty(void) 
{ 
    DiscUIDrawObjectPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the DiscUIDrawObject::_sfCenter field.
inline
SFPnt2s *DiscUIDrawObjectBase::getSFCenter(void)
{
    return &_sfCenter;
}

//! Get the DiscUIDrawObject::_sfWidth field.
inline
SFInt16 *DiscUIDrawObjectBase::getSFWidth(void)
{
    return &_sfWidth;
}

//! Get the DiscUIDrawObject::_sfHeight field.
inline
SFInt16 *DiscUIDrawObjectBase::getSFHeight(void)
{
    return &_sfHeight;
}

//! Get the DiscUIDrawObject::_sfStartAngleRad field.
inline
SFReal32 *DiscUIDrawObjectBase::getSFStartAngleRad(void)
{
    return &_sfStartAngleRad;
}

//! Get the DiscUIDrawObject::_sfEndAngleRad field.
inline
SFReal32 *DiscUIDrawObjectBase::getSFEndAngleRad(void)
{
    return &_sfEndAngleRad;
}

//! Get the DiscUIDrawObject::_sfSubDivisions field.
inline
SFUInt16 *DiscUIDrawObjectBase::getSFSubDivisions(void)
{
    return &_sfSubDivisions;
}

//! Get the DiscUIDrawObject::_sfColor field.
inline
SFColor4f *DiscUIDrawObjectBase::getSFColor(void)
{
    return &_sfColor;
}

//! Get the DiscUIDrawObject::_sfOpacity field.
inline
SFReal32 *DiscUIDrawObjectBase::getSFOpacity(void)
{
    return &_sfOpacity;
}


//! Get the value of the DiscUIDrawObject::_sfCenter field.
inline
Pnt2s &DiscUIDrawObjectBase::getCenter(void)
{
    return _sfCenter.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfCenter field.
inline
const Pnt2s &DiscUIDrawObjectBase::getCenter(void) const
{
    return _sfCenter.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfCenter field.
inline
void DiscUIDrawObjectBase::setCenter(const Pnt2s &value)
{
    _sfCenter.setValue(value);
}

//! Get the value of the DiscUIDrawObject::_sfWidth field.
inline
Int16 &DiscUIDrawObjectBase::getWidth(void)
{
    return _sfWidth.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfWidth field.
inline
const Int16 &DiscUIDrawObjectBase::getWidth(void) const
{
    return _sfWidth.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfWidth field.
inline
void DiscUIDrawObjectBase::setWidth(const Int16 &value)
{
    _sfWidth.setValue(value);
}

//! Get the value of the DiscUIDrawObject::_sfHeight field.
inline
Int16 &DiscUIDrawObjectBase::getHeight(void)
{
    return _sfHeight.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfHeight field.
inline
const Int16 &DiscUIDrawObjectBase::getHeight(void) const
{
    return _sfHeight.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfHeight field.
inline
void DiscUIDrawObjectBase::setHeight(const Int16 &value)
{
    _sfHeight.setValue(value);
}

//! Get the value of the DiscUIDrawObject::_sfStartAngleRad field.
inline
Real32 &DiscUIDrawObjectBase::getStartAngleRad(void)
{
    return _sfStartAngleRad.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfStartAngleRad field.
inline
const Real32 &DiscUIDrawObjectBase::getStartAngleRad(void) const
{
    return _sfStartAngleRad.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfStartAngleRad field.
inline
void DiscUIDrawObjectBase::setStartAngleRad(const Real32 &value)
{
    _sfStartAngleRad.setValue(value);
}

//! Get the value of the DiscUIDrawObject::_sfEndAngleRad field.
inline
Real32 &DiscUIDrawObjectBase::getEndAngleRad(void)
{
    return _sfEndAngleRad.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfEndAngleRad field.
inline
const Real32 &DiscUIDrawObjectBase::getEndAngleRad(void) const
{
    return _sfEndAngleRad.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfEndAngleRad field.
inline
void DiscUIDrawObjectBase::setEndAngleRad(const Real32 &value)
{
    _sfEndAngleRad.setValue(value);
}

//! Get the value of the DiscUIDrawObject::_sfSubDivisions field.
inline
UInt16 &DiscUIDrawObjectBase::getSubDivisions(void)
{
    return _sfSubDivisions.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfSubDivisions field.
inline
const UInt16 &DiscUIDrawObjectBase::getSubDivisions(void) const
{
    return _sfSubDivisions.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfSubDivisions field.
inline
void DiscUIDrawObjectBase::setSubDivisions(const UInt16 &value)
{
    _sfSubDivisions.setValue(value);
}

//! Get the value of the DiscUIDrawObject::_sfColor field.
inline
Color4f &DiscUIDrawObjectBase::getColor(void)
{
    return _sfColor.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfColor field.
inline
const Color4f &DiscUIDrawObjectBase::getColor(void) const
{
    return _sfColor.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfColor field.
inline
void DiscUIDrawObjectBase::setColor(const Color4f &value)
{
    _sfColor.setValue(value);
}

//! Get the value of the DiscUIDrawObject::_sfOpacity field.
inline
Real32 &DiscUIDrawObjectBase::getOpacity(void)
{
    return _sfOpacity.getValue();
}

//! Get the value of the DiscUIDrawObject::_sfOpacity field.
inline
const Real32 &DiscUIDrawObjectBase::getOpacity(void) const
{
    return _sfOpacity.getValue();
}

//! Set the value of the DiscUIDrawObject::_sfOpacity field.
inline
void DiscUIDrawObjectBase::setOpacity(const Real32 &value)
{
    _sfOpacity.setValue(value);
}


OSG_END_NAMESPACE

#define OSGDISCUIDRAWOBJECTBASE_INLINE_CVSID "@(#)$Id: FCBaseTemplate_inl.h,v 1.20 2002/12/04 14:22:22 dirk Exp $"

