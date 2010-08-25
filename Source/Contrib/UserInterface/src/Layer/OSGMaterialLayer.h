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

#ifndef _OSGMATERIALLAYER_H_
#define _OSGMATERIALLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMaterialLayerBase.h"
#include "OSGMaterial.h"

OSG_BEGIN_NAMESPACE

/*! \brief MaterialLayer class. See \ref
           PageContribUserInterfaceMaterialLayer for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MaterialLayer : public MaterialLayerBase
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

    typedef MaterialLayerBase Inherited;
    typedef MaterialLayer     Self;

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

    // Variables should all be in MaterialLayerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialLayer(void);
    MaterialLayer(const MaterialLayer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialLayer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MaterialLayerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialLayer &source);
};

typedef MaterialLayer *MaterialLayerP;

OSG_END_NAMESPACE

#include "OSGMaterialLayerBase.inl"
#include "OSGMaterialLayer.inl"

#endif /* _OSGMATERIALLAYER_H_ */
