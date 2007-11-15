/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGQUADDISTRIBUTION2D_H_
#define _OSGQUADDISTRIBUTION2D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicsDef.h"

#include "OSGQuadDistribution2DBase.h"

OSG_BEGIN_NAMESPACE

#define OSG_QUAD2D_DIST_OUTPUTPARAMETERS (1, \
    (\
      ("RandomPoint", Pnt2f) \
    ))

#define OSG_QUAD2D_DIST_INPUTPARAMETERS (0, ())

class OSG_DYNAMICSLIB_DLLMAPPING QuadDistribution2D : public QuadDistribution2DBase
{
  private:

    typedef QuadDistribution2DBase Inherited;

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
    virtual FunctionIOTypeVector getOutputTypes(FunctionIOTypeVector& InputTypes) const;
    virtual FunctionIOTypeVector getInputTypes(FunctionIOTypeVector& OutputTypes) const;
    virtual FunctionIOParameterVector evaluate(FunctionIOParameterVector& InputParameters);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in QuadDistribution2DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    QuadDistribution2D(void);
    QuadDistribution2D(const QuadDistribution2D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~QuadDistribution2D(void); 

    /*! \}                                                                 */
    virtual Pnt2f generate(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class QuadDistribution2DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const QuadDistribution2D &source);
};

typedef QuadDistribution2D *QuadDistribution2DP;

OSG_END_NAMESPACE

#include "OSGQuadDistribution2DBase.inl"
#include "OSGQuadDistribution2D.inl"

#define OSGQUADDISTRIBUTION2D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGQUADDISTRIBUTION2D_H_ */
