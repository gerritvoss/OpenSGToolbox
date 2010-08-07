/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGImageComponentBase.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGImageFileHandler.h"

OSG_BEGIN_NAMESPACE

/*! \brief ImageComponent class. See \ref
           PageContribUserInterfaceImageComponent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ImageComponent : public ImageComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum Scale
    {
        SCALE_NONE     = 0,
        SCALE_STRETCH  = 1,
        SCALE_MIN_AXIS = 2,
        SCALE_MAX_AXIS = 3,
        SCALE_ABSOLUTE = 4
    };

    typedef ImageComponentBase Inherited;
    typedef ImageComponent     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	void setImage(Image* const Image);
	void setImages(Image* const  Image);
	void setImages(const BoostPath& fileName, const char *mimeType = 0);
	void setImage(const char *fileName, const char *mimeType = 0);
	
	void setRolloverImage(Image* const Image);
	void setRolloverImage(const char *fileName, const char *mimeType = 0);

	void setDisabledImage(Image* const Image);
	void setDisabledImage(const char *fileName, const char *mimeType = 0);
	
	void setFocusedImage(Image* const Image);
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;
    virtual TextureBaseChunk* getDrawnTexture(void) const;
    static TextureObjChunkTransitPtr createTexture(Image* Image);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ImageComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ImageComponent &source);
};

typedef ImageComponent *ImageComponentP;

OSG_END_NAMESPACE

#include "OSGImageComponentBase.inl"
#include "OSGImageComponent.inl"

#endif /* _OSGIMAGECOMPONENT_H_ */
