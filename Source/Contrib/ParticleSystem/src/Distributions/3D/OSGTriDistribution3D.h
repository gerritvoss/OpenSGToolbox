/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
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

#ifndef _OSGTRIDISTRIBUTION3D_H_
#define _OSGTRIDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleSystemDef.h"

#include "OSGTriDistribution3DBase.h"
#include <OpenSG/OSGVecFieldDataType.h>

OSG_BEGIN_NAMESPACE

class OSG_PARTICLESYSTEMLIB_DLLMAPPING TriDistribution3D : public TriDistribution3DBase
{
  private:

    typedef TriDistribution3DBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    enum SurfaceOrEdge {SURFACE=0, EDGE=1};

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
    virtual Vec3f generate(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TriDistribution3DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TriDistribution3D(void);
    TriDistribution3D(const TriDistribution3D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TriDistribution3D(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TriDistribution3DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TriDistribution3D &source);
};

typedef TriDistribution3D *TriDistribution3DP;

OSG_END_NAMESPACE

#include "OSGTriDistribution3DBase.inl"
#include "OSGTriDistribution3D.inl"

#endif /* _OSGTRIDISTRIBUTION3D_H_ */
