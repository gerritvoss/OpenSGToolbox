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

#ifndef _OSGIMAGECOMPONENT_H_
#define _OSGIMAGECOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGImageComponentBase.h"
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureChunk.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING ImageComponent : public ImageComponentBase
{
  private:

    typedef ImageComponentBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	enum Scale{SCALE_NONE=0, SCALE_STRETCH, SCALE_MIN_AXIS, SCALE_MAX_AXIS, SCALE_ABSOLUTE};

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

	void setImage(ImagePtr Image);
	void setImage(const char *fileName, const char *mimeType = 0);
	
	void setRolloverImage(ImagePtr Image);
	void setRolloverImage(const char *fileName, const char *mimeType = 0);

	void setDisabledImage(ImagePtr Image);
	void setDisabledImage(const char *fileName, const char *mimeType = 0);
	
	void setFocusedImage(ImagePtr Image);
	void setFocusedImage(const char *fileName, const char *mimeType = 0);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ImageComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ImageComponent(void);
    ImageComponent(const ImageComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ImageComponent(void); 

    /*! \}                                                                 */
	virtual void drawInternal(const GraphicsPtr Graphics) const;
    virtual TextureChunkPtr getDrawnTexture(void) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ImageComponentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ImageComponent &source);
};

typedef ImageComponent *ImageComponentP;

OSG_END_NAMESPACE

#include "OSGImageComponentBase.inl"
#include "OSGImageComponent.inl"

#define OSGIMAGECOMPONENT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGIMAGECOMPONENT_H_ */
