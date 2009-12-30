/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

#ifndef _OSGCONDITIONALPARTICLEAFFECTOR_H_
#define _OSGCONDITIONALPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGConditionalParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ConditionalParticleAffector class. See \ref 
           PageParticleSystemConditionalParticleAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ConditionalParticleAffector : public ConditionalParticleAffectorBase
{
  private:

    typedef ConditionalParticleAffectorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	enum Conditional{EQUALS = 1, NOT_EQUAL = 2, LESS_THAN = 3, GREATER_THAN = 4, LESS_THAN_EQUAL = 5, GREATER_THAN_EQUAL = 6 };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	virtual bool affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ConditionalParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ConditionalParticleAffector(void);
    ConditionalParticleAffector(const ConditionalParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ConditionalParticleAffector(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ConditionalParticleAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ConditionalParticleAffector &source);
};

typedef ConditionalParticleAffector *ConditionalParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGConditionalParticleAffectorBase.inl"
#include "OSGConditionalParticleAffector.inl"

#endif /* _OSGCONDITIONALPARTICLEAFFECTOR_H_ */
