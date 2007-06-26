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
 **     class Component!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &ComponentBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 ComponentBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 


/*------------------------------ get -----------------------------------*/

//! Get the Component::_sfMinSize field.
inline
SFVec2s *ComponentBase::getSFMinSize(void)
{
    return &_sfMinSize;
}

//! Get the Component::_sfMaxSize field.
inline
SFVec2s *ComponentBase::getSFMaxSize(void)
{
    return &_sfMaxSize;
}

//! Get the Component::_sfPreferredSize field.
inline
SFVec2s *ComponentBase::getSFPreferredSize(void)
{
    return &_sfPreferredSize;
}

//! Get the Component::_sfSize field.
inline
SFVec2s *ComponentBase::getSFSize(void)
{
    return &_sfSize;
}

//! Get the Component::_sfVisible field.
inline
SFBool *ComponentBase::getSFVisible(void)
{
    return &_sfVisible;
}

//! Get the Component::_sfEnabled field.
inline
SFBool *ComponentBase::getSFEnabled(void)
{
    return &_sfEnabled;
}

//! Get the Component::_sfConstraints field.
inline
SFLayoutConstraintsPtr *ComponentBase::getSFConstraints(void)
{
    return &_sfConstraints;
}


//! Get the value of the Component::_sfMinSize field.
inline
Vec2s &ComponentBase::getMinSize(void)
{
    return _sfMinSize.getValue();
}

//! Get the value of the Component::_sfMinSize field.
inline
const Vec2s &ComponentBase::getMinSize(void) const
{
    return _sfMinSize.getValue();
}

//! Set the value of the Component::_sfMinSize field.
inline
void ComponentBase::setMinSize(const Vec2s &value)
{
    _sfMinSize.setValue(value);
}

//! Get the value of the Component::_sfMaxSize field.
inline
Vec2s &ComponentBase::getMaxSize(void)
{
    return _sfMaxSize.getValue();
}

//! Get the value of the Component::_sfMaxSize field.
inline
const Vec2s &ComponentBase::getMaxSize(void) const
{
    return _sfMaxSize.getValue();
}

//! Set the value of the Component::_sfMaxSize field.
inline
void ComponentBase::setMaxSize(const Vec2s &value)
{
    _sfMaxSize.setValue(value);
}

//! Get the value of the Component::_sfPreferredSize field.
inline
Vec2s &ComponentBase::getPreferredSize(void)
{
    return _sfPreferredSize.getValue();
}

//! Get the value of the Component::_sfPreferredSize field.
inline
const Vec2s &ComponentBase::getPreferredSize(void) const
{
    return _sfPreferredSize.getValue();
}

//! Set the value of the Component::_sfPreferredSize field.
inline
void ComponentBase::setPreferredSize(const Vec2s &value)
{
    _sfPreferredSize.setValue(value);
}

//! Get the value of the Component::_sfSize field.
inline
Vec2s &ComponentBase::getSize(void)
{
    return _sfSize.getValue();
}

//! Get the value of the Component::_sfSize field.
inline
const Vec2s &ComponentBase::getSize(void) const
{
    return _sfSize.getValue();
}

//! Set the value of the Component::_sfSize field.
inline
void ComponentBase::setSize(const Vec2s &value)
{
    _sfSize.setValue(value);
}

//! Get the value of the Component::_sfVisible field.
inline
bool &ComponentBase::getVisible(void)
{
    return _sfVisible.getValue();
}

//! Get the value of the Component::_sfVisible field.
inline
const bool &ComponentBase::getVisible(void) const
{
    return _sfVisible.getValue();
}

//! Set the value of the Component::_sfVisible field.
inline
void ComponentBase::setVisible(const bool &value)
{
    _sfVisible.setValue(value);
}

//! Get the value of the Component::_sfEnabled field.
inline
bool &ComponentBase::getEnabled(void)
{
    return _sfEnabled.getValue();
}

//! Get the value of the Component::_sfEnabled field.
inline
const bool &ComponentBase::getEnabled(void) const
{
    return _sfEnabled.getValue();
}

//! Set the value of the Component::_sfEnabled field.
inline
void ComponentBase::setEnabled(const bool &value)
{
    _sfEnabled.setValue(value);
}

//! Get the value of the Component::_sfConstraints field.
inline
LayoutConstraintsPtr &ComponentBase::getConstraints(void)
{
    return _sfConstraints.getValue();
}

//! Get the value of the Component::_sfConstraints field.
inline
const LayoutConstraintsPtr &ComponentBase::getConstraints(void) const
{
    return _sfConstraints.getValue();
}

//! Set the value of the Component::_sfConstraints field.
inline
void ComponentBase::setConstraints(const LayoutConstraintsPtr &value)
{
    _sfConstraints.setValue(value);
}


OSG_END_NAMESPACE

#define OSGCOMPONENTBASE_INLINE_CVSID "@(#)$Id: FCBaseTemplate_inl.h,v 1.20 2002/12/04 14:22:22 dirk Exp $"

