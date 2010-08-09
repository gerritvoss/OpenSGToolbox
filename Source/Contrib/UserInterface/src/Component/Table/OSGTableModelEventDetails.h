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

#ifndef _OSGTABLEMODELEVENTDETAILS_H_
#define _OSGTABLEMODELEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableModelEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableModelEventDetails class. See \ref
           PageContribUserInterfaceTableModelEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableModelEventDetails : public TableModelEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableModelEventDetailsBase Inherited;
    typedef TableModelEventDetails     Self;

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

    static  TableModelEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                    Time TimeStamp,
                                                    UInt32 FirstColumn,
                                                    UInt32 LastColumn,
                                                    UInt32 FirstRow,
                                                    UInt32 LastRow); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableModelEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableModelEventDetails(void);
    TableModelEventDetails(const TableModelEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableModelEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableModelEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableModelEventDetails &source);
};

typedef TableModelEventDetails *TableModelEventDetailsP;

OSG_END_NAMESPACE

#include "OSGTableModelEventDetailsBase.inl"
#include "OSGTableModelEventDetails.inl"

#endif /* _OSGTABLEMODELEVENTDETAILS_H_ */
