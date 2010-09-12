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

#ifndef _OSGMOUSEWHEELEVENTDETAILS_H_
#define _OSGMOUSEWHEELEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMouseWheelEventDetailsBase.h"
#include "OSGViewport.h"            // FieldContainer type
#include "OSGInputSettings.h"

OSG_BEGIN_NAMESPACE

/*! \brief MouseWheelEventDetails class. See \ref
           PageSystemMouseWheelEventDetails for a description.
*/

class OSG_SYSTEM_DLLMAPPING MouseWheelEventDetails : public MouseWheelEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum ScrollType {
        UNIT_SCROLL  = 1,
        BLOCK_SCROLL = 2
    };

    enum ScrollOrientation {
        SCROLL_ORIENTATION_VERTICAL    = 1,
        SCROLL_ORIENTATION_HORIZONTAL  = 2
    };

    typedef MouseWheelEventDetailsBase Inherited;
    typedef MouseWheelEventDetails     Self;

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

    Int32 getScrollAmount(void) const;
    Int32 getUnitsToScroll(void) const;

    static  MouseWheelEventDetailsTransitPtr create(FieldContainer* const Source,
                                                    Time TimeStamp,
                                                    Int32 WheelRotation,
                                                    UInt8 TheScrollType,
                                                    UInt8 ScrollOrientation,
                                                    Pnt2f Location,
                                                    Viewport* const TheViewport); 

    static  MouseWheelEventDetailsTransitPtr create(MouseWheelEventDetails* const Details,
                                                    FieldContainer*         const NewSource);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MouseWheelEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MouseWheelEventDetails(void);
    MouseWheelEventDetails(const MouseWheelEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MouseWheelEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MouseWheelEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MouseWheelEventDetails &source);
};

typedef MouseWheelEventDetails *MouseWheelEventDetailsP;

OSG_END_NAMESPACE

#include "OSGMouseWheelEventDetailsBase.inl"
#include "OSGMouseWheelEventDetails.inl"

#endif /* _OSGMOUSEWHEELEVENTDETAILS_H_ */
