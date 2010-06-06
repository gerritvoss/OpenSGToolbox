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

#ifndef _OSGELAPSEDTIMEANIMATIONADVANCER_H_
#define _OSGELAPSEDTIMEANIMATIONADVANCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGElapsedTimeAnimationAdvancerBase.h"

OSG_BEGIN_NAMESPACE

class OSG_ANIMATIONLIB_DLLMAPPING ElapsedTimeAnimationAdvancer : public ElapsedTimeAnimationAdvancerBase
{
  private:

    typedef ElapsedTimeAnimationAdvancerBase Inherited;

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
    
    virtual osg::Real32 getValue(void) const;
    virtual osg::Real32 getPrevValue(void) const;
    
    virtual void start(void);
    
    virtual void reset(void);
    
    virtual void stop(void);
    
    virtual void update(const Real32& elps);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ElapsedTimeAnimationAdvancerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ElapsedTimeAnimationAdvancer(void);
    ElapsedTimeAnimationAdvancer(const ElapsedTimeAnimationAdvancer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ElapsedTimeAnimationAdvancer(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ElapsedTimeAnimationAdvancerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ElapsedTimeAnimationAdvancer &source);
};

typedef ElapsedTimeAnimationAdvancer *ElapsedTimeAnimationAdvancerP;

OSG_END_NAMESPACE

#include "OSGElapsedTimeAnimationAdvancerBase.inl"
#include "OSGElapsedTimeAnimationAdvancer.inl"

#define OSGELAPSEDTIMEANIMATIONADVANCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGELAPSEDTIMEANIMATIONADVANCER_H_ */


