/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, David Oluwatimi                                  *
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

#ifndef _OSGAGESIZEPARTICLEAFFECTOR_H_
#define _OSGAGESIZEPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGAgeSizeParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AgeSizeParticleAffector class. See \ref 
           PageParticleSystemAgeSizeParticleAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING AgeSizeParticleAffector : public AgeSizeParticleAffectorBase
{
  private:

    typedef AgeSizeParticleAffectorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

    // Variables should all be in AgeSizeParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AgeSizeParticleAffector(void);
    AgeSizeParticleAffector(const AgeSizeParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AgeSizeParticleAffector(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AgeSizeParticleAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AgeSizeParticleAffector &source);
};

typedef AgeSizeParticleAffector *AgeSizeParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGAgeSizeParticleAffectorBase.inl"
#include "OSGAgeSizeParticleAffector.inl"

#define OSGAGESIZEPARTICLEAFFECTOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGAGESIZEPARTICLEAFFECTOR_H_ */
