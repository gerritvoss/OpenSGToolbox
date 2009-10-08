/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
 **     class GeometryCollisionParticleSystemAffector!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &GeometryCollisionParticleSystemAffectorBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 GeometryCollisionParticleSystemAffectorBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! access the producer type of the class
inline
const EventProducerType &GeometryCollisionParticleSystemAffectorBase::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 GeometryCollisionParticleSystemAffectorBase::getProducerClassTypeId(void)
{
    return _producerType.getId();
}

//! create a new instance of the class
inline
GeometryCollisionParticleSystemAffectorPtr GeometryCollisionParticleSystemAffectorBase::create(void) 
{
    GeometryCollisionParticleSystemAffectorPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = GeometryCollisionParticleSystemAffectorPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
GeometryCollisionParticleSystemAffectorPtr GeometryCollisionParticleSystemAffectorBase::createEmpty(void) 
{ 
    GeometryCollisionParticleSystemAffectorPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the GeometryCollisionParticleSystemAffector::_mfCollisionAffectors field.
inline
const MFParticleAffectorPtr *GeometryCollisionParticleSystemAffectorBase::getMFCollisionAffectors(void) const
{
    return &_mfCollisionAffectors;
}

//! Get the GeometryCollisionParticleSystemAffector::_mfCollisionAffectors field.
inline
MFParticleAffectorPtr *GeometryCollisionParticleSystemAffectorBase::editMFCollisionAffectors(void)
{
    return &_mfCollisionAffectors;
}

//! Get the GeometryCollisionParticleSystemAffector::_sfCollisionNode field.
inline
const SFNodePtr *GeometryCollisionParticleSystemAffectorBase::getSFCollisionNode(void) const
{
    return &_sfCollisionNode;
}

//! Get the GeometryCollisionParticleSystemAffector::_sfCollisionNode field.
inline
SFNodePtr *GeometryCollisionParticleSystemAffectorBase::editSFCollisionNode(void)
{
    return &_sfCollisionNode;
}


//! Get the value of the GeometryCollisionParticleSystemAffector::_sfCollisionNode field.
inline
NodePtr &GeometryCollisionParticleSystemAffectorBase::editCollisionNode(void)
{
    return _sfCollisionNode.getValue();
}

//! Get the value of the GeometryCollisionParticleSystemAffector::_sfCollisionNode field.
inline
const NodePtr &GeometryCollisionParticleSystemAffectorBase::getCollisionNode(void) const
{
    return _sfCollisionNode.getValue();
}

//! Set the value of the GeometryCollisionParticleSystemAffector::_sfCollisionNode field.
inline
void GeometryCollisionParticleSystemAffectorBase::setCollisionNode(const NodePtr &value)
{
    _sfCollisionNode.setValue(value);
}


//! Get the value of the \a index element the GeometryCollisionParticleSystemAffector::_mfCollisionAffectors field.
inline
ParticleAffectorPtr &GeometryCollisionParticleSystemAffectorBase::editCollisionAffectors(const UInt32 index)
{
    return _mfCollisionAffectors[index];
}

//! Get the value of the \a index element the GeometryCollisionParticleSystemAffector::_mfCollisionAffectors field.
inline
const ParticleAffectorPtr &GeometryCollisionParticleSystemAffectorBase::getCollisionAffectors(const UInt32 index) const
{
    return _mfCollisionAffectors[index];
}

#ifndef OSG_2_PREP
//! Get the GeometryCollisionParticleSystemAffector::_mfCollisionAffectors field.
inline
MFParticleAffectorPtr &GeometryCollisionParticleSystemAffectorBase::getCollisionAffectors(void)
{
    return _mfCollisionAffectors;
}

//! Get the GeometryCollisionParticleSystemAffector::_mfCollisionAffectors field.
inline
const MFParticleAffectorPtr &GeometryCollisionParticleSystemAffectorBase::getCollisionAffectors(void) const
{
    return _mfCollisionAffectors;
}

#endif

inline
EventConnection GeometryCollisionParticleSystemAffectorBase::attachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId)
{
    return _Producer.attachActivity(TheActivity, ProducedEventId);
}

inline
bool GeometryCollisionParticleSystemAffectorBase::isActivityAttached(ActivityPtr TheActivity, UInt32 ProducedEventId) const
{
    return _Producer.isActivityAttached(TheActivity, ProducedEventId);
}

inline
UInt32 GeometryCollisionParticleSystemAffectorBase::getNumActivitiesAttached(UInt32 ProducedEventId) const
{
    return _Producer.getNumActivitiesAttached(ProducedEventId);
}

inline
ActivityPtr GeometryCollisionParticleSystemAffectorBase::getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
{
    return _Producer.getAttachedActivity(ProducedEventId,ActivityIndex);
}

inline
void GeometryCollisionParticleSystemAffectorBase::detachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId)
{
    _Producer.detachActivity(TheActivity, ProducedEventId);
}

inline
UInt32 GeometryCollisionParticleSystemAffectorBase::getNumProducedEvents(void) const
{
    return _Producer.getNumProducedEvents();
}

inline
const MethodDescription *GeometryCollisionParticleSystemAffectorBase::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return _Producer.getProducedEventDescription(ProducedEventName);
}

inline
const MethodDescription *GeometryCollisionParticleSystemAffectorBase::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return _Producer.getProducedEventDescription(ProducedEventId);
}

inline
UInt32 GeometryCollisionParticleSystemAffectorBase::getProducedEventId(const Char8 *ProducedEventName) const
{
    return _Producer.getProducedEventId(ProducedEventName);
}
OSG_END_NAMESPACE

