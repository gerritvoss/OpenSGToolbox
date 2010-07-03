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

#ifndef _OSGPATTERNLAYER_H_
#define _OSGPATTERNLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPatternLayerBase.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureTransformChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief PatternLayer class. See \ref
           PageContribUserInterfacePatternLayer for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING PatternLayer : public PatternLayerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum PatternRepeat
    {
        PATTERN_REPEAT_BY_POINT = 0,
        PATTERN_REPEAT_ABSOLUTE = 1
    };

    typedef PatternLayerBase Inherited;
    typedef PatternLayer     Self;

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

	Vec2f getCorrectedPatternSize(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PatternLayerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PatternLayer(void);
    PatternLayer(const PatternLayer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PatternLayer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PatternLayerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PatternLayer &source);
};

typedef PatternLayer *PatternLayerP;

OSG_END_NAMESPACE

#include "OSGPatternLayerBase.inl"
#include "OSGPatternLayer.inl"

#endif /* _OSGPATTERNLAYER_H_ */
