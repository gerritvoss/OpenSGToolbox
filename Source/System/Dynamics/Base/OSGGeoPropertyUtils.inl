/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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
#include "OSGGL.h"

OSG_BEGIN_NAMESPACE

template<class TypeT> inline
void zeroGeoPropertyTmpl(GeoVectorProperty* GeoProp)
{
    TypeT*  BasePropData(reinterpret_cast<TypeT*>(GeoProp->editData()));

    UInt32 NumElements(GeoProp->size() * GeoProp->getDimension());
    for(UInt32 i(0) ; i<NumElements ; ++i)
    {
        *BasePropData = static_cast<TypeT>(0);
        ++BasePropData;
    }
}

template<class TypeT> inline
void morphGeoPropertyTmpl(GeoVectorProperty* BaseGeoProp,
                                  GeoVectorProperty* TargetGeoProp,
                                  GeoVectorProperty* ResultGeoProp,
                                  Real32 Weight)
{
    //If this property should be treated as a normal
    if(ResultGeoProp->getUsage() & GeoProperty::UsageTangentSpace &&
       ResultGeoProp->getDimension() == 3 &&
       (
#ifndef OSG_EMBEDED
        ResultGeoProp->getFormat() == GL_FLOAT ||
        ResultGeoProp->getFormat() == GL_DOUBLE
#endif
#ifdef OSG_EMBEDED
        ResultGeoProp->getFormat() == GL_FIXED
#endif
      ))
    {
#ifndef OSG_EMBEDED
    if(ResultGeoProp->getFormat() == GL_FLOAT)
    {
        morphNormGeoPropertyTmpl<GLfloat>(BaseGeoProp,
                                 TargetGeoProp,
                                 ResultGeoProp,
                                 Weight);
    }
    else if(ResultGeoProp->getFormat() == GL_DOUBLE)
    {
        morphNormGeoPropertyTmpl<GLdouble>(BaseGeoProp,
                                 TargetGeoProp,
                                 ResultGeoProp,
                                 Weight);
    }
#endif
#ifdef OSG_EMBEDED
        morphNormGeoPropertyTmpl<GLfixed>(BaseGeoProp,
                                 TargetGeoProp,
                                 ResultGeoProp,
                                 Weight);
#endif
        return;
    }

    assert(TargetGeoProp->size() == ResultGeoProp->size() &&
           TargetGeoProp->size() == BaseGeoProp->size());

    const TypeT*  BasePropData(reinterpret_cast<const TypeT*>(BaseGeoProp->getData()));
    const TypeT*  TargetPropData(reinterpret_cast<const TypeT*>(TargetGeoProp->getData()));
    TypeT*  ResultPropData(reinterpret_cast<TypeT*>(ResultGeoProp->editData()));

    UInt32 NumElements(ResultGeoProp->size() * ResultGeoProp->getDimension());
    for(UInt32 i(0) ; i<NumElements ; ++i)
    {
        *ResultPropData += Weight * (*TargetPropData - *BasePropData);

        ++BasePropData;
        ++TargetPropData;
        ++ResultPropData;
    }
}

template<class TypeT> inline
void morphNormGeoPropertyTmpl(GeoVectorProperty* BaseGeoProp,
                          GeoVectorProperty* TargetGeoProp,
                          GeoVectorProperty* ResultGeoProp,
                          Real32 Weight)
{
    assert(TargetGeoProp->getDimension() == 3 && "Can only do Normal morphs on properties with dimension 3");
    assert(TargetGeoProp->size() == ResultGeoProp->size() &&
           TargetGeoProp->size() == BaseGeoProp->size());

    const Vector<TypeT,3>*  BasePropData(reinterpret_cast<const Vector<TypeT,3>*>(BaseGeoProp->getData()));
    const Vector<TypeT,3>*  TargetPropData(reinterpret_cast<const Vector<TypeT,3>*>(TargetGeoProp->getData()));
    Vector<TypeT,3>*  ResultPropData(reinterpret_cast<Vector<TypeT,3>*>(ResultGeoProp->editData()));

    for(UInt32 i(0) ; i<ResultGeoProp->size() ; ++i)
    {
        QuaternionBase<TypeT> q(*TargetPropData,*BasePropData);
        q.scaleAngle(Weight);
        q.multVec(*ResultPropData,*ResultPropData);

        ++BasePropData;
        ++TargetPropData;
        ++ResultPropData;
    }
}

OSG_END_NAMESPACE


