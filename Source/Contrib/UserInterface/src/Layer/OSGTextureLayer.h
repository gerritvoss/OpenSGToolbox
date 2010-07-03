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

#ifndef _OSGTEXTURELAYER_H_
#define _OSGTEXTURELAYER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextureLayerBase.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureTransformChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextureLayer class. See \ref
           PageContribUserInterfaceTextureLayer for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TextureLayer : public TextureLayerBase
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

    typedef TextureLayerBase Inherited;
    typedef TextureLayer     Self;

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
	virtual void draw(Graphics* const TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextureLayerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureLayer(void);
    TextureLayer(const TextureLayer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureLayer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextureLayerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureLayer &source);
};

typedef TextureLayer *TextureLayerP;

OSG_END_NAMESPACE

#include "OSGTextureLayerBase.inl"
#include "OSGTextureLayer.inl"

#endif /* _OSGTEXTURELAYER_H_ */
