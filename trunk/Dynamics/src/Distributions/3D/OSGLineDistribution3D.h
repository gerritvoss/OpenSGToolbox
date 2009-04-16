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

#ifndef _OSGLINEDISTRIBUTION3D_H_
#define _OSGLINEDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicsDef.h"

#include "OSGLineDistribution3DBase.h"
#include <OpenSG/OSGVecFieldDataType.h>

OSG_BEGIN_NAMESPACE

#define OSG_LINE3D_DIST_OUTPUTPARAMETERS (1, \
    (\
      ("RandomPoint", Pnt3f) \
    ))

//      ("RandomPoint", FieldDataTraits<Pnt3f>::getType()) \

#define OSG_LINE3D_DIST_INPUTPARAMETERS (0, ())

/*#define OSG_LINE3D_DIST_INPUTPARAMETERS (3, \
    (\
      ("Bla1", FieldDataTraits<Pnt3f>::getType()), \
      ("Bla2", FieldDataTraits<Pnt2f>::getType()), \
      ("Bla3", FieldDataTraits<Real32>::getType()) \
    ))*/

class OSG_DYNAMICSLIB_DLLMAPPING LineDistribution3D : public LineDistribution3DBase
{
  private:

    typedef LineDistribution3DBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    typedef FunctionIOData<Pnt3f> Output0DataType;

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

    // Variables should all be in LineDistribution3DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LineDistribution3D(void);
    LineDistribution3D(const LineDistribution3D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LineDistribution3D(void); 

    /*! \}                                                                 */
    
    Pnt3f generate(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LineDistribution3DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LineDistribution3D &source);
};

typedef LineDistribution3D *LineDistribution3DP;

OSG_END_NAMESPACE

#include "OSGLineDistribution3DBase.inl"
#include "OSGLineDistribution3D.inl"

#define OSGLINEDISTRIBUTION3D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLINEDISTRIBUTION3D_H_ */
