/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
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

#ifndef _OSGSHADERTEXTUREFILTER_H_
#define _OSGSHADERTEXTUREFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGChunkMaterialFields.h>

#include "OSGShaderTextureFilterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderTextureFilter class. See \ref 
           PageImageProcessingShaderTextureFilter for a description.
*/

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING ShaderTextureFilter : public ShaderTextureFilterBase
{
  private:

    typedef ShaderTextureFilterBase Inherited;

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
    virtual bool isSource(void) const;
    virtual bool isSink(void) const;
    
    virtual TextureChunkPtr pullTexture(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:
    virtual void internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize);

    FBOViewportPtr createDefaultFBO(void);
    SHLChunkPtr createDefaultShader(void);
    SHLParameterChunkPtr createDefaultParameters(void);

    void onCreate(const ShaderTextureFilter *source = NULL);
    void onDestroy(void);

    // Variables should all be in ShaderTextureFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderTextureFilter(void);
    ShaderTextureFilter(const ShaderTextureFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderTextureFilter(void); 

    /*! \}                                                                 */

    ChunkMaterialPtr _DefaultMat;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShaderTextureFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShaderTextureFilter &source);
};

typedef ShaderTextureFilter *ShaderTextureFilterP;

OSG_END_NAMESPACE

#include "OSGShaderTextureFilterBase.inl"
#include "OSGShaderTextureFilter.inl"

#endif /* _OSGSHADERTEXTUREFILTER_H_ */
