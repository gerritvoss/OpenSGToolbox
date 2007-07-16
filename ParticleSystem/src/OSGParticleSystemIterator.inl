/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE
inline ParticleSystemIterator::ParticleSystemIterator() :
                     _PosIter(NULL),
                     _SecPosIter(NULL),
                     _NormIter(NULL),
                     _SizeIter(NULL),
                     _ColorIter(NULL),
                     _LifespanIter(NULL),
                     _AgeIter(NULL),
                     _VelIter(NULL),
                     _SecVelIter(NULL),
                     _AccIter(NULL),
                     _PropIter(NULL),
                     _IsSizeExpanded(false),
                     _IsNormalExpanded(false),
                     _IsColorExpanded(false),
                     _IsLifespanExpanded(false),
                     _IsVelExpanded(false),
                     _IsSecVelExpanded(false),
                     _IsAccelerationExpanded(false),
                     _IsPropertyExpanded(false)
{
}

inline 
ParticleSystemIterator::ParticleSystemIterator(const ParticleSystemIterator &source)
{
   _PSystem = source._PSystem;
   _PosIter = source._PosIter;
   _SecPosIter = source._SecPosIter;
   _NormIter = source._NormIter;
   _SizeIter = source._SizeIter;
   _ColorIter = source._ColorIter;
   _LifespanIter = source._LifespanIter;
   _AgeIter = source._AgeIter;
   _VelIter = source._VelIter;
   _SecVelIter = source._SecVelIter;
   _AccIter = source._AccIter;
   _PropIter = source._PropIter;
   
   _IsSizeExpanded = source._IsSizeExpanded;
   _IsNormalExpanded = source._IsNormalExpanded;
   _IsColorExpanded = source._IsColorExpanded;
   _IsLifespanExpanded = source._IsLifespanExpanded;
   _IsVelExpanded = source._IsVelExpanded;
   _IsSecVelExpanded = source._IsSecVelExpanded;
   _IsAccelerationExpanded = source._IsAccelerationExpanded;
   _IsPropertyExpanded = source._IsPropertyExpanded;
}

inline
bool 	ParticleSystemIterator::operator== (const int val) const
{
   return (val == NULL && _PosIter == NULL);
}

inline
bool 	ParticleSystemIterator::operator!= (const int val) const
{
   return (val == NULL && _PosIter != NULL);
}

inline
ParticleSystemIterator& 	ParticleSystemIterator::operator= (const int val)
{
   if(val == NULL)
   {
      _PosIter = NULL;
   }
   return *this;
}

inline
bool ParticleSystemIterator::isEnd(void) const
{
   return _PosIter == _PSystem->getPositions().end();
}

inline
bool ParticleSystemIterator::isBegin(void) const
{
   return _PosIter == _PSystem->getPositions().begin();
}

inline
bool ParticleSystemIterator::killParticle(void)
{
   updateSizeIter();
   updateNormalIter();
   updateColorIter();
   updateLifespanIter();
   updateVelIter();
   updateSecVelIter();
   updateAccelerationIter();
   updatePropertyIter();
   
   ParticleSystemIterator temp(*this);
   ++temp;
   
   bool val = _PSystem->killParticle(_PosIter,
                           _SecPosIter,
                           _NormIter,
                           _SizeIter,
                           _ColorIter,
                           _LifespanIter,
                           _AgeIter,
                           _VelIter,
                           _SecVelIter,
                           _AccIter,
                           _PropIter);
   *this = temp;
   return val;
}

inline
const Pnt3f ParticleSystemIterator::getPosition(void) const
{
   return (*_PosIter);
}

inline
const Pnt3f ParticleSystemIterator::getSecPosition(void) const
{
   return (*_SecPosIter);
}

inline
const Vec3f ParticleSystemIterator::getNormal(void) const
{
   updateNormalIter();
   return (*_NormIter);
}

inline
const Color4f ParticleSystemIterator::getColor(void) const
{
   updateColorIter();
   return (*_ColorIter);
}

inline
const Vec3f ParticleSystemIterator::getSize(void) const
{
   updateSizeIter();
   return (*_SizeIter);
}

inline
const Real32 ParticleSystemIterator::getLifespan(void) const
{
   updateLifespanIter();
   return (*_LifespanIter);
}

inline
const Real32 ParticleSystemIterator::getAge(void) const
{
   return (*_AgeIter);
}

inline
const Vec3f ParticleSystemIterator::getVelocity(void) const
{
   updateVelIter();
   return (*_VelIter);
}

inline
const Vec3f ParticleSystemIterator::getSecVelocity(void) const
{
   updateSecVelIter();
   return (*_SecVelIter);
}

inline
const Vec3f ParticleSystemIterator::getAcceleration(void) const
{
   updateAccelerationIter();
   return (*_AccIter);
}

inline
const UInt64 ParticleSystemIterator::getProperty(void) const
{
   updatePropertyIter();
   return (*_PropIter);
}

inline
void ParticleSystemIterator::setPosition(Pnt3f p)
{
    _PSystem->setPosition(p, _PosIter);
}

inline
void ParticleSystemIterator::setNormal(Vec3f n)
{
    updateNormalIter();
    _PSystem->setNormal(n, _NormIter, _PosIter);
    updateNormalIter();
}

inline
void ParticleSystemIterator::setColor(Color4f c)
{
    updateColorIter();
    _PSystem->setColor(c, _ColorIter, _PosIter);
    updateColorIter();
}

inline
void ParticleSystemIterator::setSize(Vec3f s)
{
    updateSizeIter();
    _PSystem->setSize(s, _SizeIter, _PosIter);
    updateSizeIter();
}

inline
void ParticleSystemIterator::setLifespan(Real32 l)
{
    updateLifespanIter();
    _PSystem->setLifespan(l, _LifespanIter, _PosIter);
    updateLifespanIter();
}

inline
void ParticleSystemIterator::setAge(Real32 a)
{
    _PSystem->setAge(a, _AgeIter, _PosIter);
}

inline
void ParticleSystemIterator::setVelocity(Vec3f v)
{
    updateVelIter();
    updateSecVelIter();
    _PSystem->setVelocity(v, _VelIter, _PosIter);
    updateVelIter();
    updateSecVelIter();
}

inline
void ParticleSystemIterator::setAcceleration(Vec3f a)
{
    updateAccelerationIter();
    _PSystem->setAcceleration(a, _AccIter, _PosIter);
    updateAccelerationIter();
}


inline
void ParticleSystemIterator::addProperty(UInt64 val)
{
    updatePropertyIter();
    _PSystem->addProperty(val, _PropIter, _PosIter);
    updatePropertyIter();
}

inline
void ParticleSystemIterator::removeProperty(UInt64 val)
{
    updatePropertyIter();
    _PSystem->removeProperty(val, _PropIter);
    updatePropertyIter();
}

inline
bool ParticleSystemIterator::hasProperty(UInt64 val)
{
   updatePropertyIter();
   return _PSystem->hasProperty(val, _PropIter);
   updatePropertyIter();
}

inline
ParticleSystemIterator::ParticleSystemIterator (const ParticleSystemPtr PSystem, 
                           Pnt3fList::iterator PosIter,
                           Pnt3fList::iterator SecPosIter,
                           Vec3fList::iterator NormIter,
                           Vec3fList::iterator SizeIter,
                           Color4fList::iterator ColorIter,
                           Real32List::iterator LifespanIter,
                           Real32List::iterator AgeIter,
                           Vec3fList::iterator VelIter,
                           Vec3fList::iterator SecVelIter,
                           Vec3fList::iterator AccIter,
                           UInt64List::iterator PropIter) : _PSystem(PSystem),
                           _PosIter(PosIter),
                           _SecPosIter(SecPosIter),
                           _NormIter(NormIter),
                           _SizeIter(SizeIter),
                           _ColorIter(ColorIter),
                           _LifespanIter(LifespanIter),
                           _AgeIter(AgeIter),
                           _VelIter(VelIter),
                           _SecVelIter(SecVelIter),
                           _AccIter(AccIter),
                           _PropIter(PropIter)
{
   _IsSizeExpanded = (_PSystem->getSizes().size() > 1);
   _IsNormalExpanded = (_PSystem->getNormals().size() > 1);
   _IsColorExpanded = (_PSystem->getColors().size() > 1);
   _IsLifespanExpanded = (_PSystem->getLifespan().size() > 1);
   _IsVelExpanded = (_PSystem->getVelocities().size() > 1);
   _IsSecVelExpanded = (_PSystem->getSecVelocities().size() > 1);
   _IsAccelerationExpanded = (_PSystem->getAccelerations().size() > 1);
   _IsPropertyExpanded = (_PSystem->getProperties().size() > 1);
}

inline 
ParticleSystemIterator& 	ParticleSystemIterator::operator= (const ParticleSystemIterator &source)
{
   _PSystem = source._PSystem;
   _PosIter = source._PosIter;
   _SecPosIter = source._SecPosIter;
   _NormIter = source._NormIter;
   _SizeIter = source._SizeIter;
   _ColorIter = source._ColorIter;
   _LifespanIter = source._LifespanIter;
   _AgeIter = source._AgeIter;
   _VelIter = source._VelIter;
   _SecVelIter = source._SecVelIter;
   _AccIter = source._AccIter;
   _PropIter = source._PropIter;
   
   _IsSizeExpanded = source._IsSizeExpanded;
   _IsNormalExpanded = source._IsNormalExpanded;
   _IsColorExpanded = source._IsColorExpanded;
   _IsLifespanExpanded = source._IsLifespanExpanded;
   _IsVelExpanded = source._IsVelExpanded;
   _IsSecVelExpanded = source._IsSecVelExpanded;
   _IsAccelerationExpanded = source._IsAccelerationExpanded;
   _IsPropertyExpanded = source._IsPropertyExpanded;
   
   return *this;
}

inline
void 	ParticleSystemIterator::operator++ (void)
{
   if(_PosIter != _PSystem->getPositions().end())
   {
      updateSizeIter();
      updateNormalIter();
      updateColorIter();
      updateLifespanIter();
      updateVelIter();
      updateSecVelIter();
      updateAccelerationIter();
      updatePropertyIter();
      ++_PosIter;
      ++_SecPosIter;
      if(_PSystem->getNormals().size() > 1){++_NormIter;}
      if(_PSystem->getSizes().size() > 1){++_SizeIter;}
      if(_PSystem->getColors().size() > 1){++_ColorIter;}
      if(_PSystem->getLifespan().size() > 1){++_LifespanIter;}
      ++_AgeIter;
      if(_PSystem->getVelocities().size() > 1){++_VelIter;}
      //if(_PSystem->getSecVelocities().size() > 1){++_SecVelIter;}
      if(_PSystem->getAccelerations().size() > 1){++_AccIter;}
      if(_PSystem->getProperties().size() > 1){++_PropIter;}
   }
}

inline
void 	ParticleSystemIterator::operator-- (void)
{
   if(_PosIter != _PSystem->getPositions().begin())
   {
      updateSizeIter();
      updateNormalIter();
      updateColorIter();
      updateLifespanIter();
      updateVelIter();
      updateSecVelIter();
      updateAccelerationIter();
      updatePropertyIter();
      --_PosIter;
      --_SecPosIter;
      if(_PSystem->getNormals().size() > 1){--_NormIter;}
      if(_PSystem->getSizes().size() > 1){--_SizeIter;}
      if(_PSystem->getColors().size() > 1){--_ColorIter;}
      if(_PSystem->getLifespan().size() > 1){--_LifespanIter;}
      --_AgeIter;
      if(_PSystem->getVelocities().size() > 1){--_VelIter;}
      //if(_PSystem->getSecVelocities().size() > 1){--_SecVelIter;}
      if(_PSystem->getAccelerations().size() > 1){--_AccIter;}
      if(_PSystem->getProperties().size() > 1){--_PropIter;}
   }
}

inline
bool 	ParticleSystemIterator::operator== (const ParticleSystemIterator &other) const
{
   return (_PSystem == other._PSystem) && (_PosIter == other._PosIter);
}

inline
bool 	ParticleSystemIterator::operator!= (const ParticleSystemIterator &other) const
{
   return (_PSystem == other._PSystem) && (_PosIter != other._PosIter);
}
   
OSG_END_NAMESPACE
