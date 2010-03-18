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

#ifndef _OSGTABLEMODELEVENT_H_
#define _OSGTABLEMODELEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableModelEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableModelEvent class. See \ref
           PageContribUserInterfaceTableModelEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableModelEvent : public TableModelEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableModelEventBase Inherited;
    typedef TableModelEvent     Self;

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

    static  TableModelEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                    Time TimeStamp,
                                                    UInt32 FirstColumn,
                                                    UInt32 LastColumn,
                                                    UInt32 FirstRow,
                                                    UInt32 LastRow); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableModelEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableModelEvent(void);
    TableModelEvent(const TableModelEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableModelEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableModelEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableModelEvent &source);
};

typedef TableModelEvent *TableModelEventP;

OSG_END_NAMESPACE

#include "OSGTableModelEventBase.inl"
#include "OSGTableModelEvent.inl"

#endif /* _OSGTABLEMODELEVENT_H_ */
