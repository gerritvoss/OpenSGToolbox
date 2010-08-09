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

#ifndef _OSGTABLECOLUMNMODELEVENTDETAILS_H_
#define _OSGTABLECOLUMNMODELEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableColumnModelEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableColumnModelEventDetails class. See \ref
           PageContribUserInterfaceTableColumnModelEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableColumnModelEventDetails : public TableColumnModelEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableColumnModelEventDetailsBase Inherited;
    typedef TableColumnModelEventDetails     Self;

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

    static  TableColumnModelEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                          Time TimeStamp,
                                                          UInt32 FromIndex,
                                                          UInt32 ToIndex); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableColumnModelEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableColumnModelEventDetails(void);
    TableColumnModelEventDetails(const TableColumnModelEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableColumnModelEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableColumnModelEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableColumnModelEventDetails &source);
};

typedef TableColumnModelEventDetails *TableColumnModelEventDetailsP;

OSG_END_NAMESPACE

#include "OSGTableColumnModelEventDetailsBase.inl"
#include "OSGTableColumnModelEventDetails.inl"

#endif /* _OSGTABLECOLUMNMODELEVENTDETAILS_H_ */
