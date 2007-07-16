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

#ifndef _OSGPARTICLESYSTEM_H_
#define _OSGPARTICLESYSTEM_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "ParticleSystem/OSGParticleSystemConfig.h"
#include <OpenSG/OSGAction.h>

#include <ParticleSystem/OSGParticleSystemBase.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;
class ParticleSystemIterator;

struct ParticleSystemDrawer;

class OSG_PARTICLE_SYSTEM_CLASS_API ParticleSystem : public ParticleSystemBase
{
  private:

    typedef ParticleSystemBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    friend class ParticleSystemIterator;
    static StatElemDesc<StatIntElem>  statNParticles;

    /*---------------------------------------------------------------------*/
    /*! \name                     Modes                                    */
    /*! \{                                                                 */
    
    enum { Points=0, Lines, Quads, ViewDirQuads, ViewerQuads, VelocityDirQuads, Nodes,
           LastMode }
           ModeE;
    
    enum { Any=0, BackToFront, FrontToBack } DrawOrderE;
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    Action::ResultE drawPrimitives (DrawActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */
    
    void setMaterial       (const MaterialPtr     &value);

    /*! \}                                                                 */
    
    UInt32 numParticles(void) const;
    
    bool addParticle(Pnt3f& pos,
                     Vec3f& normal,
                     Color4f& color,
                     Vec3f& size,
                     Real32& lifespan,
                     Real32& age,
                     Vec3f& velocity,
                     Vec3f& acceleration );
    bool killParticle(Pnt3fList::iterator PosIter,
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
    
    void preUpdate(void);
    void postUpdate(const float& elps);
    
    ParticleSystemIterator begin(void);
    ParticleSystemIterator end(void);
    static UInt64 createNewPropType(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ParticleSystemBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystem(void);
    ParticleSystem(const ParticleSystem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystem(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                NodeCore Specific                             */
    /*! \{                                                                 */

    void    adjustVolume(Volume & volume);

    /*! \}                                                                 */
   
    void sort(void);
    void adjustDynamicProperty(void);
    
    void setPosition(Pnt3f& val, Pnt3fList::iterator i);
    void setNormal(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter);
    void setSize(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter);
    void setColor(Color4f& val, Color4fList::iterator& i, Pnt3fList::iterator PosIter);
    void setLifespan(Real32& val, Real32List::iterator& i, Pnt3fList::iterator PosIter);
    void setAge(Real32& val, Real32List::iterator& i, Pnt3fList::iterator PosIter);
    void setVelocity(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter);
    void setAcceleration(Vec3f& val, Vec3fList::iterator& i, Pnt3fList::iterator PosIter);
    void addProperty(UInt64& val, UInt64List::iterator& i, Pnt3fList::iterator PosIter);
    void removeProperty(UInt64& val, UInt64List::iterator i);
    
    bool hasProperty(UInt64& val, UInt64List::iterator i);
    
    void expandSize(void);
    void expandNormal(void);
    void expandColor(void);
    void expandLifespan(void);
    void expandAge(void);
    void expandVelocity(void);
    void expandSecVelocity(void);
    void expandAcceleration(void);
    void expandSecPosition(void);
    void expandProperty(void);
    
    void drawLines (DrawActionBase *action);
    void drawPoints (DrawActionBase *action);
    void drawQuads (DrawActionBase *action);
    void drawViewDirQuads (DrawActionBase *action);
    void drawViewerQuads (DrawActionBase *action);
    void drawVelocityDirQuads (DrawActionBase *action);
    void drawNodes (DrawActionBase *action);
    
    static UInt16 _numPropTypes;
    /*==========================  PRIVATE  ================================*/
    
  private:

    friend class FieldContainer;
    friend class ParticleSystemBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ParticleSystem &source);
    
     /*---------------------------------------------------------------------*/
    /*! \name                ParticleSystem Specific                            */
    /*! \{                                                                 */

    
    /*! \}                                                                 */
};

typedef ParticleSystem *ParticleSystemP;

/*class ParticleCompare {
private:
   const GeoPositionsPtr Positions;
public:
   ParticleCompare(const GeoPositionsPtr P) : Positions(P)
   {
   }
   //Return true if s1 < s2; otherwise, return false.
   inline bool operator()(const UInt32& s1, const UInt32& s2)
   {
      return  dist( Positions->getValue(s1) ) < dist( Positions->getValue(s2) );
   }
   
   inline Real32 dist(const Pnt3f& p)
   {
      Real32 result(0.0);
      for(UInt16 i=0 ; i<GeoPositions::GenericType::Inherited::_iSize ; ++i)
      {
         result += p[i]*p[i];
      }
      return result;
   }
   
};*/

OSG_END_NAMESPACE

#include <ParticleSystem/OSGParticleSystemBase.inl>
#include <ParticleSystem/OSGParticleSystem.inl>

#endif /* _OSGPARTICLESYSTEM_H_ */
