/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGPARTICLESYSTEMITERATOR_H_
#define _OSGPARTICLESYSTEMITERATOR_H_

#include "VSEConfig.h"
#include <OpenSG/OSGConfig.h>
#include "ParticleSystem/OSGParticleSystemConfig.h"

#include <ParticleSystem/OSGParticleSystem.h>

OSG_BEGIN_NAMESPACE

class OSG_PARTICLE_SYSTEM_CLASS_API ParticleSystemIterator
{
    /*==========================  PUBLIC  =================================*/
public:
   ParticleSystemIterator ();
   ParticleSystemIterator (const ParticleSystemIterator &source);
   friend class ParticleSystem;

   void 	operator++ (void);
   void 	operator-- (void);
   ParticleSystemIterator & 	operator= (const ParticleSystemIterator &source);
   bool 	operator== (const ParticleSystemIterator &other) const;
   bool 	operator== (const int val) const;
   bool 	operator!= (const int val) const;
   bool 	operator!= (const ParticleSystemIterator &other) const;
   ParticleSystemIterator & 	operator= (const int val);
        
   const Pnt3f     getPosition      (void) const;
   const Pnt3f     getSecPosition   (void) const;
   const Vec3f       getNormal        (void) const;
   const Color4f        getColor         (void) const;
   const Vec3f               getSize          (void) const;
   const Real32              getLifespan       (void) const;
   const Real32              getAge       (void) const;
   const Vec3f               getVelocity     (void) const;
   const Vec3f               getSecVelocity  (void) const;
   const Vec3f               getAcceleration  (void) const;
   const UInt64               getProperty  (void) const;
   
   bool isEnd(void) const;
   bool isBegin(void) const;
         
   bool killParticle(void);
   
   void setPosition(Pnt3f p);
   void setNormal(Vec3f n);
   void setColor(Color4f c);
   void setSize(Vec3f s);
   void setLifespan(Real32 l);
   void setAge(Real32 a);
   void setVelocity(Vec3f v);
   void setAcceleration(Vec3f a);
   void addProperty(UInt64 val);
   void removeProperty(UInt64 val);
   
   bool hasProperty(UInt64 val);
   
   bool isValid(void) const;
private:
   ParticleSystemIterator (const ParticleSystemPtr PSystem, 
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
                           UInt64List::iterator PropIter);
                           
   void updateSizeIter(void) const;
   void updateNormalIter(void) const;
   void updateColorIter(void) const;
   void updateLifespanIter(void) const;
   void updateVelIter(void) const;
   void updateSecVelIter(void) const;
   void updateAccelerationIter(void) const;
   void updatePropertyIter(void) const;

   mutable ParticleSystemPtr _PSystem;

   mutable Pnt3fList::iterator _PosIter;
   mutable Pnt3fList::iterator _SecPosIter;
   mutable Vec3fList::iterator _NormIter;
   mutable Vec3fList::iterator _SizeIter;
   mutable Color4fList::iterator _ColorIter;
   mutable Real32List::iterator _LifespanIter;
   mutable Real32List::iterator _AgeIter;
   mutable Vec3fList::iterator _VelIter;
   mutable Vec3fList::iterator _SecVelIter;
   mutable Vec3fList::iterator _AccIter;
   mutable UInt64List::iterator _PropIter;
   
   mutable bool _IsSizeExpanded;
   mutable bool _IsNormalExpanded;
   mutable bool _IsColorExpanded;
   mutable bool _IsLifespanExpanded;
   mutable bool _IsVelExpanded;
   mutable bool _IsSecVelExpanded;
   mutable bool _IsAccelerationExpanded;
   mutable bool _IsPropertyExpanded;
};


OSG_END_NAMESPACE

#include <ParticleSystem/OSGParticleSystemIterator.inl>

#endif /* _OSGPARTICLESYSTEMITERATOR_H_ */
