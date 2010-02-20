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

#ifndef _OSGLISTDATAEVENT_H_
#define _OSGLISTDATAEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGListDataEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ListDataEvent class. See \ref
           PageContribUserInterfaceListDataEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ListDataEvent : public ListDataEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ListDataEventBase Inherited;
    typedef ListDataEvent     Self;

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

    static  ListDataEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                  Time TimeStamp,
                                                  Int32 Index0,
                                                  Int32 Index1); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ListDataEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ListDataEvent(void);
    ListDataEvent(const ListDataEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ListDataEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ListDataEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ListDataEvent &source);
};

typedef ListDataEvent *ListDataEventP;

OSG_END_NAMESPACE

#include "OSGListDataEventBase.inl"
#include "OSGListDataEvent.inl"

#endif /* _OSGLISTDATAEVENT_H_ */
