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

#ifndef _OSGGLASSLAYER_H_
#define _OSGGLASSLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGlassLayerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GlassLayer class. See \ref
           PageContribUserInterfaceGlassLayer for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING GlassLayer : public GlassLayerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GlassLayerBase Inherited;
    typedef GlassLayer     Self;

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

    // Variables should all be in GlassLayerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GlassLayer(void);
    GlassLayer(const GlassLayer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GlassLayer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    std::vector<Pnt2f> _Segments;

    void updateSegments(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GlassLayerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GlassLayer &source);
};

typedef GlassLayer *GlassLayerP;

OSG_END_NAMESPACE

#include "OSGGlassLayerBase.inl"
#include "OSGGlassLayer.inl"

#endif /* _OSGGLASSLAYER_H_ */
