/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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
 **     class MultiColorMatteBorder!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &MultiColorMatteBorderBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 MultiColorMatteBorderBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 MultiColorMatteBorderBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the MultiColorMatteBorder::_sfLeftWidth field.

inline
Real32 &MultiColorMatteBorderBase::editLeftWidth(void)
{
    editSField(LeftWidthFieldMask);

    return _sfLeftWidth.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfLeftWidth field.
inline
      Real32  MultiColorMatteBorderBase::getLeftWidth(void) const
{
    return _sfLeftWidth.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfLeftWidth field.
inline
void MultiColorMatteBorderBase::setLeftWidth(const Real32 value)
{
    editSField(LeftWidthFieldMask);

    _sfLeftWidth.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfRightWidth field.

inline
Real32 &MultiColorMatteBorderBase::editRightWidth(void)
{
    editSField(RightWidthFieldMask);

    return _sfRightWidth.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfRightWidth field.
inline
      Real32  MultiColorMatteBorderBase::getRightWidth(void) const
{
    return _sfRightWidth.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfRightWidth field.
inline
void MultiColorMatteBorderBase::setRightWidth(const Real32 value)
{
    editSField(RightWidthFieldMask);

    _sfRightWidth.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfTopWidth field.

inline
Real32 &MultiColorMatteBorderBase::editTopWidth(void)
{
    editSField(TopWidthFieldMask);

    return _sfTopWidth.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfTopWidth field.
inline
      Real32  MultiColorMatteBorderBase::getTopWidth(void) const
{
    return _sfTopWidth.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfTopWidth field.
inline
void MultiColorMatteBorderBase::setTopWidth(const Real32 value)
{
    editSField(TopWidthFieldMask);

    _sfTopWidth.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfBottomWidth field.

inline
Real32 &MultiColorMatteBorderBase::editBottomWidth(void)
{
    editSField(BottomWidthFieldMask);

    return _sfBottomWidth.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfBottomWidth field.
inline
      Real32  MultiColorMatteBorderBase::getBottomWidth(void) const
{
    return _sfBottomWidth.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfBottomWidth field.
inline
void MultiColorMatteBorderBase::setBottomWidth(const Real32 value)
{
    editSField(BottomWidthFieldMask);

    _sfBottomWidth.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfLeftLineLeftColor field.

inline
Color4f &MultiColorMatteBorderBase::editLeftLineLeftColor(void)
{
    editSField(LeftLineLeftColorFieldMask);

    return _sfLeftLineLeftColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfLeftLineLeftColor field.
inline
const Color4f &MultiColorMatteBorderBase::getLeftLineLeftColor(void) const
{
    return _sfLeftLineLeftColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfLeftLineLeftColor field.
inline
void MultiColorMatteBorderBase::setLeftLineLeftColor(const Color4f &value)
{
    editSField(LeftLineLeftColorFieldMask);

    _sfLeftLineLeftColor.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfLeftLineRightColor field.

inline
Color4f &MultiColorMatteBorderBase::editLeftLineRightColor(void)
{
    editSField(LeftLineRightColorFieldMask);

    return _sfLeftLineRightColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfLeftLineRightColor field.
inline
const Color4f &MultiColorMatteBorderBase::getLeftLineRightColor(void) const
{
    return _sfLeftLineRightColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfLeftLineRightColor field.
inline
void MultiColorMatteBorderBase::setLeftLineRightColor(const Color4f &value)
{
    editSField(LeftLineRightColorFieldMask);

    _sfLeftLineRightColor.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfTopLineTopColor field.

inline
Color4f &MultiColorMatteBorderBase::editTopLineTopColor(void)
{
    editSField(TopLineTopColorFieldMask);

    return _sfTopLineTopColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfTopLineTopColor field.
inline
const Color4f &MultiColorMatteBorderBase::getTopLineTopColor(void) const
{
    return _sfTopLineTopColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfTopLineTopColor field.
inline
void MultiColorMatteBorderBase::setTopLineTopColor(const Color4f &value)
{
    editSField(TopLineTopColorFieldMask);

    _sfTopLineTopColor.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfTopLineBottomColor field.

inline
Color4f &MultiColorMatteBorderBase::editTopLineBottomColor(void)
{
    editSField(TopLineBottomColorFieldMask);

    return _sfTopLineBottomColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfTopLineBottomColor field.
inline
const Color4f &MultiColorMatteBorderBase::getTopLineBottomColor(void) const
{
    return _sfTopLineBottomColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfTopLineBottomColor field.
inline
void MultiColorMatteBorderBase::setTopLineBottomColor(const Color4f &value)
{
    editSField(TopLineBottomColorFieldMask);

    _sfTopLineBottomColor.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfRightLineLeftColor field.

inline
Color4f &MultiColorMatteBorderBase::editRightLineLeftColor(void)
{
    editSField(RightLineLeftColorFieldMask);

    return _sfRightLineLeftColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfRightLineLeftColor field.
inline
const Color4f &MultiColorMatteBorderBase::getRightLineLeftColor(void) const
{
    return _sfRightLineLeftColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfRightLineLeftColor field.
inline
void MultiColorMatteBorderBase::setRightLineLeftColor(const Color4f &value)
{
    editSField(RightLineLeftColorFieldMask);

    _sfRightLineLeftColor.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfRightLineRightColor field.

inline
Color4f &MultiColorMatteBorderBase::editRightLineRightColor(void)
{
    editSField(RightLineRightColorFieldMask);

    return _sfRightLineRightColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfRightLineRightColor field.
inline
const Color4f &MultiColorMatteBorderBase::getRightLineRightColor(void) const
{
    return _sfRightLineRightColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfRightLineRightColor field.
inline
void MultiColorMatteBorderBase::setRightLineRightColor(const Color4f &value)
{
    editSField(RightLineRightColorFieldMask);

    _sfRightLineRightColor.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfBottomLineTopColor field.

inline
Color4f &MultiColorMatteBorderBase::editBottomLineTopColor(void)
{
    editSField(BottomLineTopColorFieldMask);

    return _sfBottomLineTopColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfBottomLineTopColor field.
inline
const Color4f &MultiColorMatteBorderBase::getBottomLineTopColor(void) const
{
    return _sfBottomLineTopColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfBottomLineTopColor field.
inline
void MultiColorMatteBorderBase::setBottomLineTopColor(const Color4f &value)
{
    editSField(BottomLineTopColorFieldMask);

    _sfBottomLineTopColor.setValue(value);
}
//! Get the value of the MultiColorMatteBorder::_sfBottomLineBottomColor field.

inline
Color4f &MultiColorMatteBorderBase::editBottomLineBottomColor(void)
{
    editSField(BottomLineBottomColorFieldMask);

    return _sfBottomLineBottomColor.getValue();
}

//! Get the value of the MultiColorMatteBorder::_sfBottomLineBottomColor field.
inline
const Color4f &MultiColorMatteBorderBase::getBottomLineBottomColor(void) const
{
    return _sfBottomLineBottomColor.getValue();
}

//! Set the value of the MultiColorMatteBorder::_sfBottomLineBottomColor field.
inline
void MultiColorMatteBorderBase::setBottomLineBottomColor(const Color4f &value)
{
    editSField(BottomLineBottomColorFieldMask);

    _sfBottomLineBottomColor.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void MultiColorMatteBorderBase::execSync (      MultiColorMatteBorderBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (LeftWidthFieldMask & whichField))
        _sfLeftWidth.syncWith(pFrom->_sfLeftWidth);

    if(FieldBits::NoField != (RightWidthFieldMask & whichField))
        _sfRightWidth.syncWith(pFrom->_sfRightWidth);

    if(FieldBits::NoField != (TopWidthFieldMask & whichField))
        _sfTopWidth.syncWith(pFrom->_sfTopWidth);

    if(FieldBits::NoField != (BottomWidthFieldMask & whichField))
        _sfBottomWidth.syncWith(pFrom->_sfBottomWidth);

    if(FieldBits::NoField != (LeftLineLeftColorFieldMask & whichField))
        _sfLeftLineLeftColor.syncWith(pFrom->_sfLeftLineLeftColor);

    if(FieldBits::NoField != (LeftLineRightColorFieldMask & whichField))
        _sfLeftLineRightColor.syncWith(pFrom->_sfLeftLineRightColor);

    if(FieldBits::NoField != (TopLineTopColorFieldMask & whichField))
        _sfTopLineTopColor.syncWith(pFrom->_sfTopLineTopColor);

    if(FieldBits::NoField != (TopLineBottomColorFieldMask & whichField))
        _sfTopLineBottomColor.syncWith(pFrom->_sfTopLineBottomColor);

    if(FieldBits::NoField != (RightLineLeftColorFieldMask & whichField))
        _sfRightLineLeftColor.syncWith(pFrom->_sfRightLineLeftColor);

    if(FieldBits::NoField != (RightLineRightColorFieldMask & whichField))
        _sfRightLineRightColor.syncWith(pFrom->_sfRightLineRightColor);

    if(FieldBits::NoField != (BottomLineTopColorFieldMask & whichField))
        _sfBottomLineTopColor.syncWith(pFrom->_sfBottomLineTopColor);

    if(FieldBits::NoField != (BottomLineBottomColorFieldMask & whichField))
        _sfBottomLineBottomColor.syncWith(pFrom->_sfBottomLineBottomColor);
}
#endif


inline
const Char8 *MultiColorMatteBorderBase::getClassname(void)
{
    return "MultiColorMatteBorder";
}
OSG_GEN_CONTAINERPTR(MultiColorMatteBorder);

OSG_END_NAMESPACE

