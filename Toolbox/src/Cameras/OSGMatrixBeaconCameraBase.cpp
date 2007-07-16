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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class MatrixBeaconCamera!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEMATRIXBEACONCAMERAINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGMatrixBeaconCameraBase.h"
#include "OSGMatrixBeaconCamera.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  MatrixBeaconCameraBase::TransformationMatrixFieldMask = 
    (TypeTraits<BitVector>::One << MatrixBeaconCameraBase::TransformationMatrixFieldId);

const OSG::BitVector MatrixBeaconCameraBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var Matrix          MatrixBeaconCameraBase::_sfTransformationMatrix
    
*/

//! MatrixBeaconCamera description

FieldDescription *MatrixBeaconCameraBase::_desc[] = 
{
    new FieldDescription(SFMatrix::getClassType(), 
                     "TransformationMatrix", 
                     TransformationMatrixFieldId, TransformationMatrixFieldMask,
                     false,
                     (FieldAccessMethod) &MatrixBeaconCameraBase::getSFTransformationMatrix)
};


FieldContainerType MatrixBeaconCameraBase::_type(
    "MatrixBeaconCamera",
    "Camera",
    NULL,
    (PrototypeCreateF) &MatrixBeaconCameraBase::createEmpty,
    MatrixBeaconCamera::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(MatrixBeaconCameraBase, MatrixBeaconCameraPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &MatrixBeaconCameraBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &MatrixBeaconCameraBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr MatrixBeaconCameraBase::shallowCopy(void) const 
{ 
    MatrixBeaconCameraPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const MatrixBeaconCamera *>(this)); 

    return returnValue; 
}

UInt32 MatrixBeaconCameraBase::getContainerSize(void) const 
{ 
    return sizeof(MatrixBeaconCamera); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void MatrixBeaconCameraBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((MatrixBeaconCameraBase *) &other, whichField);
}
#else
void MatrixBeaconCameraBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((MatrixBeaconCameraBase *) &other, whichField, sInfo);
}
void MatrixBeaconCameraBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void MatrixBeaconCameraBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

MatrixBeaconCameraBase::MatrixBeaconCameraBase(void) :
    _sfTransformationMatrix   (), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

MatrixBeaconCameraBase::MatrixBeaconCameraBase(const MatrixBeaconCameraBase &source) :
    _sfTransformationMatrix   (source._sfTransformationMatrix   ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

MatrixBeaconCameraBase::~MatrixBeaconCameraBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 MatrixBeaconCameraBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (TransformationMatrixFieldMask & whichField))
    {
        returnValue += _sfTransformationMatrix.getBinSize();
    }


    return returnValue;
}

void MatrixBeaconCameraBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (TransformationMatrixFieldMask & whichField))
    {
        _sfTransformationMatrix.copyToBin(pMem);
    }


}

void MatrixBeaconCameraBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (TransformationMatrixFieldMask & whichField))
    {
        _sfTransformationMatrix.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void MatrixBeaconCameraBase::executeSyncImpl(      MatrixBeaconCameraBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (TransformationMatrixFieldMask & whichField))
        _sfTransformationMatrix.syncWith(pOther->_sfTransformationMatrix);


}
#else
void MatrixBeaconCameraBase::executeSyncImpl(      MatrixBeaconCameraBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (TransformationMatrixFieldMask & whichField))
        _sfTransformationMatrix.syncWith(pOther->_sfTransformationMatrix);



}

void MatrixBeaconCameraBase::execBeginEditImpl (const BitVector &whichField, 
                                                 UInt32     uiAspect,
                                                 UInt32     uiContainerSize)
{
    Inherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

}
#endif



OSG_END_NAMESPACE

#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldDataTraits<MatrixBeaconCameraPtr>::_type("MatrixBeaconCameraPtr", "CameraPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(MatrixBeaconCameraPtr, OSG_TOOLBOXLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(MatrixBeaconCameraPtr, OSG_TOOLBOXLIB_DLLTMPLMAPPING);


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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCBaseTemplate_cpp.h,v 1.47 2006/03/17 17:03:19 pdaehne Exp $";
    static Char8 cvsid_hpp       [] = OSGMATRIXBEACONCAMERABASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMATRIXBEACONCAMERABASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMATRIXBEACONCAMERAFIELDS_HEADER_CVSID;
}

OSG_END_NAMESPACE

