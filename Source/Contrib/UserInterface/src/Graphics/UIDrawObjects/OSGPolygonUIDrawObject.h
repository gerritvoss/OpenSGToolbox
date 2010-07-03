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

#ifndef _OSGPOLYGONUIDRAWOBJECT_H_
#define _OSGPOLYGONUIDRAWOBJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPolygonUIDrawObjectBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PolygonUIDrawObject class. See \ref
           PageContribUserInterfacePolygonUIDrawObject for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING PolygonUIDrawObject : public PolygonUIDrawObjectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PolygonUIDrawObjectBase Inherited;
    typedef PolygonUIDrawObject     Self;

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

	virtual void draw(Graphics* const Graphics, Real32 Opacity = 1.0f) const;

    virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PolygonUIDrawObjectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PolygonUIDrawObject(void);
    PolygonUIDrawObject(const PolygonUIDrawObject &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PolygonUIDrawObject(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PolygonUIDrawObjectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PolygonUIDrawObject &source);
};

typedef PolygonUIDrawObject *PolygonUIDrawObjectP;

OSG_END_NAMESPACE

#include "OSGPolygonUIDrawObjectBase.inl"
#include "OSGPolygonUIDrawObject.inl"

#endif /* _OSGPOLYGONUIDRAWOBJECT_H_ */
