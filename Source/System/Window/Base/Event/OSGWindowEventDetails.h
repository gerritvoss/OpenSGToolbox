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

#ifndef _OSGWINDOWEVENTDETAILS_H_
#define _OSGWINDOWEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGWindowEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief WindowEventDetails class. See \ref
           PageSystemWindowEventDetails for a description.
*/

class OSG_SYSTEM_DLLMAPPING WindowEventDetails : public WindowEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef WindowEventDetailsBase Inherited;
    typedef WindowEventDetails     Self;

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

    static  WindowEventDetailsTransitPtr      create(FieldContainer* const Source,
                                                     Time TimeStamp); 

    static  WindowEventDetailsTransitPtr      create(WindowEventDetails* const Details,
                                                     FieldContainer*     const NewSource); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in WindowEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    WindowEventDetails(void);
    WindowEventDetails(const WindowEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~WindowEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class WindowEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const WindowEventDetails &source);
};

typedef WindowEventDetails *WindowEventDetailsP;

OSG_END_NAMESPACE

#include "OSGWindowEventDetailsBase.inl"
#include "OSGWindowEventDetails.inl"

#endif /* _OSGWINDOWEVENTDETAILS_H_ */
