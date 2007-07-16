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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGMaterial.h>
#include <OpenSG/OSGGeoPropPtrs.h>
#include <OpenSG/OSGCamera.h>

#include "OSGParticleSystem.h"
#include "OSGParticleSystemIterator.h"

#include <algorithm>

OSG_USING_NAMESPACE

osg::UInt16 ParticleSystem::_numPropTypes = 0;

osg::StatElemDesc<StatIntElem>  ParticleSystem::statNParticles("NParticles",
 "number of particles");
/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleSystem
    \ingroup GrpSystemNodeCoresDrawablesParticleSystem
    
See \ref PageSystemParticleSystem for details.

*/

 ParticleSystemIterator ParticleSystem::begin(void)
 {
    return ParticleSystemIterator(ParticleSystemPtr(this),
                                  getPositions().begin(),
                                  getSecPositions().begin(),
                                  getNormals().begin(),
                                  getSizes().begin(),
                                  getColors().begin(),
                                  getLifespan().begin(),
                                  getAge().begin(),
                                  getVelocities().begin(),
                                  getSecVelocities().begin(),
                                  getAccelerations().begin(),
                                  getProperties().begin());
 }
 
 ParticleSystemIterator ParticleSystem::end(void)
 {
    return ParticleSystemIterator(ParticleSystemPtr(this),
                                  getPositions().end(),
                                  getSecPositions().end(),
                                  getNormals().end(),
                                  getSizes().end(),
                                  getColors().end(),
                                  getLifespan().end(),
                                  getAge().end(),
                                  getVelocities().end(),
                                  getSecVelocities().end(),
                                  getAccelerations().end(),
                                  getProperties().end());
 }
    
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystem::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ParticleSystemPtr  ,
                                          CNodePtr      ,
                                          Action       *>
                                       (&MaterialDrawable::drawActionHandler));

    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ParticleSystemPtr  ,
                                          CNodePtr      ,
                                          Action       *>
                                       (&MaterialDrawable::renderActionHandler));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

ParticleSystem::ParticleSystem(void) :
    Inherited()
{
}

ParticleSystem::ParticleSystem(const ParticleSystem &source) :
    Inherited(source)
{
}

ParticleSystem::~ParticleSystem(void)
{
    ParticleSystemPtr thisP(*this);

    subRefCP(_sfMaterial.getValue());
}

/*------------------------------- Sync -----------------------------------*/

void ParticleSystem::changed(BitVector whichField, UInt32 origin)
{

    if(whichField & MaterialFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfMaterial.getValue());
            }
            else
            {
                MaterialPtr pMat = _sfMaterial.getValue();
                
                _sfMaterial.setValue(NullFC);
                
                setMaterial(pMat);
            }
        }
    }

    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void ParticleSystem::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystem NI" << std::endl;
}


void ParticleSystem::adjustVolume( Volume & volume )
{

   //if ( pos == NullFC )
   //    return;                 // Node has no particles, no volume

   volume.setValid();
   volume.setEmpty();
   
   if(getSizes().size() == getPositions().size())
   {
      Pnt3f p;
      Real32 s;

      Pnt3fList::iterator PosListIter( getPositions().begin() );
      Vec3fList::iterator SizeListIter( getSizes().begin() );
      for(; PosListIter != getPositions().end(); )
      {
         p = (*PosListIter);
         // make the size bigger to accomodate rotations
         s = (*SizeListIter)[0]*Sqrt2;
         
         p[0]+=s/2;
         p[1]+=s/2;
         p[2]+=s/2;
         volume.extendBy(p);
         p[0]-=s;
         volume.extendBy(p);
         p[1]-=s;
         volume.extendBy(p);
         p[0]+=s;
         volume.extendBy(p);
         p[2]-=s;
         volume.extendBy(p);
         p[0]-=s;
         volume.extendBy(p);
         p[1]+=s;
         volume.extendBy(p);
         p[0]+=s;
         volume.extendBy(p);
         
         ++PosListIter;
         ++SizeListIter;
      }

   }
   else if(getSizes().size() == 1)
   {
      Pnt3f p;
      Real32 s,s2;
      // make the size bigger to accomodate rotations
      s=getSizes().front()[0]*Sqrt2;
      s2=s/2;

      Pnt3fList::iterator PosListIter;
      for(PosListIter = getPositions().begin(); PosListIter != getPositions().end(); ++PosListIter)
      {
         p = (*PosListIter);

         p[0]+=s2;
         p[1]+=s2;
         p[2]+=s2;
         volume.extendBy(p);
         p[0]-=s;
         volume.extendBy(p);
         p[1]-=s;
         volume.extendBy(p);
         p[0]+=s;
         volume.extendBy(p);
         p[2]-=s;
         volume.extendBy(p);
         p[0]-=s;
         volume.extendBy(p);
         p[1]+=s;
         volume.extendBy(p);
         p[0]+=s;
         volume.extendBy(p);
      }
   }
   else
   {
      Pnt3fList::iterator PosListIter;
      for(PosListIter = getPositions().begin(); PosListIter != getPositions().end(); ++PosListIter)
      {
         volume.extendBy((*PosListIter));
      }
   }
}


bool ParticleSystem::addParticle(Pnt3f& pos,
                     Vec3f& normal,
                     Color4f& color,
                     Vec3f& size,
                     Real32& lifespan,
                     Real32& age,
                     Vec3f& velocity,
                     Vec3f& acceleration )
{
   //Position
   getPositions().push_back(pos);
   //SecPosition
   getSecPositions().push_back(pos);
   
   //Normal
   if(getNormals().size() != 1 )
   {
      getNormals().push_back(normal);
   }
   else if(getNormals().front() != normal)
   {
      //The normal of the particle added is different from all of the other particles normals
      //So we will need to expand the normals array to have a separate normal value defined for
      //each particle
      expandNormal();
      getNormals().back() = normal;
   }
   
   //Color
   if(getColors().size() != 1 )
   {
      getColors().push_back(color);
   }
   else if(getColors().front() != color)
   {
      //The color of the particle added is different from all of the other particles colors
      //So we will need to expand the colors array to have a separate size value defined for
      //each particle
      expandColor();
      getColors().back() = color;
   }
   
   //Size
   if(getSizes().size() != 1 )
   {
      getSizes().push_back(size);
   }
   else if(getSizes().front() != size )
   {
      //The size of the particle added is different from all of the other particles sizes
      //So we will need to expand the sizes array to have a separate size value defined for
      //each particle
      expandSize();
      getSizes().back() = size;
   }
   
   //Lifespan
   if(getLifespan().size() != 1 )
   {
      getLifespan().push_back(lifespan);
   }
   else if(getLifespan().front() != lifespan)
   {
      //The lifespan of the particle added is different from all of the other particles lifespans
      //So we will need to expand the lifespans array to have a separate size value defined for
      //each particle
      expandLifespan();
      getLifespan().back() = lifespan;
   }
   //Age
   getAge().push_back(age);
   //Velocity
   if(getVelocities().size() != 1 )
   {
      getVelocities().push_back(velocity);
      //getSecVelocities().push_back(velocity);
   }
   else if(getVelocities().front() != velocity)
   {
      //The velocity of the particle added is different from all of the other particles velocitys
      //So we will need to expand the velocitys array to have a separate size value defined for
      //each particle
      expandVelocity();
      getVelocities().back() = velocity;
      //expandSecVelocity();
      //getSecVelocities().back() = velocity;
   }
   //Acceleration
   if(getAccelerations().size() != 1 )
   {
      getAccelerations().push_back(acceleration);
   }
   else if(getAccelerations().front() != acceleration )
   {
      //The acceleration of the particle added is different from all of the other particles accelerations
      //So we will need to expand the accelerations array to have a separate size value defined for
      //each particle
      expandAcceleration();
      getAccelerations().back() = acceleration;
   }
   //Properties
   if(getProperties().size() != 1 )
   {
      getProperties().push_back(0);
   }
   else if(getProperties().front() != 0 )
   {
      expandProperty();
      getProperties().back() = 0;
   }
   return true;
}

bool ParticleSystem::killParticle(Pnt3fList::iterator PosIter,
                           Pnt3fList::iterator SecPosIter,
                           Vec3fList::iterator NormIter,
                           Vec3fList::iterator SizeIter,
                           Color4fList::iterator ColorIter,
                           Real32List::iterator LifespanIter,
                           Real32List::iterator AgeIter,
                           Vec3fList::iterator VelIter,
                           Vec3fList::iterator SecVelIter,
                           Vec3fList::iterator AccIter,
                           UInt64List::iterator PropIter)
{
   if(getPositions().size() == 0)
   {
      return false;
   }
   else
   {
      getPositions().erase(PosIter);
      getSecPositions().erase(SecPosIter);
      if((getPositions().size() == 0 && getNormals().size() > 0) || getNormals().size()>1 ){ getNormals().erase(NormIter); };
      if((getPositions().size() == 0 && getSizes().size() > 0) || getSizes().size()>1 ){ getSizes().erase(SizeIter); };
      if((getPositions().size() == 0 && getColors().size() > 0) || getColors().size()>1 ){ getColors().erase(ColorIter); };
      if((getPositions().size() == 0 && getLifespan().size() > 0) || getLifespan().size()>1 ){ getLifespan().erase(LifespanIter); };
      getAge().erase(AgeIter);
      if((getPositions().size() == 0 && getVelocities().size() > 0) || getVelocities().size()>1 ){ getVelocities().erase(VelIter); };
      //if((getPositions().size() == 0 && getSecVelocities().size() > 0) || getSecVelocities().size()>1 ){ getSecVelocities().erase(SecVelIter); };
      if((getPositions().size() == 0 && getAccelerations().size() > 0) || getAccelerations().size()>1 ){ getAccelerations().erase(AccIter); };
      if((getPositions().size() == 0 && getProperties().size() > 0) || getProperties().size()>1 ){ getProperties().erase(PropIter); };
      return true;
   }   
}

template<class ListType, class ListTypeIter, class StrictWeakOrdering>
int insertSort(ListType List, ListTypeIter ListBegin, ListTypeIter ListEnd, StrictWeakOrdering Comp)
{
   ListTypeIter i, next_i, indexLeastGreaterThan, ListFront;
   bool swap_needed(false);
   int steps(0);
   
   /*ListFront = ListBegin;
   --ListFront;

   i=ListBegin;
   ++i;
   while ( i != ListEnd )
   {
      indexLeastGreaterThan = i;
      --indexLeastGreaterThan;
      swap_needed = false;
      while ((indexLeastGreaterThan != ListFront) && ( Comp( (*i), (*indexLeastGreaterThan) )))
      {
         swap_needed = true;
         --indexLeastGreaterThan;
         ++steps;
      }
      next_i = i;
      ++next_i;
      if(swap_needed)
      {
         ++indexLeastGreaterThan;
         typename ListType::StoredType Temp( (*i) );
         (*i) = (*indexLeastGreaterThan);
         (*indexLeastGreaterThan) = Temp;
         //List.splice(indexLeastGreaterThan,List, i,next_i);
      }
      i = next_i;
      
      ++steps;
   }*/
   return steps;
}

void ParticleSystem::sort(void)
{
   //insertSort(getIndices(), getIndices().begin(), getIndices().end(), ParticleCompare( getPositions() ) );
}

void ParticleSystem::preUpdate(void)
{
   //Check if the Particle system is dynamic
   //If it is then update the secPositions and secVelocities
   if(getDynamic())
   {
      //Update all of the secPositions
      //Update the size of the secPosition MField if it is different from the Position MField
      if(getSecPositions().size() != getPositions().size() )
      {
         expandSecPosition();
      }
      
      Pnt3fList::iterator PosListIter( getPositions().begin() );
      Pnt3fList::iterator SecPosListIter( getSecPositions().begin() );
      while(PosListIter != getPositions().end() )
      {
         (*SecPosListIter) = (*PosListIter);
         ++PosListIter;
         ++SecPosListIter;
      }

      //Update all of the secVelocities
      //Check if the Particle system has any Velocities defined
      if( getVelocities().size() != 0 )
      {
         //Update the size of the secVelocity MField if it is different from the Velocity MField
         /*if(getSecVelocities().size() != getVelocities().size() )
         {
            getSecVelocities().resize( getVelocities().size() );
         }
         Vec3fList::iterator VelListIter( getVelocities().begin() );
         Vec3fList::iterator SecVelListIter( getSecVelocities().begin() );
         for(; VelListIter != getVelocities().end(); )
         {
            (*SecVelListIter) = (*VelListIter);
            ++VelListIter;
            ++SecVelListIter;
         }*/
      }
   }
}

void ParticleSystem::postUpdate(const float& elps)
{
   if( getDynamic() )
   {
      //Update Velocities and Accelerations
      if( getAccelerations().size() > 1 || (getAccelerations().size() == 1 && getAccelerations().front() != Vec3f(0.0,0.0,0)) )
      {
         Pnt3fList::iterator PosListIter;
         Vec3fList::iterator VelListIter( getVelocities().begin() );
         Vec3fList::iterator AccListIter( getAccelerations().begin() );
         for(PosListIter = getPositions().begin(); PosListIter != getPositions().end(); ++PosListIter)
         {
            (*PosListIter) += elps * (*VelListIter) + 0.5f * elps * elps * (*AccListIter);
            (*VelListIter) += elps * (*AccListIter);
            if(getVelocities().size() == 1)
            {
               if(getAccelerations().size() > 1) //1 Velocity & Many Accelerations
               {
                  //Move Accelerations forward
                  ++AccListIter;
                  //Expand the Velocities
                  expandVelocity();
                  //Move Velocities forward
                  ++VelListIter;
               }
            }
            else
            {
               if(getAccelerations().size() == 1)//Many Velocities & 1 Acceleration
               {
                  //Move Velocities forward
                  ++VelListIter;
               }
               else//Many Velocities & Many Accelerations
               {
                  //Move Velocities forward
                  ++VelListIter;
                  //Move Accelerations forward
                  ++AccListIter;
               }
            }
         }
      }
      else if( getVelocities().size() > 1 || (getVelocities().size() == 1 && getVelocities().front() != Vec3f(0.0,0.0,0)) )
      {
         //Just Velocity - Acceleration is not present so apply only velocity
         Pnt3fList::iterator PosListIter;
         Vec3fList::iterator VelListIter( getVelocities().begin() );
         for(PosListIter = getPositions().begin(); PosListIter != getPositions().end(); ++PosListIter)
         {
            (*PosListIter) += elps * (*VelListIter);
            if(getVelocities().size() > 1)
            {
               //If there is > 1 Velocity then move the velocity iterator forward
               ++VelListIter;
            }
         }
      }
      
      //invalidateVolume();
      
      //Check if the Particle system is Sorted
      if(_sfDrawOrder.getValue()!=ParticleSystem::Any)
      {
         //Sort the Particle System
         sort();
      }
   }
}

void ParticleSystem::drawLines (DrawActionBase *action)
{
   Color4fList::iterator ColorIter(getColors().begin());
   Pnt3fList::iterator PosIter;
   Pnt3fList::iterator SecPosIter;
   //Lines
	glLineWidth(2.0);
	glDisable( GL_LIGHTING );
   glBegin( GL_LINES );
      //Same color for each particle
      if(getColors().size() == 1){ glColor4fv((GLfloat*) getColors().front().getValuesRGBA()); }
      
      SecPosIter= getSecPositions().begin();
      PosIter = getPositions().begin();
      while( PosIter != getPositions().end())
      {
         //Colors per particle
         if(getColors().size() != 1)
         {
            glColor4fv((GLfloat*) (*ColorIter).getValuesRGBA());
            ++ColorIter;
         }
         
         glVertex3fv( (*SecPosIter).getValues() );
         glVertex3fv( (*PosIter).getValues() );
         ++PosIter;
         ++SecPosIter;
      }
   glEnd();
   
   //Stat Collection
   StatCollector *coll = action->getStatistics();
   if(coll != NULL)
   {
       StatIntElem *el = coll->getElem(Drawable::statNTriangles,false);
       if(el)
       {
           coll->getElem(ParticleSystem::statNParticles)->add( getPositions().size() );
           coll->getElem(Drawable::statNVertices)->add( getPositions().size()*2 );
           coll->getElem(Drawable::statNLines)->add( getPositions().size() );
       }
   }
}

void ParticleSystem::drawPoints (DrawActionBase *action)
{
   Pnt3fList::iterator PosIter;
   Color4fList::iterator ColorIter(getColors().begin());
    
	glPointSize(2.0);
	glDisable( GL_LIGHTING );
   glBegin( GL_POINTS );
      //Same color for each particle
      if(getColors().size() == 1){ glColor4fv((GLfloat*) getColors().front().getValuesRGBA()); }
      
      for(PosIter = getPositions().begin() ; PosIter != getPositions().end(); ++PosIter)
      {
         //Colors per particle
         if(getColors().size() != 1)
         {
            glColor4fv((GLfloat*) (*ColorIter).getValuesRGBA());
            ++ColorIter;
         }
         
         glVertex3fv( (*PosIter).getValues() );
      }
   glEnd();

   //Stat Collection
   StatCollector *coll = action->getStatistics();
   if(coll != NULL)
   {
       StatIntElem *el = coll->getElem(Drawable::statNTriangles,false);
       if(el)
       {
           coll->getElem(ParticleSystem::statNParticles)->add( getPositions().size() );
           coll->getElem(Drawable::statNVertices)->add( getPositions().size() );
           coll->getElem(Drawable::statNPoints)->add( getPositions().size() );
       }
   }
}

void ParticleSystem::drawQuads (DrawActionBase *action)
{
   Pnt3fList::iterator PosIter;
   Vec3fList::iterator SizeIter;
   Vec3fList::iterator NormalIter;
   
   SizeIter = getSizes().end();
   --SizeIter;
   NormalIter = getNormals().end();
   --NormalIter;
   
   Color4fList::iterator ColorIter(getColors().end());
   --ColorIter;
   Pnt3f LL,UL, LR, UR;
   Vec3f Normal, Up(0.0,1.0,0.0), BiNormal;
   glBegin( GL_QUADS );
      //Same color for each particle
      if(getColors().size() == 1){ glColor4fv((GLfloat*) getColors().front().getValuesRGBA()); }
      if(getNormals().size() == 1)
      {
         Normal = (*NormalIter);
         BiNormal = Up.cross(Normal);
      }
      
      for(PosIter = --getPositions().end() ; PosIter != getPositions().begin(); --PosIter)
      {
         //Colors per particle
         if(getColors().size() != 1)
         {
            glColor4fv((GLfloat*) (*ColorIter).getValuesRGBA());
            --ColorIter;
         }
         //Normals per particle
         if(getNormals().size() != 1)
         {
            Normal = (*NormalIter);
            BiNormal = Up.cross(Normal);
            --NormalIter;
         }
         
         LL = (*PosIter) - (getQuadWidth() * (*SizeIter)[0] * BiNormal) - (getQuadHeight() * (*SizeIter)[1] * Up);
         UL = (*PosIter) - (getQuadWidth() * (*SizeIter)[0] * BiNormal) + (getQuadHeight() * (*SizeIter)[1] * Up);
         LR = (*PosIter) + (getQuadWidth() * (*SizeIter)[0] * BiNormal) - (getQuadHeight() * (*SizeIter)[1] * Up);
         UR = (*PosIter) + (getQuadWidth() * (*SizeIter)[0] * BiNormal) + (getQuadHeight() * (*SizeIter)[1] * Up);
         
         glTexCoord2i(0,0);
         glNormal3f( 0.0,0.0,1.0 );
         glTexCoord2i(0,0);
         glVertex3fv( LL.getValues() );
         glTexCoord2i(1,0);
         glVertex3fv( LR.getValues() );
         glTexCoord2i(1,1);
         glVertex3fv( UR.getValues() );
         glTexCoord2i(0,1);
         glVertex3fv( UL.getValues() );
         
         if(getSizes().size() != 1) { --SizeIter; }
      }
   glEnd();
   
   //Stat Collection
   StatCollector *coll = action->getStatistics();
   if(coll != NULL)
   {
       StatIntElem *el = coll->getElem(Drawable::statNTriangles,false);
       if(el)
       {
           coll->getElem(ParticleSystem::statNParticles)->add( getPositions().size() );
           coll->getElem(Drawable::statNPrimitives)->add( getPositions().size() );
           coll->getElem(Drawable::statNVertices)->add( getPositions().size() * 4 );
       }
   }
}

void ParticleSystem::drawViewDirQuads (DrawActionBase *action)
{
   Matrix camera,toworld;
   camera = action->getCameraToWorld();
 
   RenderAction *ra = dynamic_cast<RenderAction *>(action);
   
   if(ra != NULL)
   {
       toworld = ra->top_matrix();
   }
   else
   {
       action->getActNode()->getToWorld(toworld);
   }
 
   // normalize them, we don't want to neutralize scales in toworld
   toworld[0].normalize();
   toworld[1].normalize();
   toworld[2].normalize();       
   toworld.transpose();
   camera.multLeft(toworld);
   
   Vec3f u(camera[0][0],camera[0][1],camera[0][2]),v(camera[1][0],camera[1][1],camera[1][2]), n(camera[2][0],camera[2][1],camera[2][2]);
   

   Pnt3fList::iterator PosIter;
   Vec3fList::iterator SizeIter;
   Vec3fList::iterator NormIter;
   
   SizeIter = getSizes().end();
   --SizeIter;
   NormIter = getNormals().end();
   --NormIter;
   
   Color4fList::iterator ColorIter(getColors().end());
   --ColorIter;
   Pnt3f LL,UL, LR, UR;
   glBegin( GL_QUADS );
      //Same color for each particle
      if(getColors().size() == 1){ glColor4fv((GLfloat*) getColors().front().getValuesRGBA()); }
      
      for(PosIter = --getPositions().end() ; PosIter != getPositions().begin(); --PosIter)
      {
         //Colors per particle
         if(getColors().size() != 1)
         {
            glColor4fv((GLfloat*) (*ColorIter).getValuesRGBA());
            --ColorIter;
         }
         
         if(getUseNormalAsObjectSpaceRotation())
         {
            v = (*NormIter)[1] * Vec3f(camera[1][0],camera[1][1],camera[1][2]) + (*NormIter)[0] * Vec3f(camera[0][0],camera[0][1],camera[0][2]);
            u = v.cross(n);
         }
         
         LL = (*PosIter) - (getQuadWidth() * (*SizeIter)[0] * u) - (getQuadHeight() * (*SizeIter)[1] * v);
         UL = (*PosIter) - (getQuadWidth() * (*SizeIter)[0] * u) + (getQuadHeight() * (*SizeIter)[1] * v);
         LR = (*PosIter) + (getQuadWidth() * (*SizeIter)[0] * u) - (getQuadHeight() * (*SizeIter)[1] * v);
         UR = (*PosIter) + (getQuadWidth() * (*SizeIter)[0] * u) + (getQuadHeight() * (*SizeIter)[1] * v);
         
         glTexCoord2i(0,0);
         glNormal3f( 0.0,0.0,1.0 );
         glTexCoord2i(0,0);
         glVertex3fv( LL.getValues() );
         glTexCoord2i(1,0);
         glVertex3fv( LR.getValues() );
         glTexCoord2i(1,1);
         glVertex3fv( UR.getValues() );
         glTexCoord2i(0,1);
         glVertex3fv( UL.getValues() );
         
         if(getSizes().size() != 1) { --SizeIter; }
         if(getNormals().size() != 1) { --NormIter; }
      }
   glEnd();

   //Stat Collection
   StatCollector *coll = action->getStatistics();
   if(coll != NULL)
   {
       StatIntElem *el = coll->getElem(Drawable::statNTriangles,false);
       if(el)
       {
           coll->getElem(ParticleSystem::statNParticles)->add( getPositions().size() );
           coll->getElem(Drawable::statNPrimitives)->add( getPositions().size() );
           coll->getElem(Drawable::statNVertices)->add( getPositions().size() * 4 );
       }
   }
}

void ParticleSystem::drawViewerQuads (DrawActionBase *action)
{
   Matrix camera,toworld;
   camera = action->getCameraToWorld();
 
   RenderAction *ra = dynamic_cast<RenderAction *>(action);
   
   if(ra != NULL)
   {
       toworld = ra->top_matrix();
   }
   else
   {
       action->getActNode()->getToWorld(toworld);
   }
 
   // normalize them, we don't want to neutralize scales in toworld
   toworld[0].normalize();
   toworld[1].normalize();
   toworld[2].normalize();       
   toworld.transpose();
   camera.multLeft(toworld);
   
   // Viewer position & up
   Pnt3f  vpos(camera[3]);
   Vec3f  vup (camera[1]);
   vup.normalize();
 
   // direction vector
   Vec3f d,v,u;
   

   Pnt3fList::reverse_iterator PosIter;
   Vec3fList::reverse_iterator SizeIter;
   Vec3fList::reverse_iterator NormIter;
   
   SizeIter = getSizes().rbegin();
   NormIter = getNormals().rbegin();
   
   Color4fList::reverse_iterator ColorIter(getColors().rbegin());
   Pnt3f LL,UL, LR, UR;
   glBegin( GL_QUADS );
      //Same color for each particle
      if(getColors().size() == 1){ glColor4fv((GLfloat*) getColors().front().getValuesRGBA()); }
      
      for(PosIter = getPositions().rbegin() ; PosIter != getPositions().rend(); ++PosIter)
      {
         //Colors per particle
         if(getColors().size() != 1)
         {
            glColor4fv((GLfloat*) (*ColorIter).getValuesRGBA());
            ++ColorIter;
         }
         d = vpos - (*PosIter);
         d.normalize();
         u = vup.cross(d);
         v = d.cross(u);
         
         if(getUseNormalAsObjectSpaceRotation())
         {
            v = (*NormIter)[1] * v + (*NormIter)[0] * u;
            u = v.cross(d);
         }
         
         LL = (*PosIter) - (getQuadWidth() * (*SizeIter)[0] * u) - (getQuadHeight() * (*SizeIter)[1] * v);
         UL = (*PosIter) - (getQuadWidth() * (*SizeIter)[0] * u) + (getQuadHeight() * (*SizeIter)[1] * v);
         LR = (*PosIter) + (getQuadWidth() * (*SizeIter)[0] * u) - (getQuadHeight() * (*SizeIter)[1] * v);
         UR = (*PosIter) + (getQuadWidth() * (*SizeIter)[0] * u) + (getQuadHeight() * (*SizeIter)[1] * v);
         
         glNormal3f( 0.0,0.0,1.0 );
         glTexCoord2i(0,0);
         glVertex3fv( LL.getValues() );
         glTexCoord2i(1,0);
         glVertex3fv( LR.getValues() );
         glTexCoord2i(1,1);
         glVertex3fv( UR.getValues() );
         glTexCoord2i(0,1);
         glVertex3fv( UL.getValues() );
         
         if(getSizes().size() != 1) { ++SizeIter; }
         if(getNormals().size() != 1) { ++NormIter; }
      }
   glEnd();

   //Stat Collection
   StatCollector *coll = action->getStatistics();
   if(coll != NULL)
   {
       StatIntElem *el = coll->getElem(Drawable::statNTriangles,false);
       if(el)
       {
           coll->getElem(ParticleSystem::statNParticles)->add( getPositions().size() );
           coll->getElem(Drawable::statNPrimitives)->add( getPositions().size() );
           coll->getElem(Drawable::statNVertices)->add( getPositions().size() * 4 );
       }
   }
}

void ParticleSystem::drawVelocityDirQuads (DrawActionBase *action)
{
}

void ParticleSystem::drawNodes (DrawActionBase *action)
{
   //Do nothing, Setting this is done in postUpdate
}

/*! Low-level Draw method that pumps OpenGL commands.
*/
Action::ResultE ParticleSystem::drawPrimitives(DrawActionBase * action)
{switch( getDrawMode() )
   {
      case Points:
         drawPoints(action);
         break;
      case Lines:
         drawLines(action);
         break;
      case Quads:
         drawQuads(action);
         break;
      case ViewDirQuads:
         drawViewDirQuads(action);
         break;
      case ViewerQuads:
         drawViewerQuads(action);
         break;
      case VelocityDirQuads:
         drawVelocityDirQuads(action);
         break;
      case Nodes:
         drawNodes(action);
         break;
      default:
         drawPoints(action);
         break;
   }
   // some variables for faster access
   
   
 
    /*if((size   ->size() > 1 && size   ->size() != pos->getSize())  ||
       (col  != NullFC && col->getSize()  != 1 &&
                          col->getSize()  != pos->getSize())       ||
       (norm != NullFC && norm->getSize() != 1 &&
                          norm->getSize() != pos->getSize())
      )
    {
        FWARNING(("ParticleSystem::draw: inconsistent attributes "
                    "(p:%d s:%d c:%d)!\n",
                    pos->getSize(), size->size(),
                    (col != NullFC)? (int)col->getSize() : -1));
        return Action::Continue;
    }
    
    //if(drawer == NULL)
    //{
    //    FWARNING(("ParticleSystem 0x%lx: couldn't find drawer!\n", this));
    //    return Action::Continue;;
    //}
    
    UInt32 *index = NULL;
    UInt32 length = 0;
    bool freeIndex = false;
    
    if(_sfDrawOrder.getValue()!=ParticleSystem::Any)
    {
        if(getDynamic())
        {
            //index=calcIndex(action,length);
        }
        else
        {
            //if(!getBsp().created())
            //{
            //    getBsp().build(this);
            //}
            Matrix modelview,toworld;

            modelview = action->getCameraToWorld();
    
            RenderAction *ra = dynamic_cast<RenderAction *>(action);
            
            if(ra != NULL)
            {
                toworld = ra->top_matrix();
            }
            else
            {
                action->getActNode()->getToWorld(toworld);
            }

//            action->getCamera()->getBeacon()->getToWorld(modelview);
//            action->getActNode()->getToWorld(toworld);

            toworld.invert();
            modelview.mult(toworld);

            Pnt3f ref(modelview[3][0],modelview[3][1],
                      modelview[3][2]);
            Vec3f refvec(  modelview[2][0],modelview[2][1],
                      modelview[2][2]);  

        }
        freeIndex = true;
    }
    else if (getIndices().size() > 0)
    {
        index  = &getMFIndices()->getValues()[0];
        length = getIndices().size();
    }

    if(index != NULL)
    {
        //drawer->drawIndexed(this,action,index,length);
    }
    else
    {
        //drawer->draw(this,action);   
    }
    
    if(freeIndex)
        delete [] index;*/
        
    return Action::Continue;
}
 
