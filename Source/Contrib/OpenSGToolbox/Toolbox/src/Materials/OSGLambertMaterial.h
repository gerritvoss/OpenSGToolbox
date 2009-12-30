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

#ifndef _OSGLAMBERTMATERIAL_H_
#define _OSGLAMBERTMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGLambertMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief LambertMaterial class. See \ref 
           PageToolboxLambertMaterial for a description.
*/

class OSG_TOOLBOXLIB_DLLMAPPING LambertMaterial : public LambertMaterialBase
{
  private:

    typedef LambertMaterialBase Inherited;

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
    virtual bool 	isTransparent (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in LambertMaterialBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LambertMaterial(void);
    LambertMaterial(const LambertMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LambertMaterial(void); 

    /*! \}                                                                 */
    void onCreate(const LambertMaterial *source = NULL);
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
    virtual bool shouldRecreateShaderCode(void) const;

    virtual std::string generateVertexCode(void);
    virtual std::string generateFragmentCode(void);

    virtual void       rebuildState  (void);

    
    /*==========================  PRIVATE  ================================*/
  private:
      enum   ShaderParamBits{VERTEXCOLORING_SHADERPARAM               =1,
                              COLORTEXTURE_SHADERPARAM                =2,
                              TRANSPARENCYTEXTURE_SHADERPARAM         =4,
                              AMBIENTCOLORTEXTURE_SHADERPARAM         =8,
                              INCANDESCENCETEXTURE_SHADERPARAM        =16,
                              NORMALMAPTEXTURE_SHADERPARAM            =32,
                              BUMPDEPTHTEXTURE_SHADERPARAM            =64,
                              DIFFUSETEXTURE_SHADERPARAM              =128,
                              IS_TRANSPARENT_SHADERPARAM              =256};
    UInt32 _ShaderParameters;
    UInt8  _ShaderNumLights;

    friend class FieldContainer;
    friend class LambertMaterialBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LambertMaterial &source);
};

typedef LambertMaterial *LambertMaterialP;

OSG_END_NAMESPACE

#include "OSGLambertMaterialBase.inl"
#include "OSGLambertMaterial.inl"

#endif /* _OSGLAMBERTMATERIAL_H_ */
