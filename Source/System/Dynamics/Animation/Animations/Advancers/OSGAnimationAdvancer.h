/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
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

#ifndef _OSGANIMATIONADVANCER_H_
#define _OSGANIMATIONADVANCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGAnimationAdvancerBase.h"

OSG_BEGIN_NAMESPACE

class OSG_ANIMATIONLIB_DLLMAPPING AnimationAdvancer : public AnimationAdvancerBase
{
  private:

    typedef AnimationAdvancerBase Inherited;

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

    virtual osg::Real32 getValue(void) const = 0;
    virtual osg::Real32 getPrevValue(void) const = 0;

    virtual void start(void);

    virtual void pause(void);
    virtual void unpause(void);
    virtual void pauseToggle(void);
    virtual bool isPaused(void);
    virtual bool isRunning(void);
    
    virtual void stop(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AnimationAdvancerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimationAdvancer(void);
    AnimationAdvancer(const AnimationAdvancer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimationAdvancer(void); 

    /*! \}                                                                 */

   bool _IsPaused;
   bool _IsRunning;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AnimationAdvancerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AnimationAdvancer &source);
};

typedef AnimationAdvancer *AnimationAdvancerP;

OSG_END_NAMESPACE

#include "OSGAnimationAdvancerBase.inl"
#include "OSGAnimationAdvancer.inl"

#define OSGANIMATIONADVANCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGANIMATIONADVANCER_H_ */


