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

#ifndef _OSGCOMPONENTMENUITEM_H_
#define _OSGCOMPONENTMENUITEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComponentMenuItemBase.h"
#include "OSGMenuFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComponentMenuItem class. See \ref
           PageContribUserInterfaceComponentMenuItem for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ComponentMenuItem : public ComponentMenuItemBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComponentMenuItemBase Inherited;
    typedef ComponentMenuItem     Self;

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

	Vec2f getContentRequestedSize(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ComponentMenuItemBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComponentMenuItem(void);
    ComponentMenuItem(const ComponentMenuItem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComponentMenuItem(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;

	void updateComponentBounds(void);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComponentMenuItemBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComponentMenuItem &source);
};

typedef ComponentMenuItem *ComponentMenuItemP;

OSG_END_NAMESPACE

#include "OSGMenu.h"
#include "OSGPopupMenu.h"

#include "OSGComponentMenuItemBase.inl"
#include "OSGComponentMenuItem.inl"

#endif /* _OSGCOMPONENTMENUITEM_H_ */
