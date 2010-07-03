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

#ifndef _OSGUIDRAWOBJECT_H_
#define _OSGUIDRAWOBJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIDrawObjectBase.h"
#include "OSGGraphics.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIDrawObject class. See \ref
           PageContribUserInterfaceUIDrawObject for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIDrawObject : public UIDrawObjectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIDrawObjectBase Inherited;
    typedef UIDrawObject     Self;

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

	virtual void draw(Graphics* const Graphics, Real32 Opacity = 1.0f) const = 0;

    virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIDrawObjectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIDrawObject(void);
    UIDrawObject(const UIDrawObject &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIDrawObject(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UIDrawObjectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIDrawObject &source);
};

typedef UIDrawObject *UIDrawObjectP;

OSG_END_NAMESPACE

#include "OSGUIDrawObjectBase.inl"
#include "OSGUIDrawObject.inl"

#endif /* _OSGUIDRAWOBJECT_H_ */
