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

#ifndef _OSGFOCUSEVENTDETAILS_H_
#define _OSGFOCUSEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFocusEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FocusEventDetails class. See \ref
           PageContribUserInterfaceFocusEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING FocusEventDetails : public FocusEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FocusEventDetailsBase Inherited;
    typedef FocusEventDetails     Self;

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

    static  FocusEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                               Time TimeStamp,
                                               bool Temporary,
                                               Component* const Opposite); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FocusEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FocusEventDetails(void);
    FocusEventDetails(const FocusEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FocusEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FocusEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FocusEventDetails &source);
};

typedef FocusEventDetails *FocusEventDetailsP;

OSG_END_NAMESPACE

#include "OSGComponent.h"

#include "OSGFocusEventDetailsBase.inl"
#include "OSGFocusEventDetails.inl"

#endif /* _OSGFOCUSEVENTDETAILS_H_ */
