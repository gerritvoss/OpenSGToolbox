/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class GradientLayer!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &GradientLayerBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 GradientLayerBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
GradientLayerPtr GradientLayerBase::create(void) 
{
    GradientLayerPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = GradientLayerPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
GradientLayerPtr GradientLayerBase::createEmpty(void) 
{ 
    GradientLayerPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the GradientLayer::_sfStartPosition field.
inline
SFPnt2f *GradientLayerBase::getSFStartPosition(void)
{
    return &_sfStartPosition;
}

//! Get the GradientLayer::_sfEndPosition field.
inline
SFPnt2f *GradientLayerBase::getSFEndPosition(void)
{
    return &_sfEndPosition;
}

//! Get the GradientLayer::_mfColors field.
inline
MFColor4f *GradientLayerBase::getMFColors(void)
{
    return &_mfColors;
}

//! Get the GradientLayer::_mfStops field.
inline
MFReal32 *GradientLayerBase::getMFStops(void)
{
    return &_mfStops;
}

//! Get the GradientLayer::_sfSpreadMethod field.
inline
SFUInt32 *GradientLayerBase::getSFSpreadMethod(void)
{
    return &_sfSpreadMethod;
}


//! Get the value of the GradientLayer::_sfStartPosition field.
inline
Pnt2f &GradientLayerBase::getStartPosition(void)
{
    return _sfStartPosition.getValue();
}

//! Get the value of the GradientLayer::_sfStartPosition field.
inline
const Pnt2f &GradientLayerBase::getStartPosition(void) const
{
    return _sfStartPosition.getValue();
}

//! Set the value of the GradientLayer::_sfStartPosition field.
inline
void GradientLayerBase::setStartPosition(const Pnt2f &value)
{
    _sfStartPosition.setValue(value);
}

//! Get the value of the GradientLayer::_sfEndPosition field.
inline
Pnt2f &GradientLayerBase::getEndPosition(void)
{
    return _sfEndPosition.getValue();
}

//! Get the value of the GradientLayer::_sfEndPosition field.
inline
const Pnt2f &GradientLayerBase::getEndPosition(void) const
{
    return _sfEndPosition.getValue();
}

//! Set the value of the GradientLayer::_sfEndPosition field.
inline
void GradientLayerBase::setEndPosition(const Pnt2f &value)
{
    _sfEndPosition.setValue(value);
}

//! Get the value of the GradientLayer::_sfSpreadMethod field.
inline
UInt32 &GradientLayerBase::getSpreadMethod(void)
{
    return _sfSpreadMethod.getValue();
}

//! Get the value of the GradientLayer::_sfSpreadMethod field.
inline
const UInt32 &GradientLayerBase::getSpreadMethod(void) const
{
    return _sfSpreadMethod.getValue();
}

//! Set the value of the GradientLayer::_sfSpreadMethod field.
inline
void GradientLayerBase::setSpreadMethod(const UInt32 &value)
{
    _sfSpreadMethod.setValue(value);
}


//! Get the value of the \a index element the GradientLayer::_mfColors field.
inline
Color4f &GradientLayerBase::getColors(const UInt32 index)
{
    return _mfColors[index];
}

//! Get the GradientLayer::_mfColors field.
inline
MFColor4f &GradientLayerBase::getColors(void)
{
    return _mfColors;
}

//! Get the GradientLayer::_mfColors field.
inline
const MFColor4f &GradientLayerBase::getColors(void) const
{
    return _mfColors;
}

//! Get the value of the \a index element the GradientLayer::_mfStops field.
inline
Real32 &GradientLayerBase::getStops(const UInt32 index)
{
    return _mfStops[index];
}

//! Get the GradientLayer::_mfStops field.
inline
MFReal32 &GradientLayerBase::getStops(void)
{
    return _mfStops;
}

//! Get the GradientLayer::_mfStops field.
inline
const MFReal32 &GradientLayerBase::getStops(void) const
{
    return _mfStops;
}

OSG_END_NAMESPACE

#define OSGGRADIENTLAYERBASE_INLINE_CVSID "@(#)$Id: FCBaseTemplate_inl.h,v 1.20 2002/12/04 14:22:22 dirk Exp $"
