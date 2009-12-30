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

#ifndef _OSGTEXTURESOURCETEXTUREFILTER_H_
#define _OSGTEXTURESOURCETEXTUREFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGTextureSourceTextureFilterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextureSourceTextureFilter class. See \ref 
           PageImageProcessingTextureSourceTextureFilter for a description.
*/

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING TextureSourceTextureFilter : public TextureSourceTextureFilterBase
{
  private:

    typedef TextureSourceTextureFilterBase Inherited;

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
    
    virtual TextureChunkPtr pullTexture(UInt8 OutputSlot = 0) const;

    //Output Slots
    virtual Int32 getNumOutputSlots(void) const;

    //Description
    virtual std::string getDescription(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:
    virtual void internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize);

    virtual TextureFilterOutputSlot* editOutputSlot(UInt32 OutputSlot = 0); 

    // Variables should all be in TextureSourceTextureFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureSourceTextureFilter(void);
    TextureSourceTextureFilter(const TextureSourceTextureFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureSourceTextureFilter(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TextureSourceTextureFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TextureSourceTextureFilter &source);
};

typedef TextureSourceTextureFilter *TextureSourceTextureFilterP;

OSG_END_NAMESPACE

#include "OSGTextureSourceTextureFilterBase.inl"
#include "OSGTextureSourceTextureFilter.inl"

#endif /* _OSGTEXTURESOURCETEXTUREFILTER_H_ */
