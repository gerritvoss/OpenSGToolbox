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

#ifndef _OSGDISCUIDRAWOBJECT_H_
#define _OSGDISCUIDRAWOBJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDiscUIDrawObjectBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DiscUIDrawObject class. See \ref
           PageContribUserInterfaceDiscUIDrawObject for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DiscUIDrawObject : public DiscUIDrawObjectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DiscUIDrawObjectBase Inherited;
    typedef DiscUIDrawObject     Self;

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

    // Variables should all be in DiscUIDrawObjectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DiscUIDrawObject(void);
    DiscUIDrawObject(const DiscUIDrawObject &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DiscUIDrawObject(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DiscUIDrawObjectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DiscUIDrawObject &source);
};

typedef DiscUIDrawObject *DiscUIDrawObjectP;

OSG_END_NAMESPACE

#include "OSGDiscUIDrawObjectBase.inl"
#include "OSGDiscUIDrawObject.inl"

#endif /* _OSGDISCUIDRAWOBJECT_H_ */
