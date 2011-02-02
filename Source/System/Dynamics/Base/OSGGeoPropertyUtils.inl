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
#include "OSGQuaternion.h"
#include "OSGBaseTypeTraits.h"

OSG_BEGIN_NAMESPACE

template<class TypeT> inline
void zeroGeoPropertyTmpl(GeoVectorProperty* GeoProp)
{
    //If this property should be treated as a normal
    if(GeoProp->getUsage() & GeoProperty::UsageTangentSpace &&
       GeoProp->getDimension() == 3 &&
       (
        GeoProp->getFormat() == GL_FLOAT ||
        GeoProp->getFormat() == GL_DOUBLE/* ||*/
        /*GeoProp->getFormat() == GL_FIXED*/
      ))
    {
        if(GeoProp->getFormat() == GL_FLOAT)
        {
            zeroNormGeoPropertyTmpl<GLfloat>(GeoProp);
        }
        else if(GeoProp->getFormat() == GL_DOUBLE)
        {
            zeroNormGeoPropertyTmpl<GLdouble>(GeoProp);
        }
        return;
    }

    TypeT*  BasePropData(reinterpret_cast<TypeT*>(GeoProp->editData()));

    UInt32 NumElements(GeoProp->size() * GeoProp->getDimension());
    TypeT ZeroElement(TypeTraits<TypeT>::getZeroElement());
    for(UInt32 i(0) ; i<NumElements ; ++i)
    {
        *BasePropData = ZeroElement;
        ++BasePropData;
    }
}

template<class TypeT> inline
void zeroNormGeoPropertyTmpl(GeoVectorProperty* GeoProp)
{
    assert(GeoProp->getDimension() == 3 && "Can only do Normal zeroing on properties with dimension 3");

    TypeT*  GeoPropData(reinterpret_cast<TypeT*>(GeoProp->editData()));

    UInt32 NumElements(GeoProp->size() * GeoProp->getDimension());
    TypeT ZeroElement(TypeTraits<TypeT>::getZeroElement());
    TypeT OneElement(TypeTraits<TypeT>::getOneElement());
    for(UInt32 i(0) ; i<NumElements ; ++i)
    {
        if((i % 3) == 2)
        {
            *GeoPropData = OneElement;
        }
        else
        {
            *GeoPropData = ZeroElement;
        }
        ++GeoPropData;
    }
}

template<class TypeT> inline
void morphGeoPropertyTmpl(GeoVectorProperty* TargetGeoProp,
                          GeoVectorProperty* ResultGeoProp,
                          Real32 Weight)
{
    //If this property should be treated as a normal
    if(ResultGeoProp->getUsage() & GeoProperty::UsageTangentSpace &&
       ResultGeoProp->getDimension() == 3 &&
       (
        ResultGeoProp->getFormat() == GL_FLOAT ||
        ResultGeoProp->getFormat() == GL_DOUBLE/* ||*/
        /*ResultGeoProp->getFormat() == GL_FIXED*/
      ))
    {
        if(ResultGeoProp->getFormat() == GL_FLOAT)
        {
            morphNormGeoPropertyTmpl<GLfloat>(TargetGeoProp,
                                              ResultGeoProp,
                                              Weight);
        }
        else if(ResultGeoProp->getFormat() == GL_DOUBLE)
        {
            morphNormGeoPropertyTmpl<GLdouble>(TargetGeoProp,
                                               ResultGeoProp,
                                               Weight);
        }
        //else if(ResultGeoProp->getFormat() == GL_FIXED)
        //{
        //morphNormGeoPropertyTmpl<GLfixed>(TargetGeoProp,
        //ResultGeoProp,
        //Weight);
        //return;
        return;
    }

    assert(TargetGeoProp->size() == ResultGeoProp->size());

    const TypeT*  TargetPropData(reinterpret_cast<const TypeT*>(TargetGeoProp->getData()));
    TypeT*  ResultPropData(reinterpret_cast<TypeT*>(ResultGeoProp->editData()));

    UInt32 NumElements(ResultGeoProp->size() * ResultGeoProp->getDimension());
    for(UInt32 i(0) ; i<NumElements ; ++i)
    {
        *ResultPropData += Weight * (*TargetPropData);

        ++TargetPropData;
        ++ResultPropData;
    }
}

template<class TypeT> inline
void morphNormGeoPropertyTmpl(GeoVectorProperty* TargetGeoProp,
                              GeoVectorProperty* ResultGeoProp,
                              Real32 Weight)
{
    assert(TargetGeoProp->getDimension() == 3 && "Can only do Normal morphs on properties with dimension 3");
    assert(TargetGeoProp->size() == ResultGeoProp->size());

    const Vector<TypeT,3>*  TargetPropData(reinterpret_cast<const Vector<TypeT,3>*>(TargetGeoProp->getData()));
    Vector<TypeT,3>*  ResultPropData(reinterpret_cast<Vector<TypeT,3>*>(ResultGeoProp->editData()));

    Vector<TypeT,3> BaseNormal(TypeTraits<TypeT>::getZeroElement(),
                               TypeTraits<TypeT>::getZeroElement(),
                               TypeTraits<TypeT>::getOneElement());
    for(UInt32 i(0) ; i<ResultGeoProp->size() ; ++i)
    {
        QuaternionBase<TypeT> q(*TargetPropData,BaseNormal);
        q.scaleAngle(Weight);
        q.multVec(*ResultPropData,*ResultPropData);

        ++TargetPropData;
        ++ResultPropData;
    }
}

OSG_END_NAMESPACE


