/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
 **     class ArcUIDrawObject!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGArcUIDrawObjectBase.h"
#include "OSGArcUIDrawObject.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ArcUIDrawObject
    A UI ArcUIDrawObject.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Pnt2f           ArcUIDrawObjectBase::_sfCenter
    
*/

/*! \var Real32          ArcUIDrawObjectBase::_sfWidth
    
*/

/*! \var Real32          ArcUIDrawObjectBase::_sfHeight
    
*/

/*! \var Real32          ArcUIDrawObjectBase::_sfStartAngleRad
    
*/

/*! \var Real32          ArcUIDrawObjectBase::_sfEndAngleRad
    
*/

/*! \var UInt16          ArcUIDrawObjectBase::_sfSubDivisions
    
*/

/*! \var Color4f         ArcUIDrawObjectBase::_sfColor
    
*/

/*! \var Real32          ArcUIDrawObjectBase::_sfLineWidth
    
*/

/*! \var Real32          ArcUIDrawObjectBase::_sfOpacity
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ArcUIDrawObject *>::_type("ArcUIDrawObjectPtr", "UIDrawObjectPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ArcUIDrawObject *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ArcUIDrawObject *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ArcUIDrawObject *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ArcUIDrawObjectBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFPnt2f::Description(
        SFPnt2f::getClassType(),
        "Center",
        "",
        CenterFieldId, CenterFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleCenter),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleCenter));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "Width",
        "",
        WidthFieldId, WidthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleWidth),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "Height",
        "",
        HeightFieldId, HeightFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleHeight),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleHeight));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "StartAngleRad",
        "",
        StartAngleRadFieldId, StartAngleRadFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleStartAngleRad),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleStartAngleRad));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "EndAngleRad",
        "",
        EndAngleRadFieldId, EndAngleRadFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleEndAngleRad),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleEndAngleRad));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt16::Description(
        SFUInt16::getClassType(),
        "SubDivisions",
        "",
        SubDivisionsFieldId, SubDivisionsFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleSubDivisions),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleSubDivisions));

    oType.addInitialDesc(pDesc);

    pDesc = new SFColor4f::Description(
        SFColor4f::getClassType(),
        "Color",
        "",
        ColorFieldId, ColorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleColor),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleColor));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "LineWidth",
        "",
        LineWidthFieldId, LineWidthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleLineWidth),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleLineWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "Opacity",
        "",
        OpacityFieldId, OpacityFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ArcUIDrawObject::editHandleOpacity),
        static_cast<FieldGetMethodSig >(&ArcUIDrawObject::getHandleOpacity));

    oType.addInitialDesc(pDesc);
}


ArcUIDrawObjectBase::TypeObject ArcUIDrawObjectBase::_type(
    ArcUIDrawObjectBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ArcUIDrawObjectBase::createEmptyLocal),
    ArcUIDrawObject::initMethod,
    ArcUIDrawObject::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ArcUIDrawObject::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ArcUIDrawObject\"\n"
    "\tparent=\"UIDrawObject\"\n"
    "    library=\"ContribUserInterface\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "A UI ArcUIDrawObject.\n"
    "\t<Field\n"
    "\t\tname=\"Center\"\n"
    "\t\ttype=\"Pnt2f\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"0,0\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"Width\"\n"
    "\t\ttype=\"Real32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"1\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"Height\"\n"
    "\t\ttype=\"Real32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"1\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"StartAngleRad\"\n"
    "\t\ttype=\"Real32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"0.0\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"EndAngleRad\"\n"
    "\t\ttype=\"Real32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"6.283185307\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"SubDivisions\"\n"
    "\t\ttype=\"UInt16\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"24\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"Color\"\n"
    "\t\ttype=\"Color4f\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"1.0,1.0,1.0,1.0\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"LineWidth\"\n"
    "\t\ttype=\"Real32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"1.0\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"Opacity\"\n"
    "\t\ttype=\"Real32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t\tdefaultValue=\"1.0\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "A UI ArcUIDrawObject.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ArcUIDrawObjectBase::getType(void)
{
    return _type;
}

const FieldContainerType &ArcUIDrawObjectBase::getType(void) const
{
    return _type;
}

UInt32 ArcUIDrawObjectBase::getContainerSize(void) const
{
    return sizeof(ArcUIDrawObject);
}

/*------------------------- decorator get ------------------------------*/


SFPnt2f *ArcUIDrawObjectBase::editSFCenter(void)
{
    editSField(CenterFieldMask);

    return &_sfCenter;
}

const SFPnt2f *ArcUIDrawObjectBase::getSFCenter(void) const
{
    return &_sfCenter;
}


SFReal32 *ArcUIDrawObjectBase::editSFWidth(void)
{
    editSField(WidthFieldMask);

    return &_sfWidth;
}

const SFReal32 *ArcUIDrawObjectBase::getSFWidth(void) const
{
    return &_sfWidth;
}


SFReal32 *ArcUIDrawObjectBase::editSFHeight(void)
{
    editSField(HeightFieldMask);

    return &_sfHeight;
}

const SFReal32 *ArcUIDrawObjectBase::getSFHeight(void) const
{
    return &_sfHeight;
}


SFReal32 *ArcUIDrawObjectBase::editSFStartAngleRad(void)
{
    editSField(StartAngleRadFieldMask);

    return &_sfStartAngleRad;
}

const SFReal32 *ArcUIDrawObjectBase::getSFStartAngleRad(void) const
{
    return &_sfStartAngleRad;
}


SFReal32 *ArcUIDrawObjectBase::editSFEndAngleRad(void)
{
    editSField(EndAngleRadFieldMask);

    return &_sfEndAngleRad;
}

const SFReal32 *ArcUIDrawObjectBase::getSFEndAngleRad(void) const
{
    return &_sfEndAngleRad;
}


SFUInt16 *ArcUIDrawObjectBase::editSFSubDivisions(void)
{
    editSField(SubDivisionsFieldMask);

    return &_sfSubDivisions;
}

const SFUInt16 *ArcUIDrawObjectBase::getSFSubDivisions(void) const
{
    return &_sfSubDivisions;
}


SFColor4f *ArcUIDrawObjectBase::editSFColor(void)
{
    editSField(ColorFieldMask);

    return &_sfColor;
}

const SFColor4f *ArcUIDrawObjectBase::getSFColor(void) const
{
    return &_sfColor;
}


SFReal32 *ArcUIDrawObjectBase::editSFLineWidth(void)
{
    editSField(LineWidthFieldMask);

    return &_sfLineWidth;
}

const SFReal32 *ArcUIDrawObjectBase::getSFLineWidth(void) const
{
    return &_sfLineWidth;
}


SFReal32 *ArcUIDrawObjectBase::editSFOpacity(void)
{
    editSField(OpacityFieldMask);

    return &_sfOpacity;
}

const SFReal32 *ArcUIDrawObjectBase::getSFOpacity(void) const
{
    return &_sfOpacity;
}






/*------------------------------ access -----------------------------------*/

UInt32 ArcUIDrawObjectBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        returnValue += _sfCenter.getBinSize();
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        returnValue += _sfWidth.getBinSize();
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        returnValue += _sfHeight.getBinSize();
    }
    if(FieldBits::NoField != (StartAngleRadFieldMask & whichField))
    {
        returnValue += _sfStartAngleRad.getBinSize();
    }
    if(FieldBits::NoField != (EndAngleRadFieldMask & whichField))
    {
        returnValue += _sfEndAngleRad.getBinSize();
    }
    if(FieldBits::NoField != (SubDivisionsFieldMask & whichField))
    {
        returnValue += _sfSubDivisions.getBinSize();
    }
    if(FieldBits::NoField != (ColorFieldMask & whichField))
    {
        returnValue += _sfColor.getBinSize();
    }
    if(FieldBits::NoField != (LineWidthFieldMask & whichField))
    {
        returnValue += _sfLineWidth.getBinSize();
    }
    if(FieldBits::NoField != (OpacityFieldMask & whichField))
    {
        returnValue += _sfOpacity.getBinSize();
    }

    return returnValue;
}

void ArcUIDrawObjectBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        _sfCenter.copyToBin(pMem);
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        _sfHeight.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StartAngleRadFieldMask & whichField))
    {
        _sfStartAngleRad.copyToBin(pMem);
    }
    if(FieldBits::NoField != (EndAngleRadFieldMask & whichField))
    {
        _sfEndAngleRad.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SubDivisionsFieldMask & whichField))
    {
        _sfSubDivisions.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ColorFieldMask & whichField))
    {
        _sfColor.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LineWidthFieldMask & whichField))
    {
        _sfLineWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OpacityFieldMask & whichField))
    {
        _sfOpacity.copyToBin(pMem);
    }
}

void ArcUIDrawObjectBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        _sfCenter.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        _sfHeight.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StartAngleRadFieldMask & whichField))
    {
        _sfStartAngleRad.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (EndAngleRadFieldMask & whichField))
    {
        _sfEndAngleRad.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SubDivisionsFieldMask & whichField))
    {
        _sfSubDivisions.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ColorFieldMask & whichField))
    {
        _sfColor.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LineWidthFieldMask & whichField))
    {
        _sfLineWidth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OpacityFieldMask & whichField))
    {
        _sfOpacity.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ArcUIDrawObjectTransitPtr ArcUIDrawObjectBase::createLocal(BitVector bFlags)
{
    ArcUIDrawObjectTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ArcUIDrawObject>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ArcUIDrawObjectTransitPtr ArcUIDrawObjectBase::createDependent(BitVector bFlags)
{
    ArcUIDrawObjectTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ArcUIDrawObject>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ArcUIDrawObjectTransitPtr ArcUIDrawObjectBase::create(void)
{
    ArcUIDrawObjectTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ArcUIDrawObject>(tmpPtr);
    }

    return fc;
}

ArcUIDrawObject *ArcUIDrawObjectBase::createEmptyLocal(BitVector bFlags)
{
    ArcUIDrawObject *returnValue;

    newPtr<ArcUIDrawObject>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ArcUIDrawObject *ArcUIDrawObjectBase::createEmpty(void)
{
    ArcUIDrawObject *returnValue;

    newPtr<ArcUIDrawObject>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ArcUIDrawObjectBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ArcUIDrawObject *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ArcUIDrawObject *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ArcUIDrawObjectBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ArcUIDrawObject *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ArcUIDrawObject *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ArcUIDrawObjectBase::shallowCopy(void) const
{
    ArcUIDrawObject *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ArcUIDrawObject *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ArcUIDrawObjectBase::ArcUIDrawObjectBase(void) :
    Inherited(),
    _sfCenter                 (Pnt2f(0,0)),
    _sfWidth                  (Real32(1)),
    _sfHeight                 (Real32(1)),
    _sfStartAngleRad          (Real32(0.0)),
    _sfEndAngleRad            (Real32(6.283185307)),
    _sfSubDivisions           (UInt16(24)),
    _sfColor                  (Color4f(1.0,1.0,1.0,1.0)),
    _sfLineWidth              (Real32(1.0)),
    _sfOpacity                (Real32(1.0))
{
}

ArcUIDrawObjectBase::ArcUIDrawObjectBase(const ArcUIDrawObjectBase &source) :
    Inherited(source),
    _sfCenter                 (source._sfCenter                 ),
    _sfWidth                  (source._sfWidth                  ),
    _sfHeight                 (source._sfHeight                 ),
    _sfStartAngleRad          (source._sfStartAngleRad          ),
    _sfEndAngleRad            (source._sfEndAngleRad            ),
    _sfSubDivisions           (source._sfSubDivisions           ),
    _sfColor                  (source._sfColor                  ),
    _sfLineWidth              (source._sfLineWidth              ),
    _sfOpacity                (source._sfOpacity                )
{
}


/*-------------------------- destructors ----------------------------------*/

ArcUIDrawObjectBase::~ArcUIDrawObjectBase(void)
{
}


GetFieldHandlePtr ArcUIDrawObjectBase::getHandleCenter          (void) const
{
    SFPnt2f::GetHandlePtr returnValue(
        new  SFPnt2f::GetHandle(
             &_sfCenter,
             this->getType().getFieldDesc(CenterFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleCenter         (void)
{
    SFPnt2f::EditHandlePtr returnValue(
        new  SFPnt2f::EditHandle(
             &_sfCenter,
             this->getType().getFieldDesc(CenterFieldId),
             this));


    editSField(CenterFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleWidth           (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleWidth          (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             this));


    editSField(WidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleHeight          (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleHeight         (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             this));


    editSField(HeightFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleStartAngleRad   (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfStartAngleRad,
             this->getType().getFieldDesc(StartAngleRadFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleStartAngleRad  (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfStartAngleRad,
             this->getType().getFieldDesc(StartAngleRadFieldId),
             this));


    editSField(StartAngleRadFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleEndAngleRad     (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfEndAngleRad,
             this->getType().getFieldDesc(EndAngleRadFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleEndAngleRad    (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfEndAngleRad,
             this->getType().getFieldDesc(EndAngleRadFieldId),
             this));


    editSField(EndAngleRadFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleSubDivisions    (void) const
{
    SFUInt16::GetHandlePtr returnValue(
        new  SFUInt16::GetHandle(
             &_sfSubDivisions,
             this->getType().getFieldDesc(SubDivisionsFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleSubDivisions   (void)
{
    SFUInt16::EditHandlePtr returnValue(
        new  SFUInt16::EditHandle(
             &_sfSubDivisions,
             this->getType().getFieldDesc(SubDivisionsFieldId),
             this));


    editSField(SubDivisionsFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleColor           (void) const
{
    SFColor4f::GetHandlePtr returnValue(
        new  SFColor4f::GetHandle(
             &_sfColor,
             this->getType().getFieldDesc(ColorFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleColor          (void)
{
    SFColor4f::EditHandlePtr returnValue(
        new  SFColor4f::EditHandle(
             &_sfColor,
             this->getType().getFieldDesc(ColorFieldId),
             this));


    editSField(ColorFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleLineWidth       (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfLineWidth,
             this->getType().getFieldDesc(LineWidthFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleLineWidth      (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfLineWidth,
             this->getType().getFieldDesc(LineWidthFieldId),
             this));


    editSField(LineWidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr ArcUIDrawObjectBase::getHandleOpacity         (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfOpacity,
             this->getType().getFieldDesc(OpacityFieldId),
             const_cast<ArcUIDrawObjectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ArcUIDrawObjectBase::editHandleOpacity        (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfOpacity,
             this->getType().getFieldDesc(OpacityFieldId),
             this));


    editSField(OpacityFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ArcUIDrawObjectBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ArcUIDrawObject *pThis = static_cast<ArcUIDrawObject *>(this);

    pThis->execSync(static_cast<ArcUIDrawObject *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ArcUIDrawObjectBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ArcUIDrawObject *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ArcUIDrawObject *>(pRefAspect),
                  dynamic_cast<const ArcUIDrawObject *>(this));

    return returnValue;
}
#endif

void ArcUIDrawObjectBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
