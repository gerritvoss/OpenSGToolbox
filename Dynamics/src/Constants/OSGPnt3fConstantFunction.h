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

#ifndef _OSGPNT3FCONSTANTFUNCTION_H_
#define _OSGPNT3FCONSTANTFUNCTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPnt3fConstantFunctionBase.h"

OSG_BEGIN_NAMESPACE


#define OSG_PNT3F_CONSTANT_OUTPUTPARAMETERS (1, \
    (\
      ("Value", Pnt3f) \
    ))


#define OSG_PNT3F_CONSTANT_INPUTPARAMETERS (0, ())
/*! \brief Pnt3fConstantFunction class. See \ref 
           PageDynamicsPnt3fConstantFunction for a description.
*/

class OSG_DYNAMICSLIB_DLLMAPPING Pnt3fConstantFunction : public Pnt3fConstantFunctionBase
{
  private:

    typedef Pnt3fConstantFunctionBase Inherited;

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
    virtual FunctionIOTypeVector getOutputTypes(FunctionIOTypeVector& InputTypes) const;
    virtual FunctionIOTypeVector getInputTypes(FunctionIOTypeVector& OutputTypes) const;
    virtual FunctionIOParameterVector evaluate(FunctionIOParameterVector& InputParameters);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in Pnt3fConstantFunctionBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Pnt3fConstantFunction(void);
    Pnt3fConstantFunction(const Pnt3fConstantFunction &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Pnt3fConstantFunction(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class Pnt3fConstantFunctionBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Pnt3fConstantFunction &source);
};

typedef Pnt3fConstantFunction *Pnt3fConstantFunctionP;

OSG_END_NAMESPACE

#include "OSGPnt3fConstantFunctionBase.inl"
#include "OSGPnt3fConstantFunction.inl"

#define OSGPNT3FCONSTANTFUNCTION_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPNT3FCONSTANTFUNCTION_H_ */
