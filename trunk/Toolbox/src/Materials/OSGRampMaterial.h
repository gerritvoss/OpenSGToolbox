/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
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

#ifndef _OSGRAMPMATERIAL_H_
#define _OSGRAMPMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGRampMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief RampMaterial class. See \ref 
           PageToolboxRampMaterial for a description.
*/

class OSG_TOOLBOXLIB_DLLMAPPING RampMaterial : public RampMaterialBase
{
  private:

    typedef RampMaterialBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

      enum RampSource {RAMP_SOURCE_FACING_ANGLE = 0,RAMP_SOURCE_LIGHT_ANGLE = 1,RAMP_SOURCE_BRIGHTNESS = 2};
      enum RampInterpolation {RAMP_INTERPOLATION_STEP = 1,RAMP_INTERPOLATION_LINEAR = 0,RAMP_INTERPOLATION_SMOOTH = 3,RAMP_INTERPOLATION_SPLINE = 2};

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
    virtual bool 	isTransparent (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in RampMaterialBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RampMaterial(void);
    RampMaterial(const RampMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RampMaterial(void); 

    /*! \}                                                                 */
    void onCreate(const RampMaterial *source = NULL);
    void onDestroy(void);

    virtual void updateShaderCode(void);
    virtual void createShaderParameters(void);
    virtual void internalCreateShaderParameters(void);
    virtual void updateShaderParameters(void);
    virtual void internalUpdateShaderParameters(UInt8& NumTextures, UInt8& ParamIndex);
    virtual void attachChunks(void);
    virtual void internalAttachChunks(void);

    virtual bool shouldRecreateChunks(BitVector FieldMask) const;
    virtual bool shouldUpdateParameters(BitVector FieldMask) const;

    virtual std::string generateVertexCode(void) const;
    virtual std::string generateFragmentCode(void) const;
    void generateRampFunc(const MFUInt8 &Interpolators, const TypeBase& Type, const std::string& FuncNamePrefix, std::string& FuncName, std::string& RampCode) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class RampMaterialBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const RampMaterial &source);
};

typedef RampMaterial *RampMaterialP;

OSG_END_NAMESPACE

#include "OSGRampMaterialBase.inl"
#include "OSGRampMaterial.inl"

#endif /* _OSGRAMPMATERIAL_H_ */
