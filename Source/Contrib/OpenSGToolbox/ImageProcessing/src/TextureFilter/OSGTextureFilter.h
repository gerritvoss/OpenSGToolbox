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

#ifndef _OSGTEXTUREFILTER_H_
#define _OSGTEXTUREFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGTextureChunkFields.h>
#include <OpenSG/OSGRenderAction.h>

#include "OSGTextureFilterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextureFilter class. See \ref 
           PageImageProcessingTextureFilter for a description.
*/
class TextureFilterInputSlot;
class TextureFilterOutputSlot;

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING TextureFilter : public TextureFilterBase
{
  private:

    typedef TextureFilterBase Inherited;

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

    //Is the Filter a Source and/or Sink
    bool isSource(void) const;
    bool isSink(void) const;

    //Description
    virtual std::string getDescription(void) const = 0;

    //Pixel Radius of Filter
    //This should return the max distance, in pixels, that 
    //this filter may require for utilizing neighboring pixels
    virtual Real32 getDepPixelRadius(void) const = 0;

    //Input Slots
    virtual bool attachSource(TextureFilterPtr OutputSlotSrc, UInt8 OutputSlot, UInt8 InputSlot = 0);
    virtual bool detachSource(UInt8 InputSlot = 0);
    const TextureFilterInputSlot* getInputSlot(UInt32 InputSlot = 0) const; 
    virtual Int32 getNumInputSlots(void) const = 0;
    TextureFilterPtr getSource(UInt8 InputSlot = 0) const;

    //Output Slots
    const TextureFilterOutputSlot* getOutputSlot(UInt32 OutputSlot = 0) const; 
    virtual Int32 getNumOutputSlots(void) const = 0;

    virtual TextureChunkPtr pullTexture(UInt8 OutputSlot = 0) const;
    void update(RenderActionBase *action, const Vec2f& DrawnSize);

    
    virtual bool isDirty(void) const;
    virtual void setDirty(bool dirty);
    /*=========================  PROTECTED  ===============================*/
  protected:
    virtual bool attachOutputSlot(TextureFilterPtr Sink, UInt8 SinkInputSlot, UInt8 OuputSlot = 0);
    virtual bool detachOutputSlot(TextureFilterPtr Sink, UInt8 SinkInputSlot, UInt8 OuputSlot = 0);
    bool wouldMakeCyclic(TextureFilterPtr Src);

    virtual TextureFilterInputSlot* editInputSlot(UInt32 InputSlot = 0) = 0; 

    virtual TextureFilterOutputSlot* editOutputSlot(UInt32 OutputSlot = 0) = 0; 
    
    virtual void internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize) = 0;


    // Variables should all be in TextureFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureFilter(void);
    TextureFilter(const TextureFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureFilter(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TextureFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TextureFilter &source);
};

typedef TextureFilter *TextureFilterP;

OSG_END_NAMESPACE

#include "OSGTextureFilterBase.inl"
#include "OSGTextureFilter.inl"

#endif /* _OSGTEXTUREFILTER_H_ */
