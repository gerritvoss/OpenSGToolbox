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

inline
UInt32 ParticleSystem::numParticles(void) const
{
   return getPositions().size();
}

inline
UInt64 ParticleSystem::createNewPropType(void)
{
   if(_numPropTypes >= 64)
   {
      return 0;
   }
   else
   {
      ++_numPropTypes;
      return osg::osgpow(static_cast<UInt64>(2), static_cast<UInt64>(_numPropTypes-1) );
   }
}

inline
void ParticleSystem::setPosition(Pnt3f& val, Pnt3fList::iterator i)
{
   (*i) = val;
}

inline
void ParticleSystem::setNormal(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter)
{
   if(getNormals().size() == 1 && val != getNormals().front())
   {
      //Expand
      expandNormal();
      //Move Iter to correct Position
      i = getNormals().begin();
      Pnt3fList::iterator Iter;
      for(Iter = getPositions().begin() ; Iter != getPositions().end() ; ++Iter)
      {
         if(Iter == PosIter)
         {
            break;
         }
         ++i;
      }
   }
   (*i) = val;
}

inline
void ParticleSystem::setSize(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter)
{
   if(getSizes().size() == 1 && val != getSizes().front())
   {
      //Expand
      expandSize();
      //Move Iter to correct Position
      i = getSizes().begin();
      Pnt3fList::iterator Iter;
      for(Iter = getPositions().begin() ; Iter != getPositions().end() ; ++Iter)
      {
         if(Iter == PosIter)
         {
            break;
         }
         ++i;
      }
   }
   (*i) = val;
}

inline
void ParticleSystem::setColor(Color4f& val, Color4fList::iterator& i, Pnt3fList::iterator PosIter)
{
   if(getColors().size() == 1 && val != getColors().front())
   {
      //Expand
      expandColor();
      //Move Iter to correct Position
      i = getColors().begin();
      Pnt3fList::iterator Iter;
      for(Iter = getPositions().begin() ; Iter != getPositions().end() ; ++Iter)
      {
         if(Iter == PosIter)
         {
            break;
         }
         ++i;
      }
   }
   (*i) = val;
}

inline
void ParticleSystem::setLifespan(Real32& val, Real32List::iterator& i, Pnt3fList::iterator PosIter)
{
   if(getLifespan().size() == 1 && val != getLifespan().front())
   {
      //Expand
      expandLifespan();
      //Move Iter to correct Position
      i = getLifespan().begin();
      Pnt3fList::iterator Iter;
      for(Iter = getPositions().begin() ; Iter != getPositions().end() ; ++Iter)
      {
         if(Iter == PosIter)
         {
            break;
         }
         ++i;
      }
   }
   (*i) = val;
}

inline
void ParticleSystem::setAge(Real32& val, Real32List::iterator& i, Pnt3fList::iterator PosIter)
{
   (*i) = val;
}

inline
void ParticleSystem::setVelocity(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter)
{
   if(getVelocities().size() == 1 && val != getVelocities().front())
   {
      //Expand
      expandVelocity();
      //Expand
      expandSecVelocity();
      
      //Move Iter to correct Position
      i = getVelocities().begin();
      Pnt3fList::iterator Iter;
      for(Iter = getPositions().begin() ; Iter != getPositions().end() ; ++Iter)
      {
         if(Iter == PosIter)
         {
            break;
         }
         ++i;
      }
   }
   (*i) = val;
}

inline
void ParticleSystem::setAcceleration(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter)
{
   if(getAccelerations().size() == 1 && val != getAccelerations().front())
   {
      //Expand
      expandAcceleration();
      //Move Iter to correct Position
      i = getAccelerations().begin();
      Pnt3fList::iterator Iter;
      for(Iter = getPositions().begin() ; Iter != getPositions().end() ; ++Iter)
      {
         if(Iter == PosIter)
         {
            break;
         }
         ++i;
      }
   }
   (*i) = val;
}

inline
void ParticleSystem::addProperty(UInt64& val, UInt64List::iterator& i, Pnt3fList::iterator PosIter)
{
   if(getProperties().size() == 1 && (val & getProperties().front()) != val)
   {
      //Expand
      expandProperty();
      //Move Iter to correct Position
      i = getProperties().begin();
      Pnt3fList::iterator Iter;
      for(Iter = getPositions().begin() ; Iter != getPositions().end() ; ++Iter)
      {
         if(Iter == PosIter)
         {
            break;
         }
         ++i;
      }
   }
   (*i) |= val;
}

inline
void ParticleSystem::removeProperty(UInt64& val, UInt64List::iterator i)
{
   (*i) = (*i) & (~val);
}

inline
bool ParticleSystem::hasProperty(UInt64& val, UInt64List::iterator i)
{
   return ( ((*i) & val) == val );
}

inline
void ParticleSystem::expandSecPosition(void)
{
   getSecPositions().resize( getPositions().size(), getSecPositions().front() );
}

inline
void ParticleSystem::expandSize(void)
{
   getSizes().resize( getPositions().size(), getSizes().front() );
}

inline
void ParticleSystem::expandNormal(void)
{
   getNormals().resize( getPositions().size(), getNormals().front() );
}

inline
void ParticleSystem::expandColor(void)
{
   getColors().resize( getPositions().size(), getColors().front() );
}

inline
void ParticleSystem::expandLifespan(void)
{
   getLifespan().resize( getPositions().size(), getLifespan().front() );
}

inline
void ParticleSystem::expandAge(void)
{
   getAge().resize( getPositions().size(), getAge().front() );
}

inline
void ParticleSystem::expandVelocity(void)
{
   getVelocities().resize( getPositions().size(), getVelocities().front() );
}

inline
void ParticleSystem::expandSecVelocity(void)
{
   getSecVelocities().resize( getPositions().size(), getSecVelocities().front() );
}

inline
void ParticleSystem::expandAcceleration(void)
{
   getAccelerations().resize( getPositions().size(), getAccelerations().front() );
}

inline
void ParticleSystem::expandProperty(void)
{
   getProperties().resize( getPositions().size(), getProperties().front() );
}
/*------------------------------ access -----------------------------------*/

inline
void ParticleSystem::setMaterial(const MaterialPtr &value)
{
    setRefdCP(_sfMaterial.getValue(), value);
}

OSG_END_NAMESPACE
