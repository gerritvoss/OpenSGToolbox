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

#ifndef _OSGUNDOABLEEDITEVENTDETAILS_H_
#define _OSGUNDOABLEEDITEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUndoableEditEventDetailsBase.h"
#include "OSGUndoableEdit.h"

OSG_BEGIN_NAMESPACE

/*! \brief UndoableEditEventDetails class. See \ref
           PageContribUserInterfaceUndoableEditEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UndoableEditEventDetails : public UndoableEditEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UndoableEditEventDetailsBase Inherited;
    typedef UndoableEditEventDetails     Self;

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

    static  UndoableEditEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                      Time TimeStamp,
                                                      UndoableEditPtr TheUndoableEdit); 

    const UndoableEditPtr getUndoableEdit(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UndoableEditEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UndoableEditEventDetails(void);
    UndoableEditEventDetails(const UndoableEditEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UndoableEditEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    UndoableEditPtr _UndoableEdit;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UndoableEditEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UndoableEditEventDetails &source);
};

typedef UndoableEditEventDetails *UndoableEditEventDetailsP;

OSG_END_NAMESPACE

#include "OSGUndoableEditEventDetailsBase.inl"
#include "OSGUndoableEditEventDetails.inl"

#endif /* _OSGUNDOABLEEDITEVENTDETAILS_H_ */
