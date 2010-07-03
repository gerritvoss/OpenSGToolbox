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

#ifndef _OSGTOOLTIP_H_
#define _OSGTOOLTIP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGToolTipBase.h"
#include "OSGUIFont.h"

OSG_BEGIN_NAMESPACE

/*! \brief ToolTip class. See \ref
           PageContribUserInterfaceToolTip for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ToolTip : public ToolTipBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ToolTipBase Inherited;
    typedef ToolTip     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ToolTipBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ToolTip(void);
    ToolTip(const ToolTip &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ToolTip(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawInternal(Graphics* const TheGraphics, Real32 Opacity = 1.0f) const;

    virtual Vec2f calculatePreferredSize(void) const;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ToolTipBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ToolTip &source);
};

typedef ToolTip *ToolTipP;

OSG_END_NAMESPACE

#include "OSGToolTipBase.inl"
#include "OSGToolTip.inl"

#endif /* _OSGTOOLTIP_H_ */
