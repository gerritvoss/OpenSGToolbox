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

#ifndef _OSGFBOSOURCETEXTUREFILTER_H_
#define _OSGFBOSOURCETEXTUREFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGFBOSourceTextureFilterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FBOSourceTextureFilter class. See \ref 
           PageImageProcessingFBOSourceTextureFilter for a description.
*/

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING FBOSourceTextureFilter : public FBOSourceTextureFilterBase
{
  private:

    typedef FBOSourceTextureFilterBase Inherited;

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
    
    virtual TextureChunkPtr pullTexture(UInt8 OutputSlot) const;

    //Output Slots
    virtual Int32 getNumOutputSlots(void) const;

    //Description
    virtual std::string getDescription(void) const;

    virtual bool isDirty(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:
    virtual void internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize);

    virtual TextureFilterOutputSlot* editOutputSlot(UInt32 OutputSlot = 0); 

    void updateOuputSlots(void);

    void detachAllOutputSlots(void);

    // Variables should all be in FBOSourceTextureFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FBOSourceTextureFilter(void);
    FBOSourceTextureFilter(const FBOSourceTextureFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FBOSourceTextureFilter(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FBOSourceTextureFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FBOSourceTextureFilter &source);
};

typedef FBOSourceTextureFilter *FBOSourceTextureFilterP;

OSG_END_NAMESPACE

#include "OSGFBOSourceTextureFilterBase.inl"
#include "OSGFBOSourceTextureFilter.inl"

#endif /* _OSGFBOSOURCETEXTUREFILTER_H_ */
