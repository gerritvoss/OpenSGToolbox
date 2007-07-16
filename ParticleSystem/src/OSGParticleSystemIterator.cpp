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
#include "OSGParticleSystemIterator.h"

OSG_BEGIN_NAMESPACE

bool ParticleSystemIterator::isValid(void) const
{
   for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PSystem->getPositions().end() ; ++tPosIter)
   {
      if(tPosIter == _PosIter)
      {
         return true;
      }
   }
   return false;
}

void ParticleSystemIterator::updateSizeIter(void) const
{
   if(_IsSizeExpanded != (_PSystem->getSizes().size() > 1))
   {
      _SizeIter = _PSystem->getSizes().begin();
      if(_PSystem->getSizes().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_SizeIter;
         }
      }
      
      _IsSizeExpanded = (_PSystem->getSizes().size() > 1);
   }
   else if(_PSystem->getSizes().size() == 1)
   {
      _SizeIter = _PSystem->getSizes().begin();
   }
}

void ParticleSystemIterator::updateNormalIter(void) const
{
   if(_IsNormalExpanded != (_PSystem->getNormals().size() > 1))
   {
      _NormIter = _PSystem->getNormals().begin();
      if(_PSystem->getNormals().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_NormIter;
         }
      }
      
      _IsNormalExpanded = (_PSystem->getNormals().size() > 1);
   }
   else if(_PSystem->getNormals().size() == 1)
   {
      _NormIter = _PSystem->getNormals().begin();
   }
}

void ParticleSystemIterator::updateColorIter(void) const
{
   if(_IsColorExpanded != (_PSystem->getColors().size() > 1))
   {
      _ColorIter = _PSystem->getColors().begin();
      if(_PSystem->getColors().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_ColorIter;
         }
      }
      
      _IsColorExpanded = (_PSystem->getColors().size() > 1);
   }
   else if(_PSystem->getColors().size() == 1)
   {
      _ColorIter = _PSystem->getColors().begin();
   }
}

void ParticleSystemIterator::updateLifespanIter(void) const
{
   if(_IsLifespanExpanded != (_PSystem->getLifespan().size() > 1))
   {
      _LifespanIter = _PSystem->getLifespan().begin();
      if(_PSystem->getLifespan().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_LifespanIter;
         }
      }
      
      _IsLifespanExpanded = (_PSystem->getLifespan().size() > 1);
   }
   else if(_PSystem->getLifespan().size() == 1)
   {
      _LifespanIter = _PSystem->getLifespan().begin();
   }
}

void ParticleSystemIterator::updateVelIter(void) const
{
   if(_IsVelExpanded != (_PSystem->getVelocities().size() > 1))
   {
      _VelIter = _PSystem->getVelocities().begin();
      if(_PSystem->getVelocities().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_VelIter;
         }
      }
      
      _IsVelExpanded = (_PSystem->getVelocities().size() > 1);
   }
   else if(_PSystem->getVelocities().size() == 1)
   {
      _VelIter = _PSystem->getVelocities().begin();
   }
}

void ParticleSystemIterator::updateSecVelIter(void) const
{
   /*if(_IsSecVelExpanded != (_PSystem->getSecVelocities().size() > 1))
   {
      _SecVelIter = _PSystem->getSecVelocities().begin();
      if(_PSystem->getSecVelocities().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_VelIter;
         }
      }
      
      _IsSecVelExpanded = (_PSystem->getSecVelocities().size() > 1);
   }*/
}

void ParticleSystemIterator::updateAccelerationIter(void) const
{
   if(_IsAccelerationExpanded != (_PSystem->getAccelerations().size() > 1))
   {
      _AccIter = _PSystem->getAccelerations().begin();
      if(_PSystem->getAccelerations().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_AccIter;
         }
      }
      
      _IsAccelerationExpanded = (_PSystem->getAccelerations().size() > 1);
   }
   else if(_PSystem->getAccelerations().size() == 1)
   {
      _AccIter = _PSystem->getAccelerations().begin();
   }
}

void ParticleSystemIterator::updatePropertyIter(void) const
{
   if(_IsPropertyExpanded != (_PSystem->getProperties().size() > 1))
   {
      _PropIter = _PSystem->getProperties().begin();
      if(_PSystem->getProperties().size() != 1)
      {
         Pnt3fList::iterator tPosIter;
         for(Pnt3fList::iterator tPosIter = _PSystem->getPositions().begin() ; tPosIter != _PosIter ; ++tPosIter)
         {
            ++_PropIter;
         }
      }
      
      _IsPropertyExpanded = (_PSystem->getProperties().size() > 1);
   }
   else if(_PSystem->getProperties().size() == 1)
   {
      _PropIter = _PSystem->getProperties().begin();
   }
}

OSG_END_NAMESPACE
